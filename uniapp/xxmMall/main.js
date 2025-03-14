import App from './App'
import uvUI from '@/uni_modules/uv-ui-tools'

// #ifndef VUE3
import Vue from 'vue'
import './uni.promisify.adaptor'
Vue.config.productionTip = false
App.mpType = 'app'
const app = new Vue({
	...App
})
app.$mount()
// #endif

// #ifdef VUE3
import {
	createSSRApp
} from 'vue'
// 引入Pinia
import pinia from './store/index.js'

export function createApp() {
	const app = createSSRApp(App)
	app.use(pinia)
	app.use(uvUI)
	return {
		app
	}
}
// #endif