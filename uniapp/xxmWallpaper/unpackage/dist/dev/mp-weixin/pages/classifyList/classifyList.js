"use strict";
const common_vendor = require("../../common/vendor.js");
const api_apis = require("../../api/apis.js");
if (!Array) {
  const _easycom_uni_load_more2 = common_vendor.resolveComponent("uni-load-more");
  _easycom_uni_load_more2();
}
const _easycom_uni_load_more = () => "../../uni_modules/uni-load-more/components/uni-load-more/uni-load-more.js";
if (!Math) {
  _easycom_uni_load_more();
}
const _sfc_main = {
  __name: "classifyList",
  setup(__props) {
    let queryParams = {};
    let classifyPicList = common_vendor.ref([]);
    let noData = common_vendor.ref(false);
    common_vendor.onLoad((e) => {
      let {
        id = null,
        name = "分类"
      } = e;
      queryParams.classid = id;
      queryParams.pageNum = 1;
      common_vendor.index.setNavigationBarTitle({
        title: name
      });
      getClassifyPicList();
    });
    common_vendor.onUnload(() => {
      common_vendor.index.removeStorageSync("classifyPicList");
    });
    common_vendor.onReachBottom(() => {
      if (noData.value)
        return;
      queryParams.pageNum++;
      getClassifyPicList();
    });
    async function getClassifyPicList() {
      let res = await api_apis.apiGetClassifyPicList(queryParams);
      if (res.data.length <= 0) {
        noData.value = true;
      }
      console.log(res);
      classifyPicList.value = [...classifyPicList.value, ...res.data];
      common_vendor.index.setStorageSync("classifyPicList", classifyPicList.value);
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.f(common_vendor.unref(classifyPicList), (item, k0, i0) => {
          return {
            a: item.smallPicurl,
            b: "/pages/preview/preview?id=" + item._id,
            c: item._id
          };
        }),
        b: common_vendor.p({
          status: common_vendor.unref(noData) ? "noMore" : "loading"
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-d7121c9c"]]);
wx.createPage(MiniProgramPage);
