"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_pro_num_box2 = common_vendor.resolveComponent("pro-num-box");
  _easycom_pro_num_box2();
}
const _easycom_pro_num_box = () => "../pro-num-box/pro-num-box.js";
if (!Math) {
  _easycom_pro_num_box();
}
const _sfc_main = {
  __name: "product-item",
  props: {
    // 商品信息
    item: {
      type: Object,
      default: () => ({})
    }
  },
  setup(__props) {
    let props = __props;
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.unref(props).item.thumb,
        b: common_vendor.t(common_vendor.unref(props).item.name),
        c: common_vendor.t(common_vendor.unref(props).item.price),
        d: common_vendor.t(common_vendor.unref(props).item.before_price)
      }, {
        e: common_vendor.p({
          item: common_vendor.unref(props).item
        })
      });
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-aff2f6d2"]]);
wx.createComponent(Component);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/components/product-item/product-item.js.map
