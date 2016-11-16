var express = require('express');
var router = express.Router();
var path = require('path');
var mongoose = require('mongoose');
var passport = require('passport');
var LocalStrategy = require('passport-local').Strategy;
var User = require('../models/user');
passport.use(new LocalStrategy(
  function(username, password, done) {
    User.getUserByUsername(username,function(err,user){
      if(err)
        throw err;
      if(!user)
      {
        return done(null,false,{message:'Unknown User'});
      }
      User.comparePassword(password,user.password,function(err,isMatch){
        if(err)
        {
            throw err;
        }

        if(isMatch)
        {
            return done(null,user);
        }

        else
        {
            return done(null,false,{message:'wrong password'});
        }

      });
    });
}));

passport.serializeUser(function(user, done) {
  done(null, user.id);
});

passport.deserializeUser(function(id, done) {
  User.getUserById(id, function(err, user) {
    done(err, user);
  });
});
router.get('/register',function(req,res)
{
  res.render('register');
});
router.get('/login',function(req,res)
{
  res.render('login');
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
  passport.authenticate('local',{successRedirect:'/users/register',failureRedirect:'/users/login',failureFlash:true}),
  function(req, res) {
    res.redirect('/');
  });
router.get('/logout',function(req,res)
  {
    req.logout();
    req.flash('success_msg','you logged out');
    res.redirect('login')
  });
module.exports = router;
