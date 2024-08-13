use std::fs::read_to_string;
use std::path::Path;

#[derive(Debug, PartialEq, Eq)]
pub enum Answer {
    String(String),
    Int(i128),
}

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