var mongoose = require('mongoose');
console.log('albums');
var albumsSchema = mongoose.Schema({
  name:{
    type:String,
    required:true
  },
  description:{
    type:String
  },
  genre:{
    type:[String]
  },
  songs:{
    type:[{type:mongoose.Schema.Types.ObjectId,ref :'Song'}]
  },
  listened:{
    type:Number
  }
});
var Album = module.exports =  mongoose.model('Albums',albumsSchema);
var AlbumSchema = module.exports = mongoose.model('Albums').schema;
//Get artists
module.exports.getAlbums = function(callback,limit){
  Album.findOne(callback);
}
module.exports.getAlbumById = function(id,callback){
  Album.findById(id,callback);
}
module.exports.getAlbumsWithSongs = function(id,callback,limit){
  Album.findById(id)
      .populate({
      path : 'songs',
      populate :{path:'songs'}
    }).exec(callback);

}
module.exports.getAlbumsWithSongsc = function(callback,limit){
  Album.find()
      .populate({
      path : 'songs'
      ,populate :{path:'songs'}
    }).exec(callback);

}
