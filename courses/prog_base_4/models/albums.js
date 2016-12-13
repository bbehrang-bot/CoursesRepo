var mongoose = require('mongoose');
var albumsSchema = mongoose.Schema({
  name:{
    type:String,
    required:true
  },
  coverArt : {
    type:String,
    default : null
  },
  description:{
    type:String,
    default : null
  },
  genre:{
    type:[String]
  },
  artist:{
    type:String,
    required : true
  },
  songs:{
    type:[{type:mongoose.Schema.Types.ObjectId,ref :'Song'}]
  }
});
var Album = module.exports =  mongoose.model('Albums',albumsSchema);
//Get artists
module.exports.getAlbums = function(callback,limit){
  Album.find(callback).limit(limit);
}
module.exports.getAlbumsByArtist = function(artist,callback)
{
  var query = {artist : artist};
  Album.find(query,callback);
}
module.exports.getAlbumById = function(id,callback){
  Album.findById(id,callback);
}
module.exports.getAlbumSongsById = function(id,callback,limit){
  Album.findById(id)
      .populate({
      path : 'songs',
      populate :{path:'songs'}
    }).exec(callback);

}
module.exports.getAlbumInfoByName = function(artistName,albumName,callback){
  var query = {artist:artistName,name:albumName}
  Album.findOne(query)
  .populate({path : 'songs',populate :{path:'songs'}}).exec(callback);

}
module.exports.getAllAlbumsSongs = function(callback,limit){
  Album.find()
      .populate({
      path : 'songs'
      ,populate :{path:'songs'}
    }).exec(callback);
}
