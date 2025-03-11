"use strict";
const common_vendor = require("../common/vendor.js");
let systemInfo = common_vendor.index.getSystemInfoSync();
const getStatusBarHeight = () => systemInfo.statusBarHeight || 20;
const getTitleBarHeight = () => {
  let menuBtnInfo = common_vendor.index.getMenuButtonBoundingClientRect();
  return (menuBtnInfo.top - getStatusBarHeight()) * 2 + menuBtnInfo.height;
};
const useSystem = common_vendor.defineStore("system", {
  state: () => ({
    foldState: false
  }),
  getters: {
    // 顶部状态栏高度
    statusBarHeight() {
      return getStatusBarHeight();
    },
    // 胶囊按钮高度（包含边距）
    titleBarHeight() {
      return getTitleBarHeight();
    },
    // 店铺信息栏（body）高度
    bodyBarHeight(state) {
      return state.foldState ? this.titleBarHeight : 100;
    },
    // 菜单(免费配送)上边整体的高度
    totalHeight(state) {
      return state.foldState ? this.statusBarHeight + 10 + this.titleBarHeight + 10 : this.statusBarHeight + this.titleBarHeight + 100 + 10;
    }
  },
  actions: {
    // 设置折叠状态
    setFoldState(value) {
      this.foldState = value;
    }
  }
});
exports.useSystem = useSystem;
//# sourceMappingURL=../../.sourcemap/mp-weixin/store/system.js.map
