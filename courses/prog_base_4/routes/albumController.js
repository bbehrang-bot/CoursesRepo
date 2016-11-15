var express = require('express');
var router = express.Router();
var path = require('path');
var mongoose = require('mongoose');
Album = require('../models/albums.js');
router.all('/',function(req,res)
{
  Album.getAlbumsWithSongsc(function(err,callback){
    res.json(callback);
  });
});
module.exports = router;
