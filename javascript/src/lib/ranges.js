/**
 * Returns the number at position ``idx`` in a range starting at ``start`` and iterating by ``step``.
 * @param {number} start
 * @param {number} idx
 * @param {number} step
 * @return {number}
 */
function rangeEntry3(start, idx, step) {
    return start + idx * step;
}
exports.rangeEntry3 = rangeEntry3;

/**
 * Returns the number at position ``idx`` in the range [``start``, ``stop``) and iterating by ``step``.
 * @param {number} start
 * @param {number} stop
 * @param {number} idx
 * @param {number} step
 * @return {number | undefined}
 */
function rangeEntry4(start, stop, idx, step) {
    let length = 0;
    if (step > 0 && start < stop) {
        length = Math.floor(1 + (stop - 1 - start) / step);
    } else if (step < 0 && start > stop) {
        length = Math.floor(1 + (start - 1 - stop) / (-step));
    }
    if (idx < 0) {
        idx = length + idx;
    }
    if (idx < 0 || idx >= length) {
        return undefined;
    }
    return rangeEntry3(start, idx, step);
}
exports.rangeEntry4 = rangeEntry4;
