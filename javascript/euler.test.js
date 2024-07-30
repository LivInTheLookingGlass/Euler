const chai = require('chai');
const expect = chai.expect;

const answers = {
    1: [require('./src/p0001.js'), 233168],
    2: [require('./src/p0002.js'), 4613732],
    4: [require('./src/p0004.js'), 906609],
    6: [require('./src/p0006.js'), 25164150],
    8: [require('./src/p0008.js'), 23514624000],
    9: [require('./src/p0009.js'), 31875000],
    11: [require('./src/p0011.js'), 70600674],
    17: [require('./src/p0017.js'), 21124],
    836: [require('./src/p0836.js'), 'aprilfoolsjoke'],
};
const knownSlow = [];

for (question in answers) {
    if (answers.hasOwnProperty(question)) {
        const formattedQuestion = `${question}`.padStart(4, '0');
        const [module, answer] = answers[question];
        const problem = module[`p${formattedQuestion}`];
        describe(`Problem ${formattedQuestion}`, ()=>{
            it(`Should equal ${answer}`, function() {
                if (typeof this.timeout !== 'undefined') {
                    if (knownSlow.includes(question)) {
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
