/*
Project Euler Problem 22

Porting my file reader from C# was a bit more troublesome than I expected

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
package euler;

import java.io.IOException;
import java.util.Arrays;

import euler.lib.Utilities;

public class p0022 implements IEuler {
    @Override
    public Object answer() {
        int answer = 0;
        String[] names;
        try {
            names = Utilities.getDataFileText("p0022_names.txt")
                             .replace("\"", "")
                             .split(",", 0);
        } catch (IOException e) {
            return null;
        }
        Arrays.sort(names);
        for (int i = 0; i < names.length; i += 1) {
            int sum = 0;
            for (int j = 0; j < names[i].length(); j += 1) {
                sum += names[i].charAt(j) & 0x3F;
            }
            answer += sum * (i + 1);
        }
        return answer;
    }
}