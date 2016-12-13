var mongoose = require('mongoose');
var songsSchema = mongoose.Schema({
  name:{
    type:String,
    required:true,
    default : null
  },
  listened:{
    type:Number,
    default:0
  },
  price:{
    type:Number,
    default :0
  },
  trackNumber:{
    type:Number,
    defualt : 1
  },
  lyrics:{
    type:String,
    default : null
  },
  songPath:{
    type:String,
    default : null
  }
  /*album:{
    type:[{type:mongoose.Schema.Types.ObjectId,ref :'Album'}]
  }*/


});
var Song = module.export = mongoose.model('Song',songsSchema);
//Get artists
module.exports.getSongs = function(callback,limit){
  Song.find(callback).limit(limit);
}
module.exports.getSongById = function(id,callback){
  Song.findById(id,callback);
}
module.exports.addSong = function(song,callback){
  Song.create(song,callback);
}
module.exports.updateSong = function(id,song,options,callback){
  var query = {_id :id };
  var update = {'$set' :song};
  Song.findOneAndUpdate(query,update,options,callback);
}
