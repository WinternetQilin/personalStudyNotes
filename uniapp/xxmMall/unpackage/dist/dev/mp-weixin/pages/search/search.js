"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uv_search2 = common_vendor.resolveComponent("uv-search");
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  const _easycom_product_item2 = common_vendor.resolveComponent("product-item");
  const _easycom_uv_empty2 = common_vendor.resolveComponent("uv-empty");
  const _component_pro_detail_popup = common_vendor.resolveComponent("pro-detail-popup");
  const _component_pro_select_specs = common_vendor.resolveComponent("pro-select-specs");
  const _easycom_car_layout2 = common_vendor.resolveComponent("car-layout");
  (_easycom_uv_search2 + _easycom_uv_icon2 + _easycom_product_item2 + _easycom_uv_empty2 + _component_pro_detail_popup + _component_pro_select_specs + _easycom_car_layout2)();
}
const _easycom_uv_search = () => "../../uni_modules/uv-search/components/uv-search/uv-search.js";
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
const _easycom_product_item = () => "../../components/product-item/product-item.js";
const _easycom_uv_empty = () => "../../uni_modules/uv-empty/components/uv-empty/uv-empty.js";
const _easycom_car_layout = () => "../../components/car-layout/car-layout.js";
if (!Math) {
  (_easycom_uv_search + _easycom_uv_icon + _easycom_product_item + _easycom_uv_empty + _easycom_car_layout)();
}
const _sfc_main = {
  __name: "search",
  setup(__props) {
    let searchStr = common_vendor.ref("");
    let historyList = common_vendor.ref([]);
    common_vendor.onLoad(() => {
      historyList.value = common_vendor.index.getStorageSync("historyList") || [];
    });
    function onSearch() {
      if (searchStr.value.trim() === "")
        return;
      historyList.value.unshift(searchStr.value);
      historyList.value = [...new Set(historyList.value)];
      common_vendor.index.setStorageSync("historyList", historyList.value);
    }
    function onClose(idx) {
      historyList.value.splice(idx, 1);
      common_vendor.index.setStorageSync("historyList", historyList.value);
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.o(onSearch),
        b: common_vendor.o(onSearch),
        c: common_vendor.o(_ctx.onClear),
        d: common_vendor.o(($event) => common_vendor.isRef(searchStr) ? searchStr.value = $event : searchStr = $event),
        e: common_vendor.p({
          placeholder: "请输入搜索内容",
          clearabled: true,
          showAction: true,
          actionText: "搜索",
          animation: true,
          modelValue: common_vendor.unref(searchStr)
        }),
        f: _ctx.goodsData.length == 0
      }, _ctx.goodsData.length == 0 ? {
        g: common_vendor.f(common_vendor.unref(historyList), (item, index, i0) => {
          return {
            a: common_vendor.t(item),
            b: common_vendor.o(($event) => _ctx.clickHitText(item), item),
            c: "c10c040c-1-" + i0,
            d: common_vendor.o(($event) => onClose(index), item),
            e: item
          };
        }),
        h: common_vendor.p({
          name: "close",
          size: "16",
          color: "#999"
        })
      } : {}, {
        i: common_vendor.f(_ctx.goodsData, (item, k0, i0) => {
          return {
            a: "c10c040c-2-" + i0,
            b: common_vendor.p({
              item
            }),
            c: item._id
          };
        }),
        j: _ctx.noData
      }, _ctx.noData ? {
        k: common_vendor.p({
          mode: "search",
          icon: "https://cdn.uviewui.com/uview/empty/search.png"
        })
      } : {}, {
        l: _ctx.buyNum > 0
      }, _ctx.buyNum > 0 ? {} : {});
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-c10c040c"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/search/search.js.map
