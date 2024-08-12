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
package euler;

public class p0076 implements IEuler {
    @Override
    public Object answer() {
        int idx, sum = 100, answer = 0;
        int[] counts = new int[101];
        counts[2] = 100;
        while (counts[100] == 0) {
            counts[2] += 2;
            if (sum >= 100) {
                answer += (100 + counts[2] - sum) / 2;
                idx = 2;
                do {
                    counts[idx] = 0;
                    idx++;
                    counts[idx] += idx;
                    sum = 0;
                    for (int i = idx - 1; i < 101; i++)
                        sum += counts[i];
                } while (sum > 100);
            }
            sum = 0;
            for (int i = 0; i < 101; i++)
                sum += counts[i];
        }
        return answer;
    }
}