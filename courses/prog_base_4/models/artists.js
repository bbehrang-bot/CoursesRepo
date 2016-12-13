var mongoose = require('mongoose');
var artistsSchema = mongoose.Schema({
  name:{
    type:String,
    required:true
  },
  description:{
    type:String
  },
  albums:{
    type:[{type:mongoose.Schema.Types.ObjectId,ref :'Album'}]
  },
  priority:{
    type:Number
  },
  images:{
    artistPage : {type:String},
    logo : {type:String},
    otherImgs : [{type:String}]
  }
});
var Artist = module.exports =  mongoose.model('Artist',artistsSchema);
//Get artists

//Index page methods
module.exports.getArtistsByPriority = function(lastPriority,limit,callback){
  var query = {"priority" : 1}
  Artist.find({priority : {$gt:lastPriority}}).sort(query).limit(limit).exec(callback);
}
module.exports.getArtistLastPriority = function(callback){
  var query = {"priority" : -1}
  Artist.find().sort(query).limit(1).exec(callback);
}
module.exports.getArtists = function(limit,callback){
  Artist.find(callback).limit(limit);
}
module.exports.getArtistById = function(id,callback){
  Artist.findById(id,callback);
}

module.exports.searchArtistsByName = function(name,limit,callback){
  var query = {'name' : new RegExp('^'+name,"i")}
  Artist.find(query,callback).limit(limit);
}
module.exports.getArtistByName = function(name,callback)
{
  var query = {name : name};
  Artist.findOne(query,callback);
}
