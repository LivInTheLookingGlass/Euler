use seq_macro::seq;

use crate::include::utils::Answer;
seq!(N in 0001..=0024 {
    use crate::p~N::p~N;
});
use crate::p0027::p0027;
use crate::p0034::p0034;
use crate::p0036::p0036;
use crate::p0037::p0037;
use crate::p0044::p0044;
use crate::p0045::p0045;
use crate::p0053::p0053;
use crate::p0059::p0059;
use crate::p0067::p0067;
use crate::p0069::p0069;
use crate::p0076::p0076;
use crate::p0077::p0077;
use crate::p0087::p0087;
use crate::p0187::p0187;
use crate::p0357::p0357;
use crate::p0836::p0836;

type ProblemType = fn() -> Answer;
type ProblemRef<'a> = (&'a usize, ProblemType, bool);

seq!(N in 0001..=0020 {
    pub fn get_problem<'b>(n: usize) -> Option<ProblemRef<'b>> {
        return match n {
            #(
                N => Some(( &N, p~N, false)),
            )*
            21 =>  Some(( &21, p0021, true)),
            22 =>  Some(( &22, p0022, false)),
            23 =>  Some(( &23, p0023, false)),
            24 =>  Some(( &24, p0024, false)),
            27 =>  Some(( &27, p0027, true)),
            34 =>  Some(( &34, p0034, false)),
            35 =>  Some(( &35, p0035, false)),
            36 =>  Some(( &36, p0036, false)),
            37 =>  Some(( &37, p0037, true)),
            41 =>  Some(( &41, p0041, false)),
            44 =>  Some(( &44, p0044, false)),
            45 =>  Some(( &45, p0045, false)),
            53 =>  Some(( &53, p0053, false)),
            59 =>  Some(( &59, p0059, false)),
            67 =>  Some(( &67, p0067, false)),
            69 =>  Some(( &69, p0069, false)),
            76 =>  Some(( &76, p0076, false)),
            77 =>  Some(( &77, p0077, false)),
            87 =>  Some(( &87, p0087, false)),
            187 => Some((&187, p0187, false)),
            357 => Some((&357, p0357, true)),
            836 => Some((&836, p0836, false)),
            _ => None,
        };
    }
});


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
