namespace Tests
{
    public class EulerTest
    {
        public static IEnumerable<object[]> Data()
        {
            yield return new object[] { typeof(p0000), 0 };
        }

        [Theory]
        [MemberData(nameof(Data))]
        public async Task EulerTest_Problem(Type problem, Int64 expected)
        {
            IEuler? prob;
            prob = (IEuler?)Activator.CreateInstance(problem);
            Assert.NotNull(prob);
            Assert.Equal(expected, await prob.Answer());
        }
    }
}
