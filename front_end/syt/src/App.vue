<template>
  <div class="container">
    <!-- 顶部组件 -->
    <HospitalTop/>
    <!-- 展示路由组件区域 -->
    <div class="content">
      <routerView/>
    </div>
    <HospitalBottom/>
  </div>
</template>

<script setup lang="ts">

</script>

<style scoped lang="scss">
.container{
  display: flex;
  flex-direction: column;
  align-items: center;
  .content{
    margin-top: 70px;
    width: 1200px;
    min-height: 500px;
    background-color: #bfa;
  }

}

</style>
