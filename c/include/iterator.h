#ifndef _ITERATOR
#define _ITERATOR

#include <stdbool.h>

#define IteratorHead \
    void * (*iterator_function)(void *it); \
    bool exhausted : 1; \
    bool started : 1; \
    bool phase : 1;
    /**
     * The base struct for all iterators in this project
     * @iterator_function: The function to advance the iterator and return the next element
     * @exhausted: An indicator that tells you if the iterator is exhausted
     * @started: An indicator that tells you if the interator has moved at all
     * @phase: An indicator that flips every time the iterator moves
     * 
     * See counter for an example implementation
     */

#define IterationHead(it) \
    it->started = 1; \
    it->phase = !(it->phase);
    /**
     * The base macro for all iteration functions in this project
     * @it: The pointer to the iterator you are advancing
     * 
     * See counter for an example implementation
     */

#define next(state) (*(state.iterator_function))(&state)
    /**
     * The macro to advance generic iterators
     * @state: The iterator you wish to advance
     * 
     * See counter for an example implementation
     */

typedef struct {
    /**
     * The reference struct for all iterators in this project
     * @iterator_function: The function to advance the iterator and return the next element
     * @exhausted: An indicator that tells you if the iterator is exhausted
     * @idx: The current position of the counter
     * @stop: The point where the counter is exhausted
     * @step: The amount to step by each time you iterate the counter
     * 
     * See IteratorHead
     */
    IteratorHead
    unsigned long long idx;
    unsigned long long stop;
    long long step;
} counter;

unsigned long long iterate_counter(counter *i)  {
    /**
     * The function to advance a counter
     * @i the counter you want to advance
     * 
     * Returns the next number in the iteration
     */
    IterationHead(i)
    unsigned long long ret = i->idx;
    long long step = i->step;
    i->idx += step;
    if ((step > 0 && i->idx >= i->stop) || (step < 0 && i->idx <= i->stop))   {
        i->exhausted = 1;
    }
    return ret;
}

counter counter3(unsigned long long start, unsigned long long stop, long long step)  {
    /**
     * The base constructor for the counter iterator
     * @start: The beginning position of the counter
     * @stop: The point where the counter is exhausted
     * @step: The amount to step by each time you iterate the counter
     * 
     * See counter
     */
    return (counter) {(void * (*)(void *)) &iterate_counter, 0, 0, 0, start, stop, step};
}

counter counter2(unsigned long long start, unsigned long long stop)    {
    /**
     * The simpler constructor for the counter iterator
     * @start: The beginning position of the counter
     * @stop: The point where the counter is exhausted
     * 
     * See counter
     */
    return counter3(start, stop, 1);
}

counter counter1(unsigned long long stop)  {
    /**
     * The simplest constructor for the counter iterator
     * @stop: The point where the counter is exhausted
     * 
     * See counter
     */
    return counter2(0, stop);
}

#endif
