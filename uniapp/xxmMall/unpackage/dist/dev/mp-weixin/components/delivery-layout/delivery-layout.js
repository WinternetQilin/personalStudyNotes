"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  _easycom_uv_icon2();
}
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
if (!Math) {
  _easycom_uv_icon();
}
const _sfc_main = {
  __name: "delivery-layout",
  props: {
    deliveryInfo: {
      type: Object,
      default() {
        return {
          address: "",
          username: "",
          mobile: null
        };
      }
    }
  },
  setup(__props) {
    function goAddress() {
      common_vendor.index.navigateTo({
        url: "/pages/address/list"
      });
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: __props.deliveryInfo.address
      }, __props.deliveryInfo.address ? {
        b: common_vendor.t(__props.deliveryInfo.address),
        c: common_vendor.t(__props.deliveryInfo.username + "-" + __props.deliveryInfo.mobile)
      } : {}, {
        d: common_vendor.p({
          name: "arrow-right",
          color: "#999",
          size: "18"
        }),
        e: common_vendor.o(goAddress)
      });
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-5a83e519"]]);
wx.createComponent(Component);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/components/delivery-layout/delivery-layout.js.map
