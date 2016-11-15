var express = require('express');
var router = express.Router();
var path = require('path');
var mongoose = require('mongoose');
Artist = require('../models/artists.js');
router.get('/',function(req,res)
{
  Artist.getArtistsFull(function(err,callback){
    res.json(callback);
  });
});
module.exports = router;
