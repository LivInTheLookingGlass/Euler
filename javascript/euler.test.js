const assert = require('assert');
const benchmark = require('benchmark');

const answers = {
    1: [require('./src/p0001.js'), 233168],
    2: [require('./src/p0002.js'), 4613732],
    4: [require('./src/p0004.js'), 906609],
    6: [require('./src/p0006.js'), 25164150],
    8: [require('./src/p0008.js'), 23514624000],
    9: [require('./src/p0009.js'), 31875000],
    11: [require('./src/p0011.js'), 70600674],
    17: [require('./src/p0017.js'), 21124],
};
const knownSlow = [];
let benchmarkReport = '';

for (question in answers) {
    if (answers.hasOwnProperty(question)) {
        const formattedQuestion = `${question}`.padStart(4, '0');
        const [module, answer] = answers[question];
        describe(`Problem ${formattedQuestion}`, ()=>{
            it(`Should equal ${answer}`, function() {
                if (typeof this.timeout !== 'undefined')
                  if (knownSlow.includes(question)) {
                    this.timeout(-1);
                  }
                  else {
                    this.timeout(60 * 1000);
                  }
                assert.equal(answer, module[`p${formattedQuestion}`]());
            });
            it('should return take less than 1 minute', function(done) {
                if (typeof this.timeout !== 'undefined') {
                  this.timeout(-1);
                  this.slow(300000); // five minutes
                }
                const b = new benchmark.Benchmark(formattedQuestion, module.main, {'minSamples': 10});
                const [results] = benchmark.Benchmark.invoke([b], 'run');
                const max = Math.max(...(results.stats.sample));
                assert.ok(60 > max);
                benchmarkReport += `================= p${formattedQuestion} =================\n`;
                benchmarkReport += `Maximum time:            ${max.toFixed(6)}s\n`;
                benchmarkReport += `Minimum time:            ${Math.min(...(results.stats.sample)).toFixed(6)}s\n`;
                benchmarkReport += `Average time:            ${results.stats.mean.toFixed(6)}s\n`;
                benchmarkReport += `OPS:                     ${results.hz.toFixed(6)}/s\n`;
                benchmarkReport += `Standard Deviation:      ${results.stats.deviation.toFixed(6)}s\n`;
                benchmarkReport += `Margin of Error:         ${results.stats.moe.toFixed(6)}s\n`;
                benchmarkReport += `Iterations:              ${results.stats.sample.length}\n\n\n`;
                done();
                process.stdout.write(`        Max time: ${max.toFixed(6)}s\n`);
            });
        });
    }
}

if (typeof after !== 'undefined') {
    after(()=>{
        process.stdout.write(benchmarkReport);
    });
}
