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
          error.jade
          index.jade
          layout.jade
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
  * set views value to specify the folder where the templates will be stored
    * `app.set('views', path.join(__dirname, 'views'));
    * `app.set('view engine', 'jade');
  * use app.use() to add the middleware libraries into request handling chain
    * `app.use(logger('dev'))`
    * `app.use(express.json())`
    * `app.use(express.urlencoded({extended:false}))`
    * `app.use(cookieParser())`
    * `app.use(express.static(path.join(__dirname,'public')))
  * add route-handling code to request handling chain
    * `app.use('/',indexRouter)`
    * `app.use('/users',userRouter)`
    * `/ and /users` are treated as a prefix to routes defiend in the imported files.
  * also need to add HTTP 404 and error response by app.use()
  * Finally exports the application object by `module.exports = app;`.

* Routes
  * index.js and users.js are similar
  * First it loads the xpress module and uses it to get an express.Router object.
  * Then it specifies a route on that object and lastly exports the router from the module.
  * test it by run `http://localhost:3000/users/`
#
    var express = require('express');
    var router = express.Router();

    /* GET users listing. */
    router.get('/', function(req, res, next) {
      res.send('respond with a resource');
    });

    module.exports = router;
 
* Views(templates)
  * `Response.render()` is used to render a specified template along with the values of named variables passed in an object, and then send the result as a response.
  * In the example, `title` variable is inserted where specified in the template.
