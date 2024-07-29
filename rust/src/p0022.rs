/*
Project Euler Problem 24

This one was fairly easy for code golf, thanks to the port of Python's itertools

Problem:

A permutation is an ordered arrangement of objects. For example, 3124 is one
possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
are listed numerically or alphabetically, we call it lexicographic order. The
lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
5, 6, 7, 8 and 9?
*/
use crate::include::utils::get_data_file;

fn score(idx: usize, name: &str) -> u32 {
    return (idx as u32) * name.bytes().map(|x| (x as u8 - b'A' + 1) as u32).sum::<u32>();
}

pub fn p0022() -> i128 {
    let raw_str = get_data_file("p0022_names.txt").replace("\"", "").to_ascii_uppercase();
    let mut names: Vec<&str> = raw_str.split(",").collect();
    names.sort();
    return names.into_iter()
		.enumerate()
		.map(|(idx, name)| score(idx + 1, name))
		.sum::<u32>().into();
}
