/*
Project Euler Problem 19

Problem:

*/
use chrono::DateTime;

use crate::include::utils::Answer;

pub fn p0019() -> Answer {
    let mut answer: u8 = 0;
    for year in 1901..2001 {
        for month in 1..13 {
            let day = DateTime::parse_from_rfc3339(&format!("{}-{:0>2}-01T01:00:00+00:00", year, month)).unwrap();
            if day.to_rfc2822().starts_with("Sun") {
                answer += 1;
            }
        }
    }
    return Answer::Int(answer.into());
}
