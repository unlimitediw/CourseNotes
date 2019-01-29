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
  * `catalog/`
  * `catalog/<objects>/`  list of all books, bookinstances, genres, authors
  * `catalog/<object>/<id>` detail of a specific book, bookinstance...
  * `catalog/<object>/create` the form to create a new book, bookinstance...
  * `catalog/<object>/<id>/update` the form to update a specific book, bookinstance...
  * `catalog/<object>/<id>/delete` the form to delete a specific book, bookinstance...
  
  
* authorController.js (same as bookController, bookinstanceController and genreController)
#
    var Author = require('../models/author');

    // Display list of all Authors.
    exports.author_list = function(req, res) {
        res.send('NOT IMPLEMENTED: Author list');
    };

    // Display detail page for a specific Author.
    exports.author_detail = function(req, res) {
        res.send('NOT IMPLEMENTED: Author detail: ' + req.params.id);
    };
    ...

* Create the catalog route module, catalog.js
  * The routes are defined either using .get() and .post() methods on the router object. All the paths are defined using strings.

#
    var express = require('express');
    var router = express.Router();

    // Require controller modules.
    var book_controller = require('../controllers/bookController');
    var author_controller = require('../controllers/authorController');
    var genre_controller = require('../controllers/genreController');
    var book_instance_controller = require('../controllers/bookinstanceController');

    /// BOOK ROUTES ///

    // GET catalog home page.
    router.get('/', book_controller.index);

    // GET request for creating a Book. NOTE This must come before routes that display Book (uses id).
    router.get('/book/create', book_controller.book_create_get);
    ...
 
* Generally speaking, to route you need:
  * build your controller for get/post options
  * build router in /routes to call the controller and define the router get/post function with defined path
  * give a defined path in /routes/index.js
  * update router to app.js and use it with app.use

> Display Library Data: 12 sub topics

> Asynchronous flow control using async

* Methods:
  * `async.parallel()` to execute any operations that must be performed in parallel.
  * `async.series()` for when we need to ensure that asynchronous operations are performed in series.
  * `async.waterfall()` in series, with each operation depending on the results of preceding operations.

* Asynchronous operations in parallel
   * The method `async.parallel()` is used to run multiple asynchronous operations in parallel
   * the first argument to async.parallel() is a collection of asynchronous functions to run, each function is passed a callback(err, result) where result is optional.
   * The optional second argument is a callback that will be run when all the functions in the first argument have completed. The callback is invoked with an error agrument and a result collection that contains the results of the individual asynchronous operations where the result collection is of the same type as the first argument. If any of the parallel functions reports an error the callback will be invoked earlier.
#
    async.parallel({
      one: function(callback){...},
      two: function(callback){...},
      ...
    },
    //optional callback
    function(err, results){
      // 'results' is now equal to:{one:1, two:2 or some value,...}
    });

* Asynchronous operations in series(independent)
  * the format is the same as parallel
  * If the order is really important, you should pass an array instead of an object.
#
    async.series([
      function(callback){
        callback(null, 'one');
      },
      function(callback){
        callback(null, 'two');
      }
    ],
    //optional callback
    function(err, results){
    // results is now equal to ['one','two']
    });

* Dependent asynchronous operations in series, 
  * `async.waterfall()` is used to run multiple asynchronous operations in sequence when each operation is dependent on the result of the previous operation.
  * The callback invoked by each asynchronous function contains `null` for the first argument and the result in subsequent arguments. Each function in the series takes `the results arguments of the previous callback as the first parameters`, and then a callback function. When all operations are complete, a final callback is invoked with the result of the last operation. 
#
    async.waterfall([
      function(callback){
        callback(null, 'one', 'two');
      },
      function(arg1, arg2, callback){
        //arg1 now equals 'one' and arg2 now equals 'two'
        callback(null, 'three');
      },
      function(arg1,callback){
        //arg1 now equals 'three'
        callback(null,'done');
      }],
      function(err, result){
        //result now equals 'done'
      });
  
