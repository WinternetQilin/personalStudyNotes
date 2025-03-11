"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_UserInfo2 = common_vendor.resolveComponent("UserInfo");
  _easycom_UserInfo2();
}
const _easycom_UserInfo = () => "../../components/UserInfo/UserInfo.js";
if (!Math) {
  _easycom_UserInfo();
}
const _sfc_main = {
  __name: "demo8",
  setup(__props) {
    let goods = common_vendor.ref([
      {
        id: 1,
        name: "商品1",
        price: 100
      },
      {
        id: 2,
        name: "商品2",
        price: 200
      },
      {
        id: 3,
        name: "商品3",
        price: 300
      },
      {
        id: 4,
        name: "商品4",
        price: 400
      },
      {
        id: 5,
        name: "商品5",
        price: 500
      },
      {
        id: 6,
        name: "商品6",
        price: 600
      }
    ]);
    let selectedNum = common_vendor.ref(0);
    let sumMoney = common_vendor.ref(0);
    function onDelete(id) {
      goods.value.splice(goods.value.findIndex((g) => g.id == id), 1);
    }
    function cbClicked(e) {
      console.log(e);
      let selectArr = e.detail.value;
      selectedNum.value = selectArr.length;
      let temp = 0;
      console.log("selectArr: " + selectArr);
      for (let i of selectArr) {
        let index = goods.value.findIndex((item) => item.id == i);
        temp += goods.value[index].price;
      }
      sumMoney = temp;
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.f(common_vendor.unref(goods), (g, k0, i0) => {
          return {
            a: g.id.toString(),
            b: common_vendor.t(g.name),
            c: common_vendor.t(g.price),
            d: common_vendor.o(($event) => onDelete(g.id), g.id),
            e: g.id
          };
        }),
        b: common_vendor.o(cbClicked),
        c: common_vendor.t(common_vendor.unref(selectedNum)),
        d: common_vendor.t(common_vendor.unref(sumMoney))
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-69910d40"]]);
wx.createPage(MiniProgramPage);
