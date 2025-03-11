"use strict";
const common_vendor = require("../../common/vendor.js");
if (!Array) {
  const _easycom_uni_icons2 = common_vendor.resolveComponent("uni-icons");
  _easycom_uni_icons2();
}
const _easycom_uni_icons = () => "../../uni_modules/uni-icons/components/uni-icons/uni-icons.js";
if (!Math) {
  _easycom_uni_icons();
}
const _sfc_main = {
  __name: "classify",
  setup(__props) {
    const demoObj = common_vendor.Zs.importObject("demoObj");
    const classname = common_vendor.ref("");
    const classList = common_vendor.ref([]);
    const db = common_vendor.Zs.database();
    const getClassify = async () => {
      console.log("获取分类");
      let res = await demoObj.getClassify();
      console.log(res.data);
      classList.value = res.data;
    };
    const switchChange = async (e, classId) => {
      console.log(e, classId);
      let res = await db.collection("demo-classify").doc(classId).update({
        status: e.detail.value
      });
      console.log(res);
      common_vendor.index.showToast({
        title: "修改成功",
        icon: "success"
      });
    };
    const handleRemove = async (classId) => {
      console.log("删除方法", classId);
      let res = await db.collection("demo-classify").doc(classId).remove();
      console.log(res);
      getClassify();
    };
    const onConfirm = async () => {
      console.log("确认提交添加");
      let res = await db.collection("demo-classify").add({
        name: classname.value
      });
      console.log(res);
      classname.value = "";
      getClassify();
    };
    getClassify();
    return (_ctx, _cache) => {
      return {
        a: common_vendor.o(onConfirm),
        b: classname.value,
        c: common_vendor.o(($event) => classname.value = $event.detail.value),
        d: common_vendor.f(classList.value, (item, k0, i0) => {
          return {
            a: common_vendor.t(item.name),
            b: item.status,
            c: common_vendor.o((e) => switchChange(e, item._id), item._id),
            d: common_vendor.o(($event) => handleRemove(item._id), item._id),
            e: "3a660802-0-" + i0,
            f: item._id
          };
        }),
        e: common_vendor.p({
          type: "trash",
          size: "26"
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-3a660802"]]);
wx.createPage(MiniProgramPage);
