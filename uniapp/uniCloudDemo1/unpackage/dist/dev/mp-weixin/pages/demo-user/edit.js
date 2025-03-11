"use strict";
const common_vendor = require("../../common/vendor.js");
const js_sdk_validator_demoUser = require("../../js_sdk/validator/demo-user.js");
const db = common_vendor.Zs.database();
const dbCollectionName = "demo-user";
function getValidator(fields) {
  let result = {};
  for (let key in js_sdk_validator_demoUser.validator) {
    if (fields.indexOf(key) > -1) {
      result[key] = js_sdk_validator_demoUser.validator[key];
    }
  }
  return result;
}
const _sfc_main = {
  data() {
    let formData = {
      "name": "",
      "age": null,
      "gender": 2
    };
    return {
      formData,
      formOptions: {
        "gender_localdata": [
          {
            "text": "男",
            "value": 0
          },
          {
            "text": "女",
            "value": 1
          },
          {
            "text": "保密",
            "value": 2
          }
        ]
      },
      rules: {
        ...getValidator(Object.keys(formData))
      }
    };
  },
  onLoad(e) {
    if (e.id) {
      const id = e.id;
      this.formDataId = id;
      this.getDetail(id);
    }
  },
  onReady() {
    this.$refs.form.setRules(this.rules);
  },
  methods: {
    /**
     * 验证表单并提交
     */
    submit() {
      common_vendor.index.showLoading({
        mask: true
      });
      this.$refs.form.validate().then((res) => {
        return this.submitForm(res);
      }).catch(() => {
      }).finally(() => {
        common_vendor.index.hideLoading();
      });
    },
    /**
     * 提交表单
     */
    submitForm(value) {
      return db.collection(dbCollectionName).doc(this.formDataId).update(value).then((res) => {
        common_vendor.index.showToast({
          icon: "none",
          title: "修改成功"
        });
        this.getOpenerEventChannel().emit("refreshData");
        setTimeout(() => common_vendor.index.navigateBack(), 500);
      }).catch((err) => {
        common_vendor.index.showModal({
          content: err.message || "请求服务失败",
          showCancel: false
        });
      });
    },
    /**
     * 获取表单数据
     * @param {Object} id
     */
    getDetail(id) {
      common_vendor.index.showLoading({
        mask: true
      });
      db.collection(dbCollectionName).doc(id).field("name,age,gender").get().then((res) => {
        const data = res.result.data[0];
        if (data) {
          this.formData = data;
        }
      }).catch((err) => {
        common_vendor.index.showModal({
          content: err.message || "请求服务失败",
          showCancel: false
        });
      }).finally(() => {
        common_vendor.index.hideLoading();
      });
    }
  }
};
if (!Array) {
  const _easycom_uni_easyinput2 = common_vendor.resolveComponent("uni-easyinput");
  const _easycom_uni_forms_item2 = common_vendor.resolveComponent("uni-forms-item");
  const _easycom_uni_data_checkbox2 = common_vendor.resolveComponent("uni-data-checkbox");
  const _easycom_uni_forms2 = common_vendor.resolveComponent("uni-forms");
  (_easycom_uni_easyinput2 + _easycom_uni_forms_item2 + _easycom_uni_data_checkbox2 + _easycom_uni_forms2)();
}
const _easycom_uni_easyinput = () => "../../uni_modules/uni-easyinput/components/uni-easyinput/uni-easyinput.js";
const _easycom_uni_forms_item = () => "../../uni_modules/uni-forms/components/uni-forms-item/uni-forms-item.js";
const _easycom_uni_data_checkbox = () => "../../uni_modules/uni-data-checkbox/components/uni-data-checkbox/uni-data-checkbox.js";
const _easycom_uni_forms = () => "../../uni_modules/uni-forms/components/uni-forms/uni-forms.js";
if (!Math) {
  (_easycom_uni_easyinput + _easycom_uni_forms_item + _easycom_uni_data_checkbox + _easycom_uni_forms)();
}
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return {
    a: common_vendor.o(($event) => $data.formData.name = $event),
    b: common_vendor.p({
      placeholder: "请输入用户名",
      modelValue: $data.formData.name
    }),
    c: common_vendor.p({
      name: "name",
      label: "用户名"
    }),
    d: common_vendor.o(($event) => $data.formData.age = $event),
    e: common_vendor.p({
      placeholder: "请输入年龄",
      type: "number",
      modelValue: $data.formData.age
    }),
    f: common_vendor.p({
      name: "age",
      label: "年龄"
    }),
    g: common_vendor.o(($event) => $data.formData.gender = $event),
    h: common_vendor.p({
      localdata: $data.formOptions.gender_localdata,
      modelValue: $data.formData.gender
    }),
    i: common_vendor.p({
      name: "gender",
      label: "性别"
    }),
    j: common_vendor.o((...args) => $options.submit && $options.submit(...args)),
    k: common_vendor.sr("form", "6a6edb22-0"),
    l: common_vendor.p({
      model: $data.formData,
      ["validate-trigger"]: "submit",
      ["err-show-type"]: "toast"
    })
  };
}
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["render", _sfc_render]]);
wx.createPage(MiniProgramPage);
