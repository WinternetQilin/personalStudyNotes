//创建一个路由器，并暴露出去

import { createRouter, createWebHashHistory } from "vue-router";
import netDisk from "../page/netDisk.vue";
import download from "../page/download.vue";
import profile from "../page/profile.vue";

//创建路由器
const router = createRouter({
  //路由模式
  history: createWebHashHistory(),
  //路由规则
  routes: [
    {
      path: "/",
      redirect: "/netDisk",
    },
    {
      path: "/netDisk",
      component: () => netDisk,
    },
    {
      path: "/download",
      component: () => download,
    },
    {
      path: "/profile",
      component: () => profile,
    },
  ],
});
export default router;
