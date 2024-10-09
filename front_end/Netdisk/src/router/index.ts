import { createRouter, createWebHashHistory } from "vue-router";

const router = createRouter({
  history: createWebHashHistory(),
  routes: [
    {
      path: "/",
      redirect: "/login",
    },
    {
      path: "/login",
      component: () => import("../pages/Login.vue"),
    },
    {
      path: "/home",
      component: () => import("../pages/Home.vue"),
      children:[
        {
          path:"file",
          component: () => import("../pages/File.vue"),
        },
        {
          path:"download",
          component: () => import("../pages/Download.vue"),
        },
      ],
    },
  ],
  scrollBehavior() {return {left: 0,top: 0}},
});

export default router;
