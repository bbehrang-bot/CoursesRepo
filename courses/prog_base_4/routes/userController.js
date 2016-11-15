var express = require('express');
var router = express.Router();
var path = require('path');
var mongoose = require('mongoose');
var User = require('../models/user');

router.get('/register',function(req,res)
{
  res.render('register');
});
router.get('/login',function(req,res)
{
  res.render('register');
});
router.post('/register',function(req,res)
{
  var name = req.body.name;
  var username = req.body.username;
  var email = req.body.email;
  var password = req.body.password;
  var password2 = req.body.password2;

  req.checkBody('name','Name is required').notEmpty();
  req.checkBody('username','username is required').notEmpty();
  req.checkBody('email','Email is required').notEmpty();
  req.checkBody('email','Email is not valud').isEmail();
  req.checkBody('password','password is required').notEmpty();
  req.checkBody('password2','Passwords do not match').notEmpty();
  var errors = req.validationErrors();
  if(errors)
    res.render('register',{errors : errors});
  else{
    var newUser = new User({
      name:name,
      email:email,
      username:username,
      password:password
    });
    User.createUser(newUser,function(err,user){
      if(err)
        throw err;
        console.log(user);
        req.flash('success_msg','You are registered and can now login');
        res.redirect('register');
    });
  }
});

router.post('/login',
  passport.authenticate('local'),
  function(req, res) {
    // If this function gets called, authentication was successful.
    // `req.user` contains the authenticated user.
    res.redirect('/users/' + req.user.username);
  });

module.exports = router;
