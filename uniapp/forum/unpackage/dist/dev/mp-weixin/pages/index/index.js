"use strict";
const common_vendor = require("../../common/vendor.js");
const uni_modules_uniIdPages_common_store = require("../../uni_modules/uni-id-pages/common/store.js");
if (!Array) {
  const _easycom_uv_tabs2 = common_vendor.resolveComponent("uv-tabs");
  const _easycom_uv_skeletons2 = common_vendor.resolveComponent("uv-skeletons");
  const _easycom_blog_item2 = common_vendor.resolveComponent("blog-item");
  (_easycom_uv_tabs2 + _easycom_uv_skeletons2 + _easycom_blog_item2)();
}
const _easycom_uv_tabs = () => "../../uni_modules/uv-tabs/components/uv-tabs/uv-tabs.js";
const _easycom_uv_skeletons = () => "../../uni_modules/uv-skeletons/components/uv-skeletons/uv-skeletons.js";
const _easycom_blog_item = () => "../../components/blog-item/blog-item.js";
if (!Math) {
  (_easycom_uv_tabs + _easycom_uv_skeletons + _easycom_blog_item)();
}
const _sfc_main = {
  __name: "index",
  setup(__props) {
    const forumCloudObj = common_vendor.Zs.importObject("forumCloudObj", {
      customUI: true
    });
    let navlist = common_vendor.ref([
      {
        name: "最新",
        type: "publish_date"
      },
      {
        name: "热门",
        type: "view_count"
      }
    ]);
    let dataList = common_vendor.ref([]);
    let loadState = common_vendor.ref(false);
    let skeleton = [{
      type: "line",
      num: 3,
      gap: "20rpx",
      style: ["width: 200rpx;marginBottom: 50rpx;", "height: 100rpx;", "width: 500rpx;"]
      // style: 'width: 200rpx;marginBottom: 50rpx;'
      // style: {width: '200rpx',marginBottom: '50rpx'}
    }];
    common_vendor.onLoad(async () => {
      getArticleList();
    });
    async function getArticleList(type = "publish_date") {
      loadState.value = true;
      dataList.value = [];
      let res = null;
      try {
        res = await forumCloudObj.getArticleList(type);
      } catch (e) {
        common_vendor.index.showModal({
          title: "错误",
          content: e.errMsg,
          showCancel: false
        });
      }
      dataList.value = res.data;
      loadState.value = false;
      if (!uni_modules_uniIdPages_common_store.store.hasLogin) {
        return;
      }
      let idArr = [];
      for (let item of dataList.value) {
        idArr.push(item._id);
      }
      let resLike = (await forumCloudObj.isArticleLike(idArr, common_vendor.Zs.getCurrentUserInfo().uid)).data;
      resLike.forEach((item) => {
        let findIndex = dataList.value.findIndex((i) => {
          return i._id == item.article_id;
        });
        if (findIndex != -1) {
          dataList.value[findIndex].isLike = true;
        }
      });
    }
    function clickNav(e) {
      console.log(e.type);
      getArticleList(e.type);
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.o(clickNav),
        b: common_vendor.p({
          list: common_vendor.unref(navlist),
          activeStyle: {
            color: "#333",
            fontWeight: "bold",
            transform: "scale(1.08)"
          },
          inactiveStyle: {
            color: "#888",
            transform: "scale(1)"
          }
        }),
        c: common_vendor.p({
          loading: common_vendor.unref(loadState),
          skeleton: common_vendor.unref(skeleton)
        }),
        d: common_vendor.unref(loadState),
        e: common_vendor.f(common_vendor.unref(dataList), (item, k0, i0) => {
          return {
            a: "1cf27b2a-2-" + i0,
            b: common_vendor.p({
              articleItem: item
            })
          };
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-1cf27b2a"]]);
wx.createPage(MiniProgramPage);
