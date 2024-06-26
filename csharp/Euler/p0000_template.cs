/*
Project Euler Template

This template is used to format Project Euler solution scripts. This paragraph
should be replaced by a description of how I approached the problem, as well as
critque.

This paragraph should be replaced by the problem description, excluding images.
*/
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
