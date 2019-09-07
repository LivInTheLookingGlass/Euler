const benchmark = require('benchmark');
const assert = require('assert');

const answers = {
    1: 233168
};
const known_slow = [];

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
            assert.ok(60 > Math.max(...(results.stats.sample)));
            done();
        });
    });
}