> Template primer
* A template is a text file defining the structure or layout of an output file, with placeholders used to represent where data will be inserted when the template is rendered.(in Express, templates are referred to as views)
* View engine setup
#
    app.set('views', path.join(__dirname, 'views'));
    app.set('view engine', 'jade');
* Template syntax
  * the file maps the structure of a typical HTML file
  * Element attributes are defined in parentheses after the associated element.
* LocalLibrary base template
  * use js and css from bootstrap.
  * remember to update the `/public/stylesheets/style.css`
#
    .sidebar-nav {
        margin-top: 20px;
        padding: 0;
        list-style: none;
    }

> Home page

* Update controller function to fetch "counts" of records from database and create a view to render the page.
* Use `countDocuments()` method to get the number of instances of each model.
#
    var Book = require('../models/book');
    var Author = require('../models/author');
    var Genre = require('../models/genre');
    var BookInstance = require('../models/bookinstance');

    var async = require('async');

    exports.index = function(req, res) {   

        async.parallel({
            book_count: function(callback) {
                Book.countDocuments({}, callback); // Pass an empty object as match condition to find all documents of this collection
            },
            book_instance_count: function(callback) {
                BookInstance.countDocuments({}, callback);
            },
            book_instance_available_count: function(callback) {
                BookInstance.countDocuments({status:'Available'}, callback);
            },
            author_count: function(callback) {
                Author.countDocuments({}, callback);
            },
            genre_count: function(callback) {
                Genre.countDocuments({}, callback);
            }
        }, function(err, results) {
            res.render('index', { title: 'Local Library Home', error: err, data: results });
        });
    };
