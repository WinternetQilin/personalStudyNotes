"use strict";
const common_vendor = require("../../common/vendor.js");
const _sfc_main = {};
if (!Array) {
  const _easycom_uni_section2 = common_vendor.resolveComponent("uni-section");
  const _easycom_uni_list_item2 = common_vendor.resolveComponent("uni-list-item");
  const _easycom_uni_list2 = common_vendor.resolveComponent("uni-list");
  (_easycom_uni_section2 + _easycom_uni_list_item2 + _easycom_uni_list2)();
}
const _easycom_uni_section = () => "../../uni_modules/uni-section/components/uni-section/uni-section.js";
const _easycom_uni_list_item = () => "../../uni_modules/uni-list/components/uni-list-item/uni-list-item.js";
const _easycom_uni_list = () => "../../uni_modules/uni-list/components/uni-list/uni-list.js";
if (!Math) {
  (_easycom_uni_section + _easycom_uni_list_item + _easycom_uni_list)();
}
function _sfc_render(_ctx, _cache) {
  return {
    a: common_vendor.p({
      title: "分类管理",
      type: "line"
    }),
    b: common_vendor.p({
      title: "管理分类",
      ["show-arrow"]: true,
      to: "/pages_manage/category/category"
    }),
    c: common_vendor.p({
      title: "商品管理",
      type: "line"
    }),
    d: common_vendor.p({
      title: "商品列表",
      ["show-arrow"]: true,
      to: "/pages_manage/goods/list"
    }),
    e: common_vendor.p({
      title: "新增商品",
      ["show-arrow"]: true,
      to: "/pages_manage/goods/add"
    }),
    f: common_vendor.p({
      title: "关于商家",
      type: "line"
    }),
    g: common_vendor.p({
      title: "所有订单",
      ["show-arrow"]: true,
      to: "/pages_manage/order/order"
    }),
    h: common_vendor.p({
      title: "商家信息",
      ["show-arrow"]: true,
      to: "/pages_manage/brand/brand"
    })
  };
}
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__scopeId", "data-v-d0d3e4f6"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages_manage/index/index.js.map
