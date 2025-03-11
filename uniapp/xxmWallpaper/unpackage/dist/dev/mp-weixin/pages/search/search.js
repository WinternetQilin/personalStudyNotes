"use strict";
const common_vendor = require("../../common/vendor.js");
const api_apis = require("../../api/apis.js");
if (!Array) {
  const _easycom_uni_search_bar2 = common_vendor.resolveComponent("uni-search-bar");
  const _easycom_uni_icons2 = common_vendor.resolveComponent("uni-icons");
  const _easycom_uni_load_more2 = common_vendor.resolveComponent("uni-load-more");
  (_easycom_uni_search_bar2 + _easycom_uni_icons2 + _easycom_uni_load_more2)();
}
const _easycom_uni_search_bar = () => "../../uni_modules/uni-search-bar/components/uni-search-bar/uni-search-bar.js";
const _easycom_uni_icons = () => "../../uni_modules/uni-icons/components/uni-icons/uni-icons.js";
const _easycom_uni_load_more = () => "../../uni_modules/uni-load-more/components/uni-load-more/uni-load-more.js";
if (!Math) {
  (_easycom_uni_search_bar + _easycom_uni_icons + _easycom_uni_load_more)();
}
const _sfc_main = {
  __name: "search",
  setup(__props) {
    const queryParams = common_vendor.ref({
      pageNum: 1,
      pageSize: 12,
      keyword: ""
    });
    let historySearch = common_vendor.ref(common_vendor.index.getStorageSync("historySearch") || []);
    const recommendList = common_vendor.ref(["美女", "帅哥", "宠物", "卡通"]);
    const noData = common_vendor.ref(false);
    const noSearch = common_vendor.ref(false);
    const classList = common_vendor.ref([]);
    const onSearch = () => {
      if (!historySearch.value.includes(queryParams.value.keyword))
        historySearch.value.unshift(queryParams.value.keyword);
      historySearch.value = historySearch.value.slice(0, 10);
      common_vendor.index.setStorageSync("historySearch", historySearch.value);
      classList.value = [];
      queryParams.value.pageNum = 1;
      queryParams.value.pageSize = 12;
      noData.value = false;
      noSearch.value = false;
      onSearchFunc();
    };
    const onClear = () => {
      classList.value = [];
      queryParams.value = {
        pageNum: 1,
        pageSize: 12,
        keyword: ""
      };
      noData.value = false;
      noSearch.value = false;
    };
    const clickTab = (value) => {
      queryParams.value.keyword = value;
      if (!historySearch.value.includes(queryParams.value.keyword))
        historySearch.value.push(queryParams.value.keyword);
      common_vendor.index.setStorageSync("historySearch", historySearch.value);
      classList.value = [];
      queryParams.value.pageNum = 1;
      onSearchFunc();
    };
    const removeHistory = () => {
      common_vendor.index.showModal({
        title: "是否清空历史搜索？",
        success: (res) => {
          if (res.confirm) {
            console.log("确认删除");
            common_vendor.index.removeStorageSync("historySearch");
            historySearch.value = [];
          }
        }
      });
    };
    async function onSearchFunc() {
      let res = await api_apis.apiSearchData(queryParams.value);
      classList.value = [...classList.value, ...res.data];
      common_vendor.index.setStorageSync("classifyPicList", classList.value);
      if (res.data.length <= 0) {
        noData.value = true;
      } else {
        noData.value = false;
      }
      if (res.data.length <= 0 && classList.value.length == 0) {
        noSearch.value = true;
      } else {
        noSearch.value = false;
      }
    }
    common_vendor.onReachBottom(() => {
      console.log("noData:");
      console.log(noData.value);
      if (noData.value)
        return;
      queryParams.value.pageNum++;
      onSearchFunc();
    });
    common_vendor.onUnload(() => {
      common_vendor.index.removeStorageSync("classifyPicList");
    });
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.o(onSearch),
        b: common_vendor.o(onClear),
        c: common_vendor.o(onClear),
        d: common_vendor.o(($event) => queryParams.value.keyword = $event),
        e: common_vendor.p({
          focus: true,
          placeholder: "搜索",
          modelValue: queryParams.value.keyword
        }),
        f: !classList.value.length
      }, !classList.value.length ? common_vendor.e({
        g: common_vendor.unref(historySearch).length
      }, common_vendor.unref(historySearch).length ? {
        h: common_vendor.p({
          type: "trash",
          size: "25"
        }),
        i: common_vendor.o(removeHistory),
        j: common_vendor.f(common_vendor.unref(historySearch), (tab, k0, i0) => {
          return {
            a: common_vendor.t(tab),
            b: tab,
            c: common_vendor.o(($event) => clickTab(tab), tab)
          };
        })
      } : {}, {
        k: common_vendor.f(recommendList.value, (tab, k0, i0) => {
          return {
            a: common_vendor.t(tab),
            b: tab,
            c: common_vendor.o(($event) => clickTab(tab), tab)
          };
        })
      }) : {}, {
        l: noSearch.value
      }, noSearch.value ? {} : {}, {
        m: common_vendor.f(classList.value, (item, k0, i0) => {
          return {
            a: item.smallPicurl,
            b: `/pages/preview/preview?id=${item._id}`,
            c: item._id
          };
        }),
        n: classList.value.length && !noSearch.value
      }, classList.value.length && !noSearch.value ? {
        o: common_vendor.p({
          status: noData.value ? "noMore" : "loading"
        })
      } : {});
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-c10c040c"]]);
wx.createPage(MiniProgramPage);
