#![allow(unused_imports)]
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
use wasm_bindgen::prelude::*;

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
use js_sys::Array;

use seq_macro::seq;
seq!(N in 0001..=0020 {
pub mod p~N;
});
pub mod p0022;
pub mod p0024;
pub mod p0027;
pub mod p0034;
pub mod p0069;
pub mod p0076;
pub mod p0077;
pub mod p0087;
pub mod p0357;
pub mod p0836;

pub mod include;
pub use crate::include::problems::{generate_supported_problems,get_problem};
pub use crate::include::utils::{Answer,get_answer};

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
#[wasm_bindgen]
pub fn run_problem(n: usize) -> JsValue {
    let Some((_, problem_function, _)) = get_problem(n) else { return JsValue::UNDEFINED };
    let answer = problem_function();
    return match answer {
        Answer::String(e) => JsValue::from_str(&e),
        Answer::Int(e) => JsValue::from(e),
    }
}

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
#[wasm_bindgen]
pub fn get_problems(include_slow: bool) -> JsValue {
    let problems = generate_supported_problems(include_slow);
    let js_array = Array::new_with_length(problems.len() as u32);

    for (i, &item) in problems.iter().enumerate() {
        js_array.set(i as u32, item.into());
    }

    return JsValue::from(js_array);
}

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
#[wasm_bindgen]
pub fn get_js_answer(n: usize) -> JsValue {
    let answer = get_answer(n);
    return match answer {
        Answer::String(e) => JsValue::from_str(&e),
        Answer::Int(e) => JsValue::from(e),
    }
}
