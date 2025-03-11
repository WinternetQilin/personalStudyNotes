"use strict";
const common_vendor = require("../common/vendor.js");
function getImgSrc(richtext, num = 3) {
  let imgList = [];
  richtext.replace(/<img [^>]*src=['"]([^'"]+)[^>]*>/g, (match, capture) => {
    imgList.push(capture);
  });
  imgList = imgList.slice(0, num);
  return imgList;
}
function getProvince() {
  return new Promise((resolve, reject) => {
    let historyProvince = common_vendor.index.getStorageSync("historyProvince");
    if (historyProvince) {
      if (Date.now() - historyProvince.time > 1e3 * 60 * 60) {
        getIp().then((res) => {
          resolve(res);
        }).catch((err) => {
          reject(err);
        });
      } else {
        resolve(historyProvince.province);
      }
    } else {
      getIp().then((res) => {
        resolve(res);
      }).catch((err) => {
        reject(err);
      });
    }
  });
}
function getIp() {
  return new Promise((resolve, reject) => {
    common_vendor.index.request({
      url: "https://restapi.amap.com/v3/ip?key=7202a754ec3c0a87e7a503b64e8cac2c",
      success: (res) => {
        let str = "";
        typeof res.data.province == "string" ? str = res.data.province : str = "火星";
        resolve(str);
        let obj = {
          province: str,
          time: Date.now()
        };
        common_vendor.index.setStorageSync("historyProvince", obj);
      },
      fail: (err) => {
        reject(err);
      }
    });
  });
}
function getNickName(item) {
  return item.user_id[0].nickname || item.user_id[0].username || item.user_id[0].mobile || "匿名用户";
}
function getAvatar(item) {
  var _a, _b;
  return ((_b = (_a = item.user_id[0]) == null ? void 0 : _a.avatar_file) == null ? void 0 : _b.url) ?? "../../static/images/user-default.jpg";
}
exports.getAvatar = getAvatar;
exports.getImgSrc = getImgSrc;
exports.getNickName = getNickName;
exports.getProvince = getProvince;
