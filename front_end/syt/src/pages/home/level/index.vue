<template>
  <div class="level">
    <div>医院</div>
    <div class="hospitalLevel">
      <div class="left">等级:</div>
      <ul class="right">
        <li :class="{active:activeFlag==''}" @click="changeLevel('')">全部</li>
        <li v-for="level in levelArr" :key="level.value" @click="changeLevel(level.value)" :class="{active:activeFlag==level.value}">{{ level.name }}</li>
      </ul>
    </div>
  </div>
</template>

<script lang="ts">export default {name:"Level"}</script>

<script setup lang="ts">
import { reqHospitalLevelRegion } from "@/api/home/index";
import { ref, onMounted } from "vue";

let levelArr=ref([]);
//控制医院点击高亮
let activeFlag=ref<string>('');

function changeLevel(level:string){
  activeFlag.value=level
}

onMounted(() => {
  // getLevel()
});
const getLevel = async() => {
  let res:any = await reqHospitalLevelRegion("hosType");
  if(res.code==200)
  {
    levelArr.value=res.data;
  }
};
</script>

<style scoped lang="scss">
.level {
  color: gray;
  .hospitalLevel {
    display: flex;
    margin-top: 10px;
    .right {
      display: flex;
      li {
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
}
</style>
