"use strict";
const common_vendor = require("../common/vendor.js");
const system = common_vendor.index.getSystemInfoSync();
const getStatusBarHeight = () => system.statusBarHeight || 30;
const getTitleBarHeight = () => {
  if (common_vendor.index.getMenuButtonBoundingClientRect) {
    const {
      top,
      height
    } = common_vendor.index.getMenuButtonBoundingClientRect();
    return (top - getStatusBarHeight()) * 2 + height;
  } else {
    return 60;
  }
};
exports.getStatusBarHeight = getStatusBarHeight;
exports.getTitleBarHeight = getTitleBarHeight;
