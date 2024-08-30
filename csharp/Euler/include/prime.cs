using System;
using System.Collections.Generic;

namespace Euler
{
    public static class Prime
    {
        private static readonly Dictionary<Type, (dynamic LastCached, List<dynamic> Cache)> Caches = new();

        public static IEnumerable<T> Primes<T>(T? stop = null) where T : struct
        {
            foreach (dynamic p in _Primes(stop))
            {
                yield return (T) p;
            }
        }

        private static IEnumerable<dynamic> _Primes(dynamic? stop = null)
        {
            Type type = stop != null ? stop.GetType() : typeof(long);
            if (!Caches.TryGetValue(type, out var cacheData))
            {
                cacheData = (LastCached: (dynamic)0, Cache: new List<dynamic>());
                Caches[type] = cacheData;
            }
            (dynamic lastCached, List<dynamic> cache) = cacheData;

            // Yield cached values
            if (stop == null)
            {
                foreach (dynamic p in cache)
                {
                    yield return p;
                }
            }
            else
            {
                foreach (dynamic p in cache)
                {
                    if (p < stop)
                        yield return p;
                    else
                        break;
                }
            }

            // Generate new primes
            if (stop != null && lastCached > stop)
                yield break;

            foreach (dynamic p in ModifiedEratosthenes())
            {
                if (p <= lastCached)
                    continue;
                if (stop != null && p > stop)
                    break;

                cache.Add(p);
                lastCached = p;
                Caches[type] = (lastCached, cache);
                yield return p;
            }
        }

        private static IEnumerable<dynamic> ModifiedEratosthenes()
        {
            yield return 2;
            yield return 3;
            yield return 5;
            yield return 7;
            var sieve = new Dictionary<dynamic, dynamic>();
            var recurse = ModifiedEratosthenes().GetEnumerator();
            recurse.MoveNext();
            recurse.MoveNext();
            dynamic prime = recurse.Current;
            if (prime != 3)
                throw new Exception();
            dynamic primeSquared = prime * prime;
            dynamic step = 2;
            for (dynamic candidate = 9; ; candidate += 2)
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
                dynamic tc = candidate;
                do
                {
                    tc += step;
                } while (sieve.ContainsKey(tc));
                sieve.Add(tc, step);
            }
        }

        public static IEnumerable<T> PrimeFactors<T>(T n) where T : struct
        {
            foreach (dynamic f in _PrimeFactors(n))
            {
                yield return (T) f;
            }
        }

        private static IEnumerable<dynamic> _PrimeFactors(dynamic n)
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
                dynamic root = (dynamic)Math.Ceiling(Math.Sqrt((double)n));
                foreach (dynamic factor in _Primes())
                {
                    dynamic modulo = n % factor;
                    if (modulo == 0)
                    {
                        do
                        {
                            yield return factor;
                            n /= factor;
                            modulo = n % factor;
                        } while (modulo == 0);
                        root = (dynamic)Math.Ceiling(Math.Sqrt((double)n));
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

        public static dynamic IsComposite(dynamic n)
        {
            var factors = PrimeFactors(n).GetEnumerator();
            factors.MoveNext();
            dynamic first = factors.Current;
            if (first == n)
                return 0;
            return first;
        }

        public static bool IsPrime(dynamic n)
        {
            if (n < 2)
                return false;
            return IsComposite(n) == 0;
        }
    }
}
