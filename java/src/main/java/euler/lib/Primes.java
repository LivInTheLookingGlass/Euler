import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class PrimeGenerator {

    private static class Cache {
        long lastCached;
        List<Long> primes;

        Cache(long lastCached, List<Long> primes) {
            this.lastCached = lastCached;
            this.primes = primes;
        }
    }

    private static final Cache CACHE = new Cache(0, new ArrayList<>());

    public static Stream<Long> primes() {
        return StreamSupport.stream(new PrimeIterator(null).spliterator(), false);
    }

    public static Stream<Long> primesUntil(Long limit) {
        return StreamSupport.stream(new PrimeIterator(limit).spliterator(), false);
    }

    private static class PrimeIterator implements Iterator<Long> {
        private final Long limit;
        private Iterator<Long> primeGenerator;
        private boolean exhausted = false; // Flag to indicate if we have exhausted all primes

        PrimeIterator(Long limit) {
            this.limit = limit;
            // Initialize primeGenerator with a recursive prime generator
            primeGenerator = new PrimeGeneratorIterator(null);
        }

        @Override
        public boolean hasNext() {
            if (exhausted) {
                return false;
            }

            // Check if the limit has been reached with cached primes
            if (limit != null && CACHE.lastCached >= limit) {
                return false;
            }

            // Check if there are more primes to generate
            return primeGenerator.hasNext();
        }

        @Override
        public Long next() {
            if (limit != null && CACHE.lastCached >= limit) {
                exhausted = true;
                return null; // Indicate end of stream
            }

            // Generate and yield new primes
            while (true) {
                if (primeGenerator.hasNext()) {
                    long prime = primeGenerator.next();
                    if (limit != null && prime >= limit) {
                        exhausted = true;
                        return null; // Indicate end of stream
                    }
                    CACHE.primes.add(prime);
                    CACHE.lastCached = prime;
                    return prime;
                }

                // Reinitialize primeGenerator if needed
                primeGenerator = new PrimeGeneratorIterator(null);
            }
        }
    }

    private static class PrimeGeneratorIterator implements Iterator<Long> {
        private final List<Long> initialPrimes = List.of(2L, 3L, 5L, 7L);
        private final Map<Long, Long> sieve = new HashMap<>();
        private Iterator<Long> recursivePrimes;
        private long currentPrime;
        private long primeSquared;
        private long step = 2;
        private long candidate = 9;

        PrimeGeneratorIterator(Long stop) {
            // Initialize with initial primes and state
            initialPrimes.forEach(prime -> {
                sieve.put(prime, step);
                step = prime * 2;
            });
            recursivePrimes = new PrimeGeneratorIterator(null);
            if (recursivePrimes.hasNext()) {
                currentPrime = recursivePrimes.next();
            }
            if (currentPrime != 3) {
                throw new IllegalStateException("Unexpected prime value");
            }
            primeSquared = currentPrime * currentPrime;
        }

        @Override
        public boolean hasNext() {
            return true; // Infinite sequence
        }

        @Override
        public Long next() {
            while (true) {
                if (sieve.containsKey(candidate)) {
                    step = sieve.remove(candidate);
                } else if (candidate < primeSquared) {
                    long result = candidate;
                    candidate += 2;
                    return result;
                } else {
                    step = currentPrime * 2;
                    if (recursivePrimes.hasNext()) {
                        currentPrime = recursivePrimes.next();
                    }
                    primeSquared = currentPrime * currentPrime;
                }
                long multiple = candidate;
                while (sieve.containsKey(multiple)) {
                    multiple += step;
                }
                sieve.put(multiple, step);
                candidate += 2;
            }
        }
    }
}
