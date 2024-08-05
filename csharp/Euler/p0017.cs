/*
Project Euler Problem 17

I feel like there is a better way to recurse this problem, but I could not
think of one at the time

Problem:

If the numbers 1 to 5 are written out in words: one, two, three, four, five,
then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in
words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
letters. The use of "and" when writing out numbers is in compliance with
British usage.
*/
using System;

namespace Euler
{
    public class p0017 : IEuler
    {
        public object Answer()
        {
            ushort answer = 0;
            for (ushort x = 1; x < 1001; x += 1)
            {
                string str = to_string(x);
                answer += str.Replace(" ", "").Replace("-", "").Length;
            }
            return answer;
        }

        static String to_string(ushort n)
        {
            if (n >= 1000)
            {
                return to_string(n / 1000 % 100) + " thousand";
            }
            else if (n >= 100)
            {
                string hundreds = to_string(n / 100 % 10) + " hundred";
                if (n % 100 != 0)
                    return hundreds + " and " + to_string(n % 100);
                return hundreds;
            }
            else if (n >= 20)
            {
                string tens = "";
                switch (n / 10)
                {
                    case 2:
                        tens = "twenty";
                        break;
                    case 3:
                        tens = "thirty";
                        break;
                    case 4:
                        tens = "forty";
                        break;
                    case 5:
                        tens = "fifty";
                        break;
                    case 6:
                        tens = "sixty";
                        break;
                    case 7:
                        tens = "seventy";
                        break;
                    case 8:
                        tens = "eighty";
                        break;
                    case 9:
                        tens = "ninety";
                        break;
                    default:
                        throw new Exception();
                }
                if (n % 10 != 0)
                    return tens + "-" + to_string(n % 10);
                return tens;
            }
            switch (n)
            {
                case 1: return "one";
                case 2: return "two";
                case 3: return "three";
                case 4: return "four";
                case 5: return "five";
                case 6: return "six";
                case 7: return "seven";
                case 8: return "eight";
                case 9: return "nine";
                case 10: return "ten";
                case 11: return "eleven";
                case 12: return "twelve";
                case 13: return "thirteen";
                case 14: return "fourteen";
                case 15: return "fifteen";
                case 16: return "sixteen";
                case 17: return "seventeen";
                case 18: return "eighteen";
                case 19: return "nineteen";
                default: throw new Exception();
            }
        }
    }
}
