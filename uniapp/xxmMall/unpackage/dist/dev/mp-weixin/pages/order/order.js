"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _component_uni_nav_bar = common_vendor.resolveComponent("uni-nav-bar");
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  const _easycom_uv_empty2 = common_vendor.resolveComponent("uv-empty");
  (_component_uni_nav_bar + _easycom_uv_icon2 + _easycom_uv_empty2)();
}
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
const _easycom_uv_empty = () => "../../uni_modules/uv-empty/components/uv-empty/uv-empty.js";
if (!Math) {
  (_easycom_uv_icon + _easycom_uv_empty)();
}
const _sfc_main = {
  __name: "order",
  setup(__props) {
    function goDetail(item) {
      common_vendor.index.navigateTo({
        url: "/pages/order/detail?item=" + item
      });
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.o(_ctx.clickLeft),
        b: common_vendor.p({
          title: "我的订单",
          border: false,
          backgroundColor: "#fff",
          leftIcon: "left",
          statusBar: true
        }),
        c: _ctx.orderList.length
      }, _ctx.orderList.length ? {
        d: common_vendor.f(_ctx.orderList, (item, k0, i0) => {
          return common_vendor.e({
            a: common_vendor.t(item.order_no)
          }, {
            b: item.payType == "wxpay"
          }, item.payType == "wxpay" ? {
            c: "93207a4f-1-" + i0,
            d: common_vendor.p({
              name: "weixin-fill",
              size: "22",
              color: "#04C15F"
            })
          } : {}, {
            e: item.payType == "alipay"
          }, item.payType == "alipay" ? {
            f: "93207a4f-2-" + i0,
            g: common_vendor.p({
              name: "zhifubao",
              size: "22",
              color: "#1578FF"
            })
          } : {}, {
            h: common_vendor.t(_ctx.statusText(item.status)),
            i: common_vendor.n(item.status == -2 ? "err" : ""),
            j: item.orderType != "payment"
          }, item.orderType != "payment" ? {
            k: common_vendor.t(_ctx.getCarsListName(item.carsList))
          } : {}, {
            l: common_vendor.t(_ctx.timeFormat(item.createTime, "yyyy-MM-dd hh:mm")),
            m: item.orderType != "payment"
          }, item.orderType != "payment" ? {
            n: common_vendor.t(item.carsList.length),
            o: common_vendor.t(_ctx.priceFormat(item.total_fee))
          } : {}, {
            p: item._id,
            q: common_vendor.o(($event) => goDetail(item), item._id)
          });
        })
      } : {
        e: common_vendor.p({
          text: "没有订单",
          icon: "http://cdn.uviewui.com/uview/empty/data.png"
        })
      }, {
        f: _ctx.noData && _ctx.orderList.length
      }, _ctx.noData && _ctx.orderList.length ? {} : {});
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-93207a4f"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/order/order.js.map
