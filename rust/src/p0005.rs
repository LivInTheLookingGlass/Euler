use itertools::Itertools;

pub fn p0005() -> u64 {
    let mut answer = u64::MAX;
    let group = 1..=20u64;
    for x in group.clone() {
        for multiples in group.clone().combinations(x as usize) {
            let num = multiples.into_iter().product();
            if num < answer && group.clone().all(|divisor| num % divisor == 0) {
                answer = num;
            }
        }
    }
    return answer;
}
