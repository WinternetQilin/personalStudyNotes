"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uni_file_picker2 = common_vendor.resolveComponent("uni-file-picker");
  const _easycom_uni_data_select2 = common_vendor.resolveComponent("uni-data-select");
  const _easycom_uni_popup2 = common_vendor.resolveComponent("uni-popup");
  (_easycom_uni_file_picker2 + _easycom_uni_data_select2 + _easycom_uni_popup2)();
}
const _easycom_uni_file_picker = () => "../../uni_modules/uni-file-picker/components/uni-file-picker/uni-file-picker.js";
const _easycom_uni_data_select = () => "../../uni_modules/uni-data-select/components/uni-data-select/uni-data-select.js";
const _easycom_uni_popup = () => "../../uni_modules/uni-popup/components/uni-popup/uni-popup.js";
if (!Math) {
  (_easycom_uni_file_picker + _easycom_uni_data_select + _easycom_uni_popup)();
}
const _sfc_main = {
  __name: "piclist",
  setup(__props) {
    const db = common_vendor.Zs.database();
    const listData = common_vendor.ref([]);
    const popup = common_vendor.ref(null);
    const formData = common_vendor.ref({
      description: "",
      picUrl: {},
      classId: ""
    });
    const disabled = common_vendor.computed(() => {
      if (formData.value.description && Object.keys(formData.value.picUrl).length > 0 && formData.value.classId) {
        return false;
      }
      return true;
    });
    const getData = async () => {
      console.log("获取数据");
      let wallTemp = await db.collection("demo-wallpaper").getTemp();
      let classTemp = await db.collection("demo-classify").getTemp();
      let res = await db.collection(wallTemp, classTemp).get();
      console.log(res);
      listData.value = res.result.data;
    };
    const handleAdd = () => {
      popup.value.open();
    };
    const onSubmit = async () => {
      console.log("点击提交表单");
      let res = await db.collection("demo-wallpaper").add(formData.value);
      console.log(res);
      common_vendor.index.showToast({
        title: "提交成功",
        icon: "success"
      });
      popup.value.close();
      formData.value = {
        description: "",
        picUrl: {},
        classId: ""
      };
      getData();
    };
    const onCancel = () => {
      popup.value.close();
    };
    getData();
    return (_ctx, _cache) => {
      return {
        a: common_vendor.o(handleAdd),
        b: common_vendor.f(listData.value, (item, k0, i0) => {
          return {
            a: item.picUrl.url,
            b: common_vendor.t(item.description),
            c: common_vendor.t(item.classId[0].name),
            d: item._id
          };
        }),
        c: common_vendor.o(($event) => formData.value.picUrl = $event),
        d: common_vendor.p({
          ["return-type"]: "object",
          modelValue: formData.value.picUrl
        }),
        e: formData.value.description,
        f: common_vendor.o(($event) => formData.value.description = $event.detail.value),
        g: common_vendor.o(($event) => formData.value.classId = $event),
        h: common_vendor.p({
          collection: "demo-classify",
          field: "_id as value, name as text",
          where: "status == true",
          label: "图片分类",
          clear: false,
          modelValue: formData.value.classId
        }),
        i: common_vendor.o(onSubmit),
        j: disabled.value,
        k: common_vendor.o(onCancel),
        l: common_vendor.t(formData.value),
        m: common_vendor.sr(popup, "51ece828-0", {
          "k": "popup"
        }),
        n: common_vendor.p({
          ["border-radius"]: "10px 10px 0 0",
          ["is-mask-click"]: false
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-51ece828"]]);
wx.createPage(MiniProgramPage);
