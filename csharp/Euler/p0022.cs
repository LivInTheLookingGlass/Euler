/*
Project Euler Problem 22

I had to approach this by modifying the factors function from p0003, but it
seemed to work fairly well.

Problem:

Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
containing over five-thousand first names, begin by sorting it into
alphabetical order. Then working out the alphabetical value for each name,
multiply this value by its alphabetical position in the list to obtain a name
score.

For example, when the list is sorted into alphabetical order, COLIN, which is
worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would
obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/
using System;

namespace Euler
{
    public class p0022 : IEuler
    {
        public object Answer()
        {
            int answer = 0;
            string[] names = Utilities.GetDataFileText("p0022_names.txt").Replace("\"", "").Split(',');
            names.Sort();
            for (int i = 0; i < names.Length; i += 1)
            {
                int sum = 0;
                foreach (char c in names[i])
                {
                    sum += c & 0x3F;
                }
                answer += sum * (i + 1);
            }
            return answer;
        }
    }
}