* The final callback is invoked with the counts in the results parameter(记得在app.js连接服务器）

> List Page
* bookController.js
#
    // Display list of all Books.
    exports.book_list = function(req, res, next) {

      Book.find({}, 'title author')
        .populate('author')
        .exec(function (err, list_books) {
          if (err) { return next(err); }
          //Successful, so render
          res.render('book_list', { title: 'Book List', book_list: list_books });
        });

    };
* book_list.jade
#
    extends layout

    block content
      h1= title

      ul
        each book in book_list
          li 
            a(href=book.url) #{book.title} 
            |  (#{book.author.name})

        else
          li There are no books
* The bookinstance, author, genre are the same

> Detail Page
* genreController.js
#
    // Display detail page for a specific Genre.
    exports.genre_detail = function(req, res, next) {

        async.parallel({
            genre: function(callback) {
                Genre.findById(req.params.id)
                  .exec(callback);
            },

            genre_books: function(callback) {
              Book.find({ 'genre': req.params.id })
              .exec(callback);
            },

        }, function(err, results) {
            if (err) { return next(err); }
            if (results.genre==null) { // No results.
                var err = new Error('Genre not found');
                err.status = 404;
                return next(err);
            }
            // Successful, so render
            res.render('genre_detail', { title: 'Genre Detail', genre: results.genre, genre_books: results.genre_books } );
        });

    };
* genre_detail.jade
#
    extends layout
    
    block content

      h1 Genre: #{genre.name}

      div(style='margin-left:20px;margin-top:20px')

        h4 Books

        dl
          each book in genre_books
            dt 
              a(href=book.url) #{book.title}
            dd #{book.summary}

          else
            p This genre has no books
    T

* Others are basically same.

> Working with Forms
* Form format
#
    <form action="/team_name_url/" method="post">
      <label for="team_name">Enter name:</label>
      <input id="team_name" type = "text" name="name_field" val="Default name for team.">
      <input type="submit" value="OK">
    </form>
    
* Genre Form
* Update the genre_create_get in genreController
* Get这里就是去views那里拿jade格式了，之前已经设置好路径了
#
    exports.genre_create_get = function(req, res, next) {     
      res.render('genre_form', { title: 'Create Genre' });
    };
* Remember to require body, validationResult and sanitizeBody
#
    const { body,validationResult } = require('express-validator/check');
    const { sanitizeBody } = require('express-validator/filter');
* Update genre_create_post, post route, genreController.js
#
    exports.genre_create_post = [
      //Validate that the name field is not empty
      body('name','Genre name required').isLength({min:1}).trim(),

      //Sanitize the name field
      sanitizeBody('name').trim().escape(),

      //Process request after validation and sanitization
      //Arrow functions are a short syntax basically same sa function(){}
      (req,res,next) => {
        //Extract the validation errors from a request
        const errors=validationResult(req);

        //Create a genre object with escaped and trimmed data
        var genre = new Genre(
        {
          name: req.body.name
        });

        if(!errors.isEmpty()){
          //There are errors. Render the form again with sanitized values/error messages.
          res.render('genre_form',{title:'Create Genre',genre:genre, errors: errors.array()});
          return;
        }
        else{
          //Data from form is valid
          //Check if Genre with same name already exists
          Genre.findOne({'name': req.body.name})
            .exec(function(err,found_genre){
              if(err){return next(err);}
              if(found_genre){
                res.redirect(found_genre.url);
              }
              else{
                genre.save(function(err){
                  if(err){return next(err);}
                  //Genre saved and redirect to genre detail page.
                  res.redirect(genre.url);
                });
              }
            })
        }
      }
    ];
* genre_form.jade
#
    extends layout

    block content
      h1 #{title}

      form(method='POST' action='')
        div.form-group
          label(for='name') Genre:
          input#name.form-control(type='text', placeholder='Fantasy, Poetry etc.' name='name' value=(undefined===genre ? '' : genre.name))
        button.btn.btn-primary(type='submit') Submit

      if errors 
       ul
        for error in errors
         li!= error.msg
* Author form, book form and others are basically the same.

> Delete Author form
* authorController - get route
* req.params.id - the id of the Author instance to be deleted from the URL params, 尾号
#
    // Display Author delete form on GET.
    exports.author_delete_get = function(req, res, next) {

        async.parallel({
            author: function(callback) {
                Author.findById(req.params.id).exec(callback)
            },
            authors_books: function(callback) {
              Book.find({ 'author': req.params.id }).exec(callback)
            },
        }, function(err, results) {
            if (err) { return next(err); }
            if (results.author==null) { // No results.
                res.redirect('/catalog/authors');
            }
            // Successful, so render.
            res.render('author_delete', { title: 'Delete Author', author: results.author, author_books: results.authors_books             } );
        });

    };
* authorController - post route
#
    // Handle Author delete on POST.
    exports.author_delete_post = function(req, res, next) {

        async.parallel({
            author: function(callback) {
              Author.findById(req.body.authorid).exec(callback)
            },
            authors_books: function(callback) {
              Book.find({ 'author': req.body.authorid }).exec(callback)
            },
        }, function(err, results) {
            if (err) { return next(err); }
            // Success
            if (results.authors_books.length > 0) {
                // Author has books. Render in same way as for GET route.
                res.render('author_delete', { title: 'Delete Author', author: results.author, author_books: results.authors_books } );
                return;
            }
            else {
                // Author has no books. Delete object and redirect to the list of authors.
                Author.findByIdAndRemove(req.body.authorid, function deleteAuthor(err) {
                    if (err) { return next(err); }
                    // Success - go to author list
                    res.redirect('/catalog/authors')
                })
            }
        });
    };
* author_delete.jade
#
    extends layout

    block content
      h1 #{title}: #{author.name}
      p= author.lifespan

      if author_books.length

        p #[strong Delete the following books before attempting to delete this author.]

        div(style='margin-left:20px;margin-top:20px')

          h4 Books

          dl
          each book in author_books
            dt 
              a(href=book.url) #{book.title}
            dd #{book.summary}

      else
        p Do you really want to delete this Author?

        form(method='POST' action='')
          div.form-group
            input#authorid.form-control(type='hidden',name='authorid', required='true', value=author._id )

          button.btn.btn-primary(type='submit') Delete
* add this to author_detail.jade
#
    hr
    p
      a(href=author.url+'/delete') Delete author
* Others are the same

* Update is basically the same.

