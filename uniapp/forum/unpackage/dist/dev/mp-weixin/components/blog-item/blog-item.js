"use strict";
const common_vendor = require("../../common/vendor.js");
const utils_tools = require("../../utils/tools.js");
if (!Array) {
  const _easycom_uni_dateformat2 = common_vendor.resolveComponent("uni-dateformat");
  const _easycom_uv_action_sheet2 = common_vendor.resolveComponent("uv-action-sheet");
  (_easycom_uni_dateformat2 + _easycom_uv_action_sheet2)();
}
const _easycom_uni_dateformat = () => "../../uni_modules/uni-dateformat/components/uni-dateformat/uni-dateformat.js";
const _easycom_uv_action_sheet = () => "../../uni_modules/uv-action-sheet/components/uv-action-sheet/uv-action-sheet.js";
if (!Math) {
  (_easycom_uni_dateformat + _easycom_uv_action_sheet)();
}
const _sfc_main = {
  __name: "blog-item",
  props: {
    articleItem: {
      type: Object
    }
  },
  setup(__props) {
    const forumCloudObj = common_vendor.Zs.importObject("forumCloudObj");
    let props = __props;
    let actionSheet = common_vendor.ref(null);
    let actionList = common_vendor.ref([
      {
        name: "修改",
        type: "edit",
        disabled: true
      },
      {
        name: "删除",
        type: "delete",
        color: "red",
        disabled: true
      },
      {
        name: "填充"
      }
    ]);
    let likeStatus = common_vendor.ref(false);
    likeStatus.value = function onClickActionSheet() {
      let uid = common_vendor.Zs.getCurrentUserInfo().uid;
      if (uid == props.articleItem.user_id[0]._id) {
        actionList.value[0].disabled = false;
        actionList.value[1].disabled = false;
      }
      for (let role of common_vendor.Zs.getCurrentUserInfo().role) {
        if (role == "admin" || role == "webMaster") {
          actionList.value[0].disabled = false;
          actionList.value[1].disabled = false;
        }
      }
      actionSheet.value.open();
    };
    function onSheetSelect(e) {
      console.log(e.type);
      if (e.type == "edit")
        ;
      else if (e.type == "delete") {
        common_vendor.index.showModal({
          title: "提示",
          content: "确定删除吗？",
          success: async function(res) {
            if (res.confirm) {
              forumCloudObj.deleteArticle(props.articleItem._id);
              common_vendor.index.reLaunch({
                url: "/pages/index/index"
              });
            }
          }
        });
      }
    }
    function onSheetClose() {
    }
    function onClickImg(index) {
      common_vendor.index.previewImage({
        urls: props.articleItem.picUrls,
        current: index
      });
    }
    async function onClickLike() {
      console.log(props.articleItem);
    }
    function onClickToDetail() {
      common_vendor.index.navigateTo({
        url: "/pages/detail/detail?id=" + props.articleItem._id
      });
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.unref(utils_tools.getAvatar)(__props.articleItem),
        b: common_vendor.t(common_vendor.unref(utils_tools.getNickName)(__props.articleItem)),
        c: common_vendor.p({
          date: __props.articleItem.publish_date,
          format: "MM月dd hh:mm",
          threshold: [6e4, 36e5 * 24 * 30]
        }),
        d: common_vendor.o((...args) => _ctx.onClickActionSheet && _ctx.onClickActionSheet(...args)),
        e: common_vendor.t(__props.articleItem.title),
        f: common_vendor.o(onClickToDetail),
        g: __props.articleItem.description
      }, __props.articleItem.description ? {
        h: common_vendor.t(__props.articleItem.description),
        i: common_vendor.o(onClickToDetail)
      } : {}, {
        j: __props.articleItem.picUrls.length
      }, __props.articleItem.picUrls.length ? {
        k: common_vendor.f(__props.articleItem.picUrls, (pic, index, i0) => {
          return {
            a: common_vendor.o(($event) => onClickImg(index), index),
            b: pic,
            c: index
          };
        }),
        l: common_vendor.n(__props.articleItem.picUrls.length == 1 ? "only" : "")
      } : {}, {
        m: common_vendor.t(__props.articleItem.view_count ? __props.articleItem.view_count : "抢首览"),
        n: common_vendor.t(__props.articleItem.comment_count ? __props.articleItem.comment_count : "抢首评"),
        o: common_vendor.n(__props.articleItem.isLike ? "active" : ""),
        p: common_vendor.t(__props.articleItem.like_count ? __props.articleItem.like_count : "抢首攒"),
        q: common_vendor.o(onClickLike),
        r: common_vendor.sr(actionSheet, "ed6c1afa-1", {
          "k": "actionSheet"
        }),
        s: common_vendor.o(onSheetSelect),
        t: common_vendor.o(onSheetClose),
        v: common_vendor.p({
          actions: common_vendor.unref(actionList),
          closeOnClickOverlay: true,
          safeAreaInsetBottom: true
        })
      });
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-ed6c1afa"]]);
wx.createComponent(Component);
