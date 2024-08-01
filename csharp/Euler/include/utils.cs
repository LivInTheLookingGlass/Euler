using System.IO;

namespace Euler
{
    public static class Utilities
    {
        private static string GetDataPath(string name)
        {
            string? thisFile = new System.Diagnostics.StackTrace(true).GetFrame(0)?.GetFileName();
            if (thisFile is null)
                throw new IOException();
            return Path.Join(thisFile, "..", "..", "..", "..", "_data", name);
        }

        public static string GetDataFileText(string name)
        {
            return File.ReadAllText(GetDataPath(name));
        }

        public static byte[] GetDataFileBytes(string name)
        {
            return File.ReadAllBytes(GetDataPath(name));
        }
    }
}
