const path = require('path');
const webpack = require('webpack'); // to access built-in plugins

module.exports = {
    entry: './euler.test.js', // Adjust the entry point to your main file
    output: {
        filename: 'bundle-js.js',
        path: path.resolve(__dirname, 'dist'),
        libraryTarget: 'umd',
        globalObject: 'this',
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                exclude: /node_modules/,
                use: {
                    loader: 'babel-loader', // if you need Babel transpilation
                    options: {
                        presets: ['@babel/preset-env'],
                    },
                },
            },
        ],
    },
    resolve: {
        extensions: ['.js'],
        fallback: {
            buffer: require.resolve('buffer/'),
        },
    },
    mode: 'development', // Change to 'production' for production builds
    plugins: [
        new webpack.DefinePlugin({
            'process.env': {
                APP_ENV: JSON.stringify('browser'),
            },
        }),
        new webpack.ProvidePlugin({
            Buffer: ['buffer', 'Buffer'],
        }),
    ],
};
