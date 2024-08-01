const chai = require('chai');
const expect = chai.expect;
const Mathematics = require('./src/lib/math.js');
const Utilities = require('./src/lib/utils.js');

describe('Data Files', ()=>{
    it('Should be able to fetch files as utf8', function() {
        Utilities.get_data_file('p0022_names.txt', 'utf8');
    });
    it('Should be able to fetch files as buffer', function() {
        Utilities.get_data_file('p0022_names.txt', 'buffer');
    });
});

describe('Mathematics', ()=>{
    it('Should be able to compute factorials', function() {
        expect(Mathematics.factorial(6)).to.equal(2 * 3 * 4 * 5 * 6);
    });
});

const answers = {
    1: [require('./src/p0001.js'), false, 233168],
    2: [require('./src/p0002.js'), false, 4613732],
    4: [require('./src/p0004.js'), false, 906609],
    6: [require('./src/p0006.js'), false, 25164150],
    8: [require('./src/p0008.js'), false, 23514624000],
    9: [require('./src/p0009.js'), false, 31875000],
    11: [require('./src/p0011.js'), false, 70600674],
    14: [require('./src/p0014.js'), false, 837799],
    15: [require('./src/p0015.js'), false, 137846528820],
    17: [require('./src/p0017.js'), false, 21124],
    34: [require('./src/p0034.js'), false, 40730],
    76: [require('./src/p0076.js'), true, 190569291],
    836: [require('./src/p0836.js'), false, 'aprilfoolsjoke'],
};

for (question in answers) {
    if (answers.hasOwnProperty(question)) {
        const formattedQuestion = `${question}`.padStart(4, '0');
        const [module, isSlow, answer] = answers[question];
        const problem = module[`p${formattedQuestion}`];
        describe(`Problem ${formattedQuestion}`, ()=>{
            it(`Should equal ${answer}`, function() {
                if (typeof this.timeout !== 'undefined') {
                    if (isSlow) {
                        this.timeout(Infinity);
                    } else {
                        this.timeout(60 * 1000);
                    }
                }
                expect(answer).to.equal(problem());
            });
        });
    }
}
