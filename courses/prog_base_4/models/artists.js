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
  listened:{
    type:Number
  }

});
var Artist = module.exports =  mongoose.model('Artist',artistsSchema);
//Get artists

module.exports.getArtists = function(callback,limit){
  Artist.find(callback).limit(limit);
}
module.exports.getArtistsFull = function(callback,limit)
{
  Artist.find().limit(1)
      .populate({
      path:'albums'
      ,populate :{path:'albums'}
    }).exec(callback);
}
