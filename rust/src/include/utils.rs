use std::string::ToString;

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
const P0054_POKER_TXT: &str = include_str!("../../../_data/p0054_poker.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0059_CIPHER_TXT: &str = include_str!("../../../_data/p0059_cipher.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0067_TRIANGLE_TXT: &str = include_str!("../../../_data/p0067_triangle.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0079_KEYLOG_TXT: &str = include_str!("../../../_data/p0079_keylog.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0081_MATRIX_TXT: &str = include_str!("../../../_data/p0081_matrix.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0082_MATRIX_TXT: &str = include_str!("../../../_data/p0082_matrix.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0083_MATRIX_TXT: &str = include_str!("../../../_data/p0083_matrix.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0089_ROMAN_TXT: &str = include_str!("../../../_data/p0089_roman.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0096_SUDOKU_TXT: &str = include_str!("../../../_data/p0096_sudoku.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0098_WORDS_TXT: &str = include_str!("../../../_data/p0098_words.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0099_BASE_EXP_TXT: &str = include_str!("../../../_data/p0099_base_exp.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0102_TRIANGLES_TXT: &str = include_str!("../../../_data/p0102_triangles.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0105_SETS_TXT: &str = include_str!("../../../_data/p0105_sets.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0107_NETWORK_TXT: &str = include_str!("../../../_data/p0107_network.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0424_KAKURO200_TXT: &str = include_str!("../../../_data/p0424_kakuro200.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0673_BEDS_TXT: &str = include_str!("../../../_data/p0673_beds.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0673_DESKS_TXT: &str = include_str!("../../../_data/p0673_desks.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0674_I_EXPRESSIONS_TXT: &str = include_str!("../../../_data/p0674_i_expressions.txt");
#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
const P0828_NUMBER_CHALLENGES_TXT: &str = include_str!("../../../_data/p0828_number_challenges.txt");

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
pub fn get_data_file(name: &str) -> String {
    return match name {
        "answers.tsv" =>                 ANSWERS_TSV.to_string(),
        "p0022_names.txt" =>             P0022_NAMES_TXT.to_string(),
        "p0042_words.txt" =>             P0042_WORDS_TXT.to_string(),
        "p0059_cipher.txt" =>            P0059_CIPHER_TXT.to_string(),
        "p0067_triangle.txt" =>          P0067_TRIANGLE_TXT.to_string(),
        "p0079_keylog.txt" =>            P0079_KEYLOG_TXT.to_string(),
        "p0081_matrix.txt" =>            P0081_MATRIX_TXT.to_string(),
        "p0082_matrix.txt" =>            P0082_MATRIX_TXT.to_string(),
        "p0083_matrix.txt" =>            P0083_MATRIX_TXT.to_string(),
        "p0089_roman.txt" =>             P0089_ROMAN_TXT.to_string(),
        "p0096_sudoku.txt" =>            P0096_SUDOKU_TXT.to_string(),
        "p0098_words.txt" =>             P0098_WORDS_TXT.to_string(),
        "p0099_base_exp.txt" =>          P0099_BASE_EXP_TXT.to_string(),
        "p0102_triangles.txt" =>         P0102_TRIANGLES_TXT.to_string(),
        "p0105_sets.txt" =>              P0102_SETS_TXT.to_string(),
        "p0107_network.txt" =>           P0107_NETWORK_TXT.to_string(),
        "p0424_kakuro200.txt" =>         P0424_KAKURO200_TXT.to_string(),
        "p0673_beds.txt" =>              P0673_BEDS_TXT.to_string(),
        "p0673_desks.txt" =>             P0673_DESKS_TXT.to_string(),
        "p0674_i_expressions.txt" =>     P0674_I_EXPRESSIONS_TXT.to_string(),
        "p0828_number_challenges.txt" => P0828_NUMBER_CHALLENGES_TXT.to_string(),
        _ =>                             panic!("Unknown file name: {}", name),
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

pub fn is_palindrome<I>(x: I) -> bool where I: ToString {
    let s = x.to_string();
    return s == s.chars().rev().collect::<String>();
}
