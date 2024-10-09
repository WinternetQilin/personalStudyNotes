<template>
  <div class="fileContainer">
    <!-- 头部 -->
    <div class="header">
      <div class="searchInput">
        <el-input class="searchInput-inner" placeholder="搜索云盘内文件" />
      </div>
      <div class="infoCard"></div>
    </div>
    <!-- 路径显示 -->
    <div class="path">
      <div>全部文件</div>
    </div>
    <!-- 文件列表 -->
    <div class="fileList">
      <el-table
        ref="multipleTableRef"
        :data="fileTableData"
        style="width: 100%"
        max-height="calc(100vh - 40px - 40px - 40px - 20px)"
      >
        <el-table-column type="selection" width="50" />
        <el-table-column property="name" label="文件名" width="700" />
        <el-table-column property="changeDate" label="修改时间" width="200" />
        <el-table-column property="fileSize" label="大小" width="200" />
      </el-table>
    </div>
  </div>
</template>

<script lang="ts">
export default { name: "File" };
</script>
<script setup lang="ts">
import { ref } from "vue";

let fileTableData = ref([
  {
    id: 1,
    name: "文件A",
    changeDate: "2021-01-01",
    fileSize: "1.2 MB",
  },
  {
    id: 2,
    name: "文件B",
    changeDate: "2021-01-01",
    fileSize: "2.2 MB",
  },
  {
    id: 3,
    name: "文件C",
    changeDate: "2021-01-01",
    fileSize: "3.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
  {
    id: 4,
    name: "文件D",
    changeDate: "2021-01-01",
    fileSize: "4.2 MB",
  },
]);
</script>

<style scoped lang="scss">
.fileContainer {
  padding-left: 60px;
  padding-right: 60px;

  .header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    background-color: aqua;
    height: 60px;
    width: 100%;

    .searchInput {
      background-color: bisque;
      .searchInput-inner {
        width: 278px;
        height: 40px;
      }
    }

    .infoCard {
      width: 276px;
      height: 40px;
      background-color: aquamarine;
    }
  }

  .path {
    width: 100%;
    line-height: 40px;
    font-size: 18px;
    background-color: blueviolet;
  }

  .fileList {
    width: 100%;
    background-color: brown;
  }
}
</style>
