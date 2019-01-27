## Express Start

> Install

* Set the package.json
* install npm
* install express 
* install express-generator (if write access failed, [check](https://docs.npmjs.com/resolving-eacces-permissions-errors-when-installing-packages-globally))

## The Local Library Website
> Create a Skeleton Website

* Running seleton website
  * `express ExpressLibrary`
  * `npm-install`, it will install the dependencies
  * `DEBUG=ExpressLibrary:* npm start`, then run the application.

* Enable server restart on file changes
  * use nodemon to automate restart the server `npm install -g nodemon` (install globally)
  * update the "script" in package.json by adding `"devstart": "nodemon ./bin/www"`.
  * `DEBUG=ExpressLibrary:* npm run devstart`

* Directory structure
#
    /ExpressLibrary
      app.js
      /bin
          www
      package.json
      /node_modules
          [about 4,500 subdirectories and files]
      /public
          /images
          /javascripts
          /stylesheets
              style.css
      /routes
          index.js
          users.js
      /views
          error.pug
          index.pug
          layout.pug 
  * package.json
#
    {
      "name": "expresslibrary",
      "version": "0.0.0",
      "private": true,
      "scripts": {
        "start": "node ./bin/www",
        "devstart": "nodemon ./bin/www"
      },
      "dependencies": {
        "cookie-parser": "~1.4.3",
        "debug": "~2.6.9",
        "express": "~4.16.0",
        "http-errors": "~1.6.2",
        "jade": "~1.11.0",
        "morgan": "~1.9.0"
      },
      "devDependencies": {
        "nodemon": "^1.18.9"
      }
    }
* www file: entry of the application
* app.js
  * This file creates an express application object, sets up the application with various setting and middleware, and then exports the app from the module. The code below shows just the parts of the file that create and export the app object:
#
    var express = require('express');
    var app = express();
    ...
    module.exports = app;

* details of app.js
  * require() 
    * `express, path, serve-favicon, morgan and cookie-parser`
    * `routes/index and routes/users`
