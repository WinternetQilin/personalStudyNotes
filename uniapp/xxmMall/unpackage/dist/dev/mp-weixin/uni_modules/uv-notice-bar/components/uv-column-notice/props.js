"use strict";
var _a, _b;
const common_vendor = require("../../../../common/vendor.js");
const props = {
  props: {
    // 显示的内容，字符串
    text: {
      type: [Array],
      default: ""
    },
    // 是否显示左侧的音量图标
    icon: {
      type: [String, Boolean, null],
      default: "volume"
    },
    // 通告模式，link-显示右箭头，closable-显示右侧关闭图标
    mode: {
      type: String,
      default: ""
    },
    // 文字颜色，各图标也会使用文字颜色
    color: {
      type: String,
      default: "#f9ae3d"
    },
    // 背景颜色
    bgColor: {
      type: String,
      default: "#fdf6ec"
    },
    // 字体大小，单位px
    fontSize: {
      type: [String, Number],
      default: 14
    },
    // 水平滚动时的滚动速度，即每秒滚动多少px(px)，这有利于控制文字无论多少时，都能有一个恒定的速度
    speed: {
      type: [String, Number],
      default: 80
    },
    // direction = row时，是否使用步进形式滚动
    step: {
      type: Boolean,
      default: false
    },
    // 滚动一个周期的时间长，单位ms
    duration: {
      type: [String, Number],
      default: 1500
    },
    // 是否禁止用手滑动切换，仅`direction="column"生效`
    // 目前HX2.6.11，只支持App 2.5.5+、H5 2.5.5+、支付宝小程序、字节跳动小程序
    disableTouch: {
      type: Boolean,
      default: true
    },
    // 是否禁止滚动，仅`direction="column"生效`
    disableScroll: {
      type: Boolean,
      default: false
    },
    ...(_b = (_a = common_vendor.index.$uv) == null ? void 0 : _a.props) == null ? void 0 : _b.columnNotice
  }
};
exports.props = props;
//# sourceMappingURL=../../../../../.sourcemap/mp-weixin/uni_modules/uv-notice-bar/components/uv-column-notice/props.js.map
