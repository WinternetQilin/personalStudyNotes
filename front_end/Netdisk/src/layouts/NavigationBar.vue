<template>
  <div class="container">
    <ul class="nav-list">
      <li :class="{ active: selectedIdx == 1 }" @click="selected(1),onFile()">
        <img src="../assets/文件夹.png" alt="" />
        <p>文件</p>
      </li>
      <li :class="{ active: selectedIdx == 2 }" @click="selected(2),onDownload()">
        <img src="../assets/下载.png" alt="" />
        <p>下载</p>
      </li>
      <li @click="onQuit()">
        <img src="../assets/下载.png" alt="" />
        <p>退出</p>
      </li>
    </ul>
  </div>
</template>

<script lang="ts">export default { name: "NavigationBar" };</script>
<script setup lang="ts">
import { ref } from "vue";
import { useRouter } from "vue-router";
import request from "@/Utils/request";

let selectedIdx = ref(1);

const $router=useRouter();
const onFile = () => {
    $router.push("/home/file");
};
const onDownload = () => {
    $router.push("/home/download");
};
const onQuit = () => {
  request.get("/user/logout")
  .then((res) => {
          console.log(res);
          let data = res.data;
          if(data.code == 2000)
          {
            $router.push("/login");
          }
          else{
            alert(data.msg);
          }
        });
    
};

function selected(idx: number) {
  selectedIdx.value = idx;
}
</script>

<style scoped lang="scss">
.container {
  width: 100%;
  height: 100%;
  background-color: rgb(187, 204, 255);
  border-right: 1px solid rgba(52, 74, 186, 0.5);
  .nav-list {
    width: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    li {
      width: 80%;
      text-align: center;
      margin-top: 20px;
      padding: 10px 0;
      border-radius: 10px;
      cursor: pointer;

      p {
        font-size: 12px;
      }
    }
    .active {
      background-color: rgb(227, 227, 229);
    }
  }
}
</style>
