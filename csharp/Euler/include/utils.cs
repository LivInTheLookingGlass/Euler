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

        public static object GetAnswer(ulong n)
        {
            foreach (string line in GetDataFileText("answers.csv").Split(new [] { '\r', '\n' })) {
                var arr = line.Split("\t");
                if (arr[0] != n.ToString()) continue;
                if (arr[1] == "str") return arr[3];
                if (arr[2] <= 32) return int.Parse(arr[3]);
                return long.parse(arr[3]);
            }
            throw new IOException();
        }
    }
}
