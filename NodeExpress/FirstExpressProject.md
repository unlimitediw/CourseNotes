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

* The generated project
  * Directory structure
#
    /express-locallibrary-tutorial
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
