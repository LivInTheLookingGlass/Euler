use seq_macro::seq;

use crate::include::utils::Answer;
seq!(N in 0001..=0020 {
use crate::p~N::p~N;
});
use crate::p0022::p0022;
use crate::p0024::p0024;
use crate::p0027::p0027;
use crate::p0034::p0034;
use crate::p0069::p0069;
use crate::p0076::p0076;
use crate::p0077::p0077;
use crate::p0087::p0087;
use crate::p0357::p0357;
use crate::p0836::p0836;

type ProblemType = fn() -> Answer;
type ProblemRef<'a> = (&'a usize, ProblemType, bool);

pub fn get_problem<'b>(n: usize) -> Option<ProblemRef<'b>> {
    return match n {
        1 =>   Some((  &1, p0001, false)),
        2 =>   Some((  &2, p0002, false)),
        3 =>   Some((  &3, p0003, false)),
        4 =>   Some((  &4, p0004, false)),
        5 =>   Some((  &5, p0005, false)),
        6 =>   Some((  &6, p0006, false)),
        7 =>   Some((  &7, p0007, false)),
        8 =>   Some((  &8, p0008, false)),
        9 =>   Some((  &9, p0009, false)),
        10 =>  Some(( &10, p0010, false)),
        11 =>  Some(( &11, p0011, false)),
        12 =>  Some(( &12, p0012, false)),
        13 =>  Some(( &13, p0013, false)),
        14 =>  Some(( &14, p0014, false)),
        15 =>  Some(( &15, p0015, false)),
        16 =>  Some(( &16, p0016, false)),
        17 =>  Some(( &17, p0017, false)),
        18 =>  Some(( &18, p0018, false)),
        19 =>  Some(( &19, p0019, false)),
        20 =>  Some(( &20, p0020, false)),
        22 =>  Some(( &22, p0022, false)),
        24 =>  Some(( &24, p0024, false)),
        27 =>  Some(( &27, p0027, true)),
        34 =>  Some(( &34, p0034, false)),
        69 =>  Some(( &69, p0069, false)),
        76 =>  Some(( &76, p0076, false)),
        77 =>  Some(( &77, p0077, false)),
        87 =>  Some(( &87, p0087, false)),
        357 => Some((&357, p0357, true)),
        836 => Some((&836, p0836, false)),
        _ => None,
    };
}


pub fn generate_supported_problems(include_slow: bool) -> Vec<usize> {
    let mut supported_problems = Vec::new();
    for n in 1..10000 {
        if let Some((_, _, slow)) = get_problem(n) { 
            if !slow || include_slow {
                supported_problems.push(n);
            }
        }
    }

    return supported_problems;
}