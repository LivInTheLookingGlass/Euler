using System.Diagnostics;

namespace Tests
{
    public class EulerTest
    {
        private readonly TimeSpan oneMinute = new TimeSpan(0, 1, 0);
        public static IEnumerable<object[]> Data()
        {
            yield return new object[] { typeof(p0000), false, 0 };
            yield return new object[] { typeof(p0001), false, Utilities.GetAnswer(1) };
            yield return new object[] { typeof(p0002), false, Utilities.GetAnswer(2) };
            yield return new object[] { typeof(p0003), false, Utilities.GetAnswer(3) };
            yield return new object[] { typeof(p0004), false, Utilities.GetAnswer(4) };
            yield return new object[] { typeof(p0006), false, Utilities.GetAnswer(6) };
            yield return new object[] { typeof(p0007), false, Utilities.GetAnswer(7) };
            yield return new object[] { typeof(p0008), false, Utilities.GetAnswer(8) };
            yield return new object[] { typeof(p0009), false, Utilities.GetAnswer(9) };
            yield return new object[] { typeof(p0010), false, Utilities.GetAnswer(10) };
            yield return new object[] { typeof(p0011), false, Utilities.GetAnswer(11) };
            yield return new object[] { typeof(p0013), false, Utilities.GetAnswer(13) };
            yield return new object[] { typeof(p0014), false, Utilities.GetAnswer(14) };
            yield return new object[] { typeof(p0015), false, Utilities.GetAnswer(15) };
            yield return new object[] { typeof(p0016), false, Utilities.GetAnswer(16) };
            yield return new object[] { typeof(p0017), false, Utilities.GetAnswer(17) };
            yield return new object[] { typeof(p0019), false, Utilities.GetAnswer(19) };
            yield return new object[] { typeof(p0020), false, Utilities.GetAnswer(20) };
            yield return new object[] { typeof(p0022), false, Utilities.GetAnswer(22) };
            yield return new object[] { typeof(p0034), false, Utilities.GetAnswer(34) };
            yield return new object[] { typeof(p0076), true, Utilities.GetAnswer(76) };
            yield return new object[] { typeof(p0836), false, Utilities.GetAnswer(836) };
        }

        [Theory]
        [MemberData(nameof(Data))]
        public async Task EulerTest_Problem(Type problem, bool isSlow, object expected)
        {
            IEuler? prob = (IEuler?)Activator.CreateInstance(problem);
            if (prob is null)
                throw new Exception("Unable to construct test object");
            Stopwatch sw = Stopwatch.StartNew();
            object result = await Task.Run(() => prob.Answer());
            sw.Stop();
            Assert.Equal(expected, result);
            if (!isSlow)
                Assert.True(sw.Elapsed <= oneMinute);
        }

        [Fact]
        public void EulerTest_Mathematics_Factorial()
        {
            List<ulong> results = new() {
                1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600,6227020800, 87178291200,
                1307674368000, 20922789888000, 355687428096000, 6402373705728000, 121645100408832000,
                2432902008176640000
            };
            for (byte i = 0; i < results.Count; i += 1)
            {
                ulong expected = results[i];
                Assert.Equal(expected, Mathematics.Factorial(i));
            }
        }

        [Fact]
        public void EulerTest_Prime_Primes()
        {
            List<long> results = new() {
                2, 3, 5, 7, 11, 13, 17, 19, 23, 29
            };
            var comparison = Prime.Primes<long>().GetEnumerator();
            for (byte i = 0; i < results.Count; i += 1)
            {
                long expected = results[i];
                comparison.MoveNext();
                Assert.Equal(expected, comparison.Current);
            }
        }

        [Fact]
        public void EulerTest_Prime_PrimeFactors()
        {
            List<long> candidates = new() {
                2, 3, 5, 7, 11, 13, 17, 19, 23, 29
            };
            foreach (long x in candidates)
            {
                foreach (long y in candidates)
                {
                    List<long> result = new(Prime.PrimeFactors<long>(x * y));
                    Assert.Contains(x, result);
                    Assert.Contains(y, result);
                }
            }
        }

        [Fact]
        public async Task EulerTest_Mathematics_NChooseR()
        {
            List<List<ulong>> results = new() {
                new() { 1, 1 },
                new() { 1, 2, 1 },
                new() { 1, 3, 3, 1 },
                new() { 1, 4, 6, 4, 1 },
                new() { 1, 5, 10, 10, 5, 1 },
                new() { 1, 6, 15, 20, 15, 6, 1 },
                new() { 1, 7, 21, 35, 35, 21, 7, 1 },
                new() { 1, 8, 28, 56, 70, 56, 28, 8, 1 },
                new() { 1, 9, 36, 84, 126, 126, 84, 36, 9, 1 },
                new() { 1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1 },
                new() { 1, 11, 55, 165, 330, 462, 462, 330, 165, 55, 11, 1 },
                new() { 1, 12, 66, 220, 495, 792, 924, 792, 495, 220, 66, 12, 1 },
                new() { 1, 13, 78, 286, 715, 1287, 1716, 1716, 1287, 715, 286, 78, 13, 1 },
                new() { 1, 14, 91, 364, 1001, 2002, 3003, 3432, 3003, 2002, 1001, 364, 91, 14, 1 },
                new() { 1, 15, 105, 455, 1365, 3003, 5005, 6435, 6435, 5005, 3003, 1365, 455, 105, 15, 1 },
                new() { 1, 16, 120, 560, 1820, 4368, 8008, 11440, 12870, 11440, 8008, 4368, 1820, 560, 120, 16, 1 },
                new() { 1, 17, 136, 680, 2380, 6188, 12376, 19448, 24310, 24310, 19448, 12376, 6188, 2380, 680, 136, 17, 1 },
                new() { 1, 18, 153, 816, 3060, 8568, 18564, 21824, 43758, 48620, 43758, 21824, 18564, 8568, 3060, 816, 153, 18, 1 },
            };
            List<Task> tasks = new();
            for (byte i = 0; i < results.Count; i += 1)
            {
                for (byte j = 0; j < results[i].Count; j += 1)
                {
                    ulong expected = results[i][j];
                    tasks.Append(Task.Run(() => Assert.Equal(expected, Mathematics.NChooseR(i, j))));
                }
            }
            foreach (Task task in tasks)
                await task;
        }

        [Fact]
        public void EulerTest_Utils_GetDataFileText()
        {
            Assert.NotNull(Utilities.GetDataFileText("p0022_names.txt"));
        }

        [Fact]
        public void EulerTest_Utils_GetDataFileBytes()
        {
            Assert.NotNull(Utilities.GetDataFileBytes("p0022_names.txt"));
        }
    }
}
