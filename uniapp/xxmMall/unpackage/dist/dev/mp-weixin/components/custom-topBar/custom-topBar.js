"use strict";
const common_vendor = require("../../common/vendor.js");
const common_assets = require("../../common/assets.js");
const store_system = require("../../store/system.js");
if (!Array) {
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  _easycom_uv_icon2();
}
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
if (!Math) {
  _easycom_uv_icon();
}
const _sfc_main = {
  __name: "custom-topBar",
  props: {
    foldState: {
      type: Boolean
    }
  },
  setup(__props) {
    const systemStore = store_system.useSystem();
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_assets._imports_0$1,
        b: common_vendor.unref(systemStore).statusBarHeight + "px",
        c: !common_vendor.unref(systemStore).foldState
      }, !common_vendor.unref(systemStore).foldState ? {
        d: common_vendor.p({
          name: "server-fill",
          color: "#fff",
          size: "22"
        }),
        e: common_vendor.p({
          name: "setting-fill",
          color: "#fff",
          size: "22"
        }),
        f: common_vendor.unref(systemStore).titleBarHeight + "px"
      } : {}, {
        g: common_assets._imports_0$1,
        h: common_vendor.p({
          name: "more-circle",
          color: "#fff",
          size: "22"
        }),
        i: common_assets._imports_1,
        j: common_vendor.n(common_vendor.unref(systemStore).foldState ? "fold" : ""),
        k: common_vendor.unref(systemStore).bodyBarHeight + "px",
        l: common_vendor.unref(systemStore).totalHeight + "px"
      });
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-77797bb3"]]);
wx.createComponent(Component);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/components/custom-topBar/custom-topBar.js.map
