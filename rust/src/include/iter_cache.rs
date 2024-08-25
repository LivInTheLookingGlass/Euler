use std::any::TypeId;
use std::collections::HashMap;
use std::sync::{Mutex, RwLock};
use std::sync::Once;

static INIT: Once = Once::new();
static mut CACHE_MAP: Option<RwLock<HashMap<(TypeId, TypeId), Mutex<Vec<Box<dyn std::any::Any>>>>>> = None;

pub fn cache_iterator<I, T>(iterator: I) -> impl Iterator<Item = T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + 'static
{
    return CachingIterator::new(iterator);
}

pub struct CachingIterator<I, T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + 'static
{
    inner: I,
    index: usize,
    inner_index: usize,
    type_id: (TypeId, TypeId),
}

impl<I, T> CachingIterator<I, T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + 'static
{
    pub fn new(inner: I) -> Self {
        // Initialize the global cache map if it hasn't been initialized yet
        unsafe {
            INIT.call_once(|| {
                CACHE_MAP = Some(RwLock::new(HashMap::new()));
            });
        }
        CachingIterator {
            inner,
            index: 0,
            inner_index: 0,
            type_id: (TypeId::of::<I>(), TypeId::of::<T>())
        }
    }

    // Initialize the cache for the given type
    fn initialize_cache(&self) {
        unsafe {
            let mut cache_map = CACHE_MAP.as_ref().unwrap().write().unwrap();
            cache_map.entry(self.type_id)
                .or_insert_with(|| Mutex::new(Vec::new()));
        }
    }
}

impl<I, T> Iterator for CachingIterator<I, T>
where
    I: Iterator<Item = T> + 'static,
    T: Copy + 'static
{
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        // Ensure the cache is initialized
        self.initialize_cache();
        
        // Access the global cache map
        let cache_map = unsafe { CACHE_MAP.as_ref().unwrap().read().unwrap() };

        let mut cache = cache_map
            .get(&self.type_id)
            .expect("Cache for this type should be initialized")
            .lock()
            .unwrap();
        
        if self.index < cache.len() {
            // Return the cached result
            let boxed_item = &cache[self.index];
            let result = boxed_item.downcast_ref::<T>().unwrap();
            self.index += 1;
            Some(*result)
        } else {
            // Fetch the next result from the inner iterator and cache it
            while self.inner_index < self.index {
                self.inner.next();
                self.inner_index += 1;
            }
            match self.inner.next() {
                Some(value) => {
                    cache.push(Box::new(value));
                    self.index += 1;
                    self.inner_index += 1;
                    Some(value)
                }
                None => None,
            }
        }
    }
}
