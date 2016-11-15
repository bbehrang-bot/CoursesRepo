var mongoose = require('mongoose');
console.log('songs');
var songsSchema = mongoose.Schema({
  name:{
    type:String,
    required:true
  },
  listened:{
    type:Number
  },
  price:{
    type:Number
  },
  order:{
    type:Number
  }
  /*album:{
    type:[{type:mongoose.Schema.Types.ObjectId,ref :'Album'}]
  }*/


});
var Song = module.export = mongoose.model('Song',songsSchema);
//Get artists
module.exports.getSongs = function(callback){
  Song.find(callback);
}
module.exports.getSongById = function(id,callback){
  Song.findById(id,callback);
}
