"use strict";
const common_vendor = require("../../common/vendor.js");
const common_assets = require("../../common/assets.js");
const uni_modules_uniIdPages_common_store = require("../../uni_modules/uni-id-pages/common/store.js");
if (!Array) {
  const _easycom_uni_dateformat2 = common_vendor.resolveComponent("uni-dateformat");
  _easycom_uni_dateformat2();
}
const _easycom_uni_dateformat = () => "../../uni_modules/uni-dateformat/components/uni-dateformat/uni-dateformat.js";
if (!Math) {
  _easycom_uni_dateformat();
}
const _sfc_main = {
  __name: "self",
  setup(__props) {
    common_vendor.Zs.importObject("forumCloudObj");
    let hasLogin = null;
    let userInfo = null;
    common_vendor.onLoad(() => {
      hasLogin = common_vendor.computed(() => uni_modules_uniIdPages_common_store.store.hasLogin);
      userInfo = common_vendor.computed(() => uni_modules_uniIdPages_common_store.store.userInfo);
    });
    function onClickLogout() {
      common_vendor.index.showModal({
        title: "提示",
        content: "确定退出登录吗？",
        success: function(res) {
          if (res.confirm) {
            uni_modules_uniIdPages_common_store.mutations.logout();
          }
        }
      });
    }
    function onClickToList() {
      common_vendor.index.navigateTo({
        url: "/pages/forum_article/list"
      });
    }
    function onClickToLike() {
      common_vendor.index.navigateTo({
        url: "/pages/forum_like/list"
      });
    }
    function OnClickToUserInfo() {
      common_vendor.index.navigateTo({
        url: "/uni_modules/uni-id-pages/pages/userinfo/userinfo"
      });
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.unref(hasLogin) && common_vendor.unref(userInfo).avatar_file && common_vendor.unref(userInfo).avatar_file.url
      }, common_vendor.unref(hasLogin) && common_vendor.unref(userInfo).avatar_file && common_vendor.unref(userInfo).avatar_file.url ? {
        b: common_vendor.unref(userInfo).avatar_file.url
      } : {
        c: common_assets._imports_0
      }, common_vendor.e({
        d: common_vendor.t(common_vendor.unref(userInfo).nickname || common_vendor.unref(userInfo).username || common_vendor.unref(userInfo).mobile || "匿名用户"),
        e: common_vendor.unref(userInfo).register_date
      }, common_vendor.unref(userInfo).register_date ? {
        f: common_vendor.p({
          date: common_vendor.unref(userInfo).register_date,
          threshold: [3600, 99 * 365 * 24 * 60 * 60 * 1e3]
        })
      } : {}), {
        g: common_vendor.o(OnClickToUserInfo),
        h: common_vendor.unref(hasLogin) && common_vendor.unref(userInfo).avatar_file && common_vendor.unref(userInfo).avatar_file.url
      }, common_vendor.unref(hasLogin) && common_vendor.unref(userInfo).avatar_file && common_vendor.unref(userInfo).avatar_file.url ? {
        i: common_vendor.unref(userInfo).avatar_file.url
      } : {
        j: common_assets._imports_0
      }, {
        k: common_vendor.o(onClickToList),
        l: common_vendor.o(onClickToLike),
        m: common_vendor.o(onClickLogout)
      });
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-f94a969d"]]);
wx.createPage(MiniProgramPage);
