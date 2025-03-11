"use strict";
const common_vendor = require("../../common/vendor.js");
const common_assets = require("../../common/assets.js");
const utils_tools = require("../../utils/tools.js");
if (!Array) {
  const _easycom_uni_dateformat2 = common_vendor.resolveComponent("uni-dateformat");
  const _easycom_uv_parse2 = common_vendor.resolveComponent("uv-parse");
  (_easycom_uni_dateformat2 + _easycom_uv_parse2)();
}
const _easycom_uni_dateformat = () => "../../uni_modules/uni-dateformat/components/uni-dateformat/uni-dateformat.js";
const _easycom_uv_parse = () => "../../uni_modules/uv-parse/components/uv-parse/uv-parse.js";
if (!Math) {
  (_easycom_uni_dateformat + _easycom_uv_parse)();
}
const _sfc_main = {
  __name: "detail",
  setup(__props) {
    const forumCloudObj = common_vendor.Zs.importObject("forumCloudObj", {
      customUI: true
    });
    let detail = common_vendor.ref({});
    let likeStatus = common_vendor.ref(false);
    common_vendor.onLoad(async (e) => {
      if (!e.id) {
        errFunc();
      }
      let res = null;
      try {
        res = await forumCloudObj.getArticleDetail(e.id);
      } catch (e2) {
        common_vendor.index.showModal({
          title: "错误",
          content: e2.errMsg,
          showCancel: false
        });
      }
      if (!res.data) {
        errFunc();
      }
      detail.value = res.data;
      common_vendor.index.setNavigationBarTitle({
        title: detail.value.title
      });
      forumCloudObj.operation("forum_article", "view_count", detail.value._id, 1);
      likeStatus.value = await forumCloudObj.likeArticleStatus(detail.value._id, detail.value.user_id[0]._id);
    });
    function errFunc() {
      common_vendor.index.showToast({
        title: "参数有误",
        icon: "error"
      });
      setTimeout(() => {
        common_vendor.index.reLaunch({
          url: "/pages/index/index"
        });
      }, 1500);
    }
    let clickTiming = false;
    async function onClickLike() {
      if (clickTiming) {
        common_vendor.index.showToast({
          title: "操作过于频繁",
          icon: "none"
        });
        return;
      }
      likeStatus.value ? detail.value.like_count-- : detail.value.like_count++;
      likeStatus.value = !likeStatus.value;
      clickTiming = true;
      likeStatus.value = await forumCloudObj.likeArticle(detail.value._id, detail.value.user_id[0]._id);
      if (likeStatus.value) {
        forumCloudObj.operation("forum_article", "like_count", detail.value._id, 1);
      } else {
        forumCloudObj.operation("forum_article", "like_count", detail.value._id, -1);
      }
      clickTiming = false;
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.unref(detail) != {}
      }, common_vendor.unref(detail) != {} ? common_vendor.e({
        b: common_vendor.t(common_vendor.unref(detail).title),
        c: common_vendor.unref(detail).user_id
      }, common_vendor.unref(detail).user_id ? {
        d: common_vendor.unref(utils_tools.getAvatar)(common_vendor.unref(detail))
      } : {}, {
        e: common_vendor.unref(detail).user_id
      }, common_vendor.unref(detail).user_id ? {
        f: common_vendor.t(common_vendor.unref(utils_tools.getNickName)(common_vendor.unref(detail)))
      } : {}, {
        g: common_vendor.p({
          date: common_vendor.unref(detail).publish_date,
          format: "yyyy年MM月dd hh:mm"
        }),
        h: common_vendor.t(common_vendor.unref(detail).province),
        i: common_vendor.p({
          content: common_vendor.unref(detail).content
        }),
        j: common_vendor.t(common_vendor.unref(detail).like_count),
        k: common_vendor.n(common_vendor.unref(likeStatus) ? "active" : ""),
        l: common_assets._imports_0$2,
        m: common_vendor.t(common_vendor.unref(detail).view_count + 1),
        n: common_vendor.o(onClickLike)
      }) : {});
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-eca06f3c"]]);
wx.createPage(MiniProgramPage);
