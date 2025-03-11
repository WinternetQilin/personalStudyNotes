"use strict";
const common_vendor = require("../../common/vendor.js");
const utils_system = require("../../utils/system.js");
const api_apis = require("../../api/apis.js");
if (!Array) {
  const _easycom_uni_icons2 = common_vendor.resolveComponent("uni-icons");
  const _easycom_uni_dateformat2 = common_vendor.resolveComponent("uni-dateformat");
  const _easycom_uni_rate2 = common_vendor.resolveComponent("uni-rate");
  const _easycom_uni_popup2 = common_vendor.resolveComponent("uni-popup");
  (_easycom_uni_icons2 + _easycom_uni_dateformat2 + _easycom_uni_rate2 + _easycom_uni_popup2)();
}
const _easycom_uni_icons = () => "../../uni_modules/uni-icons/components/uni-icons/uni-icons.js";
const _easycom_uni_dateformat = () => "../../uni_modules/uni-dateformat/components/uni-dateformat/uni-dateformat.js";
const _easycom_uni_rate = () => "../../uni_modules/uni-rate/components/uni-rate/uni-rate.js";
const _easycom_uni_popup = () => "../../uni_modules/uni-popup/components/uni-popup/uni-popup.js";
if (!Math) {
  (_easycom_uni_icons + _easycom_uni_dateformat + _easycom_uni_rate + _easycom_uni_popup)();
}
const _sfc_main = {
  __name: "preview",
  setup(__props) {
    let isShowMask = common_vendor.ref(true);
    let infoPopup = common_vendor.ref(null);
    let rateSourcePopup = common_vendor.ref(null);
    let userRate = common_vendor.ref(0);
    let bigPicList = common_vendor.ref([]);
    let currentId = common_vendor.ref(null);
    let currentIdx = common_vendor.ref(-1);
    let currentInfo = common_vendor.ref({
      score: 0
    });
    let isRated = common_vendor.ref(false);
    common_vendor.onLoad((e) => {
      currentId.value = e.id;
      currentIdx.value = bigPicList.value.findIndex((item) => item._id == currentId.value);
      currentInfo.value = bigPicList.value[currentIdx.value];
    });
    async function onClickedDownLoadBtn() {
      let res = await api_apis.apiWriteDownload({
        classid: currentInfo.value.classid,
        wallId: currentInfo.value._id
      });
      if (res.errCode != 0) {
        common_vendor.index.hideLoading();
        return;
      }
      common_vendor.index.getImageInfo({
        src: currentInfo.value.picurl
      }).then((imageInfo) => {
        common_vendor.index.showLoading({
          title: "正在保存",
          mask: true
        });
        common_vendor.index.saveImageToPhotosAlbum({
          filePath: imageInfo.path
        }).then((saveImageInfo) => {
          common_vendor.index.hideLoading();
          common_vendor.index.showToast({
            title: "保存成功",
            icon: "none"
          });
        }).catch((saveImageInfo) => {
          common_vendor.index.hideLoading();
          console.log(saveImageInfo);
          if (saveImageInfo.errMsg == "saveImageToPhotosAlbum:fail auth deny") {
            common_vendor.index.showModal({
              title: "提示",
              content: "保存失败，请开启保存到相册权限"
            }).then((res2) => {
              if (res2.confirm) {
                common_vendor.index.openSetting().then((settings) => {
                  if (settings.authSetting["scope.writePhotosAlbum"]) {
                    common_vendor.index.showToast({
                      title: "获取授权成功",
                      icon: "none"
                    });
                  } else {
                    common_vendor.index.showToast({
                      title: "获取授权失败",
                      icon: "none"
                    });
                  }
                });
              }
            });
          } else {
            common_vendor.index.showToast({
              title: "保存失败,请重试",
              icon: "none"
            });
          }
        });
      });
    }
    function onClickedInfo() {
      infoPopup.value.open();
    }
    function onClickedInfoCloseBtn() {
      infoPopup.value.close();
    }
    function onClickedRateSource() {
      if (currentInfo.value.userScore) {
        isRated.value = true;
        userRate.value = currentInfo.value.userScore;
      }
      rateSourcePopup.value.open();
    }
    function onClickedRateSourceCloseBtn() {
      rateSourcePopup.value.close();
      isRated.value = false;
      userRate.value = 0;
    }
    async function onClickedConfirmBtn() {
      let {
        classid,
        _id: wallId
      } = currentInfo.value;
      let res = await api_apis.apiGetSetupScore({
        classid,
        wallId,
        userScore: userRate.value
      });
      if (res.errCode == 0) {
        common_vendor.index.showToast({
          title: "评分成功",
          icon: "success"
        });
        bigPicList.value[currentIdx.value].userScore = userRate.value;
        common_vendor.index.setStorageSync("classifyPicList", bigPicList.value);
        onClickedRateSourceCloseBtn();
        userRate.value = 0;
      }
    }
    function onClickedBackBtn() {
      common_vendor.index.navigateBack({
        fail: () => {
          common_vendor.index.reLaunch({
            url: "/pages/index/index"
          });
        }
      });
    }
    let classifyPicList = common_vendor.index.getStorageSync("classifyPicList") || [];
    bigPicList.value = classifyPicList.map((item) => {
      return {
        ...item,
        picurl: item.smallPicurl.replace("_small.webp", ".jpg")
      };
    });
    function onSwiperChange(e) {
      currentIdx.value = e.detail.current;
      currentInfo.value = bigPicList.value[currentIdx.value];
    }
    return (_ctx, _cache) => {
      return common_vendor.e({
        a: common_vendor.f(common_vendor.unref(bigPicList), (item, index, i0) => {
          return common_vendor.e({
            a: index == common_vendor.unref(currentIdx) || index == common_vendor.unref(currentIdx) - 1 || index == common_vendor.unref(currentIdx) + 1
          }, index == common_vendor.unref(currentIdx) || index == common_vendor.unref(currentIdx) - 1 || index == common_vendor.unref(currentIdx) + 1 ? {
            b: common_vendor.o(($event) => common_vendor.isRef(isShowMask) ? isShowMask.value = !common_vendor.unref(isShowMask) : isShowMask = !common_vendor.unref(isShowMask), item._id),
            c: item.picurl
          } : {}, {
            d: item._id
          });
        }),
        b: common_vendor.unref(currentIdx),
        c: common_vendor.o(onSwiperChange),
        d: common_vendor.unref(isShowMask)
      }, common_vendor.unref(isShowMask) ? {
        e: common_vendor.p({
          type: "left",
          size: "30",
          color: "#fff"
        }),
        f: common_vendor.o(onClickedBackBtn),
        g: common_vendor.unref(utils_system.getStatusBarHeight)() + "px",
        h: common_vendor.t(common_vendor.unref(currentIdx) + 1),
        i: common_vendor.t(common_vendor.unref(bigPicList).length),
        j: common_vendor.p({
          date: /* @__PURE__ */ new Date(),
          format: "hh:mm"
        }),
        k: common_vendor.p({
          date: /* @__PURE__ */ new Date(),
          format: "MM月dd日"
        }),
        l: common_vendor.p({
          type: "info",
          size: "30",
          color: "black"
        }),
        m: common_vendor.o(onClickedInfo),
        n: common_vendor.p({
          type: "star",
          size: "30",
          color: "black"
        }),
        o: common_vendor.t(common_vendor.unref(currentInfo).score),
        p: common_vendor.o(onClickedRateSource),
        q: common_vendor.p({
          type: "download",
          size: "30",
          color: "black"
        }),
        r: common_vendor.o(onClickedDownLoadBtn)
      } : {}, {
        s: common_vendor.o(onClickedInfoCloseBtn),
        t: common_vendor.p({
          type: "closeempty",
          size: "20",
          color: "#999"
        }),
        v: common_vendor.t(common_vendor.unref(currentInfo)._id),
        w: common_vendor.t(common_vendor.unref(currentInfo).nickname),
        x: common_vendor.p({
          readonly: true,
          value: common_vendor.unref(currentInfo).score
        }),
        y: common_vendor.t(common_vendor.unref(currentInfo).score),
        z: common_vendor.t(common_vendor.unref(currentInfo).description),
        A: common_vendor.f(common_vendor.unref(currentInfo).tabs, (item, k0, i0) => {
          return {
            a: common_vendor.t(item),
            b: item
          };
        }),
        B: common_vendor.sr(infoPopup, "2dad6c07-6", {
          "k": "infoPopup"
        }),
        C: common_vendor.p({
          type: "bottom"
        }),
        D: common_vendor.t(common_vendor.unref(isRated) ? "已经评过分了" : "壁纸评分"),
        E: common_vendor.o(onClickedRateSourceCloseBtn),
        F: common_vendor.p({
          type: "closeempty",
          size: "20",
          color: "#999"
        }),
        G: common_vendor.o(($event) => common_vendor.isRef(userRate) ? userRate.value = $event : userRate = $event),
        H: common_vendor.p({
          readonly: common_vendor.unref(isRated),
          allowHalf: true,
          modelValue: common_vendor.unref(userRate)
        }),
        I: common_vendor.t(common_vendor.unref(userRate)),
        J: common_vendor.o(onClickedConfirmBtn),
        K: !common_vendor.unref(userRate) || common_vendor.unref(isRated),
        L: common_vendor.sr(rateSourcePopup, "2dad6c07-9", {
          "k": "rateSourcePopup"
        }),
        M: common_vendor.p({
          ["is-mask-click"]: false
        })
      });
    };
  }
};
const MiniProgramPage = /* @__PURE__ */ common_vendor._export_sfc(_sfc_main, [["__scopeId", "data-v-2dad6c07"]]);
wx.createPage(MiniProgramPage);
