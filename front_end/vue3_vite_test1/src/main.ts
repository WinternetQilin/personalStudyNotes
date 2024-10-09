//引入createApp用于创建应用
import {createApp} from 'vue';
//引入App根组件
import App from './App.vue';
//引入全局默认样式清除插件
import 'reset-css'
//引入路由器
import router from './router';

createApp(App).use(router).mount('#app');