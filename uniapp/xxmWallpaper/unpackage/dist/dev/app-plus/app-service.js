if (typeof Promise !== "undefined" && !Promise.prototype.finally) {
  Promise.prototype.finally = function(callback) {
    const promise = this.constructor;
    return this.then(
      (value) => promise.resolve(callback()).then(() => value),
      (reason) => promise.resolve(callback()).then(() => {
        throw reason;
      })
    );
  };
}
;
if (typeof uni !== "undefined" && uni && uni.requireGlobal) {
  const global2 = uni.requireGlobal();
  ArrayBuffer = global2.ArrayBuffer;
  Int8Array = global2.Int8Array;
  Uint8Array = global2.Uint8Array;
  Uint8ClampedArray = global2.Uint8ClampedArray;
  Int16Array = global2.Int16Array;
  Uint16Array = global2.Uint16Array;
  Int32Array = global2.Int32Array;
  Uint32Array = global2.Uint32Array;
  Float32Array = global2.Float32Array;
  Float64Array = global2.Float64Array;
  BigInt64Array = global2.BigInt64Array;
  BigUint64Array = global2.BigUint64Array;
}
;
if (uni.restoreGlobal) {
  uni.restoreGlobal(Vue, weex, plus, setTimeout, clearTimeout, setInterval, clearInterval);
}
(function(vue) {
  "use strict";
  const fontData = [
    {
      "font_class": "arrow-down",
      "unicode": ""
    },
    {
      "font_class": "arrow-left",
      "unicode": ""
    },
    {
      "font_class": "arrow-right",
      "unicode": ""
    },
    {
      "font_class": "arrow-up",
      "unicode": ""
    },
    {
      "font_class": "auth",
      "unicode": ""
    },
    {
      "font_class": "auth-filled",
      "unicode": ""
    },
    {
      "font_class": "back",
      "unicode": ""
    },
    {
      "font_class": "bars",
      "unicode": ""
    },
    {
      "font_class": "calendar",
      "unicode": ""
    },
    {
      "font_class": "calendar-filled",
      "unicode": ""
    },
    {
      "font_class": "camera",
      "unicode": ""
    },
    {
      "font_class": "camera-filled",
      "unicode": ""
    },
    {
      "font_class": "cart",
      "unicode": ""
    },
    {
      "font_class": "cart-filled",
      "unicode": ""
    },
    {
      "font_class": "chat",
      "unicode": ""
    },
    {
      "font_class": "chat-filled",
      "unicode": ""
    },
    {
      "font_class": "chatboxes",
      "unicode": ""
    },
    {
      "font_class": "chatboxes-filled",
      "unicode": ""
    },
    {
      "font_class": "chatbubble",
      "unicode": ""
    },
    {
      "font_class": "chatbubble-filled",
      "unicode": ""
    },
    {
      "font_class": "checkbox",
      "unicode": ""
    },
    {
      "font_class": "checkbox-filled",
      "unicode": ""
    },
    {
      "font_class": "checkmarkempty",
      "unicode": ""
    },
    {
      "font_class": "circle",
      "unicode": ""
    },
    {
      "font_class": "circle-filled",
      "unicode": ""
    },
    {
      "font_class": "clear",
      "unicode": ""
    },
    {
      "font_class": "close",
      "unicode": ""
    },
    {
      "font_class": "closeempty",
      "unicode": ""
    },
    {
      "font_class": "cloud-download",
      "unicode": ""
    },
    {
      "font_class": "cloud-download-filled",
      "unicode": ""
    },
    {
      "font_class": "cloud-upload",
      "unicode": ""
    },
    {
      "font_class": "cloud-upload-filled",
      "unicode": ""
    },
    {
      "font_class": "color",
      "unicode": ""
    },
    {
      "font_class": "color-filled",
      "unicode": ""
    },
    {
      "font_class": "compose",
      "unicode": ""
    },
    {
      "font_class": "contact",
      "unicode": ""
    },
    {
      "font_class": "contact-filled",
      "unicode": ""
    },
    {
      "font_class": "down",
      "unicode": ""
    },
    {
      "font_class": "bottom",
      "unicode": ""
    },
    {
      "font_class": "download",
      "unicode": ""
    },
    {
      "font_class": "download-filled",
      "unicode": ""
    },
    {
      "font_class": "email",
      "unicode": ""
    },
    {
      "font_class": "email-filled",
      "unicode": ""
    },
    {
      "font_class": "eye",
      "unicode": ""
    },
    {
      "font_class": "eye-filled",
      "unicode": ""
    },
    {
      "font_class": "eye-slash",
      "unicode": ""
    },
    {
      "font_class": "eye-slash-filled",
      "unicode": ""
    },
    {
      "font_class": "fire",
      "unicode": ""
    },
    {
      "font_class": "fire-filled",
      "unicode": ""
    },
    {
      "font_class": "flag",
      "unicode": ""
    },
    {
      "font_class": "flag-filled",
      "unicode": ""
    },
    {
      "font_class": "folder-add",
      "unicode": ""
    },
    {
      "font_class": "folder-add-filled",
      "unicode": ""
    },
    {
      "font_class": "font",
      "unicode": ""
    },
    {
      "font_class": "forward",
      "unicode": ""
    },
    {
      "font_class": "gear",
      "unicode": ""
    },
    {
      "font_class": "gear-filled",
      "unicode": ""
    },
    {
      "font_class": "gift",
      "unicode": ""
    },
    {
      "font_class": "gift-filled",
      "unicode": ""
    },
    {
      "font_class": "hand-down",
      "unicode": ""
    },
    {
      "font_class": "hand-down-filled",
      "unicode": ""
    },
    {
      "font_class": "hand-up",
      "unicode": ""
    },
    {
      "font_class": "hand-up-filled",
      "unicode": ""
    },
    {
      "font_class": "headphones",
      "unicode": ""
    },
    {
      "font_class": "heart",
      "unicode": ""
    },
    {
      "font_class": "heart-filled",
      "unicode": ""
    },
    {
      "font_class": "help",
      "unicode": ""
    },
    {
      "font_class": "help-filled",
      "unicode": ""
    },
    {
      "font_class": "home",
      "unicode": ""
    },
    {
      "font_class": "home-filled",
      "unicode": ""
    },
    {
      "font_class": "image",
      "unicode": ""
    },
    {
      "font_class": "image-filled",
      "unicode": ""
    },
    {
      "font_class": "images",
      "unicode": ""
    },
    {
      "font_class": "images-filled",
      "unicode": ""
    },
    {
      "font_class": "info",
      "unicode": ""
    },
    {
      "font_class": "info-filled",
      "unicode": ""
    },
    {
      "font_class": "left",
      "unicode": ""
    },
    {
      "font_class": "link",
      "unicode": ""
    },
    {
      "font_class": "list",
      "unicode": ""
    },
    {
      "font_class": "location",
      "unicode": ""
    },
    {
      "font_class": "location-filled",
      "unicode": ""
    },
    {
      "font_class": "locked",
      "unicode": ""
    },
    {
      "font_class": "locked-filled",
      "unicode": ""
    },
    {
      "font_class": "loop",
      "unicode": ""
    },
    {
      "font_class": "mail-open",
      "unicode": ""
    },
    {
      "font_class": "mail-open-filled",
      "unicode": ""
    },
    {
      "font_class": "map",
      "unicode": ""
    },
    {
      "font_class": "map-filled",
      "unicode": ""
    },
    {
      "font_class": "map-pin",
      "unicode": ""
    },
    {
      "font_class": "map-pin-ellipse",
      "unicode": ""
    },
    {
      "font_class": "medal",
      "unicode": ""
    },
    {
      "font_class": "medal-filled",
      "unicode": ""
    },
    {
      "font_class": "mic",
      "unicode": ""
    },
    {
      "font_class": "mic-filled",
      "unicode": ""
    },
    {
      "font_class": "micoff",
      "unicode": ""
    },
    {
      "font_class": "micoff-filled",
      "unicode": ""
    },
    {
      "font_class": "minus",
      "unicode": ""
    },
    {
      "font_class": "minus-filled",
      "unicode": ""
    },
    {
      "font_class": "more",
      "unicode": ""
    },
    {
      "font_class": "more-filled",
      "unicode": ""
    },
    {
      "font_class": "navigate",
      "unicode": ""
    },
    {
      "font_class": "navigate-filled",
      "unicode": ""
    },
    {
      "font_class": "notification",
      "unicode": ""
    },
    {
      "font_class": "notification-filled",
      "unicode": ""
    },
    {
      "font_class": "paperclip",
      "unicode": ""
    },
    {
      "font_class": "paperplane",
      "unicode": ""
    },
    {
      "font_class": "paperplane-filled",
      "unicode": ""
    },
    {
      "font_class": "person",
      "unicode": ""
    },
    {
      "font_class": "person-filled",
      "unicode": ""
    },
    {
      "font_class": "personadd",
      "unicode": ""
    },
    {
      "font_class": "personadd-filled",
      "unicode": ""
    },
    {
      "font_class": "personadd-filled-copy",
      "unicode": ""
    },
    {
      "font_class": "phone",
      "unicode": ""
    },
    {
      "font_class": "phone-filled",
      "unicode": ""
    },
    {
      "font_class": "plus",
      "unicode": ""
    },
    {
      "font_class": "plus-filled",
      "unicode": ""
    },
    {
      "font_class": "plusempty",
      "unicode": ""
    },
    {
      "font_class": "pulldown",
      "unicode": ""
    },
    {
      "font_class": "pyq",
      "unicode": ""
    },
    {
      "font_class": "qq",
      "unicode": ""
    },
    {
      "font_class": "redo",
      "unicode": ""
    },
    {
      "font_class": "redo-filled",
      "unicode": ""
    },
    {
      "font_class": "refresh",
      "unicode": ""
    },
    {
      "font_class": "refresh-filled",
      "unicode": ""
    },
    {
      "font_class": "refreshempty",
      "unicode": ""
    },
    {
      "font_class": "reload",
      "unicode": ""
    },
    {
      "font_class": "right",
      "unicode": ""
    },
    {
      "font_class": "scan",
      "unicode": ""
    },
    {
      "font_class": "search",
      "unicode": ""
    },
    {
      "font_class": "settings",
      "unicode": ""
    },
    {
      "font_class": "settings-filled",
      "unicode": ""
    },
    {
      "font_class": "shop",
      "unicode": ""
    },
    {
      "font_class": "shop-filled",
      "unicode": ""
    },
    {
      "font_class": "smallcircle",
      "unicode": ""
    },
    {
      "font_class": "smallcircle-filled",
      "unicode": ""
    },
    {
      "font_class": "sound",
      "unicode": ""
    },
    {
      "font_class": "sound-filled",
      "unicode": ""
    },
    {
      "font_class": "spinner-cycle",
      "unicode": ""
    },
    {
      "font_class": "staff",
      "unicode": ""
    },
    {
      "font_class": "staff-filled",
      "unicode": ""
    },
    {
      "font_class": "star",
      "unicode": ""
    },
    {
      "font_class": "star-filled",
      "unicode": ""
    },
    {
      "font_class": "starhalf",
      "unicode": ""
    },
    {
      "font_class": "trash",
      "unicode": ""
    },
    {
      "font_class": "trash-filled",
      "unicode": ""
    },
    {
      "font_class": "tune",
      "unicode": ""
    },
    {
      "font_class": "tune-filled",
      "unicode": ""
    },
    {
      "font_class": "undo",
      "unicode": ""
    },
    {
      "font_class": "undo-filled",
      "unicode": ""
    },
    {
      "font_class": "up",
      "unicode": ""
    },
    {
      "font_class": "top",
      "unicode": ""
    },
    {
      "font_class": "upload",
      "unicode": ""
    },
    {
      "font_class": "upload-filled",
      "unicode": ""
    },
    {
      "font_class": "videocam",
      "unicode": ""
    },
    {
      "font_class": "videocam-filled",
      "unicode": ""
    },
    {
      "font_class": "vip",
      "unicode": ""
    },
    {
      "font_class": "vip-filled",
      "unicode": ""
    },
    {
      "font_class": "wallet",
      "unicode": ""
    },
    {
      "font_class": "wallet-filled",
      "unicode": ""
    },
    {
      "font_class": "weibo",
      "unicode": ""
    },
    {
      "font_class": "weixin",
      "unicode": ""
    }
  ];
  const _export_sfc = (sfc, props) => {
    const target = sfc.__vccOpts || sfc;
    for (const [key, val] of props) {
      target[key] = val;
    }
    return target;
  };
  const getVal = (val) => {
    const reg = /^[0-9]*$/g;
    return typeof val === "number" || reg.test(val) ? val + "px" : val;
  };
  const _sfc_main$h = {
    name: "UniIcons",
    emits: ["click"],
    props: {
      type: {
        type: String,
        default: ""
      },
      color: {
        type: String,
        default: "#333333"
      },
      size: {
        type: [Number, String],
        default: 16
      },
      customPrefix: {
        type: String,
        default: ""
      },
      fontFamily: {
        type: String,
        default: ""
      }
    },
    data() {
      return {
        icons: fontData
      };
    },
    computed: {
      unicode() {
        let code = this.icons.find((v) => v.font_class === this.type);
        if (code) {
          return code.unicode;
        }
        return "";
      },
      iconSize() {
        return getVal(this.size);
      },
      styleObj() {
        if (this.fontFamily !== "") {
          return `color: ${this.color}; font-size: ${this.iconSize}; font-family: ${this.fontFamily};`;
        }
        return `color: ${this.color}; font-size: ${this.iconSize};`;
      }
    },
    methods: {
      _onClick() {
        this.$emit("click");
      }
    }
  };
  function _sfc_render$g(_ctx, _cache, $props, $setup, $data, $options) {
    return vue.openBlock(), vue.createElementBlock(
      "text",
      {
        style: vue.normalizeStyle($options.styleObj),
        class: vue.normalizeClass(["uni-icons", ["uniui-" + $props.type, $props.customPrefix, $props.customPrefix ? $props.type : ""]]),
        onClick: _cache[0] || (_cache[0] = (...args) => $options._onClick && $options._onClick(...args))
      },
      [
        vue.renderSlot(_ctx.$slots, "default", {}, void 0, true)
      ],
      6
      /* CLASS, STYLE */
    );
  }
  const __easycom_1$3 = /* @__PURE__ */ _export_sfc(_sfc_main$h, [["render", _sfc_render$g], ["__scopeId", "data-v-d31e1c47"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/uni_modules/uni-icons/components/uni-icons/uni-icons.vue"]]);
  const ON_LOAD = "onLoad";
  const ON_UNLOAD = "onUnload";
  const ON_REACH_BOTTOM = "onReachBottom";
  const ON_SHARE_TIMELINE = "onShareTimeline";
  const ON_SHARE_APP_MESSAGE = "onShareAppMessage";
  function formatAppLog(type, filename, ...args) {
    if (uni.__log__) {
      uni.__log__(type, filename, ...args);
    } else {
      console[type].apply(console, [...args, filename]);
    }
  }
  function resolveEasycom(component, easycom) {
    return typeof component === "string" ? easycom : component;
  }
  const createHook = (lifecycle) => (hook, target = vue.getCurrentInstance()) => {
    !vue.isInSSRComponentSetup && vue.injectHook(lifecycle, hook, target);
  };
  const onLoad = /* @__PURE__ */ createHook(ON_LOAD);
  const onUnload = /* @__PURE__ */ createHook(ON_UNLOAD);
  const onReachBottom = /* @__PURE__ */ createHook(ON_REACH_BOTTOM);
  const onShareTimeline = /* @__PURE__ */ createHook(ON_SHARE_TIMELINE);
  const onShareAppMessage = /* @__PURE__ */ createHook(ON_SHARE_APP_MESSAGE);
  const system = uni.getSystemInfoSync();
  const getStatusBarHeight = () => system.statusBarHeight || 30;
  const getTitleBarHeight = () => {
    if (uni.getMenuButtonBoundingClientRect) {
      const {
        top,
        height
      } = uni.getMenuButtonBoundingClientRect();
      return (top - getStatusBarHeight()) * 2 + height;
    } else {
      return 60;
    }
  };
  const _sfc_main$g = {
    __name: "custom-nav-bar",
    props: {
      title: {
        type: String,
        default: "标题"
      }
    },
    setup(__props, { expose: __expose }) {
      __expose();
      let statusBarHeight = vue.ref(getStatusBarHeight());
      let titleBarHeight = getTitleBarHeight();
      const __returned__ = { get statusBarHeight() {
        return statusBarHeight;
      }, set statusBarHeight(v) {
        statusBarHeight = v;
      }, get titleBarHeight() {
        return titleBarHeight;
      }, set titleBarHeight(v) {
        titleBarHeight = v;
      }, ref: vue.ref, get getStatusBarHeight() {
        return getStatusBarHeight;
      }, get getTitleBarHeight() {
        return getTitleBarHeight;
      } };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$f(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    return vue.openBlock(), vue.createElementBlock("view", { class: "customNavBarContainer" }, [
      vue.createElementVNode("view", { class: "navBar commonPageBg" }, [
        vue.createElementVNode(
          "view",
          {
            class: "statusBar",
            style: vue.normalizeStyle({ height: $setup.statusBarHeight + "px" })
          },
          null,
          4
          /* STYLE */
        ),
        vue.createElementVNode(
          "view",
          {
            class: "titleBar",
            style: vue.normalizeStyle({ height: $setup.titleBarHeight + "px" })
          },
          [
            vue.createElementVNode(
              "view",
              { class: "title" },
              vue.toDisplayString($props.title),
              1
              /* TEXT */
            ),
            vue.createElementVNode("navigator", {
              url: "/pages/search/search",
              class: "search"
            }, [
              vue.createVNode(_component_uni_icons, {
                class: "icon",
                type: "search",
                color: "#888",
                size: "18"
              }),
              vue.createElementVNode("text", null, "搜索")
            ])
          ],
          4
          /* STYLE */
        )
      ]),
      vue.createElementVNode(
        "view",
        {
          class: "fill",
          style: vue.normalizeStyle({ height: $setup.titleBarHeight + $setup.statusBarHeight + "px" })
        },
        null,
        4
        /* STYLE */
      )
    ]);
  }
  const __easycom_0$2 = /* @__PURE__ */ _export_sfc(_sfc_main$g, [["render", _sfc_render$f], ["__scopeId", "data-v-412fc155"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/components/custom-nav-bar/custom-nav-bar.vue"]]);
  function pad(str, length = 2) {
    str += "";
    while (str.length < length) {
      str = "0" + str;
    }
    return str.slice(-length);
  }
  const parser = {
    yyyy: (dateObj) => {
      return pad(dateObj.year, 4);
    },
    yy: (dateObj) => {
      return pad(dateObj.year);
    },
    MM: (dateObj) => {
      return pad(dateObj.month);
    },
    M: (dateObj) => {
      return dateObj.month;
    },
    dd: (dateObj) => {
      return pad(dateObj.day);
    },
    d: (dateObj) => {
      return dateObj.day;
    },
    hh: (dateObj) => {
      return pad(dateObj.hour);
    },
    h: (dateObj) => {
      return dateObj.hour;
    },
    mm: (dateObj) => {
      return pad(dateObj.minute);
    },
    m: (dateObj) => {
      return dateObj.minute;
    },
    ss: (dateObj) => {
      return pad(dateObj.second);
    },
    s: (dateObj) => {
      return dateObj.second;
    },
    SSS: (dateObj) => {
      return pad(dateObj.millisecond, 3);
    },
    S: (dateObj) => {
      return dateObj.millisecond;
    }
  };
  function getDate(time) {
    if (time instanceof Date) {
      return time;
    }
    switch (typeof time) {
      case "string": {
        if (time.indexOf("T") > -1) {
          return new Date(time);
        }
        return new Date(time.replace(/-/g, "/"));
      }
      default:
        return new Date(time);
    }
  }
  function formatDate(date, format = "yyyy/MM/dd hh:mm:ss") {
    if (!date && date !== 0) {
      return "";
    }
    date = getDate(date);
    const dateObj = {
      year: date.getFullYear(),
      month: date.getMonth() + 1,
      day: date.getDate(),
      hour: date.getHours(),
      minute: date.getMinutes(),
      second: date.getSeconds(),
      millisecond: date.getMilliseconds()
    };
    const tokenRegExp = /yyyy|yy|MM|M|dd|d|hh|h|mm|m|ss|s|SSS|SS|S/;
    let flag = true;
    let result = format;
    while (flag) {
      flag = false;
      result = result.replace(tokenRegExp, function(matched) {
        flag = true;
        return parser[matched](dateObj);
      });
    }
    return result;
  }
  function friendlyDate(time, {
    locale = "zh",
    threshold = [6e4, 36e5],
    format = "yyyy/MM/dd hh:mm:ss"
  }) {
    if (time === "-") {
      return time;
    }
    if (!time && time !== 0) {
      return "";
    }
    const localeText = {
      zh: {
        year: "年",
        month: "月",
        day: "天",
        hour: "小时",
        minute: "分钟",
        second: "秒",
        ago: "前",
        later: "后",
        justNow: "刚刚",
        soon: "马上",
        template: "{num}{unit}{suffix}"
      },
      en: {
        year: "year",
        month: "month",
        day: "day",
        hour: "hour",
        minute: "minute",
        second: "second",
        ago: "ago",
        later: "later",
        justNow: "just now",
        soon: "soon",
        template: "{num} {unit} {suffix}"
      }
    };
    const text = localeText[locale] || localeText.zh;
    let date = getDate(time);
    let ms = date.getTime() - Date.now();
    let absMs = Math.abs(ms);
    if (absMs < threshold[0]) {
      return ms < 0 ? text.justNow : text.soon;
    }
    if (absMs >= threshold[1]) {
      return formatDate(date, format);
    }
    let num;
    let unit;
    let suffix = text.later;
    if (ms < 0) {
      suffix = text.ago;
      ms = -ms;
    }
    const seconds = Math.floor(ms / 1e3);
    const minutes = Math.floor(seconds / 60);
    const hours = Math.floor(minutes / 60);
    const days = Math.floor(hours / 24);
    const months = Math.floor(days / 30);
    const years = Math.floor(months / 12);
    switch (true) {
      case years > 0:
        num = years;
        unit = text.year;
        break;
      case months > 0:
        num = months;
        unit = text.month;
        break;
      case days > 0:
        num = days;
        unit = text.day;
        break;
      case hours > 0:
        num = hours;
        unit = text.hour;
        break;
      case minutes > 0:
        num = minutes;
        unit = text.minute;
        break;
      default:
        num = seconds;
        unit = text.second;
        break;
    }
    if (locale === "en") {
      if (num === 1) {
        num = "a";
      } else {
        unit += "s";
      }
    }
    return text.template.replace(/{\s*num\s*}/g, num + "").replace(/{\s*unit\s*}/g, unit).replace(
      /{\s*suffix\s*}/g,
      suffix
    );
  }
  const _sfc_main$f = {
    name: "uniDateformat",
    props: {
      date: {
        type: [Object, String, Number],
        default() {
          return "-";
        }
      },
      locale: {
        type: String,
        default: "zh"
      },
      threshold: {
        type: Array,
        default() {
          return [0, 0];
        }
      },
      format: {
        type: String,
        default: "yyyy/MM/dd hh:mm:ss"
      },
      // refreshRate使用不当可能导致性能问题，谨慎使用
      refreshRate: {
        type: [Number, String],
        default: 0
      }
    },
    data() {
      return {
        refreshMark: 0
      };
    },
    computed: {
      dateShow() {
        this.refreshMark;
        return friendlyDate(this.date, {
          locale: this.locale,
          threshold: this.threshold,
          format: this.format
        });
      }
    },
    watch: {
      refreshRate: {
        handler() {
          this.setAutoRefresh();
        },
        immediate: true
      }
    },
    methods: {
      refresh() {
        this.refreshMark++;
      },
      setAutoRefresh() {
        clearInterval(this.refreshInterval);
        if (this.refreshRate) {
          this.refreshInterval = setInterval(() => {
            this.refresh();
          }, parseInt(this.refreshRate));
        }
      }
    }
  };
  function _sfc_render$e(_ctx, _cache, $props, $setup, $data, $options) {
    return vue.openBlock(), vue.createElementBlock(
      "text",
      null,
      vue.toDisplayString($options.dateShow),
      1
      /* TEXT */
    );
  }
  const __easycom_1$2 = /* @__PURE__ */ _export_sfc(_sfc_main$f, [["render", _sfc_render$e], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/uni_modules/uni-dateformat/components/uni-dateformat/uni-dateformat.vue"]]);
  const _sfc_main$e = {};
  function _sfc_render$d(_ctx, _cache) {
    return vue.openBlock(), vue.createElementBlock("view", { class: "container" }, [
      vue.createElementVNode("view", { class: "left" }, [
        vue.renderSlot(_ctx.$slots, "left", {}, void 0, true)
      ]),
      vue.createElementVNode("view", { class: "right" }, [
        vue.renderSlot(_ctx.$slots, "right", {}, void 0, true)
      ])
    ]);
  }
  const __easycom_3$1 = /* @__PURE__ */ _export_sfc(_sfc_main$e, [["render", _sfc_render$d], ["__scopeId", "data-v-43a5d97b"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/components/common-title/common-title.vue"]]);
  function compareTimestamp(timestamp) {
    const currentTime = (/* @__PURE__ */ new Date()).getTime();
    const timeDiff = currentTime - timestamp;
    if (timeDiff < 6e4) {
      return "1分钟内";
    } else if (timeDiff < 36e5) {
      return Math.floor(timeDiff / 6e4) + "分钟";
    } else if (timeDiff < 864e5) {
      return Math.floor(timeDiff / 36e5) + "小时";
    } else if (timeDiff < 2592e6) {
      return Math.floor(timeDiff / 864e5) + "天";
    } else if (timeDiff < 7776e6) {
      return Math.floor(timeDiff / 2592e6) + "月";
    } else {
      return null;
    }
  }
  const _imports_0$1 = "/assets/more.14a1a72b.jpg";
  const _sfc_main$d = {
    __name: "theme-item",
    props: {
      isMore: {
        type: Boolean,
        default: false
      },
      item: {
        type: Object,
        default() {
          return {
            name: "分类名称",
            picurl: "../../common/images/classify1.jpg",
            updateTime: Date.now()
          };
        }
      }
    },
    setup(__props, { expose: __expose }) {
      __expose();
      const __returned__ = { get compareTimestamp() {
        return compareTimestamp;
      } };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$c(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    return vue.openBlock(), vue.createElementBlock("view", { class: "container" }, [
      !$props.isMore ? (vue.openBlock(), vue.createElementBlock("navigator", {
        key: 0,
        url: "/pages/classifyList/classifyList?id=" + $props.item._id + "&name=" + $props.item.name,
        class: "bgImg"
      }, [
        vue.createElementVNode("image", {
          src: $props.item.picurl,
          mode: "aspectFill"
        }, null, 8, ["src"]),
        vue.createElementVNode(
          "view",
          { class: "maskText" },
          vue.toDisplayString($props.item.name),
          1
          /* TEXT */
        ),
        $setup.compareTimestamp($props.item.updateTime) ? (vue.openBlock(), vue.createElementBlock(
          "view",
          {
            key: 0,
            class: "timebar"
          },
          "· " + vue.toDisplayString($setup.compareTimestamp($props.item.updateTime)) + "前更新 ",
          1
          /* TEXT */
        )) : vue.createCommentVNode("v-if", true)
      ], 8, ["url"])) : vue.createCommentVNode("v-if", true),
      $props.isMore ? (vue.openBlock(), vue.createElementBlock("navigator", {
        key: 1,
        url: "/pages/classify/classify",
        "open-type": "reLaunch",
        class: "bgImg more"
      }, [
        vue.createElementVNode("image", {
          src: _imports_0$1,
          mode: "aspectFill"
        }),
        vue.createElementVNode("view", { class: "maskText" }, [
          vue.createVNode(_component_uni_icons, {
            type: "more-filled",
            size: "36",
            color: "#fff"
          }),
          vue.createElementVNode("view", null, "更多")
        ])
      ])) : vue.createCommentVNode("v-if", true)
    ]);
  }
  const __easycom_1$1 = /* @__PURE__ */ _export_sfc(_sfc_main$d, [["render", _sfc_render$c], ["__scopeId", "data-v-f4eafbca"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/components/theme-item/theme-item.vue"]]);
  const BASE_URL = "/apis/api/bizhi";
  function request(config = {}) {
    let {
      url,
      method = "GET",
      header = {},
      data = {}
    } = config;
    header["access-key"] = "1261338615";
    return new Promise((resolve, reject) => {
      uni.request({
        url: BASE_URL + url,
        method,
        header,
        data,
        success: (res) => {
          if (res.data.errCode == 0) {
            resolve(res.data);
          } else if (res.data.errCode == 400) {
            uni.showModal({
              title: res.data.errMsg,
              showCancel: false
            });
            reject(res.data);
          } else {
            uni.showToast({
              title: res.data.errMsg,
              icon: "none"
            });
            reject(res.data);
          }
        },
        fail: (err) => {
          reject(err);
        }
      });
    });
  }
  function apiGetBannerPics() {
    return request({
      url: "/homeBanner"
    });
  }
  function apiGetRecommendPics() {
    return request({
      url: "/randomWall"
    });
  }
  function apiGetNoticeList() {
    return request({
      url: "/wallNewsList"
    });
  }
  function apiGetThemeList(data = {}) {
    return request({
      url: "/classify",
      data
    });
  }
  function apiGetClassifyPicList(data = {}) {
    return request({
      url: "/wallList",
      data
    });
  }
  function apiGetSetupScore(data = {}) {
    return request({
      url: "/setupScore",
      data
    });
  }
  function apiWriteDownload(data = {}) {
    return request({
      url: "/downloadWall",
      data
    });
  }
  function apiGetUserInfo(data = {}) {
    return request({
      url: "/userInfo",
      data
    });
  }
  function apiSearchData(data = {}) {
    return request({
      url: "/searchWall",
      data
    });
  }
  const _sfc_main$c = {
    __name: "index",
    setup(__props, { expose: __expose }) {
      __expose();
      let bannerPics = vue.ref([]);
      let recommendPics = vue.ref([]);
      let noticeList = vue.ref([]);
      let themeList = vue.ref([]);
      function goPreview() {
        uni.setStorageSync("classifyPicList", recommendPics.value);
      }
      onShareAppMessage(() => {
        return {
          title: "xxm壁纸",
          path: "/pages/index/index"
        };
      });
      onShareTimeline(() => {
        return {
          title: "xxm壁纸!!!"
        };
      });
      async function getBannerPics() {
        let temp = await apiGetBannerPics();
        bannerPics.value = temp.data;
      }
      async function getRecommendPics() {
        let temp = await apiGetRecommendPics();
        recommendPics.value = temp.data;
      }
      async function getNoticeList() {
        let temp = await apiGetNoticeList();
        noticeList.value = temp.data;
      }
      async function getThemeList() {
        let temp = await apiGetThemeList();
        themeList.value = temp.data;
      }
      getBannerPics();
      getRecommendPics();
      getNoticeList();
      getThemeList();
      const __returned__ = { get bannerPics() {
        return bannerPics;
      }, set bannerPics(v) {
        bannerPics = v;
      }, get recommendPics() {
        return recommendPics;
      }, set recommendPics(v) {
        recommendPics = v;
      }, get noticeList() {
        return noticeList;
      }, set noticeList(v) {
        noticeList = v;
      }, get themeList() {
        return themeList;
      }, set themeList(v) {
        themeList = v;
      }, goPreview, getBannerPics, getRecommendPics, getNoticeList, getThemeList, ref: vue.ref, get apiGetBannerPics() {
        return apiGetBannerPics;
      }, get apiGetRecommendPics() {
        return apiGetRecommendPics;
      }, get apiGetNoticeList() {
        return apiGetNoticeList;
      }, get apiGetThemeList() {
        return apiGetThemeList;
      }, get onShareAppMessage() {
        return onShareAppMessage;
      }, get onShareTimeline() {
        return onShareTimeline;
      } };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$b(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_custom_nav_bar = resolveEasycom(vue.resolveDynamicComponent("custom-nav-bar"), __easycom_0$2);
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    const _component_uni_dateformat = resolveEasycom(vue.resolveDynamicComponent("uni-dateformat"), __easycom_1$2);
    const _component_common_title = resolveEasycom(vue.resolveDynamicComponent("common-title"), __easycom_3$1);
    const _component_theme_item = resolveEasycom(vue.resolveDynamicComponent("theme-item"), __easycom_1$1);
    return vue.openBlock(), vue.createElementBlock("view", { class: "container commonPageBg" }, [
      vue.createCommentVNode(" 头部 "),
      vue.createVNode(_component_custom_nav_bar, {
        class: "customNavBar",
        title: "推荐"
      }),
      vue.createCommentVNode(" 轮播图 "),
      vue.createElementVNode("view", { class: "banner" }, [
        vue.createElementVNode("swiper", {
          "indicator-dots": "",
          "indicator-color": "rgba(255,255,255,.3)",
          "indicator-active-color": "#fff",
          autoplay: "",
          interval: "3000",
          circular: ""
        }, [
          (vue.openBlock(true), vue.createElementBlock(
            vue.Fragment,
            null,
            vue.renderList($setup.bannerPics, (item) => {
              return vue.openBlock(), vue.createElementBlock("swiper-item", {
                key: item._id
              }, [
                vue.createElementVNode("image", {
                  src: item.picurl,
                  mode: "aspectFill"
                }, null, 8, ["src"])
              ]);
            }),
            128
            /* KEYED_FRAGMENT */
          ))
        ])
      ]),
      vue.createCommentVNode(" 公告 "),
      vue.createElementVNode("view", { class: "notice" }, [
        vue.createElementVNode("view", { class: "left" }, [
          vue.createVNode(_component_uni_icons, {
            type: "sound-filled",
            size: "25",
            color: "#28B48F"
          }),
          vue.createElementVNode("text", null, "公告")
        ]),
        vue.createElementVNode("view", { class: "center" }, [
          vue.createElementVNode("swiper", {
            interval: "3000",
            circular: "",
            autoplay: "",
            vertical: ""
          }, [
            (vue.openBlock(true), vue.createElementBlock(
              vue.Fragment,
              null,
              vue.renderList($setup.noticeList, (item) => {
                return vue.openBlock(), vue.createElementBlock(
                  "swiper-item",
                  {
                    key: item._id
                  },
                  vue.toDisplayString(item.title),
                  1
                  /* TEXT */
                );
              }),
              128
              /* KEYED_FRAGMENT */
            ))
          ])
        ]),
        vue.createElementVNode("view", { class: "right" }, [
          vue.createVNode(_component_uni_icons, {
            type: "right",
            size: "20",
            color: "#A7A7A7"
          })
        ])
      ]),
      vue.createCommentVNode(" 推荐 "),
      vue.createElementVNode("view", { class: "recommend" }, [
        vue.createVNode(_component_common_title, null, {
          left: vue.withCtx(() => [
            vue.createTextVNode("每日推荐")
          ]),
          right: vue.withCtx(() => [
            vue.createElementVNode("view", { style: { "display": "flex", "align-items": "center" } }, [
              vue.createVNode(_component_uni_icons, {
                type: "calendar",
                size: "30"
              }),
              vue.createElementVNode("view", {
                class: "date",
                style: { "display": "flex" }
              }, [
                vue.createVNode(_component_uni_dateformat, {
                  date: Date.now(),
                  format: "dd",
                  threshold: [0, 0]
                }, null, 8, ["date"]),
                vue.createTextVNode(" 日 ")
              ])
            ])
          ]),
          _: 1
          /* STABLE */
        }),
        vue.createElementVNode("view", { class: "content" }, [
          vue.createElementVNode("scroll-view", { "scroll-x": "" }, [
            (vue.openBlock(true), vue.createElementBlock(
              vue.Fragment,
              null,
              vue.renderList($setup.recommendPics, (item) => {
                return vue.openBlock(), vue.createElementBlock("view", {
                  key: item._id
                }, [
                  vue.createElementVNode("navigator", {
                    url: "/pages/preview/preview?id=" + item._id,
                    onClick: $setup.goPreview
                  }, [
                    vue.createElementVNode("image", {
                      src: item.smallPicurl,
                      mode: "aspectFill"
                    }, null, 8, ["src"])
                  ], 8, ["url"])
                ]);
              }),
              128
              /* KEYED_FRAGMENT */
            ))
          ])
        ])
      ]),
      vue.createCommentVNode(" 专题 "),
      vue.createElementVNode("view", { class: "classify" }, [
        vue.createVNode(_component_common_title, null, {
          left: vue.withCtx(() => [
            vue.createTextVNode("专题精选")
          ]),
          right: vue.withCtx(() => [
            vue.createElementVNode("navigator", { url: "" }, "More+")
          ]),
          _: 1
          /* STABLE */
        }),
        vue.createElementVNode("view", { class: "content" }, [
          (vue.openBlock(true), vue.createElementBlock(
            vue.Fragment,
            null,
            vue.renderList($setup.themeList, (item) => {
              return vue.openBlock(), vue.createBlock(_component_theme_item, {
                key: item._id,
                item
              }, null, 8, ["item"]);
            }),
            128
            /* KEYED_FRAGMENT */
          )),
          vue.createVNode(_component_theme_item, { isMore: true })
        ])
      ])
    ]);
  }
  const PagesIndexIndex = /* @__PURE__ */ _export_sfc(_sfc_main$c, [["render", _sfc_render$b], ["__scopeId", "data-v-1cf27b2a"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/pages/index/index.vue"]]);
  const _sfc_main$b = {
    __name: "classify",
    setup(__props, { expose: __expose }) {
      __expose();
      let themeList = vue.ref([]);
      async function getThemeList() {
        let temp = await apiGetThemeList({
          pageSize: 16
        });
        themeList.value = temp.data;
      }
      getThemeList();
      const __returned__ = { get themeList() {
        return themeList;
      }, set themeList(v) {
        themeList = v;
      }, getThemeList, ref: vue.ref, get apiGetThemeList() {
        return apiGetThemeList;
      } };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$a(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_custom_nav_bar = resolveEasycom(vue.resolveDynamicComponent("custom-nav-bar"), __easycom_0$2);
    const _component_theme_item = resolveEasycom(vue.resolveDynamicComponent("theme-item"), __easycom_1$1);
    return vue.openBlock(), vue.createElementBlock("view", { class: "classifycontainer commonPageBg" }, [
      vue.createCommentVNode(" 头部 "),
      vue.createVNode(_component_custom_nav_bar, {
        class: "customNavBar",
        title: "分类"
      }),
      vue.createElementVNode("view", { class: "classifyLayout" }, [
        (vue.openBlock(true), vue.createElementBlock(
          vue.Fragment,
          null,
          vue.renderList($setup.themeList, (item) => {
            return vue.openBlock(), vue.createBlock(_component_theme_item, {
              key: item._id,
              item
            }, null, 8, ["item"]);
          }),
          128
          /* KEYED_FRAGMENT */
        ))
      ])
    ]);
  }
  const PagesClassifyClassify = /* @__PURE__ */ _export_sfc(_sfc_main$b, [["render", _sfc_render$a], ["__scopeId", "data-v-6bcfa975"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/pages/classify/classify.vue"]]);
  const _sfc_main$a = {
    __name: "option-item",
    props: {
      optionName: {
        type: String,
        required: true
      },
      jumpUrl: {
        type: String
      },
      number: {
        type: Number,
        default: -114514
      }
    },
    setup(__props, { expose: __expose }) {
      __expose();
      let props = __props;
      function onClicked() {
        formatAppLog("log", "at components/option-item/option-item.vue:33", "点击了");
      }
      const __returned__ = { get props() {
        return props;
      }, set props(v) {
        props = v;
      }, onClicked };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$9(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    return vue.openBlock(), vue.createElementBlock("navigator", { url: $props.jumpUrl }, [
      vue.createElementVNode("view", { class: "optionItemContainer" }, [
        vue.createElementVNode("view", { class: "left" }, [
          vue.createCommentVNode(' <uni-icons type="download-filled" size="30" color="#28B38C"></uni-icons> '),
          vue.renderSlot(_ctx.$slots, "leftIcon", {}, void 0, true),
          vue.createElementVNode(
            "view",
            null,
            vue.toDisplayString($props.optionName),
            1
            /* TEXT */
          )
        ]),
        vue.createElementVNode("view", { class: "right" }, [
          $setup.props.number != -114514 ? (vue.openBlock(), vue.createElementBlock(
            "view",
            { key: 0 },
            vue.toDisplayString($setup.props.number),
            1
            /* TEXT */
          )) : vue.createCommentVNode("v-if", true),
          vue.createVNode(_component_uni_icons, {
            type: "arrowright",
            size: "22",
            color: "#999"
          })
        ])
      ])
    ], 8, ["url"]);
  }
  const __easycom_1 = /* @__PURE__ */ _export_sfc(_sfc_main$a, [["render", _sfc_render$9], ["__scopeId", "data-v-54270cf5"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/components/option-item/option-item.vue"]]);
  const _imports_0 = "/static/images/xxmLogo.png";
  const _sfc_main$9 = {
    __name: "user",
    setup(__props, { expose: __expose }) {
      __expose();
      let userInfo = vue.ref(null);
      function onClickContact() {
        uni.makePhoneCall({
          phoneNumber: "114514"
        });
      }
      async function getUserInfo() {
        let temp = await apiGetUserInfo();
        userInfo.value = temp.data;
      }
      getUserInfo();
      const __returned__ = { get userInfo() {
        return userInfo;
      }, set userInfo(v) {
        userInfo = v;
      }, onClickContact, getUserInfo, get getStatusBarHeight() {
        return getStatusBarHeight;
      }, get apiGetUserInfo() {
        return apiGetUserInfo;
      }, ref: vue.ref };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$8(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    const _component_option_item = resolveEasycom(vue.resolveDynamicComponent("option-item"), __easycom_1);
    return $setup.userInfo ? (vue.openBlock(), vue.createElementBlock("view", {
      key: 0,
      class: "userContainer commonPageBg"
    }, [
      vue.createElementVNode(
        "view",
        {
          style: vue.normalizeStyle({ height: $setup.getStatusBarHeight() + "px" })
        },
        null,
        4
        /* STYLE */
      ),
      vue.createElementVNode("view", { class: "userInfo" }, [
        vue.createElementVNode("view", { class: "avatar" }, [
          vue.createElementVNode("image", {
            src: _imports_0,
            mode: "aspectFill"
          })
        ]),
        vue.createElementVNode(
          "view",
          { class: "ip" },
          vue.toDisplayString($setup.userInfo.IP),
          1
          /* TEXT */
        ),
        vue.createElementVNode(
          "view",
          { class: "address" },
          "来自于：" + vue.toDisplayString($setup.userInfo.address.city || $setup.userInfo.address.province || $setup.userInfo.address.country),
          1
          /* TEXT */
        )
      ]),
      vue.createElementVNode("view", { class: "section" }, [
        vue.createVNode(_component_option_item, {
          optionName: "我的下载",
          jumpUrl: "/pages/classifyList/classifyList",
          number: $setup.userInfo.downloadSize
        }, {
          leftIcon: vue.withCtx(() => [
            vue.createVNode(_component_uni_icons, {
              type: "download-filled",
              size: "30",
              color: "#28B38C"
            })
          ]),
          _: 1
          /* STABLE */
        }, 8, ["number"]),
        vue.createVNode(_component_option_item, {
          optionName: "我的评分",
          jumpUrl: "/pages/classifyList/classifyList",
          number: $setup.userInfo.scoreSize
        }, {
          leftIcon: vue.withCtx(() => [
            vue.createVNode(_component_uni_icons, {
              type: "star-filled",
              size: "30",
              color: "#28B38C"
            })
          ]),
          _: 1
          /* STABLE */
        }, 8, ["number"]),
        vue.createElementVNode("view", { class: "contact" }, [
          vue.createVNode(_component_option_item, {
            class: "lastItem",
            optionName: "联系客服"
          }, {
            leftIcon: vue.withCtx(() => [
              vue.createVNode(_component_uni_icons, {
                type: "chatboxes-filled",
                size: "30",
                color: "#28B38C"
              })
            ]),
            _: 1
            /* STABLE */
          }),
          vue.createElementVNode("button", { onClick: $setup.onClickContact })
        ])
      ]),
      vue.createElementVNode("view", { class: "section" }, [
        vue.createVNode(_component_option_item, { optionName: "订阅更新" }, {
          leftIcon: vue.withCtx(() => [
            vue.createVNode(_component_uni_icons, {
              type: "notification-filled",
              size: "30",
              color: "#28B38C"
            })
          ]),
          _: 1
          /* STABLE */
        }),
        vue.createVNode(_component_option_item, {
          class: "lastItem",
          optionName: "常见问题"
        }, {
          leftIcon: vue.withCtx(() => [
            vue.createVNode(_component_uni_icons, {
              type: "flag-filled",
              size: "30",
              color: "#28B38C"
            })
          ]),
          _: 1
          /* STABLE */
        })
      ])
    ])) : vue.createCommentVNode("v-if", true);
  }
  const PagesUserUser = /* @__PURE__ */ _export_sfc(_sfc_main$9, [["render", _sfc_render$8], ["__scopeId", "data-v-0f7520f0"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/pages/user/user.vue"]]);
  const isObject = (val) => val !== null && typeof val === "object";
  const defaultDelimiters = ["{", "}"];
  class BaseFormatter {
    constructor() {
      this._caches = /* @__PURE__ */ Object.create(null);
    }
    interpolate(message, values, delimiters = defaultDelimiters) {
      if (!values) {
        return [message];
      }
      let tokens = this._caches[message];
      if (!tokens) {
        tokens = parse(message, delimiters);
        this._caches[message] = tokens;
      }
      return compile(tokens, values);
    }
  }
  const RE_TOKEN_LIST_VALUE = /^(?:\d)+/;
  const RE_TOKEN_NAMED_VALUE = /^(?:\w)+/;
  function parse(format, [startDelimiter, endDelimiter]) {
    const tokens = [];
    let position = 0;
    let text = "";
    while (position < format.length) {
      let char = format[position++];
      if (char === startDelimiter) {
        if (text) {
          tokens.push({ type: "text", value: text });
        }
        text = "";
        let sub = "";
        char = format[position++];
        while (char !== void 0 && char !== endDelimiter) {
          sub += char;
          char = format[position++];
        }
        const isClosed = char === endDelimiter;
        const type = RE_TOKEN_LIST_VALUE.test(sub) ? "list" : isClosed && RE_TOKEN_NAMED_VALUE.test(sub) ? "named" : "unknown";
        tokens.push({ value: sub, type });
      } else {
        text += char;
      }
    }
    text && tokens.push({ type: "text", value: text });
    return tokens;
  }
  function compile(tokens, values) {
    const compiled = [];
    let index = 0;
    const mode = Array.isArray(values) ? "list" : isObject(values) ? "named" : "unknown";
    if (mode === "unknown") {
      return compiled;
    }
    while (index < tokens.length) {
      const token = tokens[index];
      switch (token.type) {
        case "text":
          compiled.push(token.value);
          break;
        case "list":
          compiled.push(values[parseInt(token.value, 10)]);
          break;
        case "named":
          if (mode === "named") {
            compiled.push(values[token.value]);
          } else {
            {
              console.warn(`Type of token '${token.type}' and format of value '${mode}' don't match!`);
            }
          }
          break;
        case "unknown":
          {
            console.warn(`Detect 'unknown' type of token!`);
          }
          break;
      }
      index++;
    }
    return compiled;
  }
  const LOCALE_ZH_HANS = "zh-Hans";
  const LOCALE_ZH_HANT = "zh-Hant";
  const LOCALE_EN = "en";
  const LOCALE_FR = "fr";
  const LOCALE_ES = "es";
  const hasOwnProperty = Object.prototype.hasOwnProperty;
  const hasOwn = (val, key) => hasOwnProperty.call(val, key);
  const defaultFormatter = new BaseFormatter();
  function include(str, parts) {
    return !!parts.find((part) => str.indexOf(part) !== -1);
  }
  function startsWith(str, parts) {
    return parts.find((part) => str.indexOf(part) === 0);
  }
  function normalizeLocale(locale, messages2) {
    if (!locale) {
      return;
    }
    locale = locale.trim().replace(/_/g, "-");
    if (messages2 && messages2[locale]) {
      return locale;
    }
    locale = locale.toLowerCase();
    if (locale === "chinese") {
      return LOCALE_ZH_HANS;
    }
    if (locale.indexOf("zh") === 0) {
      if (locale.indexOf("-hans") > -1) {
        return LOCALE_ZH_HANS;
      }
      if (locale.indexOf("-hant") > -1) {
        return LOCALE_ZH_HANT;
      }
      if (include(locale, ["-tw", "-hk", "-mo", "-cht"])) {
        return LOCALE_ZH_HANT;
      }
      return LOCALE_ZH_HANS;
    }
    let locales = [LOCALE_EN, LOCALE_FR, LOCALE_ES];
    if (messages2 && Object.keys(messages2).length > 0) {
      locales = Object.keys(messages2);
    }
    const lang = startsWith(locale, locales);
    if (lang) {
      return lang;
    }
  }
  class I18n {
    constructor({ locale, fallbackLocale, messages: messages2, watcher, formater: formater2 }) {
      this.locale = LOCALE_EN;
      this.fallbackLocale = LOCALE_EN;
      this.message = {};
      this.messages = {};
      this.watchers = [];
      if (fallbackLocale) {
        this.fallbackLocale = fallbackLocale;
      }
      this.formater = formater2 || defaultFormatter;
      this.messages = messages2 || {};
      this.setLocale(locale || LOCALE_EN);
      if (watcher) {
        this.watchLocale(watcher);
      }
    }
    setLocale(locale) {
      const oldLocale = this.locale;
      this.locale = normalizeLocale(locale, this.messages) || this.fallbackLocale;
      if (!this.messages[this.locale]) {
        this.messages[this.locale] = {};
      }
      this.message = this.messages[this.locale];
      if (oldLocale !== this.locale) {
        this.watchers.forEach((watcher) => {
          watcher(this.locale, oldLocale);
        });
      }
    }
    getLocale() {
      return this.locale;
    }
    watchLocale(fn) {
      const index = this.watchers.push(fn) - 1;
      return () => {
        this.watchers.splice(index, 1);
      };
    }
    add(locale, message, override = true) {
      const curMessages = this.messages[locale];
      if (curMessages) {
        if (override) {
          Object.assign(curMessages, message);
        } else {
          Object.keys(message).forEach((key) => {
            if (!hasOwn(curMessages, key)) {
              curMessages[key] = message[key];
            }
          });
        }
      } else {
        this.messages[locale] = message;
      }
    }
    f(message, values, delimiters) {
      return this.formater.interpolate(message, values, delimiters).join("");
    }
    t(key, locale, values) {
      let message = this.message;
      if (typeof locale === "string") {
        locale = normalizeLocale(locale, this.messages);
        locale && (message = this.messages[locale]);
      } else {
        values = locale;
      }
      if (!hasOwn(message, key)) {
        console.warn(`Cannot translate the value of keypath ${key}. Use the value of keypath as default.`);
        return key;
      }
      return this.formater.interpolate(message[key], values).join("");
    }
  }
  function watchAppLocale(appVm, i18n) {
    if (appVm.$watchLocale) {
      appVm.$watchLocale((newLocale) => {
        i18n.setLocale(newLocale);
      });
    } else {
      appVm.$watch(() => appVm.$locale, (newLocale) => {
        i18n.setLocale(newLocale);
      });
    }
  }
  function getDefaultLocale() {
    if (typeof uni !== "undefined" && uni.getLocale) {
      return uni.getLocale();
    }
    if (typeof global !== "undefined" && global.getLocale) {
      return global.getLocale();
    }
    return LOCALE_EN;
  }
  function initVueI18n(locale, messages2 = {}, fallbackLocale, watcher) {
    if (typeof locale !== "string") {
      const options = [
        messages2,
        locale
      ];
      locale = options[0];
      messages2 = options[1];
    }
    if (typeof locale !== "string") {
      locale = getDefaultLocale();
    }
    if (typeof fallbackLocale !== "string") {
      fallbackLocale = typeof __uniConfig !== "undefined" && __uniConfig.fallbackLocale || LOCALE_EN;
    }
    const i18n = new I18n({
      locale,
      fallbackLocale,
      messages: messages2,
      watcher
    });
    let t2 = (key, values) => {
      if (typeof getApp !== "function") {
        t2 = function(key2, values2) {
          return i18n.t(key2, values2);
        };
      } else {
        let isWatchedAppLocale = false;
        t2 = function(key2, values2) {
          const appVm = getApp().$vm;
          if (appVm) {
            appVm.$locale;
            if (!isWatchedAppLocale) {
              isWatchedAppLocale = true;
              watchAppLocale(appVm, i18n);
            }
          }
          return i18n.t(key2, values2);
        };
      }
      return t2(key, values);
    };
    return {
      i18n,
      f(message, values, delimiters) {
        return i18n.f(message, values, delimiters);
      },
      t(key, values) {
        return t2(key, values);
      },
      add(locale2, message, override = true) {
        return i18n.add(locale2, message, override);
      },
      watch(fn) {
        return i18n.watchLocale(fn);
      },
      getLocale() {
        return i18n.getLocale();
      },
      setLocale(newLocale) {
        return i18n.setLocale(newLocale);
      }
    };
  }
  const en$1 = {
    "uni-load-more.contentdown": "Pull up to show more",
    "uni-load-more.contentrefresh": "loading...",
    "uni-load-more.contentnomore": "No more data"
  };
  const zhHans$1 = {
    "uni-load-more.contentdown": "上拉显示更多",
    "uni-load-more.contentrefresh": "正在加载...",
    "uni-load-more.contentnomore": "没有更多数据了"
  };
  const zhHant$1 = {
    "uni-load-more.contentdown": "上拉顯示更多",
    "uni-load-more.contentrefresh": "正在加載...",
    "uni-load-more.contentnomore": "沒有更多數據了"
  };
  const messages$1 = {
    en: en$1,
    "zh-Hans": zhHans$1,
    "zh-Hant": zhHant$1
  };
  let platform;
  setTimeout(() => {
    platform = uni.getSystemInfoSync().platform;
  }, 16);
  const {
    t: t$1
  } = initVueI18n(messages$1);
  const _sfc_main$8 = {
    name: "UniLoadMore",
    emits: ["clickLoadMore"],
    props: {
      status: {
        // 上拉的状态：more-loading前；loading-loading中；noMore-没有更多了
        type: String,
        default: "more"
      },
      showIcon: {
        type: Boolean,
        default: true
      },
      iconType: {
        type: String,
        default: "auto"
      },
      iconSize: {
        type: Number,
        default: 24
      },
      color: {
        type: String,
        default: "#777777"
      },
      contentText: {
        type: Object,
        default() {
          return {
            contentdown: "",
            contentrefresh: "",
            contentnomore: ""
          };
        }
      },
      showText: {
        type: Boolean,
        default: true
      }
    },
    data() {
      return {
        webviewHide: false,
        platform,
        imgBase64: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMy1jMDExIDY2LjE0NTY2MSwgMjAxMi8wMi8wNi0xNDo1NjoyNyAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENTNiAoV2luZG93cykiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6QzlBMzU3OTlEOUM0MTFFOUI0NTZDNERBQURBQzI4RkUiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6QzlBMzU3OUFEOUM0MTFFOUI0NTZDNERBQURBQzI4RkUiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDpDOUEzNTc5N0Q5QzQxMUU5QjQ1NkM0REFBREFDMjhGRSIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDpDOUEzNTc5OEQ5QzQxMUU5QjQ1NkM0REFBREFDMjhGRSIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/Pt+ALSwAAA6CSURBVHja1FsLkFZVHb98LM+F5bHL8khA1iSeiyQBCRM+YGqKUnnJTDLGI0BGZlKDIU2MMglUiDApEZvSsZnQtBRJtKwQNKQMFYeRDR10WOLd8ljYXdh+v8v5fR3Od+797t1dnOnO/Ofce77z+J//+b/P+ZqtXbs2sJ9MJhNUV1cHJ06cCJo3bx7EPc2aNcvpy7pWrVoF+/fvDyoqKoI2bdoE9fX1F7TjN8a+EXBn/fkfvw942Tf+wYMHg9mzZwfjxo0LDhw4EPa1x2MbFw/fOGfPng1qa2tzcCkILsLDydq2bRsunpOTMM7TD/W/tZDZhPdeKD+yGxHhdu3aBV27dg3OnDlzMVANMheLAO3btw8KCwuDmpoaX5OxbgUIMEq7K8IcPnw4KCsrC/r37x8cP378/4cAXAB3vqSkJMuiDhTkw+XcuXNhOWbMmKBly5YhUT8xArhyFvP0BfwRsAuwxJZJsm/nzp2DTp06he/OU+cZ64K6o0ePBkOHDg2GDx8e6gEbJ5Q/NHNuAJQ1hgBeHUDlR7nVTkY8rQAvAi4z34vR/mPs1FoRsaCgIJThI0eOBC1atEiFGGV+5MiRoS45efJkqFjJFXV1dQuA012m2WcwTw98fy6CqBdsaiIO4CScrGPHjvk4odhavPquRtFWXEC25VgkREKOCh/qDSq+vn37htzD/mZTOmOc5U7zKzBPEedygWshcDyWvs30igAbU+6oyMgJBCFhwQE0fccxN60Ay9iebbjoDh06hMowjQxT4fXq1SskArmHZpkArvixp/kWzHdMeArExSJEaiXIjjRjRJ4DaAGWpibLzXN3Fm1vA5teBgh3j1Rv3bp1YgKwPdmf2p9zcyNYYgPKMfY0T5f5nNYdw158nJ8QawW4CLKwiOBSEgO/hok2eBydR+3dYH+PLxA5J8Vv0KBBwenTp0P2JWAx6+yFEBfs8lMY+y0SWMBNI9E4ThKi58VKTg3FQZS1RQF1cz27eC0QHMu+3E0SkUowjhVt5VdaWhp07949ZHv2Qd1EjDXM2cla1M0nl3GxAs3J9yREzyTdFVKVFOaE9qRA8GM0WebRuo9JGZKA7Mv2SeS/Z8+eoQ9BArMfFrLGo6jvxbhHbJZnKX2Rzz1O7QhJJ9Cs2ZMaWIyq/zhdeqPNfIoHd58clIQD+JSXl4dKlyIAuBdVXZwFVWKspSSoxE++h8x4k3uCnEhE4I5KwRiFWGOU0QWKiCYLbdoRMRKAu2kQ9vkfLU6dOhX06NEjlH+yMRZSinnuyWnYosVcji8CEA/6Cg2JF+IIUBqnGKUTCNwtwBN4f89RiK1R96DEgO2o0NDmtEdvVFdVVYV+P3UAPUEs6GFwV3PHmXkD4vh74iDFJysVI/MlaQhwKeBNTLYX5VuA8T4/gZxA4MRGFxDB6R7OmYPfyykGRJbyie+XnGYnQIC/coH9+vULiYrxrkL9ZA9+0ykaHIfEpM7ge8TiJ2CsHYwyMfafAF1yCGBHYIbCVDjDjKt7BeB51D+LgQa6OkG7IDYEEtvQ7lnXLKLtLdLuJBpE4gPUXcW2+PkZwOex+4cGDhwYDBkyRL7/HFcEwUGPo/8uWRUpYnfxGHco8HkewLHLyYmAawAPuIFZxhOpDfJQ8gbUv41yORAptMWBNr6oqMhWird5+u+iHmBb2nhjDV7HWBNQTgK8y11l5NetWzc5ULscAtSj7nbNI0skhWeUZCc0W4nyH/jO4Vz0u1IeYhbk4AiwM6tjxIWByHsoZ9qcIBPJd/y+DwPfBESOmCa/QF3WiZHucLlEDpNxcNhmheEOPgdQNx6/VZFQzFZ5TN08AHXQt2Ii3EdyFuUsPtTcGPhW5iMiCNELvz+Gdn9huG4HUJaW/w3g0wxV0XaG7arG2WeKiUWYM4Y7GO5ezshTARbbWGw/DvXkpp/ivVvE0JVoMxN4rpGzJMhE5Pl+xlATsDIqikP9F9D2z3h9nOksEUFhK+qO4rcPkoalMQ/HqJLIyb3F3JdjrCcw1yZ8joyJLR5gCo54etlag7qIoeNh1N1BRYj3DTFJ0elotxPlVzkGuYAmL0VSJVGAJA41c4Z6A3BzTLfn0HYwYKEI6CUAMzZEWvLsIcQOo1AmmyyM72nHJCfYsogflGV6jEk9vyQZXSuq6w4c16NsGcGZbwOPr+H1RkOk2LEzjNepxQkihHSCQ4ynAYNRx2zMKV92CQMWqj8J0BRE8EShxRFN6YrfCRhC0x3r/Zm4IbQCcmJoV0kMamllccR6FjHqUC5F2R/wS2dcymOlfAKOS4KmzQb5cpNC2MC7JhVn5wjXoJ44rYhLh8n0eXOCorJxa7POjbSlCGVczr34/RsAmrcvo9s+wGp3tzVhntxiXiJ4nvEYb4FJkf0O8HocAePmLvCxnL0AORraVekJk6TYjDabRVXfRE2lCN1h6ZQRN1+InUbsCpKwoBZHh0dODN9JBCUffItXxEavTQkUtnfTVAplCWL3JISz29h4NjotnuSsQKJCk8dF+kJR6RARjrqFVmfPnj3ZbK8cIJ0msd6jgHPGtfVTQ8VLmlvh4mct9sobRmPic0DyDQQnx/NlfYUgyz59+oScsH379pAwXABD32nTpoUHIToESeI5mnbE/UqDdyLcafEBf2MCqgC7NwxIbMREJQ0g4D4sfJwnD+AmRrII05cfMWJE+L1169bQr+fip06dGp4oJ83lmYd5wj/EmMa4TaHivo4EeCguYZBnkB5g2aWA69OIEnUHOaGysjIYMGBAMGnSpODYsWPZwCpFmm4lNq+4gSLQA7jcX8DwtjEyRC8wjabnXEx9kfWnTJkSJkAo90xpJVV+FmcVNeYAF5zWngS4C4O91MBxmAv8blLEpbjI5sz9MTdAhcgkCT1RO8mZkAjfiYpTEvStAS53Uw1vAiUGgZ3GpuQEYvoiBqlIan7kSDHnTwJQFNiPu0+5VxCVYhcZIjNrdXUDdp+Eq5AZ3Gkg8QAyVZRZIk4Tl4QAbF9cXJxNYZMAtAokgs4BrNxEpCtteXg7DDTMDKYNSuQdKsnJBek7HxewvxaosWxLYXtw+cJp18217wql4aKCfBNoEu0O5VU+PhctJ0YeXD4C6JQpyrlpSLTojpGGGN5YwNziChdIZLk4lvLcFJ9jMX3QdiImY9bmGQU+TRUL5CHITTRlgF8D9ouD1MfmLoEPl5xokIumZ2cfgMpHt47IW9N64Hsh7wQYYjyIugWuF5fCqYncXRd5vPMWyizzvhi/32+nvG0dZc9vR6fZOu0md5e+uC408FvKSIOZwXlGvxPv95izA2Vtvg1xKFWARI+vMX66HUhpQQb643uW1bSjuTWyw2SBvDrBvjFic1eGGlz5esq3ko9uSIlBRqPuFcCv8F4WIcN12nVaBd0SaYwI6PDDImR11JkqgHcPmQssjxIn6bUshygDFJUTxPMpHk+jfjPgupgdnYV2R/g7xSjtpah8RJBewhwf0gGK6XI92u4wXFEU40afJ4DN4h5LcAd+40HI3JgJecuT0c062W0i2hQJUTcxan3/CMW1PF2K6bbA+Daz4xRs1D3Br1Cm0OihKCqizW78/nXAF/G5TXrEcVzaNMH6CyMswqsAHqDyDLEyou8lwOXnKF8DjI6KjV3KzMBiXkDH8ij/H214J5A596ekrZ3F0zXlWeL7+P5eUrNo3/QwC15uxthuzidy7DzKRwEDaAViiDgKbTbz7CJnzo0bN7pIfIiid8SuPwn25o3QCmpnyjlZkyxPP8EomCJzrGb7GJMx7tNsq4MT2xMUYaiErZOluTzKsnz3gwCeCZyVRZJfYplNEokEjwrPtxlxjeYAk+F1F74VAzPxQRNYYdtpOUvWs8J1sGhBJMNsb7igN8plJs1eSmLIhLKE4rvaCX27gOhLpLOsIzJ7qn/i+wZzcvSOZ23/du8TZjwV8zHIXoP4R3ifBxiFz1dcVpa3aPntPE+c6TmIWE9EtcMmAcPdWAhYhAXxcLOQi9L1WhD1Sc8p1d2oL7XGiRKp8F4A2i8K/nfI+y/gsTDJ/YC/8+AD5Uh04KHiGl+cIFPnBDDrPMjwRGkLXyxO4VGbfQWnDH2v0bVWE3C9QOXlepbgjEfIJQI6XDG3z5ahD9cw2pS78ipB85wyScNTvsVzlzzhL8/jRrnmVjfFJK/m3m4nj9vbgQTguT8XZTjsm672R5uJKEaQmBI/c58gyus8ZDagLpEVSJBIyHp4jn++xqPV71OgQgJYEWOtZ/haxRtKmWOBu8xdBLftWltsY84zE6WIEy/eIOWL+BaayMx+KHtL7EAkqdNDLiEXmEMUHniedtJqg9HmZtfvt26vNi0BdG3Ft3g8ZOf7PAu59TxtzivLNIekyi+wD1i8CuUiD9FXAa8C+/xS3JPmZnomyc7H+fb4/Se0bk41Fel621r4cgVxbq91V4jVqwB7HTe2M7jgB+QWHavZkDRPmZcASoZEmBx6i75bGjPcMdL4/VKGFAGWZkGzPG0XAbdL9A81G5LOmUnC9hHKJeO7dcUMjblSl12867ElFTtaGl20xvvLGPdVz/8TVuU7y0x1PG7vtNg24oz9Uo/Z412++VFWI7Fcog9tu9Lm6gvRmIPv9x1xmQAu6RDkXtbOtlGEmpgD5Nvnyc0dcv0EE6cfdi1HmhMf9wDF3k3gtRvEedhxjpgfqPb9PU9iEJHnyOUA7bQUXh6kq/D7l2iTjWv7XOD530BDr8jIrus+srXjt4MzumJMHuTsBa63YKE1+RR5lBjEikCCnWKWiHdzOgKO+nRIBAF88za/IFmJ3eMZov4CYxGBabcpGL8EYx+SeMXJeRwHNsV/h+vdxeuhEpN3ZyNY78Gm2fknJxVGhyjixPiQvVkNzT1elD9Py/aTAL64Hb9vcYmC9zfdXdT/C1LeGbg4rnBaAihDFJH12W5ulfNCNe/xTsP3bp8ikzJs5BF+5PNfAQYAPaseTdsEcaYAAAAASUVORK5CYII="
      };
    },
    computed: {
      iconSnowWidth() {
        return (Math.floor(this.iconSize / 24) || 1) * 2;
      },
      contentdownText() {
        return this.contentText.contentdown || t$1("uni-load-more.contentdown");
      },
      contentrefreshText() {
        return this.contentText.contentrefresh || t$1("uni-load-more.contentrefresh");
      },
      contentnomoreText() {
        return this.contentText.contentnomore || t$1("uni-load-more.contentnomore");
      }
    },
    mounted() {
      var pages = getCurrentPages();
      var page = pages[pages.length - 1];
      var currentWebview = page.$getAppWebview();
      currentWebview.addEventListener("hide", () => {
        this.webviewHide = true;
      });
      currentWebview.addEventListener("show", () => {
        this.webviewHide = false;
      });
    },
    methods: {
      onClick() {
        this.$emit("clickLoadMore", {
          detail: {
            status: this.status
          }
        });
      }
    }
  };
  function _sfc_render$7(_ctx, _cache, $props, $setup, $data, $options) {
    return vue.openBlock(), vue.createElementBlock("view", {
      class: "uni-load-more",
      onClick: _cache[0] || (_cache[0] = (...args) => $options.onClick && $options.onClick(...args))
    }, [
      !$data.webviewHide && ($props.iconType === "circle" || $props.iconType === "auto" && $data.platform === "android") && $props.status === "loading" && $props.showIcon ? (vue.openBlock(), vue.createElementBlock(
        "view",
        {
          key: 0,
          style: vue.normalizeStyle({ width: $props.iconSize + "px", height: $props.iconSize + "px" }),
          class: "uni-load-more__img uni-load-more__img--android-MP"
        },
        [
          vue.createElementVNode(
            "view",
            {
              class: "uni-load-more__img-icon",
              style: vue.normalizeStyle({ borderTopColor: $props.color, borderTopWidth: $props.iconSize / 12 })
            },
            null,
            4
            /* STYLE */
          ),
          vue.createElementVNode(
            "view",
            {
              class: "uni-load-more__img-icon",
              style: vue.normalizeStyle({ borderTopColor: $props.color, borderTopWidth: $props.iconSize / 12 })
            },
            null,
            4
            /* STYLE */
          ),
          vue.createElementVNode(
            "view",
            {
              class: "uni-load-more__img-icon",
              style: vue.normalizeStyle({ borderTopColor: $props.color, borderTopWidth: $props.iconSize / 12 })
            },
            null,
            4
            /* STYLE */
          )
        ],
        4
        /* STYLE */
      )) : !$data.webviewHide && $props.status === "loading" && $props.showIcon ? (vue.openBlock(), vue.createElementBlock(
        "view",
        {
          key: 1,
          style: vue.normalizeStyle({ width: $props.iconSize + "px", height: $props.iconSize + "px" }),
          class: "uni-load-more__img uni-load-more__img--ios-H5"
        },
        [
          vue.createElementVNode("image", {
            src: $data.imgBase64,
            mode: "widthFix"
          }, null, 8, ["src"])
        ],
        4
        /* STYLE */
      )) : vue.createCommentVNode("v-if", true),
      $props.showText ? (vue.openBlock(), vue.createElementBlock(
        "text",
        {
          key: 2,
          class: "uni-load-more__text",
          style: vue.normalizeStyle({ color: $props.color })
        },
        vue.toDisplayString($props.status === "more" ? $options.contentdownText : $props.status === "loading" ? $options.contentrefreshText : $options.contentnomoreText),
        5
        /* TEXT, STYLE */
      )) : vue.createCommentVNode("v-if", true)
    ]);
  }
  const __easycom_2$1 = /* @__PURE__ */ _export_sfc(_sfc_main$8, [["render", _sfc_render$7], ["__scopeId", "data-v-9245e42c"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/uni_modules/uni-load-more/components/uni-load-more/uni-load-more.vue"]]);
  const _sfc_main$7 = {
    __name: "classifyList",
    setup(__props, { expose: __expose }) {
      __expose();
      let queryParams = {};
      let classifyPicList = vue.ref([]);
      let noData = vue.ref(false);
      onLoad((e) => {
        let {
          id = null,
          name = "分类"
        } = e;
        queryParams.classid = id;
        queryParams.pageNum = 1;
        uni.setNavigationBarTitle({
          title: name
        });
        getClassifyPicList();
      });
      onUnload(() => {
        uni.removeStorageSync("classifyPicList");
      });
      onReachBottom(() => {
        if (noData.value)
          return;
        queryParams.pageNum++;
        getClassifyPicList();
      });
      async function getClassifyPicList() {
        let res = await apiGetClassifyPicList(queryParams);
        if (res.data.length <= 0) {
          noData.value = true;
        }
        formatAppLog("log", "at pages/classifyList/classifyList.vue:63", res);
        classifyPicList.value = [...classifyPicList.value, ...res.data];
        uni.setStorageSync("classifyPicList", classifyPicList.value);
      }
      const __returned__ = { get queryParams() {
        return queryParams;
      }, set queryParams(v) {
        queryParams = v;
      }, get classifyPicList() {
        return classifyPicList;
      }, set classifyPicList(v) {
        classifyPicList = v;
      }, get noData() {
        return noData;
      }, set noData(v) {
        noData = v;
      }, getClassifyPicList, ref: vue.ref, get apiGetClassifyPicList() {
        return apiGetClassifyPicList;
      }, get onLoad() {
        return onLoad;
      }, get onUnload() {
        return onUnload;
      }, get onReachBottom() {
        return onReachBottom;
      } };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$6(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_load_more = resolveEasycom(vue.resolveDynamicComponent("uni-load-more"), __easycom_2$1);
    return vue.openBlock(), vue.createElementBlock("view", { class: "classifyListContainer" }, [
      vue.createCommentVNode(' <view class="loadingContainer" v-if="classifyPicList.length==0&&!noData">\r\n			<uni-load-more status="loading" />\r\n		</view> '),
      vue.createElementVNode("view", { class: "listContent" }, [
        (vue.openBlock(true), vue.createElementBlock(
          vue.Fragment,
          null,
          vue.renderList($setup.classifyPicList, (item) => {
            return vue.openBlock(), vue.createElementBlock("navigator", {
              class: "item",
              url: "/pages/preview/preview?id=" + item._id,
              key: item._id
            }, [
              vue.createElementVNode("image", {
                src: item.smallPicurl,
                mode: "aspectFill"
              }, null, 8, ["src"])
            ], 8, ["url"]);
          }),
          128
          /* KEYED_FRAGMENT */
        ))
      ]),
      vue.createElementVNode("view", { class: "loadingContainer" }, [
        vue.createVNode(_component_uni_load_more, {
          status: $setup.noData ? "noMore" : "loading"
        }, null, 8, ["status"])
      ]),
      vue.createElementVNode("view", { class: "safe-area-inset-bottom" })
    ]);
  }
  const PagesClassifyListClassifyList = /* @__PURE__ */ _export_sfc(_sfc_main$7, [["render", _sfc_render$6], ["__scopeId", "data-v-d7121c9c"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/pages/classifyList/classifyList.vue"]]);
  const _sfc_main$6 = {
    name: "UniRate",
    props: {
      isFill: {
        // 星星的类型，是否镂空
        type: [Boolean, String],
        default: true
      },
      color: {
        // 星星未选中的颜色
        type: String,
        default: "#ececec"
      },
      activeColor: {
        // 星星选中状态颜色
        type: String,
        default: "#ffca3e"
      },
      disabledColor: {
        // 星星禁用状态颜色
        type: String,
        default: "#c0c0c0"
      },
      size: {
        // 星星的大小
        type: [Number, String],
        default: 24
      },
      value: {
        // 当前评分
        type: [Number, String],
        default: 0
      },
      modelValue: {
        // 当前评分
        type: [Number, String],
        default: 0
      },
      max: {
        // 最大评分
        type: [Number, String],
        default: 5
      },
      margin: {
        // 星星的间距
        type: [Number, String],
        default: 0
      },
      disabled: {
        // 是否可点击
        type: [Boolean, String],
        default: false
      },
      readonly: {
        // 是否只读
        type: [Boolean, String],
        default: false
      },
      allowHalf: {
        // 是否显示半星
        type: [Boolean, String],
        default: false
      },
      touchable: {
        // 是否支持滑动手势
        type: [Boolean, String],
        default: true
      }
    },
    data() {
      return {
        valueSync: "",
        userMouseFristMove: true,
        userRated: false,
        userLastRate: 1
      };
    },
    watch: {
      value(newVal) {
        this.valueSync = Number(newVal);
      },
      modelValue(newVal) {
        this.valueSync = Number(newVal);
      }
    },
    computed: {
      stars() {
        const value = this.valueSync ? this.valueSync : 0;
        const starList = [];
        const floorValue = Math.floor(value);
        const ceilValue = Math.ceil(value);
        for (let i = 0; i < this.max; i++) {
          if (floorValue > i) {
            starList.push({
              activeWitch: "100%"
            });
          } else if (ceilValue - 1 === i) {
            starList.push({
              activeWitch: (value - floorValue) * 100 + "%"
            });
          } else {
            starList.push({
              activeWitch: "0"
            });
          }
        }
        return starList;
      },
      marginNumber() {
        return Number(this.margin);
      }
    },
    created() {
      this.valueSync = Number(this.value || this.modelValue);
      this._rateBoxLeft = 0;
      this._oldValue = null;
    },
    mounted() {
      setTimeout(() => {
        this._getSize();
      }, 100);
    },
    methods: {
      touchstart(e) {
        if (this.readonly || this.disabled)
          return;
        const {
          clientX,
          screenX
        } = e.changedTouches[0];
        this._getRateCount(clientX || screenX);
      },
      touchmove(e) {
        if (this.readonly || this.disabled || !this.touchable)
          return;
        const {
          clientX,
          screenX
        } = e.changedTouches[0];
        this._getRateCount(clientX || screenX);
      },
      /**
       * 兼容 PC @tian
       */
      mousedown(e) {
      },
      mousemove(e) {
      },
      mouseleave(e) {
      },
      /**
       * 获取星星个数
       */
      _getRateCount(clientX) {
        this._getSize();
        const size = Number(this.size);
        if (isNaN(size)) {
          return new Error("size 属性只能设置为数字");
        }
        const rateMoveRange = clientX - this._rateBoxLeft;
        let index = parseInt(rateMoveRange / (size + this.marginNumber));
        index = index < 0 ? 0 : index;
        index = index > this.max ? this.max : index;
        const range = parseInt(rateMoveRange - (size + this.marginNumber) * index);
        let value = 0;
        if (this._oldValue === index && !this.PC)
          return;
        this._oldValue = index;
        if (this.allowHalf) {
          if (range > size / 2) {
            value = index + 1;
          } else {
            value = index + 0.5;
          }
        } else {
          value = index + 1;
        }
        value = Math.max(0.5, Math.min(value, this.max));
        this.valueSync = value;
        this._onChange();
      },
      /**
       * 触发动态修改
       */
      _onChange() {
        this.$emit("input", this.valueSync);
        this.$emit("update:modelValue", this.valueSync);
        this.$emit("change", {
          value: this.valueSync
        });
      },
      /**
       * 获取星星距离屏幕左侧距离
       */
      _getSize() {
        uni.createSelectorQuery().in(this).select(".uni-rate").boundingClientRect().exec((ret) => {
          if (ret) {
            this._rateBoxLeft = ret[0].left;
          }
        });
      }
    }
  };
  function _sfc_render$5(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    return vue.openBlock(), vue.createElementBlock("view", null, [
      vue.createElementVNode(
        "view",
        {
          ref: "uni-rate",
          class: "uni-rate"
        },
        [
          (vue.openBlock(true), vue.createElementBlock(
            vue.Fragment,
            null,
            vue.renderList($options.stars, (star, index) => {
              return vue.openBlock(), vue.createElementBlock(
                "view",
                {
                  class: vue.normalizeClass(["uni-rate__icon", { "uni-cursor-not-allowed": $props.disabled }]),
                  style: vue.normalizeStyle({ "margin-right": $options.marginNumber + "px" }),
                  key: index,
                  onTouchstart: _cache[0] || (_cache[0] = vue.withModifiers((...args) => $options.touchstart && $options.touchstart(...args), ["stop"])),
                  onTouchmove: _cache[1] || (_cache[1] = vue.withModifiers((...args) => $options.touchmove && $options.touchmove(...args), ["stop"])),
                  onMousedown: _cache[2] || (_cache[2] = vue.withModifiers((...args) => $options.mousedown && $options.mousedown(...args), ["stop"])),
                  onMousemove: _cache[3] || (_cache[3] = vue.withModifiers((...args) => $options.mousemove && $options.mousemove(...args), ["stop"])),
                  onMouseleave: _cache[4] || (_cache[4] = (...args) => $options.mouseleave && $options.mouseleave(...args))
                },
                [
                  vue.createVNode(_component_uni_icons, {
                    color: $props.color,
                    size: $props.size,
                    type: $props.isFill ? "star-filled" : "star"
                  }, null, 8, ["color", "size", "type"]),
                  vue.createElementVNode(
                    "view",
                    {
                      style: vue.normalizeStyle({ width: star.activeWitch }),
                      class: "uni-rate__icon-on"
                    },
                    [
                      vue.createVNode(_component_uni_icons, {
                        color: $props.disabled ? $props.disabledColor : $props.activeColor,
                        size: $props.size,
                        type: "star-filled"
                      }, null, 8, ["color", "size"])
                    ],
                    4
                    /* STYLE */
                  )
                ],
                38
                /* CLASS, STYLE, NEED_HYDRATION */
              );
            }),
            128
            /* KEYED_FRAGMENT */
          ))
        ],
        512
        /* NEED_PATCH */
      )
    ]);
  }
  const __easycom_2 = /* @__PURE__ */ _export_sfc(_sfc_main$6, [["render", _sfc_render$5], ["__scopeId", "data-v-5c8fbdf3"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/uni_modules/uni-rate/components/uni-rate/uni-rate.vue"]]);
  class MPAnimation {
    constructor(options, _this) {
      this.options = options;
      this.animation = uni.createAnimation({
        ...options
      });
      this.currentStepAnimates = {};
      this.next = 0;
      this.$ = _this;
    }
    _nvuePushAnimates(type, args) {
      let aniObj = this.currentStepAnimates[this.next];
      let styles = {};
      if (!aniObj) {
        styles = {
          styles: {},
          config: {}
        };
      } else {
        styles = aniObj;
      }
      if (animateTypes1.includes(type)) {
        if (!styles.styles.transform) {
          styles.styles.transform = "";
        }
        let unit = "";
        if (type === "rotate") {
          unit = "deg";
        }
        styles.styles.transform += `${type}(${args + unit}) `;
      } else {
        styles.styles[type] = `${args}`;
      }
      this.currentStepAnimates[this.next] = styles;
    }
    _animateRun(styles = {}, config = {}) {
      let ref = this.$.$refs["ani"].ref;
      if (!ref)
        return;
      return new Promise((resolve, reject) => {
        nvueAnimation.transition(ref, {
          styles,
          ...config
        }, (res) => {
          resolve();
        });
      });
    }
    _nvueNextAnimate(animates, step = 0, fn) {
      let obj = animates[step];
      if (obj) {
        let {
          styles,
          config
        } = obj;
        this._animateRun(styles, config).then(() => {
          step += 1;
          this._nvueNextAnimate(animates, step, fn);
        });
      } else {
        this.currentStepAnimates = {};
        typeof fn === "function" && fn();
        this.isEnd = true;
      }
    }
    step(config = {}) {
      this.animation.step(config);
      return this;
    }
    run(fn) {
      this.$.animationData = this.animation.export();
      this.$.timer = setTimeout(() => {
        typeof fn === "function" && fn();
      }, this.$.durationTime);
    }
  }
  const animateTypes1 = [
    "matrix",
    "matrix3d",
    "rotate",
    "rotate3d",
    "rotateX",
    "rotateY",
    "rotateZ",
    "scale",
    "scale3d",
    "scaleX",
    "scaleY",
    "scaleZ",
    "skew",
    "skewX",
    "skewY",
    "translate",
    "translate3d",
    "translateX",
    "translateY",
    "translateZ"
  ];
  const animateTypes2 = ["opacity", "backgroundColor"];
  const animateTypes3 = ["width", "height", "left", "right", "top", "bottom"];
  animateTypes1.concat(animateTypes2, animateTypes3).forEach((type) => {
    MPAnimation.prototype[type] = function(...args) {
      this.animation[type](...args);
      return this;
    };
  });
  function createAnimation(option, _this) {
    if (!_this)
      return;
    clearTimeout(_this.timer);
    return new MPAnimation(option, _this);
  }
  const _sfc_main$5 = {
    name: "uniTransition",
    emits: ["click", "change"],
    props: {
      show: {
        type: Boolean,
        default: false
      },
      modeClass: {
        type: [Array, String],
        default() {
          return "fade";
        }
      },
      duration: {
        type: Number,
        default: 300
      },
      styles: {
        type: Object,
        default() {
          return {};
        }
      },
      customClass: {
        type: String,
        default: ""
      },
      onceRender: {
        type: Boolean,
        default: false
      }
    },
    data() {
      return {
        isShow: false,
        transform: "",
        opacity: 1,
        animationData: {},
        durationTime: 300,
        config: {}
      };
    },
    watch: {
      show: {
        handler(newVal) {
          if (newVal) {
            this.open();
          } else {
            if (this.isShow) {
              this.close();
            }
          }
        },
        immediate: true
      }
    },
    computed: {
      // 生成样式数据
      stylesObject() {
        let styles = {
          ...this.styles,
          "transition-duration": this.duration / 1e3 + "s"
        };
        let transform = "";
        for (let i in styles) {
          let line = this.toLine(i);
          transform += line + ":" + styles[i] + ";";
        }
        return transform;
      },
      // 初始化动画条件
      transformStyles() {
        return "transform:" + this.transform + ";opacity:" + this.opacity + ";" + this.stylesObject;
      }
    },
    created() {
      this.config = {
        duration: this.duration,
        timingFunction: "ease",
        transformOrigin: "50% 50%",
        delay: 0
      };
      this.durationTime = this.duration;
    },
    methods: {
      /**
       *  ref 触发 初始化动画
       */
      init(obj = {}) {
        if (obj.duration) {
          this.durationTime = obj.duration;
        }
        this.animation = createAnimation(Object.assign(this.config, obj), this);
      },
      /**
       * 点击组件触发回调
       */
      onClick() {
        this.$emit("click", {
          detail: this.isShow
        });
      },
      /**
       * ref 触发 动画分组
       * @param {Object} obj
       */
      step(obj, config = {}) {
        if (!this.animation)
          return;
        for (let i in obj) {
          try {
            if (typeof obj[i] === "object") {
              this.animation[i](...obj[i]);
            } else {
              this.animation[i](obj[i]);
            }
          } catch (e) {
            formatAppLog("error", "at uni_modules/uni-transition/components/uni-transition/uni-transition.vue:148", `方法 ${i} 不存在`);
          }
        }
        this.animation.step(config);
        return this;
      },
      /**
       *  ref 触发 执行动画
       */
      run(fn) {
        if (!this.animation)
          return;
        this.animation.run(fn);
      },
      // 开始过度动画
      open() {
        clearTimeout(this.timer);
        this.transform = "";
        this.isShow = true;
        let { opacity, transform } = this.styleInit(false);
        if (typeof opacity !== "undefined") {
          this.opacity = opacity;
        }
        this.transform = transform;
        this.$nextTick(() => {
          this.timer = setTimeout(() => {
            this.animation = createAnimation(this.config, this);
            this.tranfromInit(false).step();
            this.animation.run();
            this.$emit("change", {
              detail: this.isShow
            });
          }, 20);
        });
      },
      // 关闭过度动画
      close(type) {
        if (!this.animation)
          return;
        this.tranfromInit(true).step().run(() => {
          this.isShow = false;
          this.animationData = null;
          this.animation = null;
          let { opacity, transform } = this.styleInit(false);
          this.opacity = opacity || 1;
          this.transform = transform;
          this.$emit("change", {
            detail: this.isShow
          });
        });
      },
      // 处理动画开始前的默认样式
      styleInit(type) {
        let styles = {
          transform: ""
        };
        let buildStyle = (type2, mode) => {
          if (mode === "fade") {
            styles.opacity = this.animationType(type2)[mode];
          } else {
            styles.transform += this.animationType(type2)[mode] + " ";
          }
        };
        if (typeof this.modeClass === "string") {
          buildStyle(type, this.modeClass);
        } else {
          this.modeClass.forEach((mode) => {
            buildStyle(type, mode);
          });
        }
        return styles;
      },
      // 处理内置组合动画
      tranfromInit(type) {
        let buildTranfrom = (type2, mode) => {
          let aniNum = null;
          if (mode === "fade") {
            aniNum = type2 ? 0 : 1;
          } else {
            aniNum = type2 ? "-100%" : "0";
            if (mode === "zoom-in") {
              aniNum = type2 ? 0.8 : 1;
            }
            if (mode === "zoom-out") {
              aniNum = type2 ? 1.2 : 1;
            }
            if (mode === "slide-right") {
              aniNum = type2 ? "100%" : "0";
            }
            if (mode === "slide-bottom") {
              aniNum = type2 ? "100%" : "0";
            }
          }
          this.animation[this.animationMode()[mode]](aniNum);
        };
        if (typeof this.modeClass === "string") {
          buildTranfrom(type, this.modeClass);
        } else {
          this.modeClass.forEach((mode) => {
            buildTranfrom(type, mode);
          });
        }
        return this.animation;
      },
      animationType(type) {
        return {
          fade: type ? 0 : 1,
          "slide-top": `translateY(${type ? "0" : "-100%"})`,
          "slide-right": `translateX(${type ? "0" : "100%"})`,
          "slide-bottom": `translateY(${type ? "0" : "100%"})`,
          "slide-left": `translateX(${type ? "0" : "-100%"})`,
          "zoom-in": `scaleX(${type ? 1 : 0.8}) scaleY(${type ? 1 : 0.8})`,
          "zoom-out": `scaleX(${type ? 1 : 1.2}) scaleY(${type ? 1 : 1.2})`
        };
      },
      // 内置动画类型与实际动画对应字典
      animationMode() {
        return {
          fade: "opacity",
          "slide-top": "translateY",
          "slide-right": "translateX",
          "slide-bottom": "translateY",
          "slide-left": "translateX",
          "zoom-in": "scale",
          "zoom-out": "scale"
        };
      },
      // 驼峰转中横线
      toLine(name) {
        return name.replace(/([A-Z])/g, "-$1").toLowerCase();
      }
    }
  };
  function _sfc_render$4(_ctx, _cache, $props, $setup, $data, $options) {
    return vue.withDirectives((vue.openBlock(), vue.createElementBlock("view", {
      ref: "ani",
      animation: $data.animationData,
      class: vue.normalizeClass($props.customClass),
      style: vue.normalizeStyle($options.transformStyles),
      onClick: _cache[0] || (_cache[0] = (...args) => $options.onClick && $options.onClick(...args))
    }, [
      vue.renderSlot(_ctx.$slots, "default")
    ], 14, ["animation"])), [
      [vue.vShow, $data.isShow]
    ]);
  }
  const __easycom_0$1 = /* @__PURE__ */ _export_sfc(_sfc_main$5, [["render", _sfc_render$4], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/uni_modules/uni-transition/components/uni-transition/uni-transition.vue"]]);
  const _sfc_main$4 = {
    name: "uniPopup",
    components: {},
    emits: ["change", "maskClick"],
    props: {
      // 开启动画
      animation: {
        type: Boolean,
        default: true
      },
      // 弹出层类型，可选值，top: 顶部弹出层；bottom：底部弹出层；center：全屏弹出层
      // message: 消息提示 ; dialog : 对话框
      type: {
        type: String,
        default: "center"
      },
      // maskClick
      isMaskClick: {
        type: Boolean,
        default: null
      },
      // TODO 2 个版本后废弃属性 ，使用 isMaskClick
      maskClick: {
        type: Boolean,
        default: null
      },
      backgroundColor: {
        type: String,
        default: "none"
      },
      safeArea: {
        type: Boolean,
        default: true
      },
      maskBackgroundColor: {
        type: String,
        default: "rgba(0, 0, 0, 0.4)"
      },
      borderRadius: {
        type: String
      }
    },
    watch: {
      /**
       * 监听type类型
       */
      type: {
        handler: function(type) {
          if (!this.config[type])
            return;
          this[this.config[type]](true);
        },
        immediate: true
      },
      isDesktop: {
        handler: function(newVal) {
          if (!this.config[newVal])
            return;
          this[this.config[this.type]](true);
        },
        immediate: true
      },
      /**
       * 监听遮罩是否可点击
       * @param {Object} val
       */
      maskClick: {
        handler: function(val) {
          this.mkclick = val;
        },
        immediate: true
      },
      isMaskClick: {
        handler: function(val) {
          this.mkclick = val;
        },
        immediate: true
      },
      // H5 下禁止底部滚动
      showPopup(show) {
      }
    },
    data() {
      return {
        duration: 300,
        ani: [],
        showPopup: false,
        showTrans: false,
        popupWidth: 0,
        popupHeight: 0,
        config: {
          top: "top",
          bottom: "bottom",
          center: "center",
          left: "left",
          right: "right",
          message: "top",
          dialog: "center",
          share: "bottom"
        },
        maskClass: {
          position: "fixed",
          bottom: 0,
          top: 0,
          left: 0,
          right: 0,
          backgroundColor: "rgba(0, 0, 0, 0.4)"
        },
        transClass: {
          backgroundColor: "transparent",
          borderRadius: this.borderRadius || "0",
          position: "fixed",
          left: 0,
          right: 0
        },
        maskShow: true,
        mkclick: true,
        popupstyle: "top"
      };
    },
    computed: {
      getStyles() {
        let res = { backgroundColor: this.bg };
        if (this.borderRadius || "0") {
          res = Object.assign(res, { borderRadius: this.borderRadius });
        }
        return res;
      },
      isDesktop() {
        return this.popupWidth >= 500 && this.popupHeight >= 500;
      },
      bg() {
        if (this.backgroundColor === "" || this.backgroundColor === "none") {
          return "transparent";
        }
        return this.backgroundColor;
      }
    },
    mounted() {
      const fixSize = () => {
        const {
          windowWidth,
          windowHeight,
          windowTop,
          safeArea,
          screenHeight,
          safeAreaInsets
        } = uni.getSystemInfoSync();
        this.popupWidth = windowWidth;
        this.popupHeight = windowHeight + (windowTop || 0);
        if (safeArea && this.safeArea) {
          this.safeAreaInsets = safeAreaInsets.bottom;
        } else {
          this.safeAreaInsets = 0;
        }
      };
      fixSize();
    },
    // TODO vue3
    unmounted() {
      this.setH5Visible();
    },
    activated() {
      this.setH5Visible(!this.showPopup);
    },
    deactivated() {
      this.setH5Visible(true);
    },
    created() {
      if (this.isMaskClick === null && this.maskClick === null) {
        this.mkclick = true;
      } else {
        this.mkclick = this.isMaskClick !== null ? this.isMaskClick : this.maskClick;
      }
      if (this.animation) {
        this.duration = 300;
      } else {
        this.duration = 0;
      }
      this.messageChild = null;
      this.clearPropagation = false;
      this.maskClass.backgroundColor = this.maskBackgroundColor;
    },
    methods: {
      setH5Visible(visible = true) {
      },
      /**
       * 公用方法，不显示遮罩层
       */
      closeMask() {
        this.maskShow = false;
      },
      /**
       * 公用方法，遮罩层禁止点击
       */
      disableMask() {
        this.mkclick = false;
      },
      // TODO nvue 取消冒泡
      clear(e) {
        e.stopPropagation();
        this.clearPropagation = true;
      },
      open(direction) {
        if (this.showPopup) {
          return;
        }
        let innerType = ["top", "center", "bottom", "left", "right", "message", "dialog", "share"];
        if (!(direction && innerType.indexOf(direction) !== -1)) {
          direction = this.type;
        }
        if (!this.config[direction]) {
          formatAppLog("error", "at uni_modules/uni-popup/components/uni-popup/uni-popup.vue:310", "缺少类型：", direction);
          return;
        }
        this[this.config[direction]]();
        this.$emit("change", {
          show: true,
          type: direction
        });
      },
      close(type) {
        this.showTrans = false;
        this.$emit("change", {
          show: false,
          type: this.type
        });
        clearTimeout(this.timer);
        this.timer = setTimeout(() => {
          this.showPopup = false;
        }, 300);
      },
      // TODO 处理冒泡事件，头条的冒泡事件有问题 ，先这样兼容
      touchstart() {
        this.clearPropagation = false;
      },
      onTap() {
        if (this.clearPropagation) {
          this.clearPropagation = false;
          return;
        }
        this.$emit("maskClick");
        if (!this.mkclick)
          return;
        this.close();
      },
      /**
       * 顶部弹出样式处理
       */
      top(type) {
        this.popupstyle = this.isDesktop ? "fixforpc-top" : "top";
        this.ani = ["slide-top"];
        this.transClass = {
          position: "fixed",
          left: 0,
          right: 0,
          backgroundColor: this.bg,
          borderRadius: this.borderRadius || "0"
        };
        if (type)
          return;
        this.showPopup = true;
        this.showTrans = true;
        this.$nextTick(() => {
          this.showPoptrans();
          if (this.messageChild && this.type === "message") {
            this.messageChild.timerClose();
          }
        });
      },
      /**
       * 底部弹出样式处理
       */
      bottom(type) {
        this.popupstyle = "bottom";
        this.ani = ["slide-bottom"];
        this.transClass = {
          position: "fixed",
          left: 0,
          right: 0,
          bottom: 0,
          paddingBottom: this.safeAreaInsets + "px",
          backgroundColor: this.bg,
          borderRadius: this.borderRadius || "0"
        };
        if (type)
          return;
        this.showPoptrans();
      },
      /**
       * 中间弹出样式处理
       */
      center(type) {
        this.popupstyle = "center";
        this.ani = ["zoom-out", "fade"];
        this.transClass = {
          position: "fixed",
          display: "flex",
          flexDirection: "column",
          bottom: 0,
          left: 0,
          right: 0,
          top: 0,
          justifyContent: "center",
          alignItems: "center",
          borderRadius: this.borderRadius || "0"
        };
        if (type)
          return;
        this.showPoptrans();
      },
      left(type) {
        this.popupstyle = "left";
        this.ani = ["slide-left"];
        this.transClass = {
          position: "fixed",
          left: 0,
          bottom: 0,
          top: 0,
          backgroundColor: this.bg,
          borderRadius: this.borderRadius || "0",
          display: "flex",
          flexDirection: "column"
        };
        if (type)
          return;
        this.showPoptrans();
      },
      right(type) {
        this.popupstyle = "right";
        this.ani = ["slide-right"];
        this.transClass = {
          position: "fixed",
          bottom: 0,
          right: 0,
          top: 0,
          backgroundColor: this.bg,
          borderRadius: this.borderRadius || "0",
          display: "flex",
          flexDirection: "column"
        };
        if (type)
          return;
        this.showPoptrans();
      },
      showPoptrans() {
        this.$nextTick(() => {
          this.showPopup = true;
          this.showTrans = true;
        });
      }
    }
  };
  function _sfc_render$3(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_transition = resolveEasycom(vue.resolveDynamicComponent("uni-transition"), __easycom_0$1);
    return $data.showPopup ? (vue.openBlock(), vue.createElementBlock(
      "view",
      {
        key: 0,
        class: vue.normalizeClass(["uni-popup", [$data.popupstyle, $options.isDesktop ? "fixforpc-z-index" : ""]])
      },
      [
        vue.createElementVNode(
          "view",
          {
            onTouchstart: _cache[1] || (_cache[1] = (...args) => $options.touchstart && $options.touchstart(...args))
          },
          [
            $data.maskShow ? (vue.openBlock(), vue.createBlock(_component_uni_transition, {
              key: "1",
              name: "mask",
              "mode-class": "fade",
              styles: $data.maskClass,
              duration: $data.duration,
              show: $data.showTrans,
              onClick: $options.onTap
            }, null, 8, ["styles", "duration", "show", "onClick"])) : vue.createCommentVNode("v-if", true),
            vue.createVNode(_component_uni_transition, {
              key: "2",
              "mode-class": $data.ani,
              name: "content",
              styles: $data.transClass,
              duration: $data.duration,
              show: $data.showTrans,
              onClick: $options.onTap
            }, {
              default: vue.withCtx(() => [
                vue.createElementVNode(
                  "view",
                  {
                    class: vue.normalizeClass(["uni-popup__wrapper", [$data.popupstyle]]),
                    style: vue.normalizeStyle($options.getStyles),
                    onClick: _cache[0] || (_cache[0] = (...args) => $options.clear && $options.clear(...args))
                  },
                  [
                    vue.renderSlot(_ctx.$slots, "default", {}, void 0, true)
                  ],
                  6
                  /* CLASS, STYLE */
                )
              ]),
              _: 3
              /* FORWARDED */
            }, 8, ["mode-class", "styles", "duration", "show", "onClick"])
          ],
          32
          /* NEED_HYDRATION */
        )
      ],
      2
      /* CLASS */
    )) : vue.createCommentVNode("v-if", true);
  }
  const __easycom_3 = /* @__PURE__ */ _export_sfc(_sfc_main$4, [["render", _sfc_render$3], ["__scopeId", "data-v-4dd3c44b"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/uni_modules/uni-popup/components/uni-popup/uni-popup.vue"]]);
  const _sfc_main$3 = {
    __name: "preview",
    setup(__props, { expose: __expose }) {
      __expose();
      let isShowMask = vue.ref(true);
      let infoPopup = vue.ref(null);
      let rateSourcePopup = vue.ref(null);
      let userRate = vue.ref(0);
      let bigPicList = vue.ref([]);
      let currentId = vue.ref(null);
      let currentIdx = vue.ref(-1);
      let currentInfo = vue.ref({
        score: 0
      });
      let isRated = vue.ref(false);
      onLoad((e) => {
        currentId.value = e.id;
        currentIdx.value = bigPicList.value.findIndex((item) => item._id == currentId.value);
        currentInfo.value = bigPicList.value[currentIdx.value];
      });
      async function onClickedDownLoadBtn() {
        let res = await apiWriteDownload({
          classid: currentInfo.value.classid,
          wallId: currentInfo.value._id
        });
        if (res.errCode != 0) {
          uni.hideLoading();
          return;
        }
        uni.getImageInfo({
          src: currentInfo.value.picurl
        }).then((imageInfo) => {
          uni.showLoading({
            title: "正在保存",
            mask: true
          });
          uni.saveImageToPhotosAlbum({
            filePath: imageInfo.path
          }).then((saveImageInfo) => {
            uni.hideLoading();
            uni.showToast({
              title: "保存成功",
              icon: "none"
            });
          }).catch((saveImageInfo) => {
            uni.hideLoading();
            formatAppLog("log", "at pages/preview/preview.vue:171", saveImageInfo);
            if (saveImageInfo.errMsg == "saveImageToPhotosAlbum:fail auth deny") {
              uni.showModal({
                title: "提示",
                content: "保存失败，请开启保存到相册权限"
              }).then((res2) => {
                if (res2.confirm) {
                  uni.openSetting().then((settings) => {
                    if (settings.authSetting["scope.writePhotosAlbum"]) {
                      uni.showToast({
                        title: "获取授权成功",
                        icon: "none"
                      });
                    } else {
                      uni.showToast({
                        title: "获取授权失败",
                        icon: "none"
                      });
                    }
                  });
                }
              });
            } else {
              uni.showToast({
                title: "保存失败,请重试",
                icon: "none"
              });
            }
          });
        });
      }
      function onClickedImg() {
        isShowMask.value = !isShowMask.value;
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
        let res = await apiGetSetupScore({
          classid,
          wallId,
          userScore: userRate.value
        });
        if (res.errCode == 0) {
          uni.showToast({
            title: "评分成功",
            icon: "success"
          });
          bigPicList.value[currentIdx.value].userScore = userRate.value;
          uni.setStorageSync("classifyPicList", bigPicList.value);
          onClickedRateSourceCloseBtn();
          userRate.value = 0;
        }
      }
      function onClickedBackBtn() {
        uni.navigateBack({
          fail: () => {
            uni.reLaunch({
              url: "/pages/index/index"
            });
          }
        });
      }
      let classifyPicList = uni.getStorageSync("classifyPicList") || [];
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
      const __returned__ = { get isShowMask() {
        return isShowMask;
      }, set isShowMask(v) {
        isShowMask = v;
      }, get infoPopup() {
        return infoPopup;
      }, set infoPopup(v) {
        infoPopup = v;
      }, get rateSourcePopup() {
        return rateSourcePopup;
      }, set rateSourcePopup(v) {
        rateSourcePopup = v;
      }, get userRate() {
        return userRate;
      }, set userRate(v) {
        userRate = v;
      }, get bigPicList() {
        return bigPicList;
      }, set bigPicList(v) {
        bigPicList = v;
      }, get currentId() {
        return currentId;
      }, set currentId(v) {
        currentId = v;
      }, get currentIdx() {
        return currentIdx;
      }, set currentIdx(v) {
        currentIdx = v;
      }, get currentInfo() {
        return currentInfo;
      }, set currentInfo(v) {
        currentInfo = v;
      }, get isRated() {
        return isRated;
      }, set isRated(v) {
        isRated = v;
      }, onClickedDownLoadBtn, onClickedImg, onClickedInfo, onClickedInfoCloseBtn, onClickedRateSource, onClickedRateSourceCloseBtn, onClickedConfirmBtn, onClickedBackBtn, get classifyPicList() {
        return classifyPicList;
      }, set classifyPicList(v) {
        classifyPicList = v;
      }, onSwiperChange, ref: vue.ref, get getStatusBarHeight() {
        return getStatusBarHeight;
      }, get onLoad() {
        return onLoad;
      }, get apiGetSetupScore() {
        return apiGetSetupScore;
      }, get apiWriteDownload() {
        return apiWriteDownload;
      }, classifyListVue: PagesClassifyListClassifyList };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render$2(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    const _component_uni_dateformat = resolveEasycom(vue.resolveDynamicComponent("uni-dateformat"), __easycom_1$2);
    const _component_uni_rate = resolveEasycom(vue.resolveDynamicComponent("uni-rate"), __easycom_2);
    const _component_uni_popup = resolveEasycom(vue.resolveDynamicComponent("uni-popup"), __easycom_3);
    return vue.openBlock(), vue.createElementBlock("view", { class: "previewContainer" }, [
      vue.createElementVNode("swiper", {
        current: $setup.currentIdx,
        onChange: $setup.onSwiperChange
      }, [
        (vue.openBlock(true), vue.createElementBlock(
          vue.Fragment,
          null,
          vue.renderList($setup.bigPicList, (item, index) => {
            return vue.openBlock(), vue.createElementBlock("swiper-item", {
              key: item._id
            }, [
              index == $setup.currentIdx || index == $setup.currentIdx - 1 || index == $setup.currentIdx + 1 ? (vue.openBlock(), vue.createElementBlock("image", {
                key: 0,
                onClick: _cache[0] || (_cache[0] = ($event) => $setup.isShowMask = !$setup.isShowMask),
                src: item.picurl,
                mode: "aspectFill"
              }, null, 8, ["src"])) : vue.createCommentVNode("v-if", true)
            ]);
          }),
          128
          /* KEYED_FRAGMENT */
        ))
      ], 40, ["current"]),
      $setup.isShowMask ? (vue.openBlock(), vue.createElementBlock("view", {
        key: 0,
        class: "mask"
      }, [
        vue.createElementVNode(
          "view",
          {
            class: "backBtn",
            onClick: $setup.onClickedBackBtn,
            style: vue.normalizeStyle({ top: $setup.getStatusBarHeight() + "px" })
          },
          [
            vue.createVNode(_component_uni_icons, {
              type: "left",
              size: "30",
              color: "#fff"
            })
          ],
          4
          /* STYLE */
        ),
        vue.createElementVNode(
          "view",
          { class: "picCount" },
          vue.toDisplayString($setup.currentIdx + 1) + " / " + vue.toDisplayString($setup.bigPicList.length),
          1
          /* TEXT */
        ),
        vue.createElementVNode("view", { class: "time" }, [
          vue.createVNode(_component_uni_dateformat, {
            date: /* @__PURE__ */ new Date(),
            format: "hh:mm"
          }, null, 8, ["date"])
        ]),
        vue.createElementVNode("view", { class: "date" }, [
          vue.createVNode(_component_uni_dateformat, {
            date: /* @__PURE__ */ new Date(),
            format: "MM月dd日"
          }, null, 8, ["date"])
        ]),
        vue.createElementVNode("view", { class: "footer" }, [
          vue.createElementVNode("view", {
            class: "btn",
            onClick: $setup.onClickedInfo
          }, [
            vue.createVNode(_component_uni_icons, {
              type: "info",
              size: "30",
              color: "black"
            }),
            vue.createElementVNode("view", { class: "text" }, "详情")
          ]),
          vue.createElementVNode("view", {
            class: "btn",
            onClick: $setup.onClickedRateSource
          }, [
            vue.createVNode(_component_uni_icons, {
              type: "star",
              size: "30",
              color: "black"
            }),
            vue.createElementVNode(
              "view",
              { class: "text" },
              vue.toDisplayString($setup.currentInfo.score) + "分",
              1
              /* TEXT */
            )
          ]),
          vue.createElementVNode("view", {
            class: "btn",
            onClick: $setup.onClickedDownLoadBtn
          }, [
            vue.createVNode(_component_uni_icons, {
              type: "download",
              size: "30",
              color: "black"
            }),
            vue.createElementVNode("view", { class: "text" }, "下载")
          ])
        ])
      ])) : vue.createCommentVNode("v-if", true),
      vue.createCommentVNode(" 信息弹出窗 "),
      vue.createVNode(
        _component_uni_popup,
        {
          ref: "infoPopup",
          type: "bottom"
        },
        {
          default: vue.withCtx(() => [
            vue.createElementVNode("view", { class: "infoPopup" }, [
              vue.createElementVNode("view", { class: "infoHeader" }, [
                vue.createElementVNode("view"),
                vue.createElementVNode("view", { class: "text" }, "壁纸信息"),
                vue.createVNode(_component_uni_icons, {
                  onClick: $setup.onClickedInfoCloseBtn,
                  type: "closeempty",
                  size: "20",
                  color: "#999"
                })
              ]),
              vue.createElementVNode("scroll-view", {
                class: "infoBody",
                "scroll-y": ""
              }, [
                vue.createElementVNode("view", { class: "content" }, [
                  vue.createElementVNode("view", { class: "item" }, [
                    vue.createElementVNode("view", { class: "key" }, "壁纸ID："),
                    vue.createElementVNode(
                      "view",
                      {
                        class: "value",
                        selectable: ""
                      },
                      vue.toDisplayString($setup.currentInfo._id),
                      1
                      /* TEXT */
                    )
                  ]),
                  vue.createElementVNode("view", { class: "item" }, [
                    vue.createElementVNode("view", { class: "key" }, "发布者："),
                    vue.createElementVNode(
                      "view",
                      {
                        class: "value",
                        selectable: ""
                      },
                      vue.toDisplayString($setup.currentInfo.nickname),
                      1
                      /* TEXT */
                    )
                  ]),
                  vue.createElementVNode("view", { class: "item" }, [
                    vue.createElementVNode("view", { class: "key" }, "评分："),
                    vue.createElementVNode("view", { class: "value rateBox" }, [
                      vue.createVNode(_component_uni_rate, {
                        readonly: "",
                        value: $setup.currentInfo.score
                      }, null, 8, ["value"]),
                      vue.createElementVNode(
                        "text",
                        { class: "text" },
                        vue.toDisplayString($setup.currentInfo.score) + "分",
                        1
                        /* TEXT */
                      )
                    ])
                  ]),
                  vue.createElementVNode("view", { class: "item" }, [
                    vue.createElementVNode("view", { class: "key" }, "摘要："),
                    vue.createElementVNode(
                      "view",
                      {
                        class: "value",
                        selectable: ""
                      },
                      vue.toDisplayString($setup.currentInfo.description),
                      1
                      /* TEXT */
                    )
                  ]),
                  vue.createElementVNode("view", { class: "item" }, [
                    vue.createElementVNode("view", { class: "key" }, "标签："),
                    vue.createElementVNode("view", { class: "value tabs" }, [
                      (vue.openBlock(true), vue.createElementBlock(
                        vue.Fragment,
                        null,
                        vue.renderList($setup.currentInfo.tabs, (item) => {
                          return vue.openBlock(), vue.createElementBlock(
                            "view",
                            {
                              class: "tab",
                              selectable: "",
                              key: item
                            },
                            vue.toDisplayString(item),
                            1
                            /* TEXT */
                          );
                        }),
                        128
                        /* KEYED_FRAGMENT */
                      ))
                    ])
                  ])
                ])
              ])
            ])
          ]),
          _: 1
          /* STABLE */
        },
        512
        /* NEED_PATCH */
      ),
      vue.createCommentVNode(" 评分弹出窗 "),
      vue.createVNode(
        _component_uni_popup,
        {
          ref: "rateSourcePopup",
          "is-mask-click": false
        },
        {
          default: vue.withCtx(() => [
            vue.createElementVNode("view", { class: "rateSourcePopup" }, [
              vue.createElementVNode("view", { class: "header" }, [
                vue.createElementVNode("view"),
                vue.createElementVNode(
                  "view",
                  { class: "text" },
                  vue.toDisplayString($setup.isRated ? "已经评过分了" : "壁纸评分"),
                  1
                  /* TEXT */
                ),
                vue.createVNode(_component_uni_icons, {
                  onClick: $setup.onClickedRateSourceCloseBtn,
                  type: "closeempty",
                  size: "20",
                  color: "#999"
                })
              ]),
              vue.createElementVNode("view", { class: "rateBox" }, [
                vue.createVNode(_component_uni_rate, {
                  readonly: $setup.isRated,
                  allowHalf: "",
                  modelValue: $setup.userRate,
                  "onUpdate:modelValue": _cache[1] || (_cache[1] = ($event) => $setup.userRate = $event)
                }, null, 8, ["readonly", "modelValue"]),
                vue.createElementVNode(
                  "view",
                  { class: "text" },
                  vue.toDisplayString($setup.userRate) + "分",
                  1
                  /* TEXT */
                )
              ]),
              vue.createElementVNode("view", { class: "footer" }, [
                vue.createElementVNode("button", {
                  onClick: $setup.onClickedConfirmBtn,
                  disabled: !$setup.userRate || $setup.isRated,
                  size: "mini",
                  plain: ""
                }, "确认评分", 8, ["disabled"])
              ])
            ])
          ]),
          _: 1
          /* STABLE */
        },
        512
        /* NEED_PATCH */
      )
    ]);
  }
  const PagesPreviewPreview = /* @__PURE__ */ _export_sfc(_sfc_main$3, [["render", _sfc_render$2], ["__scopeId", "data-v-2dad6c07"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/pages/preview/preview.vue"]]);
  const en = {
    "uni-search-bar.cancel": "cancel",
    "uni-search-bar.placeholder": "Search enter content"
  };
  const zhHans = {
    "uni-search-bar.cancel": "取消",
    "uni-search-bar.placeholder": "请输入搜索内容"
  };
  const zhHant = {
    "uni-search-bar.cancel": "取消",
    "uni-search-bar.placeholder": "請輸入搜索內容"
  };
  const messages = {
    en,
    "zh-Hans": zhHans,
    "zh-Hant": zhHant
  };
  const {
    t
  } = initVueI18n(messages);
  const _sfc_main$2 = {
    name: "UniSearchBar",
    emits: ["input", "update:modelValue", "clear", "cancel", "confirm", "blur", "focus"],
    props: {
      placeholder: {
        type: String,
        default: ""
      },
      radius: {
        type: [Number, String],
        default: 5
      },
      clearButton: {
        type: String,
        default: "auto"
      },
      cancelButton: {
        type: String,
        default: "auto"
      },
      cancelText: {
        type: String,
        default: ""
      },
      bgColor: {
        type: String,
        default: "#F8F8F8"
      },
      textColor: {
        type: String,
        default: "#000000"
      },
      maxlength: {
        type: [Number, String],
        default: 100
      },
      value: {
        type: [Number, String],
        default: ""
      },
      modelValue: {
        type: [Number, String],
        default: ""
      },
      focus: {
        type: Boolean,
        default: false
      },
      readonly: {
        type: Boolean,
        default: false
      }
    },
    data() {
      return {
        show: false,
        showSync: false,
        searchVal: ""
      };
    },
    computed: {
      cancelTextI18n() {
        return this.cancelText || t("uni-search-bar.cancel");
      },
      placeholderText() {
        return this.placeholder || t("uni-search-bar.placeholder");
      }
    },
    watch: {
      modelValue: {
        immediate: true,
        handler(newVal) {
          this.searchVal = newVal;
          if (newVal) {
            this.show = true;
          }
        }
      },
      focus: {
        immediate: true,
        handler(newVal) {
          if (newVal) {
            if (this.readonly)
              return;
            this.show = true;
            this.$nextTick(() => {
              this.showSync = true;
            });
          }
        }
      },
      searchVal(newVal, oldVal) {
        this.$emit("input", newVal);
        this.$emit("update:modelValue", newVal);
      }
    },
    methods: {
      searchClick() {
        if (this.readonly)
          return;
        if (this.show) {
          return;
        }
        this.show = true;
        this.$nextTick(() => {
          this.showSync = true;
        });
      },
      clear() {
        this.searchVal = "";
        this.$nextTick(() => {
          this.$emit("clear", { value: "" });
        });
      },
      cancel() {
        if (this.readonly)
          return;
        this.$emit("cancel", {
          value: this.searchVal
        });
        this.searchVal = "";
        this.show = false;
        this.showSync = false;
        plus.key.hideSoftKeybord();
      },
      confirm() {
        plus.key.hideSoftKeybord();
        this.$emit("confirm", {
          value: this.searchVal
        });
      },
      blur() {
        plus.key.hideSoftKeybord();
        this.$emit("blur", {
          value: this.searchVal
        });
      },
      emitFocus(e) {
        this.$emit("focus", e.detail);
      }
    }
  };
  function _sfc_render$1(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    return vue.openBlock(), vue.createElementBlock("view", { class: "uni-searchbar" }, [
      vue.createElementVNode(
        "view",
        {
          style: vue.normalizeStyle({ borderRadius: $props.radius + "px", backgroundColor: $props.bgColor }),
          class: "uni-searchbar__box",
          onClick: _cache[5] || (_cache[5] = (...args) => $options.searchClick && $options.searchClick(...args))
        },
        [
          vue.createElementVNode("view", { class: "uni-searchbar__box-icon-search" }, [
            vue.renderSlot(_ctx.$slots, "searchIcon", {}, () => [
              vue.createVNode(_component_uni_icons, {
                color: "#c0c4cc",
                size: "18",
                type: "search"
              })
            ], true)
          ]),
          $data.show || $data.searchVal ? vue.withDirectives((vue.openBlock(), vue.createElementBlock("input", {
            key: 0,
            focus: $data.showSync,
            disabled: $props.readonly,
            placeholder: $options.placeholderText,
            maxlength: $props.maxlength,
            class: "uni-searchbar__box-search-input",
            "confirm-type": "search",
            type: "text",
            "onUpdate:modelValue": _cache[0] || (_cache[0] = ($event) => $data.searchVal = $event),
            style: vue.normalizeStyle({ color: $props.textColor }),
            onConfirm: _cache[1] || (_cache[1] = (...args) => $options.confirm && $options.confirm(...args)),
            onBlur: _cache[2] || (_cache[2] = (...args) => $options.blur && $options.blur(...args)),
            onFocus: _cache[3] || (_cache[3] = (...args) => $options.emitFocus && $options.emitFocus(...args))
          }, null, 44, ["focus", "disabled", "placeholder", "maxlength"])), [
            [vue.vModelText, $data.searchVal]
          ]) : (vue.openBlock(), vue.createElementBlock(
            "text",
            {
              key: 1,
              class: "uni-searchbar__text-placeholder"
            },
            vue.toDisplayString($props.placeholder),
            1
            /* TEXT */
          )),
          $data.show && ($props.clearButton === "always" || $props.clearButton === "auto" && $data.searchVal !== "") && !$props.readonly ? (vue.openBlock(), vue.createElementBlock("view", {
            key: 2,
            class: "uni-searchbar__box-icon-clear",
            onClick: _cache[4] || (_cache[4] = (...args) => $options.clear && $options.clear(...args))
          }, [
            vue.renderSlot(_ctx.$slots, "clearIcon", {}, () => [
              vue.createVNode(_component_uni_icons, {
                color: "#c0c4cc",
                size: "20",
                type: "clear"
              })
            ], true)
          ])) : vue.createCommentVNode("v-if", true)
        ],
        4
        /* STYLE */
      ),
      $props.cancelButton === "always" || $data.show && $props.cancelButton === "auto" ? (vue.openBlock(), vue.createElementBlock(
        "text",
        {
          key: 0,
          onClick: _cache[6] || (_cache[6] = (...args) => $options.cancel && $options.cancel(...args)),
          class: "uni-searchbar__cancel"
        },
        vue.toDisplayString($options.cancelTextI18n),
        1
        /* TEXT */
      )) : vue.createCommentVNode("v-if", true)
    ]);
  }
  const __easycom_0 = /* @__PURE__ */ _export_sfc(_sfc_main$2, [["render", _sfc_render$1], ["__scopeId", "data-v-f07ef577"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/uni_modules/uni-search-bar/components/uni-search-bar/uni-search-bar.vue"]]);
  const _sfc_main$1 = {
    __name: "search",
    setup(__props, { expose: __expose }) {
      __expose();
      const queryParams = vue.ref({
        pageNum: 1,
        pageSize: 12,
        keyword: ""
      });
      let historySearch = vue.ref(uni.getStorageSync("historySearch") || []);
      const recommendList = vue.ref(["美女", "帅哥", "宠物", "卡通"]);
      const noData = vue.ref(false);
      const noSearch = vue.ref(false);
      const classList = vue.ref([]);
      const onSearch = () => {
        if (!historySearch.value.includes(queryParams.value.keyword))
          historySearch.value.unshift(queryParams.value.keyword);
        historySearch.value = historySearch.value.slice(0, 10);
        uni.setStorageSync("historySearch", historySearch.value);
        classList.value = [];
        queryParams.value.pageNum = 1;
        queryParams.value.pageSize = 12;
        noData.value = false;
        noSearch.value = false;
        onSearchFunc();
      };
      const onClear = () => {
        classList.value = [];
        queryParams.value = {
          pageNum: 1,
          pageSize: 12,
          keyword: ""
        };
        noData.value = false;
        noSearch.value = false;
      };
      const clickTab = (value) => {
        queryParams.value.keyword = value;
        if (!historySearch.value.includes(queryParams.value.keyword))
          historySearch.value.push(queryParams.value.keyword);
        uni.setStorageSync("historySearch", historySearch.value);
        classList.value = [];
        queryParams.value.pageNum = 1;
        onSearchFunc();
      };
      const removeHistory = () => {
        uni.showModal({
          title: "是否清空历史搜索？",
          success: (res) => {
            if (res.confirm) {
              formatAppLog("log", "at pages/search/search.vue:140", "确认删除");
              uni.removeStorageSync("historySearch");
              historySearch.value = [];
            }
          }
        });
      };
      async function onSearchFunc() {
        let res = await apiSearchData(queryParams.value);
        classList.value = [...classList.value, ...res.data];
        uni.setStorageSync("classifyPicList", classList.value);
        if (res.data.length <= 0) {
          noData.value = true;
        } else {
          noData.value = false;
        }
        if (res.data.length <= 0 && classList.value.length == 0) {
          noSearch.value = true;
        } else {
          noSearch.value = false;
        }
      }
      onReachBottom(() => {
        formatAppLog("log", "at pages/search/search.vue:166", "noData:");
        formatAppLog("log", "at pages/search/search.vue:167", noData.value);
        if (noData.value)
          return;
        queryParams.value.pageNum++;
        onSearchFunc();
      });
      onUnload(() => {
        uni.removeStorageSync("classifyPicList");
      });
      const __returned__ = { queryParams, get historySearch() {
        return historySearch;
      }, set historySearch(v) {
        historySearch = v;
      }, recommendList, noData, noSearch, classList, onSearch, onClear, clickTab, removeHistory, onSearchFunc, ref: vue.ref, get onLoad() {
        return onLoad;
      }, get onUnload() {
        return onUnload;
      }, get onReachBottom() {
        return onReachBottom;
      }, get apiSearchData() {
        return apiSearchData;
      } };
      Object.defineProperty(__returned__, "__isScriptSetup", { enumerable: false, value: true });
      return __returned__;
    }
  };
  function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
    const _component_uni_search_bar = resolveEasycom(vue.resolveDynamicComponent("uni-search-bar"), __easycom_0);
    const _component_uni_icons = resolveEasycom(vue.resolveDynamicComponent("uni-icons"), __easycom_1$3);
    const _component_uni_load_more = resolveEasycom(vue.resolveDynamicComponent("uni-load-more"), __easycom_2$1);
    return vue.openBlock(), vue.createElementBlock("view", { class: "searchLayout" }, [
      vue.createElementVNode("view", { class: "search" }, [
        vue.createVNode(_component_uni_search_bar, {
          onConfirm: $setup.onSearch,
          onCancel: $setup.onClear,
          onClear: $setup.onClear,
          focus: "",
          placeholder: "搜索",
          modelValue: $setup.queryParams.keyword,
          "onUpdate:modelValue": _cache[0] || (_cache[0] = ($event) => $setup.queryParams.keyword = $event)
        }, null, 8, ["modelValue"])
      ]),
      !$setup.classList.length ? (vue.openBlock(), vue.createElementBlock("view", { key: 0 }, [
        $setup.historySearch.length ? (vue.openBlock(), vue.createElementBlock("view", {
          key: 0,
          class: "history"
        }, [
          vue.createElementVNode("view", { class: "topTitle" }, [
            vue.createElementVNode("view", { class: "text" }, "最近搜索"),
            vue.createElementVNode("view", {
              class: "icon",
              onClick: $setup.removeHistory
            }, [
              vue.createVNode(_component_uni_icons, {
                type: "trash",
                size: "25"
              })
            ])
          ]),
          vue.createElementVNode("view", { class: "tabs" }, [
            (vue.openBlock(true), vue.createElementBlock(
              vue.Fragment,
              null,
              vue.renderList($setup.historySearch, (tab) => {
                return vue.openBlock(), vue.createElementBlock("view", {
                  class: "tab",
                  key: tab,
                  onClick: ($event) => $setup.clickTab(tab)
                }, vue.toDisplayString(tab), 9, ["onClick"]);
              }),
              128
              /* KEYED_FRAGMENT */
            ))
          ])
        ])) : vue.createCommentVNode("v-if", true),
        vue.createElementVNode("view", { class: "recommend" }, [
          vue.createElementVNode("view", { class: "topTitle" }, [
            vue.createElementVNode("view", { class: "text" }, "热门搜索")
          ]),
          vue.createElementVNode("view", { class: "tabs" }, [
            (vue.openBlock(true), vue.createElementBlock(
              vue.Fragment,
              null,
              vue.renderList($setup.recommendList, (tab) => {
                return vue.openBlock(), vue.createElementBlock("view", {
                  class: "tab",
                  key: tab,
                  onClick: ($event) => $setup.clickTab(tab)
                }, vue.toDisplayString(tab), 9, ["onClick"]);
              }),
              128
              /* KEYED_FRAGMENT */
            ))
          ])
        ])
      ])) : vue.createCommentVNode("v-if", true),
      $setup.noSearch ? (vue.openBlock(), vue.createElementBlock("view", {
        key: 1,
        class: "noSearch"
      }, [
        vue.createCommentVNode(' <uv-empty mode="search" icon="http://cdn.uviewui.com/uview/empty/search.png"></uv-empty> '),
        vue.createTextVNode(" 未找到搜索内容 ")
      ])) : vue.createCommentVNode("v-if", true),
      vue.createElementVNode("view", null, [
        vue.createElementVNode("view", { class: "list" }, [
          (vue.openBlock(true), vue.createElementBlock(
            vue.Fragment,
            null,
            vue.renderList($setup.classList, (item) => {
              return vue.openBlock(), vue.createElementBlock("navigator", {
                url: `/pages/preview/preview?id=${item._id}`,
                class: "item",
                key: item._id
              }, [
                vue.createElementVNode("image", {
                  src: item.smallPicurl,
                  mode: "aspectFill"
                }, null, 8, ["src"])
              ], 8, ["url"]);
            }),
            128
            /* KEYED_FRAGMENT */
          ))
        ]),
        $setup.classList.length && !$setup.noSearch ? (vue.openBlock(), vue.createElementBlock("view", { key: 0 }, [
          vue.createVNode(_component_uni_load_more, {
            status: $setup.noData ? "noMore" : "loading"
          }, null, 8, ["status"])
        ])) : vue.createCommentVNode("v-if", true)
      ])
    ]);
  }
  const PagesSearchSearch = /* @__PURE__ */ _export_sfc(_sfc_main$1, [["render", _sfc_render], ["__scopeId", "data-v-c10c040c"], ["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/pages/search/search.vue"]]);
  __definePage("pages/index/index", PagesIndexIndex);
  __definePage("pages/classify/classify", PagesClassifyClassify);
  __definePage("pages/user/user", PagesUserUser);
  __definePage("pages/classifyList/classifyList", PagesClassifyListClassifyList);
  __definePage("pages/preview/preview", PagesPreviewPreview);
  __definePage("pages/search/search", PagesSearchSearch);
  const _sfc_main = {
    onLaunch: function() {
      formatAppLog("log", "at App.vue:4", "App Launch");
    },
    onShow: function() {
      formatAppLog("log", "at App.vue:7", "App Show");
    },
    onHide: function() {
      formatAppLog("log", "at App.vue:10", "App Hide");
    }
  };
  const App = /* @__PURE__ */ _export_sfc(_sfc_main, [["__file", "C:/Users/zmq/Documents/GitHub/personalStudyNotes/uniapp/xxmWallpaper/App.vue"]]);
  function createApp() {
    const app = vue.createVueApp(App);
    return {
      app
    };
  }
  const { app: __app__, Vuex: __Vuex__, Pinia: __Pinia__ } = createApp();
  uni.Vuex = __Vuex__;
  uni.Pinia = __Pinia__;
  __app__.provide("__globalStyles", __uniConfig.styles);
  __app__._component.mpType = "app";
  __app__._component.render = () => {
  };
  __app__.mount("#app");
})(Vue);
