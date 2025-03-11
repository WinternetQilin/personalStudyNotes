//定义关于system的store
import {
	defineStore
} from 'pinia'

let systemInfo = uni.getSystemInfoSync();
// 获取状态栏高度
const getStatusBarHeight = () => systemInfo.statusBarHeight || 20;
// 获取标题栏高度
const getTitleBarHeight = () => {
	// #ifdef MP-WEIXIN
	// 获取胶囊按钮位置信息
	let menuBtnInfo = uni.getMenuButtonBoundingClientRect();
	// console.log(menuBtnInfo)
	return (menuBtnInfo.top - getStatusBarHeight()) * 2 + menuBtnInfo.height
	// #endif

	return 40
}
/*defineStore 是需要传参数的，其中第一个参数是id，就是一个唯一的值，
简单点说就可以理解成是一个命名空间.
第二个参数就是一个对象，里面有三个模块需要处理，第一个是 state，
第二个是 getters，第三个是 actions。
*/
const useSystem = defineStore("system", {
	state: () => ({
		foldState: false,
	}),

	getters: {
		// 顶部状态栏高度
		statusBarHeight() {
			return getStatusBarHeight()
		},
		// 胶囊按钮高度（包含边距）
		titleBarHeight() {
			return getTitleBarHeight()
		},
		// 店铺信息栏（body）高度
		bodyBarHeight(state) {
			return state.foldState ? this.titleBarHeight : 100
		},
		// 菜单(免费配送)上边整体的高度
		totalHeight(state) {
			// 含100的部分：顶部状态栏高度 + 胶囊菜单栏高度 + 店铺信息栏（body） + 10px（被下面模块覆盖的部分）
			return state.foldState ? this.statusBarHeight + 10 + this.titleBarHeight + 10 : this
				.statusBarHeight +
				this.titleBarHeight + 100 + 10
		}
	},
	actions: {
		// 设置折叠状态
		setFoldState(value) {
			this.foldState = value
		},
	}
})

//暴露这个useSystem模块
export default useSystem