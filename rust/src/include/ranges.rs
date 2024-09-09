use std::cmp::PartialOrd;
use std::marker::Copy;

use num_traits::{one,zero,NumAssign};

pub fn range_entry3<I>(start: I, idx: I, step: I) -> I
where I: NumAssign
{
    return start + idx * step;
}

pub fn range_entry4<I>(start: I, stop: I, idx: I, step: I) -> Option<I>
where I: NumAssign + PartialOrd + Copy
{
    let length = if step > zero() && start < stop {
        one::<I>() + (stop - one() - start) / step
    } else if step < zero() && start > stop {
        one::<I>() + (stop + one() - start) / step
    } else {
        zero::<I>()
    };

    let i = if idx < zero() {
        length + idx
    } else {
        idx
    };

    if i < length {
        return Some(range_entry3(start, i, step));
    }
    return None;
}
