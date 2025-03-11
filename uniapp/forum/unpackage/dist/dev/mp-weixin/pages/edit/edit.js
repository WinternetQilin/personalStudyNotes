"use strict";
const common_vendor = require("../../common/vendor.js");
const utils_tools = require("../../utils/tools.js");
if (!Array) {
  const _easycom_uv_button2 = common_vendor.resolveComponent("uv-button");
  _easycom_uv_button2();
}
const _easycom_uv_button = () => "../../uni_modules/uv-button/components/uv-button/uv-button.js";
if (!Math) {
  _easycom_uv_button();
}
const _sfc_main = {
  __name: "edit",
  setup(__props) {
    const forumCloudObj = common_vendor.Zs.importObject("forumCloudObj");
    common_vendor.Zs.database();
    let editorCtx = common_vendor.ref(null);
    let headShow = common_vendor.ref(false);
    let boldShow = common_vendor.ref(false);
    let italiShow = common_vendor.ref(false);
    let articleObj = common_vendor.ref({
      title: "",
      content: "",
      description: "",
      picUrls: [],
      province: ""
    });
    common_vendor.onLoad(async () => {
      articleObj.value.province = await utils_tools.getProvince();
    });
    function checkStatus(obj, detail, name) {
      if (detail.hasOwnProperty(name)) {
        obj.value = true;
      } else {
        obj.value = false;
      }
    }
    function onStatuschange(e) {
      console.log(e.detail);
      checkStatus(headShow, e.detail, "header");
      checkStatus(boldShow, e.detail, "bold");
      checkStatus(italiShow, e.detail, "italic");
    }
    async function getContents() {
      editorCtx.value.getContents({
        success: async (res) => {
          articleObj.value.content = res.html;
          articleObj.value.description = res.text.slice(0, 50);
          articleObj.value.picUrls = utils_tools.getImgSrc(res.html);
          common_vendor.index.showLoading({
            title: "发布中"
          });
          let dbres = null;
          try {
            dbres = await forumCloudObj.createArticle(articleObj.value);
          } catch (e) {
            common_vendor.index.showModal({
              title: "发布失败",
              content: e.errMsg,
              showCancel: false
            });
            return;
          }
          console.log(res);
          common_vendor.index.hideLoading();
          common_vendor.index.showToast({
            title: "发布成功",
            icon: "success"
          });
          setTimeout(() => {
            common_vendor.index.reLaunch({
              url: "/pages/index/index"
            });
          }, 1500);
        }
      });
    }
    function onClickHead() {
      headShow.value = !headShow.value;
      editorCtx.value.format("header", headShow.value ? "H2" : false);
    }
    function onBold() {
      boldShow.value = !boldShow.value;
      editorCtx.value.format("bold");
    }
    function onItalic() {
      italiShow.value = !italiShow.value;
      editorCtx.value.format("italic", italiShow.value ? "italic" : false);
    }
    function insertDivider() {
      editorCtx.value.insertDivider();
    }
    function insertImage() {
      common_vendor.index.chooseImage({
        success: async (res) => {
          common_vendor.index.showLoading({
            title: "上传中",
            mask: true
          });
          for (let f of res.tempFiles) {
            let res2 = null;
            try {
              res2 = await common_vendor.Zs.uploadFile({
                filePath: f.path,
                cloudPath: f.name
              });
            } catch (e) {
              common_vendor.index.showToast({
                title: "上传失败",
                icon: "error"
              });
            }
            editorCtx.value.insertImage({
              src: res2.fileID
            });
          }
          common_vendor.index.hideLoading();
          common_vendor.index.showToast({
            title: "上传成功",
            icon: "success"
          });
        }
      });
    }
    function onEditFocus() {
    }
    function onEditReady() {
      common_vendor.index.createSelectorQuery().in(this).select(".myEdit").fields({
        size: true,
        context: true
      }, (res) => {
        editorCtx.value = res.context;
      }).exec();
    }
    return (_ctx, _cache) => {
      return {
        a: common_vendor.unref(articleObj).title,
        b: common_vendor.o(($event) => common_vendor.unref(articleObj).title = $event.detail.value),
        c: common_vendor.o(onEditFocus),
        d: common_vendor.o(onEditReady),
        e: common_vendor.o(onStatuschange),
        f: common_vendor.o(getContents),
        g: common_vendor.p({
          type: "primary",
          text: "确认发表",
          disabled: !common_vendor.unref(articleObj).title.length
        }),
        h: common_vendor.n(common_vendor.unref(headShow) ? "active" : ""),
        i: common_vendor.o(onClickHead),
        j: common_vendor.n(common_vendor.unref(boldShow) ? "active" : ""),
        k: common_vendor.o(onBold),
        l: common_vendor.n(common_vendor.unref(italiShow) ? "active" : ""),
        m: common_vendor.o(onItalic),
        n: common_vendor.o(insertDivider),
        o: common_vendor.o(insertImage)
      };
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-2491cc6e"]]);
wx.createPage(MiniProgramPage);
