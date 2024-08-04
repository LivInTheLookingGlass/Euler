/**
 * Project Euler Problem 22
 *
 *
 * Problem:
 *
 * Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
 * containing over five-thousand first names, begin by sorting it into
 * alphabetical order. Then working out the alphabetical value for each name,
 * multiply this value by its alphabetical position in the list to obtain a name
 * score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which is
 * worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would
 * obtain a score of 938 × 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 *
 * @return {number}
 */
exports.p0022 = function() {
    const contents = require('./lib/utils.js').get_data_file('p0022_names.txt');
    let names = contents.replaceAll('"', '').split(',');
    names.sort();
    let sum = 0;
    for (let i = 0; i < names.length; i += 1) {
        let quantity = 0;
        for (let j = 0; j < names[i].length; j += 1) {
            quantity += names[i].charCodeAt(j) & 0x3F;
        }
        sum += quantity * (i + 1);
    }
    return sum;
};
