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
            foreach (string line in GetDataFileText("answers.csv").Split(new[] { '\r', '\n' }))
            {
                var arr = line.Split("\t");
                if (arr[0] != n.ToString()) continue;
                switch (arr[1])
                {
                    case "str":
                        return arr[3];
                    case "int":
                        switch (int.Parse(arr[2])
                        {
                            case 8:
                                return sbyte.Parse(arr[3]);
                            case 16:
                                return short.Parse(arr[3]);
                            case 32:
                                return int.Parse(arr[3]);
                            case 64:
                                return long.Parse(arr[3]);
                        }
                    case "uint":
                        switch (int.Parse(arr[2])
                        {
                            case 8:
                                return byte.Parse(arr[3]);
                            case 16:
                                return ushort.Parse(arr[3]);
                            case 32:
                                return uint.Parse(arr[3]);
                            case 64:
                                return ulong.Parse(arr[3]);
                        }
                }
            }
            throw new IOException();
        }
    }
}
