## Express Start
* learn from [MDN web docs](https://developer.mozilla.org/en-US/docs/Learn/Server-side/Express_Nodejs/Tutorial_local_library_website)

> Install

* Set the package.json
* install npm
* install express 
* install express-generator (if write access failed, [check](https://docs.npmjs.com/resolving-eacces-permissions-errors-when-installing-packages-globally))

## The Local Library Website
> Create a Skeleton Website

* Running seleton website
  * `express ExpressLibrary`
  * `npm install`, it will install the dependencies
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

> Using a Database(with Mongoose)

* MongoDB: A NoSQL database which uses JSON-like documents with schemata.
* Mongoose acts as a front end to MongoDB.
* Install Mongoose and MongoDB
  * `npm install mongoose`
* Connecting to MongoDB
#
    //Import the mongoose module
    var mongoose = require('mongoose');

    //Set up default mongoose connection
    var mongoDB = 'database url';
    mongoose.connect(mongoDB,{ useNewUrlParser: true });
    // Get Mongoose to use the global promise library
    mongoose.Promise = global.Promise;
    //Get the default connection
    var db = mongoose.connection;

    //Bind connection to error event (to get notification of connection errors)
    db.on('error', console.error.bind(console, 'MongoDB connection error:'));

* Defing Schemas and creating a model
#
    //Require Mongoose
    var mongoose = require('mongoose');

    //Define a schema
    var Schema = mongoose.Schema;

    var SomeModelSchema = new Schema({
      a_string: String,
      a_date: Date
    });
    // Compile model from schema
    var SomeModel = mongoose.model('SomeModel', SomeModelSchema );
    
* Schema types(fields)
  * A schema can have an arbitrary number of fields - each one represents a field in the documents stored in MongoDB.
#
    var schema = new Schema(
    {
      name: String,
      binary: Buffer,
      living: Boolean,
      updated: { type: Date, default: Date.now() },
      age: { type: Number, min: 18, max: 65, required: true },
      mixed: Schema.Types.Mixed,
      _someId: Schema.Types.ObjectId,
      array: [],
      ofString: [String], // You can also have an array of each of the other types too.
      nested: { stuff: { type: String, lowercase: true, trim: true } }
    })
    
* Using models
var mymodel = mongoose.model('anyname',schema)
var myinstance = new mymodel({name:'123'});

> Working with related documents
* Some exaples:
* Atthention: mongoose.model first arg must be same as the model you export.
#
    var Story = mongoose.model('Story',storySchema);
    var Author = mongoose.model('Author',authorSchema);

    var bob = new Author({name:'Wentao'});
    var AWK = new Author({name:'AWK'});
    bob.save(function(err){
      if (err) return handleError(err);
      var story = new Story({
        title: "W's story",
        author: bob._id
      });

      story.save(function(err){
        if(err) return handleError(err);
      });
    });


    Story.findOne({title: "W's story"}).populate('author').exec(function(err,story){
      if(err) return handleError(err);
      console.log(story.author.name);
    })
    Story.find({author:AWK._id}).exec(function(err,stories){
      if(err) return handleError(err);
    })

* Defining Local Library Schema
  * author.js
  * book.js
  * bookinstance.js
  * genre.js

* Author model (others are same)
#
    var mongoose = require('mongoose');

    var Schema = mongoose.Schema;

    var AuthorSchema = new Schema({
      first_name: {type: String, required:true,max:100},
      family_name: {type:String, required:true,max:100},
      date_of_birth: {type:Date},
      date_of_death:{type:Date}
    });

    //Virtual for author's full name
    AuthorSchema.virtual('name').get(function(){
      return this.family_name + ', ' + this.first_name;
    });

    AuthorSchema.virtual('lifespan').get(function(){
      try{
        return (this.date_of_death.getYear() - this.date_of_birth.getYear()).toString();
      }catch(err){
          console.log(err.message);
      }
    });

    AuthorSchema.virtual('url').get(function(){
      return '/catalog/author/' + this._id;
    });

    module.exports = mongoose.model('Author',AuthorSchema);
    
* use populatedb.js to link the mongoose web db. (remeber `npm install async`)
#
    var mongoose = require('mongoose');
    var mongoDB = userArgs[0];
    mongoose.connect(mongoDB);
    mongoose.Promise = global.Promise;
    var db = mongoose.connection;
    mongoose.connection.on('error', console.error.bind(console, 'MongoDB connection error:'));
    
* use `Async.series` to go through functions.

> Routes and controllers 
* Main things:
  * Database(finished)
  * Model(finished)
  * Routes: route to forward the supported request(and any information encoded in request URLs) to the appropriate controller functions.
  * Controller: give functions to get the requested data from the models, create an HTML page displaying the data, and return it to the user to view in the website.
  * Views(templates): used by the controllers to render the data.
* Two sections:
  * Router primer: how to use the Express Router middleware
  * Set up the Local Library routes
* Routes primers
  * route(Express) associates an HTTP verb(GET, POST, PUT, DELETE, etc), an URL path/pattern, and a function that is called to handle that pattern.
* express.Router(), defining and using separate route modules.
* wiki.js
#
    var express = require('express');
    var router = express.Router();

    // Home page route.
    router.get('/', function (req, res) {
      res.send('Wiki home page');
    })

    // About page route.
    router.get('/about', function (req, res) {
      res.send('About this wiki');
    })
    
    router.post('/about', function (req, res) {
      res.send('About this wiki');
    })

    module.exports = router;
* app.js
#
    var wiki = require('./wiki.js');
    // ...
    app.use('/wiki', wiki);
    
* Route paths(regex)
  * `?`: the endpoint must have 0 or 1 of the preceding charater
  * `+`: the endpoint must have 1 or more of the preceding character
  * `*`: the endpoint may have an arbitrary string where the * character is placed.
  * `()`: grouping match on a set of characters to perform another operation on.(take the group as a character)
  
* Route parameters
  * The named segments are prefiexd with `/:`
  * It is req.params when use `app.get()`
  
* Routes needed for the LocalLibrary
  * 

  

  
