"use strict";
const common_vendor = require("../../common/vendor.js");
const store_system = require("../../store/system.js");
const store_car = require("../../store/car.js");
if (!Array) {
  const _easycom_custom_topBar2 = common_vendor.resolveComponent("custom-topBar");
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  const _easycom_uv_sticky2 = common_vendor.resolveComponent("uv-sticky");
  const _easycom_product_item2 = common_vendor.resolveComponent("product-item");
  const _easycom_car_layout2 = common_vendor.resolveComponent("car-layout");
  (_easycom_custom_topBar2 + _easycom_uv_icon2 + _easycom_uv_sticky2 + _easycom_product_item2 + _easycom_car_layout2)();
}
const _easycom_custom_topBar = () => "../../components/custom-topBar/custom-topBar.js";
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
const _easycom_uv_sticky = () => "../../uni_modules/uv-sticky/components/uv-sticky/uv-sticky.js";
const _easycom_product_item = () => "../../components/product-item/product-item.js";
const _easycom_car_layout = () => "../../components/car-layout/car-layout.js";
if (!Math) {
  (_easycom_custom_topBar + _easycom_uv_icon + _easycom_uv_sticky + _easycom_product_item + _easycom_car_layout)();
}
const _sfc_main = {
  __name: "index",
  setup(__props) {
    const systemStore = store_system.useSystem();
    const carStore = store_car.useCar();
    let navIdx = common_vendor.ref(0);
    let rightScrollValue = common_vendor.ref(0);
    let leftScrollValue = common_vendor.ref(0);
    let leftHitArr = common_vendor.ref([]);
    let rightHitArr = common_vendor.ref([]);
    let foldState = common_vendor.ref(false);
    let dataList = common_vendor.ref([{
      id: 1,
      name: "豆干制品",
      children: [{
        id: 11,
        name: "卫龙辣条",
        price: 10,
        before_price: 22,
        thumb: "https://mp-c422c6b7-799d-4ff5-9531-5051a0481131.cdn.bspapp.com/cloudstorage/83562e26-cfac-4cec-8f51-9ae6986942af.jpg",
        numvalue: 0
      }, {
        id: 12,
        name: "卫龙大面筋",
        price: 5,
        before_price: 12,
        thumb: "https://mp-c422c6b7-799d-4ff5-9531-5051a0481131.cdn.bspapp.com/cloudstorage/30569d48-bb94-40de-8d2b-a3be99d710cd.jpg",
        numvalue: 0
      }]
    }, {
      id: 2,
      name: "饼干糕点",
      children: [{
        id: 21,
        name: "丹麦曲奇",
        price: 25,
        before_price: 36,
        thumb: "https://mp-3309c116-4743-47d6-9979-462d2edf878c.cdn.bspapp.com/cloudstorage/6758e11c-949b-48c5-ae69-ddad030c2f94.png",
        numvalue: 0
      }]
    }, {
      id: 3,
      name: "酒水饮料",
      children: [{
        id: 31,
        name: "韩国烧酒",
        price: 18,
        before_price: 29,
        thumb: "https://mp-3309c116-4743-47d6-9979-462d2edf878c.cdn.bspapp.com/cloudstorage/b1a12bee-0602-4cb5-927d-b2b246700e89.jpeg",
        numvalue: 0
      }]
    }]);
    common_vendor.onReady(() => {
      getHeightArr();
    });
    function clickNav(index) {
      if (navIdx.value == index)
        return;
      let timeout;
      if (timeout) {
        clearTimeout(timeout);
      }
      timeout = setTimeout(() => {
        navIdx.value = index;
        rightScrollValue.value = rightHitArr.value[index];
        leftScrollValue.value = leftHitArr.value[index];
      }, 100);
    }
    function getHeightArr() {
      let selectQuery = common_vendor.index.createSelectorQuery();
      let customTopBarHeight = 0;
      selectQuery.select("#customTopBar").boundingClientRect((rect) => {
        customTopBarHeight = rect.height;
      }).exec();
      selectQuery.selectAll(".navItem").boundingClientRect((rects) => {
        leftHitArr.value = rects.map((item) => {
          return item.top - customTopBarHeight - 50 + 10;
        });
      }).exec();
      selectQuery.selectAll(".productView").boundingClientRect((rects) => {
        rightHitArr.value = rects.map((item) => {
          return item.top - customTopBarHeight - 50 + 10;
        });
      }).exec();
    }
    function rightScrollEnt(e) {
      let scrollTop = Math.ceil(e.detail.scrollTop);
      let idx = rightHitArr.value.findIndex((item, index, arr) => {
        return scrollTop >= item && scrollTop < arr[index + 1];
      });
      navIdx.value = idx;
      leftScrollValue.value = leftHitArr.value[idx];
      if (scrollTop > 400) {
        systemStore.setFoldState(true);
      } else {
        systemStore.setFoldState(false);
      }
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.p({
          id: "customTopBar",
          foldState: common_vendor.unref(foldState)
        }),
        b: common_vendor.p({
          name: "order",
          color: "#576b95",
          size: "22"
        }),
        c: common_vendor.f(common_vendor.unref(dataList), (i, index, i0) => {
          return {
            a: common_vendor.t(i.name),
            b: common_vendor.n(index == common_vendor.unref(navIdx) ? "active" : ""),
            c: i.id,
            d: common_vendor.o(($event) => clickNav(index), i.id)
          };
        }),
        d: common_vendor.unref(leftScrollValue),
        e: common_vendor.p({
          name: "search",
          size: "22",
          color: "#576b95"
        }),
        f: common_vendor.f(common_vendor.unref(dataList), (i, k0, i0) => {
          return {
            a: common_vendor.t(i.name),
            b: "1cf27b2a-3-" + i0,
            c: common_vendor.f(i.children, (ii, k1, i1) => {
              return {
                a: "1cf27b2a-4-" + i0 + "-" + i1,
                b: common_vendor.p({
                  item: ii
                }),
                c: ii.id
              };
            }),
            d: i.id
          };
        }),
        g: common_vendor.p({
          customNavHeight: "0",
          zIndex: "2"
        }),
        h: common_vendor.o(rightScrollEnt),
        i: common_vendor.unref(rightScrollValue),
        j: common_vendor.unref(carStore).buyNum > 0
      }, common_vendor.unref(carStore).buyNum > 0 ? {} : {});
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-1cf27b2a"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/index/index.js.map
