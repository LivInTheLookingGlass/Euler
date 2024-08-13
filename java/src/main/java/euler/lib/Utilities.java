package euler.lib;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Utilities {

    private static Path getDataPath(String name) throws IOException {
        try {
            URI classUri = Utilities.class.getProtectionDomain().getCodeSource().getLocation().toURI();
            Path classPath = Paths.get(classUri);
            return classPath.getParent().getParent().getParent().resolve("_data").resolve(name);
        } catch (URISyntaxException e) {
            throw new IOException("Invalid syntax in class path");
        }
    }

    public static byte[] getDataFileBytes(String name) throws IOException {
        return Files.readAllBytes(getDataPath(name));
    }

    public static String getDataFileText(String name) throws IOException {
        return new String(getDataFileBytes(name));
    }

    public static Object getAnswer(long n) throws IOException {
        String csvContent = getDataFileText("answers.tsv");
        try (BufferedReader reader = new BufferedReader(new StringReader(csvContent))) {
            String line;
            reader.readLine();
            while ((line = reader.readLine()) != null) {
                String[] arr = line.split("\t");
                long key = Long.parseLong(arr[0]);
                if (key != n)
                    continue;

                String type = arr[1];
                int bitLength = Integer.parseInt(arr[2]);
                String value = arr[3];

                switch (type) {
                case "str":
                    return value;
                case "int":
                    switch (bitLength) {
                    case 8:
                        return (byte) Integer.parseInt(value);
                    case 16:
                        return (short) Integer.parseInt(value);
                    case 32:
                        return Integer.parseInt(value);
                    case 64:
                        return Long.parseLong(value);
                    default:
                        // no return, just continue
                    }
                    break;
                case "uint":
                    switch (bitLength) {
                    case 8:
                        return (byte) Integer.parseUnsignedInt(value);
                    case 16:
                        return (short) Integer.parseUnsignedInt(value);
                    case 32:
                        return Integer.parseUnsignedInt(value);
                    case 64:
                        return Long.parseUnsignedLong(value);
                    default:
                        // no return, just continue
                    }
                default:
                    // no return, just continue
                }

                // If no valid type or bit length was found
                throw new IOException("Unsupported type/length: " + type + ", " + bitLength);
            }
        }
        throw new IOException("Answer not found.");
    }
}
