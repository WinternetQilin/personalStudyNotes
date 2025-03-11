"use strict";
const common_vendor = require("../../common/vendor.js");
const api_apis = require("../../api/apis.js");
if (!Array) {
  const _easycom_custom_nav_bar2 = common_vendor.resolveComponent("custom-nav-bar");
  const _easycom_uni_icons2 = common_vendor.resolveComponent("uni-icons");
  const _easycom_uni_dateformat2 = common_vendor.resolveComponent("uni-dateformat");
  const _easycom_common_title2 = common_vendor.resolveComponent("common-title");
  const _easycom_theme_item2 = common_vendor.resolveComponent("theme-item");
  (_easycom_custom_nav_bar2 + _easycom_uni_icons2 + _easycom_uni_dateformat2 + _easycom_common_title2 + _easycom_theme_item2)();
}
const _easycom_custom_nav_bar = () => "../../components/custom-nav-bar/custom-nav-bar.js";
const _easycom_uni_icons = () => "../../uni_modules/uni-icons/components/uni-icons/uni-icons.js";
const _easycom_uni_dateformat = () => "../../uni_modules/uni-dateformat/components/uni-dateformat/uni-dateformat.js";
const _easycom_common_title = () => "../../components/common-title/common-title.js";
const _easycom_theme_item = () => "../../components/theme-item/theme-item.js";
if (!Math) {
  (_easycom_custom_nav_bar + _easycom_uni_icons + _easycom_uni_dateformat + _easycom_common_title + _easycom_theme_item)();
}
const _sfc_main = {
  __name: "index",
  setup(__props) {
    let bannerPics = common_vendor.ref([]);
    let recommendPics = common_vendor.ref([]);
    let noticeList = common_vendor.ref([]);
    let themeList = common_vendor.ref([]);
    function goPreview() {
      common_vendor.index.setStorageSync("classifyPicList", recommendPics.value);
    }
    common_vendor.onShareAppMessage(() => {
      return {
        title: "xxm壁纸",
        path: "/pages/index/index"
      };
    });
    common_vendor.onShareTimeline(() => {
      return {
        title: "xxm壁纸!!!"
      };
    });
    async function getBannerPics() {
      let temp = await api_apis.apiGetBannerPics();
      bannerPics.value = temp.data;
    }
    async function getRecommendPics() {
      let temp = await api_apis.apiGetRecommendPics();
      recommendPics.value = temp.data;
    }
    async function getNoticeList() {
      let temp = await api_apis.apiGetNoticeList();
      noticeList.value = temp.data;
    }
    async function getThemeList() {
      let temp = await api_apis.apiGetThemeList();
      themeList.value = temp.data;
      console.log(themeList.value);
    }
    common_vendor.onLoad(() => {
      getBannerPics();
      getRecommendPics();
      getNoticeList();
      getThemeList();
    });
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.p({
          title: "推荐"
        }),
        b: common_vendor.f(common_vendor.unref(bannerPics), (item, k0, i0) => {
          return {
            a: item.picurl,
            b: item._id
          };
        }),
        c: common_vendor.p({
          type: "sound-filled",
          size: "25",
          color: "#28B48F"
        }),
        d: common_vendor.f(common_vendor.unref(noticeList), (item, k0, i0) => {
          return {
            a: common_vendor.t(item.title),
            b: item._id
          };
        }),
        e: common_vendor.p({
          type: "right",
          size: "20",
          color: "#A7A7A7"
        }),
        f: common_vendor.p({
          type: "calendar",
          size: "30"
        }),
        g: common_vendor.p({
          date: Date.now(),
          format: "dd",
          threshold: [0, 0]
        }),
        h: common_vendor.f(common_vendor.unref(recommendPics), (item, k0, i0) => {
          return {
            a: item.smallPicurl,
            b: "/pages/preview/preview?id=" + item._id,
            c: common_vendor.o(goPreview, item._id),
            d: item._id
          };
        }),
        i: common_vendor.unref(themeList)
      }, common_vendor.unref(themeList) ? {
        j: common_vendor.f(common_vendor.unref(themeList), (item, k0, i0) => {
          return common_vendor.e({
            a: item.name != "AI美图"
          }, item.name != "AI美图" ? {
            b: "1cf27b2a-7-" + i0,
            c: common_vendor.p({
              item
            })
          } : {}, {
            d: item._id
          });
        }),
        k: common_vendor.p({
          isMore: true
        })
      } : {});
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-1cf27b2a"]]);
_sfc_main.__runtimeHooks = 6;
wx.createPage(MiniProgramPage);
