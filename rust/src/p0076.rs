/*
Project Euler Problem 76

I ended up having to do this iteratively, which I'm not super happy with. I feel like there is almost certainly a
closed-form solution to this, but I was unable to figure it out.

Problem:

It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two
positive integers?
*/

pub fn p0076() -> i128 {
    let mut answer: u64 = 0;
    let mut idx: usize;
    let mut sum: u64 = 100;
    let mut counts: Vec<u64> = vec![0; 101];
    counts[2] = 100;
    while counts[100] == 0 {
        counts[2] += 2;
        if sum >= 100 {
            answer += (100 + counts[2] - sum) / 2;
            idx = 2;
            loop {
                counts[idx] = 0;
                idx += 1;
                counts[idx] += idx as u64;
                sum = counts.iter().sum();
                if sum <= 100 {
                    break;
                }
            }
            counts[2] = 100 - sum - (sum % 2);
        }
        sum = counts.iter().sum();
    }
    return answer.into();
}
