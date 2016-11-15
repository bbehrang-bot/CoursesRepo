var express = require('express');
var path = require('path');
var cookiePaser = require('cookie-parser');
var bodyParser = require('body-parser');
var mongoose = require('mongoose');
var expressValidator = require('express-validator');
var session = require('express-session');
var passport = require('passport');
var flash = require('connect-flash');
var LocalStrategy = require('passport-local').Strategy;
var route = express.Router();
mongoose.connect('mongodb://localhost/loginapp');
//Models

//Song = require('./models/songs.js');
//Album = require('./models/albums.js');
//Models
var indexController = require('./routes/indexController.js');
var songController = require('./routes/songController.js');
var albumController = require('./routes/albumController.js');
var artistController = require('./routes/artistController.js');
var userController = require('./routes/userController.js');
//var songController = require('./routes/artistController.js');
//connect to mongoose

var db = mongoose.connection;
db.on('error', console.error);
db.once('open', function() {
  // Create your schemas and models here.
});
// view engine setup
var app = express();
app.use(bodyParser.json());
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');
app.use("/media",express.static(path.join(__dirname + '/media')));
app.use(passport.initialize());
app.use(passport.session());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));
app.use(session({
    secret: 'secret',
    saveUninitialized: true,
    resave: true
}));
// Express Validator
app.use(expressValidator({
  errorFormatter: function(param, msg, value) {
      var namespace = param.split('.')
      , root    = namespace.shift()
      , formParam = root;

    while(namespace.length) {
      formParam += '[' + namespace.shift() + ']';
    }
    return {
      param : formParam,
      msg   : msg,
      value : value
    };
  }
}));
// Connect Flash
app.use(flash());

// Global Vars
app.use(function (req, res, next) {
  res.locals.success_msg = req.flash('success_msg');
  res.locals.error_msg = req.flash('error_msg');
  res.locals.error = req.flash('error');
  res.locals.user = req.user || null;
  next();
});
app.use(cookiePaser());
app.use('/',indexController);
app.use('/artists',artistController);
app.use('/albums',albumController);
app.use('/users',userController);

//app.use('/songs',songController);


//////
/*app.get('/artists',function(req,res){
  Artist.getArtistsFull(function(err,artists)
  {
    console.log(artists);
  });

});
app.get('/songs',function(req,res){


});
app.get('/albums',function(req,res){
  Album.getAlbums(function(err,albums)
  {
    if(err)
      throw err;
      Song.getSongById(albums.songs[0],function(err,albums)
      {
        if(err)
          throw err;
          //let artistList = JSON.parse(artists);
          res.render('home/arists',{albumArr : albums});
      });
  });


});
app.get('/',function(req,res){
  res.render('Home/index');
});*/

app.listen(8080);
console.log('8080 is the magic port');
