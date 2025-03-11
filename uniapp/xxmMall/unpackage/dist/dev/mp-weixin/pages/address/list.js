"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uv_button2 = common_vendor.resolveComponent("uv-button");
  const _easycom_uv_empty2 = common_vendor.resolveComponent("uv-empty");
  (_easycom_uv_button2 + _easycom_uv_empty2)();
}
const _easycom_uv_button = () => "../../uni_modules/uv-button/components/uv-button/uv-button.js";
const _easycom_uv_empty = () => "../../uni_modules/uv-empty/components/uv-empty/uv-empty.js";
if (!Math) {
  (_easycom_uv_button + _easycom_uv_empty)();
}
const _sfc_main = {
  __name: "list",
  setup(__props) {
    async function setDefault(id) {
      await addressCloudObj.updateDef(id);
      this.getAddressData();
    }
    function goUpdate(id) {
      common_vendor.index.navigateTo({
        url: "./edit?id=" + id
      });
    }
    function selectAddress(item) {
      let {
        address,
        area_name,
        username,
        mobile
      } = item;
      let deliveryData = {
        address: area_name + address,
        username,
        mobile
      };
      common_vendor.index.$emit("selectAddressEvent", deliveryData);
      common_vendor.index.navigateBack();
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: _ctx.addressList.length
      }, _ctx.addressList.length ? {
        b: common_vendor.f(_ctx.addressList, (item, k0, i0) => {
          return common_vendor.e({
            a: common_vendor.t(item.username),
            b: common_vendor.t(item.mobile),
            c: item.selected
          }, item.selected ? {
            d: "90a3874e-0-" + i0,
            e: common_vendor.p({
              color: "#EC544F",
              plain: true,
              size: "mini",
              text: "默认地址"
            })
          } : {
            f: common_vendor.o(($event) => setDefault(item._id), item._id),
            g: "90a3874e-1-" + i0,
            h: common_vendor.p({
              color: "#666",
              plain: true,
              size: "mini",
              text: "设为默认"
            })
          }, {
            i: common_vendor.t(item.area_name + item.address),
            j: item._id,
            k: common_vendor.o(($event) => goUpdate(item._id), item._id),
            l: common_vendor.o(($event) => selectAddress(item), item._id)
          });
        })
      } : {
        c: common_vendor.p({
          text: "还未添加过地址",
          icon: "http://cdn.uviewui.com/uview/empty/message.png"
        })
      });
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-90a3874e"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/address/list.js.map
