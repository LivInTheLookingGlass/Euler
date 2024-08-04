
/**
 * Grab the contents of a file from the _data directory at root of this repository. Valid encodings are the same as
 * those passed to Node.JS's fs.ReadFileSync(). 'utf8' (the default) will return a string. 'buffer' will return a raw
 * bytestring.
 * @param {string} name
 * @param {string} encoding
 * @return {string | Buffer}
 */
exports.get_data_file = function(name, encoding = 'utf8') {
    if (process.env.APP_ENV === 'browser') {
        const data = require(`./fallbacks/${name}.js`).value;
        const result = Buffer.from(data, 'base64');
        if (encoding !== 'buffer') {
            return result.toString(encoding);
        }
        return result;
    } else {
        const fs = require('fs');
        const path = require('path');

        const filename = path.normalize(path.join(
            __filename,
            '..',
            '..',
            '..',
            '..',
            '_data',
            name
        ));
        try {
            return fs.readFileSync(filename, encoding);
        } catch (e) {
            if (e instanceof TypeError) {
                return Buffer.from(fs.readFileSync(filename, 'utf8'), 'utf8');
            }
            throw e;
        }
    }
};
