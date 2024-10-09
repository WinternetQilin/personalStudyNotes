<template>
  <div class="app">
    <!-- <h1>vue路由</h1> -->
    <div style="display: flex; height: 100%">
      <!-- 导航区 -->
      <div class="nav">
        <ul>
          <li><RouterLink to="/netDisk" active-class="clickedAct">我的网盘</RouterLink></li>
          <li><RouterLink to="/download" active-class="clickedAct">下载列表</RouterLink></li>
          <li><RouterLink to="/profile" active-class="clickedAct">个人资料</RouterLink></li>
        </ul>
      </div>
      <!-- 展示区 -->
      <div class="main-content">
        <RouterView />
      </div>
    </div>
  </div>
</template>

<script lang="ts">export default {name: 'App'}</script>

<script lang="ts" setup>
import { RouterView,RouterLink } from 'vue-router';

</script>

<style scoped>
.app {
  background-color: rgb(187, 204, 255);
  height: 800px;
}
h1 {
  text-align: center;
}
.nav {
  background-color: rgb(10, 19, 88);
  width: 100px;
  height: calc(100% - 16px);
  margin-top: 0px;
  display: inline-block;
  border-radius: 5px;
  box-shadow: 2px 0 0 0 rgb(121, 116, 116);
}
.nav li {
  text-align: center;
  /* background-color: #fff; */
  padding: 5px;
  margin-top: 5px
}
.nav a {
    font-size: 18px;
    display: inline-block;
  color: #fff;
  width: 100%;
  line-height: 30px;
  /* background-color: #bfa; */
  text-decoration: none;
}
.main-content {
  display: inline-block;
  width: calc(100% - 100px);
  height: 100%;
  /* background-color: #bfa; */
  margin-left: 3px;
}
.clickedAct{
    background-color: rgb(52,74,186);
    border-radius: 5px;
}
</style>
