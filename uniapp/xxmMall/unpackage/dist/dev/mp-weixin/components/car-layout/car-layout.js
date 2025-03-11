"use strict";
const common_vendor = require("../../common/vendor.js");
const store_car = require("../../store/car.js");
if (!Array) {
  const _easycom_uv_overlay2 = common_vendor.resolveComponent("uv-overlay");
  const _easycom_car_pro_item2 = common_vendor.resolveComponent("car-pro-item");
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  (_easycom_uv_overlay2 + _easycom_car_pro_item2 + _easycom_uv_icon2)();
}
const _easycom_uv_overlay = () => "../../uni_modules/uv-overlay/components/uv-overlay/uv-overlay.js";
const _easycom_car_pro_item = () => "../car-pro-item/car-pro-item.js";
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
if (!Math) {
  (_easycom_uv_overlay + _easycom_car_pro_item + _easycom_uv_icon)();
}
const _sfc_main = {
  __name: "car-layout",
  props: {
    type: {
      type: String,
      default: ""
    }
  },
  setup(__props) {
    const car = store_car.useCar();
    let props = __props;
    let carShow = common_vendor.ref(false);
    function clickCarIcon() {
      carShow.value = !carShow.value;
    }
    function goPay() {
      common_vendor.index.navigateTo({
        url: "/pages/paypage/paypage"
      });
    }
    function confirmPay() {
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.o(clickCarIcon),
        b: common_vendor.p({
          show: common_vendor.unref(carShow),
          ["z-index"]: "9"
        }),
        c: common_vendor.unref(carShow)
      }, common_vendor.unref(carShow) ? {
        d: common_vendor.f(common_vendor.unref(car).getCarList, (i, k0, i0) => {
          return {
            a: "80290310-1-" + i0,
            b: common_vendor.p({
              item: i
            }),
            c: i.id
          };
        })
      } : {}, {
        e: !common_vendor.unref(props).type
      }, !common_vendor.unref(props).type ? {
        f: common_vendor.p({
          name: "shopping-cart",
          size: "34",
          color: "#EC544F"
        }),
        g: common_vendor.t(common_vendor.unref(car).buyNum),
        h: common_vendor.o(clickCarIcon)
      } : {}, {
        i: common_vendor.t(common_vendor.unref(car).totalPrice),
        j: !common_vendor.unref(props).type
      }, !common_vendor.unref(props).type ? {
        k: common_vendor.o(goPay)
      } : {
        l: common_vendor.o(confirmPay)
      });
    };
  }
};
const Component = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-80290310"]]);
wx.createComponent(Component);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/components/car-layout/car-layout.js.map
