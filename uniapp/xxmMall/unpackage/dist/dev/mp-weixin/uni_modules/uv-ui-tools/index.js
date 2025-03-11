"use strict";
const common_vendor = require("../../common/vendor.js");
const uni_modules_uvUiTools_libs_luchRequest_core_Request = require("./libs/luch-request/core/Request.js");
const uni_modules_uvUiTools_libs_mixin_mixin = require("./libs/mixin/mixin.js");
const uni_modules_uvUiTools_libs_mixin_mpMixin = require("./libs/mixin/mpMixin.js");
const uni_modules_uvUiTools_libs_mixin_mpShare = require("./libs/mixin/mpShare.js");
const uni_modules_uvUiTools_libs_util_route = require("./libs/util/route.js");
const uni_modules_uvUiTools_libs_function_index = require("./libs/function/index.js");
const uni_modules_uvUiTools_libs_function_debounce = require("./libs/function/debounce.js");
const uni_modules_uvUiTools_libs_function_throttle = require("./libs/function/throttle.js");
const uni_modules_uvUiTools_libs_function_test = require("./libs/function/test.js");
const uni_modules_uvUiTools_libs_function_colorGradient = require("./libs/function/colorGradient.js");
const uni_modules_uvUiTools_libs_config_config = require("./libs/config/config.js");
const uni_modules_uvUiTools_libs_function_platform = require("./libs/function/platform.js");
const $uv = {
  route: uni_modules_uvUiTools_libs_util_route.route,
  config: uni_modules_uvUiTools_libs_config_config.config,
  test: uni_modules_uvUiTools_libs_function_test.test,
  date: uni_modules_uvUiTools_libs_function_index.timeFormat,
  // 另名date
  ...uni_modules_uvUiTools_libs_function_index.index,
  colorGradient: uni_modules_uvUiTools_libs_function_colorGradient.colorGradient,
  hexToRgb: uni_modules_uvUiTools_libs_function_colorGradient.hexToRgb,
  rgbToHex: uni_modules_uvUiTools_libs_function_colorGradient.rgbToHex,
  colorToRgba: uni_modules_uvUiTools_libs_function_colorGradient.colorToRgba,
  http: new uni_modules_uvUiTools_libs_luchRequest_core_Request.Request(),
  debounce: uni_modules_uvUiTools_libs_function_debounce.debounce,
  throttle: uni_modules_uvUiTools_libs_function_throttle.throttle,
  platform: uni_modules_uvUiTools_libs_function_platform.platform,
  mixin: uni_modules_uvUiTools_libs_mixin_mixin.mixin,
  mpMixin: uni_modules_uvUiTools_libs_mixin_mpMixin.mpMixin
};
common_vendor.index.$uv = $uv;
const install = (Vue, options = {}) => {
  var _a, _b;
  const cloneMixin = uni_modules_uvUiTools_libs_function_index.deepClone(uni_modules_uvUiTools_libs_mixin_mixin.mixin);
  (_a = cloneMixin == null ? void 0 : cloneMixin.props) == null ? true : delete _a.customClass;
  (_b = cloneMixin == null ? void 0 : cloneMixin.props) == null ? true : delete _b.customStyle;
  Vue.mixin(cloneMixin);
  if (options.mpShare) {
    Vue.mixin(uni_modules_uvUiTools_libs_mixin_mpShare.mpShare);
  }
  Vue.config.globalProperties.$uv = $uv;
};
const uvUI = {
  install
};
exports.uvUI = uvUI;
//# sourceMappingURL=../../../.sourcemap/mp-weixin/uni_modules/uv-ui-tools/index.js.map
