"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uni_icons2 = common_vendor.resolveComponent("uni-icons");
  _easycom_uni_icons2();
}
const _easycom_uni_icons = () => "../../uni_modules/uni-icons/components/uni-icons/uni-icons.js";
if (!Math) {
  _easycom_uni_icons();
}
const _sfc_main = {
  __name: "option-item",
  props: {
    optionName: {
      type: String,
      required: true
    },
    jumpUrl: {
      type: String
    },
    number: {
      type: Number,
      default: -114514
    }
  },
  setup(__props) {
    let props = __props;
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.t(__props.optionName),
        b: common_vendor.unref(props).number != -114514
      }, common_vendor.unref(props).number != -114514 ? {
        c: common_vendor.t(common_vendor.unref(props).number)
      } : {}, {
        d: common_vendor.p({
          type: "arrowright",
          size: "22",
          color: "#999"
        }),
        e: __props.jumpUrl
      });
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-54270cf5"]]);
wx.createComponent(Component);
