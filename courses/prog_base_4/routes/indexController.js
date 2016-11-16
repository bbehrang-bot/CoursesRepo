var express = require('express');
var router = express.Router();
var path = require('path');

router.all('/',ensureAuthenticated,function(req,res)
{
  res.render('home/index');
});
function ensureAuthenticated(req,res,next){
  if(req.isAuthenticated())
    return next();
    else{
      req.flash('error','You are not logged in');
      res.redirect('/users/login');
    }
}
module.exports = router;
