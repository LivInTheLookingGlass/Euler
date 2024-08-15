#[cfg(not(any(target_arch="wasm32", target_arch="wasm64")))]
use std::fs::read_to_string;
#[cfg(not(any(target_arch="wasm32", target_arch="wasm64")))]
use std::path::Path;

#[derive(Debug, PartialEq, Eq)]
pub enum Answer {
    String(String),
    Int(i128),
}

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const ANSWERS_TSV: &str = include_str!("../../../_data/answers.tsv");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0022_NAMES_TXT: &str = include_str!("../../../_data/p0022_names.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0042_WORDS_TXT: &str = include_str!("../../../_data/p0042_words.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0067_TRIANGLE_TXT: &str = include_str!("../../../_data/p0067_triangle.txt");

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
pub fn get_data_file(name: &str) -> String {
    return match name {
        "answers.tsv" => ANSWERS_TSV.to_string(),
        "p0022_names.txt" => P0022_NAMES_TXT.to_string(),
        "p0042_words.txt" => P0042_WORDS_TXT.to_string(),
        "p0067_triangle.txt" => P0067_TRIANGLE_TXT.to_string(),
        _ => panic!("Unknown file name: {}", name),
    }
}

#[cfg(not(any(target_arch="wasm32", target_arch="wasm64")))]
pub fn get_data_file(name: &str) -> String {
    let data_file = Path::new(env!("CARGO_MANIFEST_DIR")).parent().unwrap().join("_data").join(name);
    return read_to_string(&data_file).unwrap();
}

pub fn get_answer(n: usize) -> Answer {
    let csv = get_data_file("answers.tsv");
    let mut lines = csv.lines();
    lines.next();
    for line in lines {
        let parts: Vec<_> = line.split('\t').collect();
        if parts.len() != 4 {
            panic!("Wrong number of parts: {}", parts.len());
        }
        let (id, type_, answer) = (parts[0], parts[1], parts[3]);
        if n == id.parse::<usize>().unwrap() {
            return match type_ {
                "str" => Answer::String(answer.to_string()),
                _ => Answer::Int(answer.parse::<i128>().unwrap()),
            }
        }
    }
    panic!("Answer not found");
}