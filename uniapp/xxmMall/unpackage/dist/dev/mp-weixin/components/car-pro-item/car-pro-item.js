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
  __name: "car-pro-item",
  props: {
    item: {
      type: Object,
      default: () => ({})
    }
  },
  setup(__props) {
    let props = __props;
    return (_ctx, _cache) => {
      return {
        a: common_vendor.unref(props).item.thumb,
        b: common_vendor.t(common_vendor.unref(props).item.name),
        c: common_vendor.t(common_vendor.unref(props).item.price),
        d: common_vendor.t(common_vendor.unref(props).item.before_price),
        e: common_vendor.p({
          item: common_vendor.unref(props).item
        })
      };
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-df67b6b5"]]);
wx.createComponent(Component);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/components/car-pro-item/car-pro-item.js.map
