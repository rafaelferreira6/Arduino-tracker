import {instagram} from './_instagram_auth';

const getDataUser = access_token => {
  instagram.get('users/self', { access_token: access_token }, (err, data) => {
    //setInterval(function(){console.log(data)},10000);
  });
}

const getDataTags = (access_token, tagName) => {
  instagram.get('tags/'+tagName+'/media/recent', { access_token: access_token}, (err, data) => {
    if(data.pagination.data)
    console.log(data);
    else
    console.log("No_Data");
  });
}

export {getDataUser, getDataTags}
