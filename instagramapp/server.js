// Base: https://github.com/pradel/node-instagram

const express = require('express');
const Instagram = require('node-instagram').default;
const app = express();
import {instagram} from './instagramData/_instagram_auth';
import startScript from './script';

const redirectUri = 'http://localhost:8080/auth/instagram/callback';

app.get('/auth/instagram', (req, res) => {
  res.redirect(instagram.getAuthorizationUrl(redirectUri, { scope: ['basic', 'public_content'] }));
});

app.get('/auth/instagram/callback', async (req, res) => {
  try {
    const data = await instagram.authorizeUser(req.query.code, redirectUri);
    startScript(data["access_token"]);
    //getDataTags(data["access_token"], 'bnm');
  } catch (err) {
    res.json(err);
  }
});

app.listen(8080, () => {
  console.log('app listening on http://localhost:8080');
});
