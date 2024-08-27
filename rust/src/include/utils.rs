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
macro_rules! file_name_to_constant {
    ($file_name:expr) => {
        concat!("FILE_", $file_name.to_uppercase().replace(".", "_"))
    };
}

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
macro_rules! define_files {
    ($($file_name:expr),*) => {
        $(
            // Create a constant name by transforming the file name to upper case with underscores
            const file_name_to_constant!($file_name): &str = include_str!(concat!("../../../_data/", $file_name));
        )*
    }
}

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
define_files!(
    "answers.tsv",
    "p0022_names.txt",
    "p0042_words.txt",
    "p0054_poker.txt",
    "p0059_cipher.txt",
    "p0067_triangle.txt",
    "p0079_keylog.txt",
    "p0081_matrix.txt",
    "p0082_matrix.txt",
    "p0083_matrix.txt",
    "p0089_roman.txt",
    "p0096_sudoku.txt",
    "p0098_words.txt",
    "p0099_base_exp.txt",
    "p0102_triangles.txt",
    "p0105_sets.txt",
    "p0107_network.txt",
    "p0424_kakuro200.txt",
    "p0673_beds.txt",
    "p0673_desks.txt",
    "p0674_i_expressions.txt",
    "p0828_number_challenges.txt"
);

#[cfg(any(target_arch="wasm32", target_arch="wasm64"))]
pub fn get_data_file(name: &str) -> String {
    return match name {
        "answers.tsv" =>                 file_name_to_constant!("answers.tsv").to_string(),
        "p0022_names.txt" =>             file_name_to_constant!("p0022_names.txt").to_string(),
        "p0042_words.txt" =>             file_name_to_constant!("p0042_words.txt").to_string(),
        "p0059_cipher.txt" =>            file_name_to_constant!("p0059_cipher.txt").to_string(),
        "p0067_triangle.txt" =>          file_name_to_constant!("p0067_triangle.txt").to_string(),
        "p0079_keylog.txt" =>            file_name_to_constant!("p0079_keylog.txt").to_string(),
        "p0081_matrix.txt" =>            file_name_to_constant!("p0081_matrix.txt").to_string(),
        "p0082_matrix.txt" =>            file_name_to_constant!("p0082_matrix.txt").to_string(),
        "p0083_matrix.txt" =>            file_name_to_constant!("p0083_matrix.txt").to_string(),
        "p0089_roman.txt" =>             file_name_to_constant!("p0089_roman.txt").to_string(),
        "p0096_sudoku.txt" =>            file_name_to_constant!("p0096_sudoku.txt").to_string(),
        "p0098_words.txt" =>             file_name_to_constant!("p0098_words.txt").to_string(),
        "p0099_base_exp.txt" =>          file_name_to_constant!("p0099_base_exp.txt").to_string(),
        "p0102_triangles.txt" =>         file_name_to_constant!("p0102_triangles.txt").to_string(),
        "p0105_sets.txt" =>              file_name_to_constant!("p0105_sets.txt").to_string(),
        "p0107_network.txt" =>           file_name_to_constant!("p0107_network.txt").to_string(),
        "p0424_kakuro200.txt" =>         file_name_to_constant!("p0424_kakuro200.txt").to_string(),
        "p0673_beds.txt" =>              file_name_to_constant!("p0673_beds.txt").to_string(),
        "p0673_desks.txt" =>             file_name_to_constant!("p0673_desks.txt").to_string(),
        "p0674_i_expressions.txt" =>     file_name_to_constant!("p0674_i_expressions.txt").to_string(),
        "p0828_number_challenges.txt" => file_name_to_constant!("p0828_number_challenges.txt").to_string(),
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
