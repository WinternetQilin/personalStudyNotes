"use strict";
function settle(resolve, reject, response) {
  const validateStatus = response.config.validateStatus;
  const status = response.statusCode;
  if (status && (!validateStatus || validateStatus(status))) {
    resolve(response);
  } else {
    reject(response);
  }
}
exports.settle = settle;
//# sourceMappingURL=../../../../../../.sourcemap/mp-weixin/uni_modules/uv-ui-tools/libs/luch-request/core/settle.js.map
