"use strict";
const common_vendor = require("../../common/vendor.js");
const _sfc_main = {};
if (!Array) {
  const _easycom_goods_list2 = common_vendor.resolveComponent("goods-list");
  _easycom_goods_list2();
}
const _easycom_goods_list = () => "../../components/goods-list/goods-list.js";
if (!Math) {
  _easycom_goods_list();
}
function _sfc_render(_ctx, _cache) {
  return common_vendor.e({
    a: _ctx.params
  }, _ctx.params ? common_vendor.e({
    b: _ctx.params.realPrice
  }, _ctx.params.realPrice ? {} : {}, {
    c: common_vendor.t(_ctx.priceFormat(_ctx.params.total_fee)),
    d: _ctx.params.realPrice
  }, _ctx.params.realPrice ? {
    e: common_vendor.t(_ctx.priceFormat(_ctx.params.realPrice))
  } : {}, {
    f: _ctx.params.done
  }, _ctx.params.done ? {} : {}, {
    g: common_vendor.t(_ctx.params.order_no),
    h: common_vendor.t(_ctx.timeFormat(_ctx.params.createTime)),
    i: common_vendor.t(_ctx.params.payType == "alipay" ? "支付宝支付" : "微信支付"),
    j: _ctx.params.orderType == "payment"
  }, _ctx.params.orderType == "payment" ? {} : {}, {
    k: _ctx.params.orderType != "payment"
  }, _ctx.params.orderType != "payment" ? {
    l: common_vendor.t(_ctx.params.deliveryInfo.address),
    m: common_vendor.t(_ctx.params.deliveryInfo.username),
    n: common_vendor.t(_ctx.params.deliveryInfo.mobile)
  } : {}, {
    o: _ctx.params.orderType != "payment"
  }, _ctx.params.orderType != "payment" ? {
    p: common_vendor.p({
      goodsList: _ctx.params.carsList,
      totalPrice: _ctx.totalPrice,
      prePrice: _ctx.prePrice
    })
  } : {}) : {});
}
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render], ["__scopeId", "data-v-6b23c96c"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/order/detail.js.map
