import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Spliterator;
import java.util.Spliterators;
import java.util.function.Consumer;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class Primes {

    private static class Cache {
        long lastCached;
        List<Long> primes;

        Cache(long lastCached, List<Long> primes) {
            this.lastCached = lastCached;
            this.primes = primes;
        }
    }

    private static final Cache CACHE = new Cache(0, new ArrayList<>());

    // Generate an infinite stream of primes
    public static Stream<Long> primes() {
        return StreamSupport.stream(new PrimeSpliterator(null), false);
    }

    // Generate a stream of primes up to a given limit
    public static Stream<Long> primesUntil(Long limit) {
        return StreamSupport.stream(new PrimeSpliterator(limit), false);
    }

    private static class PrimeSpliterator implements Spliterator<Long> {
        private final PrimeIterator primeIterator;

        PrimeSpliterator(Long limit) {
            primeIterator = new PrimeIterator(limit);
        }

        @Override
        public boolean tryAdvance(Consumer<? super Long> action) {
            if (primeIterator.hasNext()) {
                action.accept(primeIterator.next());
                return true;
            }
            return false;
        }

        @Override
        public Spliterator<Long> trySplit() {
            return null; // Sequential iteration only
        }

        @Override
        public long estimateSize() {
            return Long.MAX_VALUE; // Unknown size
        }

        @Override
        public int characteristics() {
            return ORDERED | SIZED | IMMUTABLE | NONNULL;
        }
    }

    private static class PrimeIterator implements Iterator<Long> {
        private final Long limit;
        private Iterator<Long> primeGenerator;
        private boolean exhausted = false; // Flag to indicate if we have exhausted all primes

        PrimeIterator(Long limit) {
            this.limit = limit;
            primeGenerator = new PrimeGeneratorIterator();
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
                primeGenerator = new PrimeGeneratorIterator();
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

        PrimeGeneratorIterator() {
            initialPrimes.forEach(prime -> {
                sieve.put(prime, step);
                step = prime * 2;
            });
            recursivePrimes = new PrimeIterator(null);
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
            return true;
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
