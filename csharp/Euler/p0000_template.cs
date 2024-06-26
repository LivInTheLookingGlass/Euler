using System;

namespace Euler
{
    public interface IEuler
    {
        public Task<Int64> Answer();
    }
    public class p0000 : IEuler
    {
        public Task<Int64> Answer()
        {
            return Task.FromResult<Int64>(0);
        }
    }
}
