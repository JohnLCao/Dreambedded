var path = require('path');

module.exports = {
  mode: 'development',
  entry: [
    './assets/js/index.js'
  ],
  output: {
    path: path.join(__dirname + '/public'),
    filename: 'bundle.js'
  },
  devServer: {
    watchContentBase: true
  },
  module: {
    rules: [
      {
        test: /\.hamlc$/,
        loader: "hamlc-loader"
      },
      {
        test: /\.js$/,
        exclude: /node_modules/,
        loader: 'babel-loader',
        query: {
          presets: ['es2015']
        }
      },
      {
        test: /\.css$/,
        exclude: /node_modules/,
        loader: 'style-loader!css-loader'
      }
    ]
  }
};
