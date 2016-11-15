var express = require('express');
var router = express.Router();
var path = require('path');

router.all('/',function(req,res)
{
  res.render('home/index');
});
module.exports = router;
