use lazy_static::lazy_static;

use std::any::{Any,TypeId};
use std::collections::HashMap;
use std::sync::{Mutex, RwLock};

type CacheVector<T> = Vec<Box<T>>;
type CacheMap<T> = HashMap<(TypeId, TypeId), Mutex<CacheVector<T>>>;
lazy_static! {
    static ref CACHE_MAP: RwLock<CacheMap<dyn Any + Send>> = RwLock::new(HashMap::new());
}

pub fn cache_iterator<I, T>(iterator: I) -> impl Iterator<Item = T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + Send + 'static
{
    return CachingIterator::new(iterator);
}

#[derive(Clone, Copy, Debug, Hash)]
pub struct CachingIterator<I, T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + Send + 'static
{
    inner: I,
    index: usize,
    inner_index: usize,
    type_id: (TypeId, TypeId),
}

impl<I, T> CachingIterator<I, T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + Send + 'static
{
    pub fn new(inner: I) -> Self {
        CachingIterator {
            inner,
            index: 0,
            inner_index: 0,
            type_id: (TypeId::of::<I>(), TypeId::of::<T>())
        }
    }

    fn initialize_cache(&self) {
        let mut cache_map = CACHE_MAP.write().unwrap();
        cache_map.entry(self.type_id)
            .or_insert_with(|| Mutex::new(Vec::new()));
    }
}

impl<I, T> Iterator for CachingIterator<I, T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + Send + 'static
{
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        self.initialize_cache();
        let cache_map = CACHE_MAP.read()
                                 .unwrap();
        let mut cache = cache_map.get(&self.type_id)
                                 .expect("Cache for this type should be initialized")
                                 .lock()
                                 .unwrap();
        
        if self.index < cache.len() {
            let boxed_item = &cache[self.index];
            let result = boxed_item.downcast_ref::<T>().unwrap();
            self.index += 1;
            return Some(*result);
        }
        while self.inner_index < self.index {
            self.inner.next();
            self.inner_index += 1;
        }
        match self.inner.next() {
            Some(value) => {
                cache.push(Box::new(value));
                self.index += 1;
                self.inner_index += 1;
                return Some(value);
            }
            None => {
                return None;
            }
        }
    }
}
