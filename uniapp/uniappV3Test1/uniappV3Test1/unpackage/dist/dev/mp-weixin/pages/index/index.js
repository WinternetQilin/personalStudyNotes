"use strict";
const common_vendor = require("../../common/vendor.js");
const _sfc_main = {
  __name: "index",
  setup(__props) {
    let postArr = common_vendor.ref([]);
    async function request() {
      postArr = await common_vendor.index.request({
        url: "https://jsonplaceholder.typicode.com/posts"
      });
      console.log(postArr);
    }
    request();
    const lists = common_vendor.ref([
      {
        id: 111,
        title: "刚满18岁"
      },
      {
        id: 222,
        title: "我不吃牛肉"
      },
      {
        id: 333,
        title: "遥遥领先"
      },
      {
        id: 444,
        title: "哪里贵了"
      }
    ]);
    let inputText = common_vendor.ref("");
    function onDel(id) {
      lists.value.splice(lists.value.findIndex((li) => li.id == id), 1);
    }
    function onPublish() {
      let newid = lists.value[lists.value.length - 1].id + 111;
      lists.value.push({ id: newid, title: inputText.value });
      inputText.value = "";
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.f(lists.value, (item, index, i0) => {
          return {
            a: common_vendor.t(index + 1),
            b: common_vendor.t(item.title),
            c: common_vendor.o(($event) => onDel(item.id), item.id),
            d: item.id
          };
        }),
        b: common_vendor.t(lists.value.length),
        c: common_vendor.unref(inputText),
        d: common_vendor.o(($event) => common_vendor.isRef(inputText) ? inputText.value = $event.detail.value : inputText = $event.detail.value),
        e: common_vendor.unref(inputText) === "" ? true : false,
        f: common_vendor.o(onPublish),
        g: common_vendor.f(common_vendor.unref(postArr), (item, k0, i0) => {
          return {
            a: common_vendor.t(item.id),
            b: common_vendor.t(item.title),
            c: item.id
          };
        })
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-1cf27b2a"]]);
wx.createPage(MiniProgramPage);
