#include <stdbool.h>

#define IteratorHead \
    void * (*iterator_function)(void *it); \
    bool exhausted : 1;
    /**
     * The base struct for all iterators in this project
     * @param void *(*)(void *it) iterator_function The function to advance the iterator and return the next element
     * @param bool exhausted An indicator that tells you if the iterator is exhausted
     * @see counter for an example implementation
    **/

#define next(state) (*(state.iterator_function))(&state)
    /**
     * The macro to advance generic iterators
     * @param iterator it The iterator you wish to advance
     * @returns void * The data type returned by the specific iterator you pass in
     * @see counter for an example implementation
    **/

typedef struct {
    /**
     * The reference struct for all iterators in this project
     * @param void *(*)(void *it) iterator_function The function to advance the iterator and return the next element
     * @param bool exhausted An indicator that tells you if the iterator is exhausted
     * @param unsigned long long idx
     * @param unsigned long long stop
     * @param unsigned long long step
     * @see IteratorHead
    **/
    IteratorHead
    unsigned long long idx;
    unsigned long long stop;
    long long step;
} counter;

unsigned long long iterate_counter(counter *i)  {
    /**
     * The function to advance a counter
     * @param counter *i the counter you want to advance
     * @returns unsigned long long
    **/
    unsigned long long ret = i->idx;
    long long step = i->step;
    i->idx += step;
    if ((step > 0 && i->idx >= i->stop) || (step < 0 && i->idx <= i->stop))   {
        i->exhausted = 1;
    }
    return ret;
}

counter counter3(unsigned long long start, unsigned long long stop, long long step)  {
    return (counter) {(void * (*)(void *)) &iterate_counter, 0, start, stop, step};
}

counter counter2(unsigned long long start, unsigned long long stop)    {
    return counter3(start, stop, 1);
}

counter counter1(unsigned long long stop)  {
    return counter2(0, stop);
}
