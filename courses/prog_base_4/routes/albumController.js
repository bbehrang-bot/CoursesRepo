var express = require('express');
var router = express.Router();
var path = require('path');
var mongoose = require('mongoose');
Artist = require('../models/artists');
var ArtistModel = mongoose.model("Artist");
Album = require('../models/albums');
var AlbumModel = mongoose.model("Album");
Song = require('../models/songs');
var SongModel = mongoose.model("Song");
var multer = require('multer');
var mkdirp = require('mkdirp');
router.get('/',function(req,res)
{
  Album.getAlbums(function(err,callback){
    res.json(callback);
  });
});
router.get('/add',function(req,res)
{
  res.render("Album/Add/AlbumAdd");
});
router.post('/add/submit',function(req,res){
  Artist.getArtistsFullInfoByName(req.body.name,function(err,artist){
    if(err)
    {
      res.render('Error/somethingwrong',{error:err});
    }
    else
    {
      res.send({artist:artist});
    }
  });
});
router.post('/add',function(req,res){
  var storage = multer.diskStorage({
    destination: function (req, file, cb) {
      //cb(null, 'artistsMedia/drake/songs')
      var dir = 'artistsMedia/' + req.body.name+ '/albums/' + req.body.albumName;
      mkdirp(dir,err => cb(err,dir))
    },
    filename: function (req, file, cb) {
      cb(null, req.body.name +'_'+ req.body.albumName +'_'+ file.originalname) //Appending extension
    },

  });
  var upload = multer({
    storage: storage,
  }).fields([{name:'coverArt',maxCount:1},{name:'songs',maxCount:20}]);
  upload(req,res,function(err)
  {
    if(err)
      res.render('Error/somethingwrong',{error:err});
      else{
        var album = new AlbumModel({
          name : req.body.albumName.toLowerCase(),
          coverArt : '/' +req.files['coverArt'][0].destination + '/' + req.files['coverArt'][0].filename,
          price : req.body.price,
          description:req.body.description,
          artist:req.body.name.toLowerCase(),
          genre:req.body.genre,
          songs:[]
        });
        for(var i=0;i<req.files['songs'].length;i++)
        {
          var song = new SongModel({
            name : req.files['songs'][i].originalname,
            album : req.body.albumName,
            artist:req.body.name.toLowerCase(),
            songPath : '/' +req.files['songs'][i].destination + '/'+req.files['songs'][i].filename
          });
          album.songs.push(song);
          Song.addSong(song,function(err,callback){
            if(err)
            {
              res.render('Error/somethingwrong',{error:err});
            }
          });
        }
        Album.addAlbum(album,function(err,albumAdded){
          if(err)
          {
            res.render('Error/somethingwrong',{error:err});

          }
          else{
            Artist.updateArtistByName(req.body.name,album,function(err,artistAdded){
              if(err)
              {
                res.render('Error/somethingwrong',{error:err});
              }
              else{
                res.json(artistAdded);
              }
            });
          }
        });
      }

  });
});
router.post('/add/artist',function(req,res)
{
  var name = req.body.name;
  Artist.searchArtistsByName(name,function(err,artists){
    if(err)
    {
      throw err;
    }
    else{
      res.send({artists:artists});
    }
  });
});
module.exports = router;
