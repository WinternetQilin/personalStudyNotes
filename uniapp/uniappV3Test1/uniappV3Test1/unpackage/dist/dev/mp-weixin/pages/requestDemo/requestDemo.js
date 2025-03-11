"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uni_segmented_control2 = common_vendor.resolveComponent("uni-segmented-control");
  const _easycom_uni_load_more2 = common_vendor.resolveComponent("uni-load-more");
  const _easycom_uni_icons2 = common_vendor.resolveComponent("uni-icons");
  (_easycom_uni_segmented_control2 + _easycom_uni_load_more2 + _easycom_uni_icons2)();
}
const _easycom_uni_segmented_control = () => "../../uni_modules/uni-segmented-control/components/uni-segmented-control/uni-segmented-control.js";
const _easycom_uni_load_more = () => "../../uni_modules/uni-load-more/components/uni-load-more/uni-load-more.js";
const _easycom_uni_icons = () => "../../uni_modules/uni-icons/components/uni-icons/uni-icons.js";
if (!Math) {
  (_easycom_uni_segmented_control + _easycom_uni_load_more + _easycom_uni_icons)();
}
const _sfc_main = {
  __name: "requestDemo",
  setup(__props) {
    let menuItems = [{ key: "all", value: "猫狗" }, { key: "cat", value: "猫" }, { key: "dog", value: "狗" }];
    let menuItemsCur = common_vendor.ref(0);
    common_vendor.index.showLoading();
    let catPicArr = common_vendor.ref([]);
    function getCatPic() {
      common_vendor.index.request({
        url: "https://tea.qingnian8.com/tools/petShow",
        data: {
          size: 7,
          type: menuItems[menuItemsCur.value].key
        },
        header: {
          "access-key": "1261338615"
        }
      }).then((res) => {
        console.log(res.data.data);
        if (res.data.errCode === 0) {
          catPicArr.value = [...catPicArr.value, ...res.data.data];
        } else if (res.data.errCode === 400) {
          common_vendor.index.showToast({
            title: res.data.errMsg,
            icon: "none"
          });
        }
      }).finally(() => {
        common_vendor.index.hideLoading();
        common_vendor.index.stopPullDownRefresh();
      });
    }
    getCatPic();
    common_vendor.onReachBottom(() => {
      getCatPic();
    });
    common_vendor.onPullDownRefresh(() => {
      catPicArr.value = [];
      getCatPic();
    });
    function onClickedRefresh() {
      common_vendor.index.startPullDownRefresh();
    }
    function onClickedBackTop() {
      common_vendor.index.pageScrollTo({
        scrollTop: 0,
        duration: 100
      });
    }
    function onClickItem(e) {
      console.log(e);
      menuItemsCur.value = e.currentIndex;
      onClickedRefresh();
    }
    function onImgClicked(idx) {
      let urls = catPicArr.value.map((item) => item.url);
      common_vendor.index.previewImage({
        current: idx,
        urls
      });
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.o(onClickItem),
        b: common_vendor.p({
          current: common_vendor.unref(menuItemsCur),
          values: common_vendor.unref(menuItems).map((item) => item.value),
          styleType: "button",
          activeColor: "#4cd964"
        }),
        c: common_vendor.f(common_vendor.unref(catPicArr), (item, index, i0) => {
          return {
            a: item.url,
            b: common_vendor.o(($event) => onImgClicked(index), item._id),
            c: common_vendor.t(item.content),
            d: item._id
          };
        }),
        d: common_vendor.p({
          status: "loading"
        }),
        e: common_vendor.p({
          type: "refreshempty",
          size: "25"
        }),
        f: common_vendor.o(onClickedRefresh),
        g: common_vendor.p({
          type: "arrow-up",
          size: "25"
        }),
        h: common_vendor.o(onClickedBackTop)
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-e25b1ed9"]]);
wx.createPage(MiniProgramPage);
