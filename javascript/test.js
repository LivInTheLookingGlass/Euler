const benchmark = require('benchmark');
const assert = require('assert');

const answers = {
    1: 233168,
    2: 4613732,
};
const knownSlow = [];
let benchmarkReport = '';

for (question in answers) {
    if (answers.hasOwnProperty(question)) {
        const formattedQuestion = `${question}`.padStart(4, '0');
        const answer = answers[question];
        const module = require(`./p${formattedQuestion}.js`);
        describe(`Problem ${formattedQuestion}`, ()=>{
            it(`Should equal ${answer}`, function() {
                if (knownSlow.includes(question)) {
                    this.timeout(-1);
                }
                assert.equal(answer, module[`p${formattedQuestion}`]());
            });
            it('should return take less than 1 minute', function(done) {
                this.timeout(-1);
                this.slow(300000); // five minutes
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

after(()=>{
    process.stdout.write(benchmarkReport);
});
