<template>
  <div class="region">
    <div class="left">地区:</div>
    <ul class="right">
      <li :class="{active:activeFlag==''}" @click="changeRegion('')">全部</li>
      <li v-for="item in regionArr" :key="item.value" @click="changeRegion(item.value)" :class="{active:activeFlag==item.value}">{{ item.name }}</li>
    </ul>
  </div>
</template>

<script lang="ts">export default {name:"Region"}</script>
<script setup lang="ts">
import { reqHospitalLevelRegion } from "@/api/home/index";
import { ref, onMounted } from "vue";

let regionArr=ref([]);
//控制医院点击高亮
let activeFlag=ref<string>('');

function changeRegion(region:string){
  activeFlag.value=region
}

onMounted(() => {
  // getRegion()
});
const getRegion = async() => {
  let res:any = await reqHospitalLevelRegion("Beijing");
  if(res.code==200)
  {
    regionArr.value=res.data;
  }
};
</script>

<style scoped lang="scss">
.region {
  
  width: 100%;
  color: gray;
  display: flex;
  .left {
    margin-top: 10px;
    width: 44px;
  }
  .right {
    display: flex;
    flex-wrap: wrap;
    li {
        margin-top: 10px;
      margin-left: 20px;
      &.active {
        color: rgb(79, 160, 228);
      }
    }
    li:hover {
      color: rgb(79, 160, 228);
      cursor: pointer;
    }
  }
}
</style>
