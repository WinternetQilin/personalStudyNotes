"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uv_icon2 = common_vendor.resolveComponent("uv-icon");
  const _easycom_uni_popup_dialog2 = common_vendor.resolveComponent("uni-popup-dialog");
  const _easycom_uni_popup2 = common_vendor.resolveComponent("uni-popup");
  (_easycom_uv_icon2 + _easycom_uni_popup_dialog2 + _easycom_uni_popup2)();
}
const _easycom_uv_icon = () => "../../uni_modules/uv-icon/components/uv-icon/uv-icon.js";
const _easycom_uni_popup_dialog = () => "../../uni_modules/uni-popup/components/uni-popup-dialog/uni-popup-dialog.js";
const _easycom_uni_popup = () => "../../uni_modules/uni-popup/components/uni-popup/uni-popup.js";
if (!Math) {
  (_easycom_uv_icon + _easycom_uni_popup_dialog + _easycom_uni_popup)();
}
const _sfc_main = {
  __name: "category",
  setup(__props) {
    let categoryList = [{
      name: "1"
    }];
    let iptValue = common_vendor.ref("");
    let updateID = common_vendor.ref(null);
    let inputDialog = common_vendor.ref(null);
    function clickAdd() {
      iptValue.value = "";
      updateID.value = null;
      inputDialog.value.open();
    }
    async function dialogConfirm(e) {
      iptValue.value = e;
      if (this.updateID) {
        await db.collection("kt-mall-category").doc(this.updateID).update({
          name: this.iptValue
        });
      } else {
        await db.collection("kt-mall-category").add({
          name: this.iptValue
        });
      }
      this.getCateGory();
    }
    function updateData(id, name) {
    }
    function deleteData(id) {
      common_vendor.index.showModal({
        content: "是否删除该分类?",
        success: (res) => {
          if (res.confirm)
            ;
        },
        fail: (err) => {
          common_vendor.index.__f__("log", "at pages_manage/category/category.vue:85", err);
        }
      });
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.p({
          name: "plus",
          color: "#576b95",
          size: "22"
        }),
        b: common_vendor.o(clickAdd),
        c: common_vendor.f(common_vendor.unref(categoryList), (item, index, i0) => {
          return {
            a: common_vendor.t(item.name),
            b: common_vendor.o(($event) => updateData(item._id, item.name), item._id),
            c: "25c05f0c-1-" + i0,
            d: common_vendor.o(($event) => deleteData(item._id), item._id),
            e: "25c05f0c-2-" + i0,
            f: item._id
          };
        }),
        d: common_vendor.p({
          name: "edit-pen",
          size: "26",
          color: "#576b95"
        }),
        e: common_vendor.p({
          name: "trash",
          size: "26",
          color: "#EC544F"
        }),
        f: common_vendor.o(dialogConfirm),
        g: common_vendor.p({
          mode: "input",
          value: common_vendor.unref(iptValue),
          placeholder: "请输入分类名称",
          title: "分类名称"
        }),
        h: common_vendor.sr(inputDialog, "25c05f0c-3", {
          "k": "inputDialog"
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-25c05f0c"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages_manage/category/category.js.map
