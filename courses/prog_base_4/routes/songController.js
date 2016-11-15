var express = require('express');
var router = express.Router();
var path = require('path');
var mongoose = require('mongoose');
Song = require('../models/songs.js');
router.all('/',function(req,res)
{
  Artist.getArtistsFull(function(err,callback){
    res.json(callback);
  });
});
module.exports = router;
