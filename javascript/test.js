const benchmark = require('benchmark');
const assert = require('assert');

const answers = {
    1: 233168,
    2: 4613732,
};
const known_slow = [];
let benchmark_report = '';

for (question in answers)   {
    const formatted_question = `${question}`.padStart(4, '0');
    const answer = answers[question];
    const module = require(`./p${formatted_question}.js`);
    describe(`Problem ${formatted_question}`, ()=>{
        it(`Should equal ${answer}`, function() {
            if (known_slow.includes(question)) {
                this.timeout(-1);
            }
            assert.equal(answer, module.main());
        });
        it('should return take less than 1 minute', function(done)   {
            this.timeout(-1);
            this.slow(300000); // five minutes
            var b = benchmark.Benchmark(formatted_question, module.main, {'minSamples': 10});
            var [results] = benchmark.Benchmark.invoke([b], 'run');
            const max = Math.max(...(results.stats.sample));
            assert.ok(60 > max);
            benchmark_report += `================= p${formatted_question} =================\n`;
            benchmark_report += `Maximum time:            ${max.toFixed(6)}s\n`;
            benchmark_report += `Minimum time:            ${Math.min(...(results.stats.sample)).toFixed(6)}s\n`;
            benchmark_report += `Average time:            ${results.stats.mean.toFixed(6)}s\n`;
            benchmark_report += `OPS:                     ${results.hz.toFixed(6)}/s\n`;
            benchmark_report += `Standard Deviation:      ${results.stats.deviation.toFixed(6)}s\n`;
            benchmark_report += `Margin of Error:         ${results.stats.moe.toFixed(6)}s\n`;
            benchmark_report += `Iterations:              ${results.stats.sample.length}\n\n\n`;
            done();
            process.stdout.write(`        Max time: ${max.toFixed(6)}s\n`);
        });
    });
}

after(()=>{
    process.stdout.write(benchmark_report);
});
