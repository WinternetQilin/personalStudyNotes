"use strict";
const common_vendor = require("../../common/vendor.js");
const _sfc_main = {
  name: "goods-list",
  data() {
    return {};
  }
};
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.t(_ctx.goodsList.length),
    b: common_vendor.f(_ctx.goodsList, (item, k0, i0) => {
      return common_vendor.e({
        a: item.thumb[0].url,
        b: common_vendor.t(item.name),
        c: common_vendor.t(item.numvalue),
        d: common_vendor.t(_ctx.priceFormat(item.price)),
        e: item.before_price
      }, item.before_price ? {
        f: common_vendor.t(_ctx.priceFormat(item.before_price))
      } : {});
    }),
    c: common_vendor.t(_ctx.priceFormat(_ctx.prePrice)),
    d: common_vendor.t(_ctx.priceFormat(_ctx.totalPrice))
  };
}
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render]]);
wx.createComponent(Component);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/components/goods-list/goods-list.js.map
