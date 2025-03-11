"use strict";
const common_vendor = require("../../common/vendor.js");
const store_car = require("../../store/car.js");
if (!Array) {
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  const _easycom_uv_number_box2 = common_vendor.resolveComponent("uv-number-box");
  (_easycom_uv_icon2 + _easycom_uv_number_box2)();
}
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
const _easycom_uv_number_box = () => "../../uni_modules/uv-number-box/components/uv-number-box/uv-number-box.js";
if (!Math) {
  (_easycom_uv_icon + _easycom_uv_number_box)();
}
const _sfc_main = {
  __name: "pro-num-box",
  props: {
    // 商品信息
    item: {
      type: Object,
      default: () => ({})
    }
  },
  setup(__props) {
    const car = store_car.useCar();
    let props = __props;
    function numChange(e) {
      common_vendor.index.__f__("log", "at components/pro-num-box/pro-num-box.vue:42", e);
      car.setCarList({
        item: props.item,
        num: e.value
      });
      common_vendor.index.__f__("log", "at components/pro-num-box/pro-num-box.vue:47", props.item.numvalue);
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.p({
          name: "minus",
          size: "12",
          color: "#ccc"
        }),
        b: common_vendor.n(common_vendor.unref(props).item.numvalue <= 0 ? "none" : ""),
        c: common_vendor.t(common_vendor.unref(props).item.numvalue),
        d: common_vendor.n(common_vendor.unref(props).item.numvalue <= 0 ? "none" : ""),
        e: common_vendor.p({
          name: "plus",
          color: "#FFFFFF",
          size: "12"
        }),
        f: common_vendor.o(numChange),
        g: common_vendor.o(($event) => common_vendor.unref(props).item.numvalue = $event),
        h: common_vendor.p({
          min: "0",
          max: "99",
          modelValue: common_vendor.unref(props).item.numvalue
        })
      };
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-d70f141c"]]);
wx.createComponent(Component);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/components/pro-num-box/pro-num-box.js.map
