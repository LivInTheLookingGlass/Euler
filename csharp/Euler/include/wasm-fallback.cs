using System.IO;

namespace Euler
{
    public static class WasmIOFallback
    {
        public static string GetText(string name)
        {
            return "";
        }

        public static byte[] GetBytes(string name)
        {
            return new byte[] { };
        }
    }
}
