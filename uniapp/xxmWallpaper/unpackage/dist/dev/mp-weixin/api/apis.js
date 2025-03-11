"use strict";
const utils_request = require("../utils/request.js");
function apiGetBannerPics() {
  return utils_request.request({
    url: "/homeBanner"
  });
}
function apiGetRecommendPics() {
  return utils_request.request({
    url: "/randomWall"
  });
}
function apiGetNoticeList() {
  return utils_request.request({
    url: "/wallNewsList"
  });
}
function apiGetThemeList(data = {}) {
  return utils_request.request({
    url: "/classify",
    data
  });
}
function apiGetClassifyPicList(data = {}) {
  return utils_request.request({
    url: "/wallList",
    data
  });
}
function apiGetSetupScore(data = {}) {
  return utils_request.request({
    url: "/setupScore",
    data
  });
}
function apiWriteDownload(data = {}) {
  return utils_request.request({
    url: "/downloadWall",
    data
  });
}
function apiGetUserInfo(data = {}) {
  return utils_request.request({
    url: "/userInfo",
    data
  });
}
function apiSearchData(data = {}) {
  return utils_request.request({
    url: "/searchWall",
    data
  });
}
exports.apiGetBannerPics = apiGetBannerPics;
exports.apiGetClassifyPicList = apiGetClassifyPicList;
exports.apiGetNoticeList = apiGetNoticeList;
exports.apiGetRecommendPics = apiGetRecommendPics;
exports.apiGetSetupScore = apiGetSetupScore;
exports.apiGetThemeList = apiGetThemeList;
exports.apiGetUserInfo = apiGetUserInfo;
exports.apiSearchData = apiSearchData;
exports.apiWriteDownload = apiWriteDownload;
