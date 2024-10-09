<template>
  <div class="top">
    <div class="content">
      <div class="left">
        <img src="@/assets/images/logo.png" alt="logo" />
        <p>尚医通 预约挂号统一平台</p>
      </div>
      <div class="right">
        <a href="#" class="help">帮助中心</a>
        <a href="#" class="login">登录/注册</a>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts"></script>

<style scoped lang="scss">
.top {
  width: 100%;
  height: 70px;
  background-color: #fff;
  display: flex;
  justify-content: center;
  position: fixed;
  z-index: 999;
  margin-top: -10px;
  box-shadow:0 3px 0 0 rgba(226, 226, 226,.5);

  .content {
    width: 1200px;
    height: 100%;
    display: flex;
    justify-content: space-between;
    align-items: center;
    // background-color: red;
    .left {
      display: flex;
      justify-content: center;
      align-items: center;
      img {
        width: 50px;
        height: 50px;
        margin-right: 10px;
      }
      p {
        font-size: 22px;
        color: #55a6fe;
      }
    }
    .right {
      font-size: 14px;
      a{
        color: gray;
      }
      .help {
        margin-right: 10px;
      }
    }
  }
}
</style>
