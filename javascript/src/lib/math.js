/**
 * @param {number} n
 * @return {number}
 */
exports.factorial = function factorial(n) {
    let answer = 1;
    for (let x = 2; x <= n; x += 1) {
        answer *= x;
    }
    return answer;
};
/**
 * @param {number} n
 * @param {number} r
 * @return {number}
 */
exports.nChooseR = function nChooseR(n, r) {
    if (n <= 20) {
        return factorial(n) / factorial(r) / factorial(n - r);
    }

    let answer; let tmp; let i; let j;
    const factors = new Int8Array(n + 1);
    // collect factors of final number
    for (i = 2; i <= n; i += 1) {
        factors[i] = 1;
    }

    // negative factor values indicate need to divide
    for (i = 2; i <= r; i += 1) {
        factors[i] -= 1;
    }
    for (i = 2; i <= n - r; i += 1) {
        factors[i] -= 1;
    }

    // this loop reduces to prime factors only
    for (i = n; i > 1; i -= 1) {
        for (j = 2; j < i; j += 1) {
            if (i % j == 0) {
                factors[j] += factors[i];
                factors[i / j] += factors[i];
                factors[i] = 0;
                break;
            }
        }
    }

    i = j = 2;
    answer = 1;
    while (i <= n) {
        while (factors[i] > 0) {
            tmp = answer;
            answer *= i;
            while (answer < tmp && j <= n) {
                while (factors[j] < 0) {
                    tmp /= j;
                    factors[j] += 1;
                }
                j += 1;
                answer = tmp * i;
            }
            if (answer < tmp) {
                return ulong.MaxValue;
            } // this indicates an overflow
            factors[i] -= 1;
        }
        i += 1;
    }

    while (j <= n) {
        while (factors[j] < 0) {
            answer /= j;
            factors[j] += 1;
        }
        j += 1;
    }

    return answer;
};
