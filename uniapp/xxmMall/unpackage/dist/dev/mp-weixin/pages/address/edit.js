"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uv_input2 = common_vendor.resolveComponent("uv-input");
  const _easycom_uv_form_item2 = common_vendor.resolveComponent("uv-form-item");
  const _component_uni_data_picker = common_vendor.resolveComponent("uni-data-picker");
  const _easycom_uv_switch2 = common_vendor.resolveComponent("uv-switch");
  const _easycom_uv_button2 = common_vendor.resolveComponent("uv-button");
  const _easycom_uv_form2 = common_vendor.resolveComponent("uv-form");
  (_easycom_uv_input2 + _easycom_uv_form_item2 + _component_uni_data_picker + _easycom_uv_switch2 + _easycom_uv_button2 + _easycom_uv_form2)();
}
const _easycom_uv_input = () => "../../uni_modules/uv-input/components/uv-input/uv-input.js";
const _easycom_uv_form_item = () => "../../uni_modules/uv-form/components/uv-form-item/uv-form-item.js";
const _easycom_uv_switch = () => "../../uni_modules/uv-switch/components/uv-switch/uv-switch.js";
const _easycom_uv_button = () => "../../uni_modules/uv-button/components/uv-button/uv-button.js";
const _easycom_uv_form = () => "../../uni_modules/uv-form/components/uv-form/uv-form.js";
if (!Math) {
  (_easycom_uv_input + _easycom_uv_form_item + _easycom_uv_switch + _easycom_uv_button + _easycom_uv_form)();
}
const _sfc_main = {
  __name: "edit",
  setup(__props) {
    let uForm = common_vendor.ref(null);
    let addressForm = common_vendor.ref({
      username: "",
      mobile: "",
      address: "",
      selected: false,
      area_code: "",
      area_name: ""
    });
    let addressRules = {
      username: [{
        required: true,
        message: "姓名是必填的",
        trigger: ["blur", "change"]
      }, {
        min: 2,
        max: 8,
        message: "长度在2-8个字符之间",
        trigger: ["blur", "change"]
      }],
      mobile: [{
        required: true,
        message: "电话是必填的",
        trigger: ["blur", "change"]
      }, {
        validator: (rule, value, callback) => {
          return common_vendor.index.$uv.test.mobile(value);
        },
        message: "手机号格式不正确",
        trigger: ["change", "blur"]
      }],
      address: [{
        required: true,
        message: "地址是必填的",
        trigger: ["blur", "change"]
      }]
    };
    function onSubmit() {
      uForm.value.validate().then(async (res) => {
        let title;
        if (this.addressForm._id) {
          await addressCloudObj.updateOne(this.addressForm);
          title = "修改成功";
        } else {
          await addressCloudObj.add(this.addressForm);
          title = "新增成功";
        }
        common_vendor.index.showToast({
          title,
          mask: true
        });
        setTimeout(() => {
          common_vendor.index.navigateBack();
        }, 1e3);
      }).catch((errors) => {
        common_vendor.index.$uv.toast("校验失败");
      });
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.o(($event) => common_vendor.unref(addressForm).username = $event),
        b: common_vendor.p({
          placeholder: "请输入姓名",
          modelValue: common_vendor.unref(addressForm).username
        }),
        c: common_vendor.p({
          label: "姓名",
          prop: "username"
        }),
        d: common_vendor.o(($event) => common_vendor.unref(addressForm).mobile = $event),
        e: common_vendor.p({
          placeholder: "请输入联系电话",
          modelValue: common_vendor.unref(addressForm).mobile
        }),
        f: common_vendor.p({
          label: "联系电话",
          prop: "mobile"
        }),
        g: common_vendor.o(_ctx.pickerChange),
        h: common_vendor.o(($event) => common_vendor.unref(addressForm).area_code = $event),
        i: common_vendor.p({
          placeholder: "请选择地址",
          ["popup-title"]: "请选择所在地区",
          collection: "opendb-city-china",
          field: "code as value, name as text",
          orderby: "value asc",
          ["self-field"]: "code",
          ["parent-field"]: "parent_code",
          modelValue: common_vendor.unref(addressForm).area_code
        }),
        j: common_vendor.p({
          label: "选择地区"
        }),
        k: common_vendor.o(($event) => common_vendor.unref(addressForm).address = $event),
        l: common_vendor.p({
          placeholder: "请输入街道门牌号",
          modelValue: common_vendor.unref(addressForm).address
        }),
        m: common_vendor.p({
          label: "详细地址",
          prop: "address"
        }),
        n: common_vendor.o(($event) => common_vendor.unref(addressForm).selected = $event),
        o: common_vendor.p({
          inactiveColor: "#eee",
          modelValue: common_vendor.unref(addressForm).selected
        }),
        p: common_vendor.p({
          label: "是否默认"
        }),
        q: common_vendor.o(onSubmit),
        r: common_vendor.p({
          type: "primary"
        }),
        s: common_vendor.sr(uForm, "dcb1f0d8-0", {
          "k": "uForm"
        }),
        t: common_vendor.p({
          labelPosition: "top",
          model: common_vendor.unref(addressForm),
          rules: common_vendor.unref(addressRules),
          labelWidth: "100"
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-dcb1f0d8"]]);
wx.createPage(MiniProgramPage);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/address/edit.js.map
