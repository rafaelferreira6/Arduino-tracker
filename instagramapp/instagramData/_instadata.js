import {instagram} from './_instagram_auth';

//Get Data User
const getDataUser = access_token => {
  instagram.get('users/self', { access_token: access_token }, (err, data) => {
    //setInterval(function(){console.log(data)},10000);
  });
}

//Get Data by Tags
const getDataTags = (access_token, tagName) => {
  instagram.get('tags/'+tagName+'/media/recent', { access_token: access_token}, (err, data) => {
    if(data.data.length>0)
    console.log(data)
    else
    console.log("No-Data");
  });
}

export {getDataUser, getDataTags}
