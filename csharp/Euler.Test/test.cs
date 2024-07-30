using System.Diagnostics;

namespace Tests
{
    public class EulerTest
    {
        private readonly TimeSpan oneMinute = new TimeSpan(0, 1, 0);
        public static IEnumerable<object[]> Data()
        {
            yield return new object[] { typeof(p0000), 0 };
            yield return new object[] { typeof(p0001), 233168 };
            yield return new object[] { typeof(p0002), 4613732 };
            yield return new object[] { typeof(p0004), 906609 };
            yield return new object[] { typeof(p0006), 25164150 };
            yield return new object[] { typeof(p0008), 23514624000 };
            yield return new object[] { typeof(p0009), 31875000 };
            yield return new object[] { typeof(p0011), 70600674 };
            yield return new object[] { typeof(p0017), 21124 };
            yield return new object[] { typeof(p0076), 190569291 };
            yield return new object[] { typeof(p0836), "aprilfoolsjoke" };
        }

        [Theory]
        [MemberData(nameof(Data))]
        public async Task EulerTest_Problem(Type problem, object expected)
        {
            IEuler? prob;
            prob = (IEuler?)Activator.CreateInstance(problem);
            Assert.NotNull(prob);
            Stopwatch sw = Stopwatch.StartNew();
            object result = await prob.Answer();
            sw.Stop();
            Assert.Equal(expected, result);
            Assert.True(sw.Elapsed <= oneMinute);
        }
    }
}
