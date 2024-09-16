package euler.lib;

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

    public static Stream<Long> primes() {
        return StreamSupport.stream(new PrimeSpliterator(null), false);
    }

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
        private boolean exhausted = false;

        PrimeIterator(Long limit) {
            this.limit = limit;
            primeGenerator = new PrimeGeneratorIterator();
        }

        @Override
        public boolean hasNext() {
            if (exhausted || (limit != null && CACHE.lastCached >= limit)) {
                return false;
            }
            return primeGenerator.hasNext();
        }

        @Override
        public Long next() {
            if (limit != null && CACHE.lastCached >= limit) {
                exhausted = true;
                return null;
            }

            if (primeGenerator.hasNext()) {
                long prime = primeGenerator.next();
                if (limit != null && prime >= limit) {
                    exhausted = true;
                    return null;
                }
                CACHE.primes.add(prime);
                CACHE.lastCached = prime;
                return prime;
            }

            return null;
        }
    }

    private static class PrimeGeneratorIterator implements Iterator<Long> {
        private final List<Long> initialPrimes = List.of(2L, 3L, 5L);
        private final Map<Long, Long> sieve = new HashMap<>();
        private Iterator<Long> recursivePrimes;
        private long currentPrime;
        private long primeSquared;
        private long step = 2;
        private long candidate = 2;

        PrimeGeneratorIterator() {
            initialPrimes.forEach(prime -> {
                sieve.put(prime, step);
                step = prime * 2;
            });
            recursivePrimes = null;
        }

        @Override
        public boolean hasNext() {
            return true;
        }

        @Override
        public Long next() {
            if (candidate <= 5) {
                if (candidate == 2) {
                    candidate = 3;
                    return 2L;
                }
                if (candidate == 3) {
                    candidate = 5;
                    return 3L;
                }
                if (candidate == 5) {
                    candidate = 7;
                    recursivePrimes = new PrimeIterator(null);
                    recursivePrimes.next();
                    currentPrime = recursivePrimes.next();
                    primeSquared = currentPrime * currentPrime;
                    return 5L;
                }
            }
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
                do {
                    multiple += step;
                } while (sieve.containsKey(multiple));
                sieve.put(multiple, step);
                candidate += 2;
            }
        }
    }
}