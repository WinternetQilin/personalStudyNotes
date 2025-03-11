"use strict";
const common_vendor = require("../../common/vendor.js");
const common_assets = require("../../common/assets.js");
const utils_system = require("../../utils/system.js");
const api_apis = require("../../api/apis.js");
if (!Array) {
  const _easycom_uni_icons2 = common_vendor.resolveComponent("uni-icons");
  const _easycom_option_item2 = common_vendor.resolveComponent("option-item");
  (_easycom_uni_icons2 + _easycom_option_item2)();
}
const _easycom_uni_icons = () => "../../uni_modules/uni-icons/components/uni-icons/uni-icons.js";
const _easycom_option_item = () => "../../components/option-item/option-item.js";
if (!Math) {
  (_easycom_uni_icons + _easycom_option_item)();
}
const _sfc_main = {
  __name: "user",
  setup(__props) {
    let userInfo = common_vendor.ref(null);
    async function getUserInfo() {
      let temp = await api_apis.apiGetUserInfo();
      userInfo.value = temp.data;
    }
    getUserInfo();
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.unref(userInfo)
      }, common_vendor.unref(userInfo) ? {
        b: common_vendor.unref(utils_system.getStatusBarHeight)() + "px",
        c: common_assets._imports_0,
        d: common_vendor.t(common_vendor.unref(userInfo).IP),
        e: common_vendor.t(common_vendor.unref(userInfo).address.city || common_vendor.unref(userInfo).address.province || common_vendor.unref(userInfo).address.country),
        f: common_vendor.p({
          type: "download-filled",
          size: "30",
          color: "#28B38C"
        }),
        g: common_vendor.p({
          optionName: "我的下载",
          jumpUrl: "/pages/classifyList/classifyList",
          number: common_vendor.unref(userInfo).downloadSize
        }),
        h: common_vendor.p({
          type: "star-filled",
          size: "30",
          color: "#28B38C"
        }),
        i: common_vendor.p({
          optionName: "我的评分",
          jumpUrl: "/pages/classifyList/classifyList",
          number: common_vendor.unref(userInfo).scoreSize
        }),
        j: common_vendor.p({
          type: "chatboxes-filled",
          size: "30",
          color: "#28B38C"
        }),
        k: common_vendor.p({
          optionName: "联系客服"
        }),
        l: common_vendor.p({
          type: "notification-filled",
          size: "30",
          color: "#28B38C"
        }),
        m: common_vendor.p({
          optionName: "订阅更新"
        }),
        n: common_vendor.p({
          type: "flag-filled",
          size: "30",
          color: "#28B38C"
        }),
        o: common_vendor.p({
          optionName: "常见问题"
        })
      } : {});
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-0f7520f0"]]);
wx.createPage(MiniProgramPage);
