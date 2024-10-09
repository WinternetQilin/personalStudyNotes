import { createApp } from 'vue'
import '@/style/reset.scss'
import App from './App.vue'
import HospitalTop from '@/components/hosipital_top/index.vue'
import HospitalBottom from '@/components/hospital_bottom/index.vue'
import router from './router'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import zhCn from 'element-plus/es/locale/lang/zh-cn'

const app = createApp(App)
app.component('HospitalTop', HospitalTop)
app.component('HospitalBottom', HospitalBottom)
app.use(router)
app.use(ElementPlus, {locale: zhCn,})
app.mount('#app')
