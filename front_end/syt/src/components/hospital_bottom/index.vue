<template>
  <div class="bottom">
    <div class="container">
      <div class="left">
        <p>京ICP备 13018369号 电话挂号:010-56253825</p>
      </div>
      <div class="right">
        <a href="#">联系我们</a>
        <a href="#">合作伙伴</a>
        <a href="#">用户协议</a>
        <a href="#">隐私协议</a>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts"></script>

<style scoped lang="scss">
.bottom {
  width: 100%;
  height: 50px;
  background-color: #f0f2f5;
  color: gray;
  font-size: 14px;
  display: flex;
  justify-content: center;
  align-items: center;
  .container{
    width: 1200px;
    height: 100%;
    // background-color: aquamarine;
    display: flex;
    align-items: center;
    justify-content: space-between;
    .right{
      display: flex;
      a{
        margin-left: 5px;
        color: gray;
      }
      a:hover{
        color: rgb(79,160,228);
      }
    }
  }
}
</style>
