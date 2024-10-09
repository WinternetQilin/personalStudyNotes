<template>
  <div class="search">
    <el-autocomplete
      :trigger-on-focus="false"
      clearable
      placeholder="请输入医院名称"
    />
    <el-button type="primary" :icon="Search">搜索</el-button>
  </div>
</template>

<script setup lang="ts">
import {Search} from "@element-plus/icons-vue"
</script>

<style scoped lang="scss">
.search {
  display: flex;
  width: 100%;
  height: 50px;
  align-items: center;
  justify-content: center;
  margin-top: 20px;
  margin-bottom: 20px;

  ::v-deep(.el-autocomplete){
    width: 600px;
    margin-right: 10px;
  }
}
</style>
