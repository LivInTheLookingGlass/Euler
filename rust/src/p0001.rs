pub fn p0001() -> u64 {
    let mut answer: u64 = 0;
    for i in (0..1000).step_by(3) {
        answer += i;
    }
    for i in (0..1000).step_by(5) {
        answer += i;
    }
    for i in (0..1000).step_by(15) {
        answer -= i;
    }
    return answer;
}
