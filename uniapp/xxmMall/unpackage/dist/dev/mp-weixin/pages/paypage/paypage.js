"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uv_notice_bar2 = common_vendor.resolveComponent("uv-notice-bar");
  const _easycom_delivery_layout2 = common_vendor.resolveComponent("delivery-layout");
  const _easycom_goods_list2 = common_vendor.resolveComponent("goods-list");
  const _easycom_car_layout2 = common_vendor.resolveComponent("car-layout");
  const _component_uni_pay = common_vendor.resolveComponent("uni-pay");
  (_easycom_uv_notice_bar2 + _easycom_delivery_layout2 + _easycom_goods_list2 + _easycom_car_layout2 + _component_uni_pay)();
}
const _easycom_uv_notice_bar = () => "../../uni_modules/uv-notice-bar/components/uv-notice-bar/uv-notice-bar.js";
const _easycom_delivery_layout = () => "../../components/delivery-layout/delivery-layout.js";
const _easycom_goods_list = () => "../../components/goods-list/goods-list.js";
const _easycom_car_layout = () => "../../components/car-layout/car-layout.js";
if (!Math) {
  (_easycom_uv_notice_bar + _easycom_delivery_layout + _easycom_goods_list + _easycom_car_layout)();
}
const _sfc_main = {
  __name: "paypage",
  setup(__props) {
    common_vendor.ref("wxpay");
    common_vendor.ref([{
      name: "支付宝",
      value: "alipay",
      color: "#1578FF",
      icon: "zhifubao-circle-fill"
    }, {
      name: "微信",
      value: "wxpay",
      color: "#04C15F",
      icon: "weixin-fill"
    }]);
    return (_ctx, _cache) => {
      return {
        a: common_vendor.p({
          text: "本商城产品为学习交流使用, 下单概不发货, 请谨慎下单~~"
        }),
        b: common_vendor.p({
          deliveryInfo: _ctx.deliveryInfo
        }),
        c: common_vendor.p({
          goodsList: _ctx.carsList,
          totalPrice: _ctx.totalPrice,
          prePrice: _ctx.preferentialPrice
        }),
        d: common_vendor.o(_ctx.onConfirmPay),
        e: common_vendor.p({
          type: "pay",
          payBtnState: _ctx.payBtnState
        }),
        f: common_vendor.sr("uniPay", "5c01ce25-4"),
        g: common_vendor.o(_ctx.paySuccess),
        h: common_vendor.o(_ctx.payCancel),
        i: common_vendor.o(_ctx.payCreate),
        j: common_vendor.p({
          returnUrl: "/pages/order/order"
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-5c01ce25"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/paypage/paypage.js.map
