package euler;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Utilities {

    private static Path getDataPath(String name) throws IOException {
        String absolutePath;
        try {
            ClassLoader classLoader = Utilities.class.getClassLoader();
            File file = new File(classLoader.getResource("Utilities.class").toURI());
            absolutePath = file.getAbsolutePath();
        } catch (URISyntaxException e) {
            e.printStackTrace();
            throw new IOException();
        }
        if (absolutePath == null) {
            throw new IOException("Unable to determine file path.");
        }
        Path filePath = Paths.get(absolutePath).getParent().resolve("../../../../../_data").resolve(name);
        return filePath.toAbsolutePath();
    }

    public static byte[] getDataFileBytes(String name) throws IOException {
        Path filePath = getDataPath(name);
        return Files.readAllBytes(filePath);
    }

    public static String getDataFileText(String name) throws IOException {
        return new String(getDataFileBytes(name));
    }

    public static Object getAnswer(long n) throws IOException {
        String csvContent = getDataFileText("answers.csv");
        try (BufferedReader reader = new BufferedReader(new StringReader(csvContent))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] arr = line.split("\t");
                if (arr.length < 4) continue;
                long key = Long.parseLong(arr[0]);
                if (key != n) continue;
                
                String type = arr[1];
                int bitLength = Integer.parseInt(arr[2]);
                String value = arr[3];
                
                switch (type) {
                    case "str":
                        return value;
                    case "int":
                        switch (bitLength) {
                            case 8:
                                return (byte)Integer.parseInt(value);
                            case 16:
                                return (short)Integer.parseInt(value);
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
                                return (byte)Integer.parseUnsignedInt(value);
                            case 16:
                                return (short)Integer.parseUnsignedInt(value);
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