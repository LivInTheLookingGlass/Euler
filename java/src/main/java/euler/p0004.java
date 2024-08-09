/*
Project Euler Problem 4

I couldn't figure out how to do this as efficiently as I would have liked. I am
SURE that there is a better way to check if a number is a palindrome, but I
could not think of one.

Problem:

A palindromic number reads the same both ways. The largest palindrome made from
the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
package euler;

public class p0004 implements IEuler {
    private boolean IsPalindrome(int x) {
        String rep = Integer.toString(x);
        int length = rep.length();
        for (int i = 0; i < length; i += 1) {
            if (rep.charAt(i) != rep.charAt(length - i - 1))
                return false;
        }
        return true;
    }

    @Override
    public Object answer() {
        int answer = 0;
        for (int v = 101; v < 1000; v++) {
            for (int u = 100; u < v; u++) {
                int p = u * v;
                if (IsPalindrome(p) && p > answer)
                    answer = p;
            }
        }

        return answer;
    }
}