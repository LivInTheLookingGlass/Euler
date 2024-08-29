using System;

namespace Euler
{
    public static class Prime
    {
        private static long lastCached = 0;
        private static List<long> cache = new();

        public static IEnumerable<long> Primes(long? stop = null)
        {
            if (stop is null)
            {
                foreach (var p in cache)
                {
                    yield return p;
                }
            }
            else
            {
                foreach (var p in cache)
                {
                    if (p < stop)
                        yield return p;
                    else
                        break;
                }
            }
            if (stop is not null && lastCached > stop)
                yield break;
            foreach (var p in ModifiedEratosthenes())
            {
                if (p <= lastCached)
                    continue;
                if (stop is not null && p > stop)
                    break;
                cache.Add(p);
                lastCached = p;
                yield return p;
            }
        }

        private static IEnumerable<long> ModifiedEratosthenes()
        {
            yield return 2;
            yield return 3;
            yield return 5;
            yield return 7;
            Dictionary<long, long> sieve = new();
            var recurse = ModifiedEratosthenes().GetEnumerator();
            recurse.MoveNext();
            recurse.MoveNext();
            long prime = recurse.Current;
            if (prime != 3)
                throw new Exception();
            long primeSquared = prime * prime;
            long step = 2;
            for (long candidate = 9; ; candidate += 2)
            {
                if (sieve.ContainsKey(candidate))
                {
                    step = sieve[candidate];
                    sieve.Remove(candidate);
                }
                else if (candidate < primeSquared)
                {
                    yield return candidate;
                    continue;
                }
                else
                {
                    step = prime * 2;
                    recurse.MoveNext();
                    prime = recurse.Current;
                    primeSquared = prime * prime;
                }
                long tc = candidate;
                do
                {
                    tc += step;
                } while (sieve.ContainsKey(tc));
                sieve.Add(tc, step);
            }
        }

        public static IEnumerable<long> PrimeFactors(long n)
        {
            if (n < 0)
            {
                yield return -1;
                n = -n;
            }
            if (n == 0)
            {
                yield return 0;
            }
            else
            {
                long root = (long)Math.Ceiling(Math.Sqrt(n));
                foreach (long factor in Primes())
                {
                    long modulo = n % factor;
                    if (modulo == 0)
                    {
                        do
                        {
                            yield return factor;
                            n /= factor;
                            modulo = n % factor;
                        } while (modulo == 0);
                        root = (long)Math.Ceiling(Math.Sqrt(n));
                    }
                    if (n <= 1)
                        break;
                    if (factor > root)
                    {
                        yield return n;
                        break;
                    }
                }
            }
        }

        public static long isComposite(long n)
        {
            var factors = PrimeFactors(n).GetEnumerator();
            factors.MoveNext();
            long first = factors.current;
            if (first == n)
                return 0;
            return first;
        }

        public static bool isPrime(long n)
        {
            if (n < 2)
                return false;
            return isComposite(n) == 0;
        }
    }
}
