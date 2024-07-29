use std::fs::read_to_string;
use std::path::Path;

pub fn get_data_file(str: &str) -> String {
    let data_file = Path::new(env!("CARGO_MANIFEST_DIR")).parent().unwrap().join("_data").join(str);
    return read_to_string(&data_file).unwrap();
}
