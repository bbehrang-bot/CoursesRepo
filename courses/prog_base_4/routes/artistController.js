var express = require('express');
var router = express.Router();
var path = require('path');
var mongoose = require('mongoose');
var fs = require('fs-extra');
Artist = require('../models/artists.js');
var ArtistModel = mongoose.model("Artist");
var multer = require('multer');
var mkdirp = require('mkdirp');
//API
router.get('/api',function(req,res){
    Artist.getArtistsFullInfoByName("drake",function(err,callback){
      if(err)
      {
        res.json('Error');
      }
      res.json(callback.albums);
    });

});
router.get('/add',function(req,res){
    res.render("Artist/Add")
});
router.post('/add',function(req,res){
  var storage = multer.diskStorage({
    destination: function (req, file, cb) {
      //cb(null, 'artistsMedia/drake/songs')
      var dir = 'artistsMedia/' + req.body.name.toLowerCase()+ '/images';
      mkdirp(dir,err => cb(err,dir))
    },
    filename: function (req, file, cb) {
      console.log(file);
      cb(null, req.body.name.toLowerCase() +'-'+ file.fieldname +'-'+ Date.now() + path.extname(file.originalname)) //Appending extension
    },

  });
  var upload = multer({
    storage: storage,
    limits :{fileSize :52428800}
  }).fields([{name:'Logo',maxCount:1},{name:'artistHome',maxCount:1},{name:'otherImgs',maxCount:10}]);
  upload(req,res,function(err)
  {
    //console.log(req.files);
    //console.log(req.files.fieldname);
    if(err)
      res.render('Error/somethingwrong',{error:err});
      else{
        Artist.getArtistLastPriority(function(err,lastprio){
          if(err)
          {
          res.render('Error/somethingwrong',{error:err});
          }
          else{
            var lastPr = lastprio.priority;
            console.log(lastprio);
            var artist = new ArtistModel({
              name : req.body.name.toLowerCase(),
              description:req.body.description,
              images:{
                artistPage:'/' +req.files['artistHome'][0].destination + '/'+req.files['artistHome'][0].filename,
                logo: '/' +req.files['Logo'][0].destination + '/'+req.files['Logo'][0].filename,
                otherImgs:[]
              }
            });
            console.log(artist);
            for(var i=0;i<req.files['otherImgs'].length;i++)
            {
              artist.images.otherImgs.push('/' + req.files['otherImgs'][i].destination + '/'+req.files['otherImgs'][i].filename)
            }
            Artist.addArtist(artist,function(err,callback){
              if(err)
              {
                res.render('Error/somethingwrong',{error:err});
              }
              else{
                res.send("created");
              }
            });
          }
        });
      }
  });
});
router.post('/add/aristName',function(req,res){
  Artist.getArtistByName(req.body.name,function(err,callback){
    if(err)
    {
      res.render('Error/somethingwrong',{error:err});
    }
    res.send({artist:callback});
  });
});
router.post('/albums',function(req,res){
    var name = req.body.name;
    Album.getAlbumsByArtist(name,function(err,albums){
      if(err)
      {
        res.render('Error/somethingwrong',{error:err});
      }
      else{
        res.send({albums:albums});
      }
    });
});
router.post('/songs',function(req,res){
    var name = req.body.name;
    Song.findSongByArtistName(name,function(err,songs){
      if(err)
      {
        res.render('Error/somethingwrong',{error:err});
      }
      else{
        res.send({songs:songs});
      }
    });
});
router.post('/albums/songs',function(req,res){
    var artistName = req.body.artistName;
    var albumName =  req.body.albumName
    Album.getAllAlbumsSongsByName(artistName,albumName,function(err,albums){
      if(err)
      {
        res.render('Error/somethingwrong',{error:err});
      }
      else{
        res.send({albums:albums});
      }
    });
});
router.get('/:name',function(req,res){
  var name = req.params.name.toLowerCase();
  Artist.getArtistByName(name,function(err,artist){
    if(err)
    {
      res.render('Error/somethingwrong',{error:err});
    }
    else
    {
      if(artist == null || typeof(artist) == 'undefined')
      {
        res.render('Error/somethingwrong',{error:"Artist not found."});
      }
      else{
        res.render('Artist/Details',{artist:artist});
      }
    }
  });

});

module.exports = router;
