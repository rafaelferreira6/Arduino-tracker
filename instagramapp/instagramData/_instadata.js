import {instagram} from './_instagram_auth';

const getDataUser = access_token => {
  instagram.get('users/self', { access_token: access_token }, (err, data) => {
    //console.log(data);
  });
}

const getDataTags = (access_token, tagName) => {
  instagram.get('tags/'+tagName+'/media/recent', { access_token: access_token }, (err, data) => {
    console.log(data);
  });
}

export {getDataUser, getDataTags}
