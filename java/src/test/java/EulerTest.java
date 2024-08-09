package euler;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.jupiter.api.Assertions;

import java.io.IOException;
import java.lang.reflect.Method;
import java.util.stream.Stream;

public class EulerTest {
    private static final long ONE_MINUTE_NS = 60_000_000_000L; // 1 minute in nanoseconds

    // Data provider for parameterized tests
    static Stream<Object[]> data() throws IOException {
        return Stream.of(
            new Object[]{p0000.class, false, 0},
            new Object[]{p0001.class, false, 233168},
            new Object[]{p0002.class, false, 4613732},
            new Object[]{p0004.class, false, 906609},
            new Object[]{p0006.class, false, 25164150},
            // new Object[]{p0008.class, false, Utilities.getAnswer(8)},
            new Object[]{p0009.class, false, 31875000},
            // new Object[]{p0011.class, false, Utilities.getAnswer(11)},
            // new Object[]{p0013.class, false, Utilities.getAnswer(13)},
            // new Object[]{p0014.class, false, Utilities.getAnswer(14)},
            // new Object[]{p0015.class, false, Utilities.getAnswer(15)},
            // new Object[]{p0016.class, false, Utilities.getAnswer(16)},
            // new Object[]{p0017.class, false, Utilities.getAnswer(17)},
            // new Object[]{p0020.class, false, Utilities.getAnswer(20)},
            // new Object[]{p0022.class, false, 871198282},
            // new Object[]{p0034.class, false, Utilities.getAnswer(34)},
            // new Object[]{p0076.class, true, Utilities.getAnswer(76)},
            new Object[]{p0836.class, false, "aprilfoolsjoke"}
        );
    }

    @ParameterizedTest
    @MethodSource("data")
    void eulerTestProblem(Class<?> problemClass, boolean isSlow, Object expected) throws Exception, IOException {
        Assertions.assertTrue(IEuler.class.isAssignableFrom(problemClass), 
            "Class does not implement IEuler: " + problemClass.getName());
        Method answerMethod = problemClass.getMethod("answer");
        IEuler instance = (IEuler)problemClass.getDeclaredConstructor().newInstance();
        long startTime = System.nanoTime();
        Object result = answerMethod.invoke(instance);
        long elapsedTime = System.nanoTime() - startTime;
        Assertions.assertEquals(expected, result);
        if (!isSlow) {
            Assertions.assertTrue(elapsedTime <= ONE_MINUTE_NS, "Test took too long");
        }
    }
}