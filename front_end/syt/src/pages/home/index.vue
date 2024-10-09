<template>
  <div>
    <!-- 上面 轮播图 -->
    <Carousel />
    <!-- 中间 首页搜索表单的搜索框 -->
    <Search />
    <!-- 下面 展示医院的网格 -->
    <el-row :gutter="20">
      <el-col :span="20">
        <!-- 医院等级选择 -->
        <Level />
        <!-- 医院地区选择 -->
        <Region />
        <!-- 医院卡片展示 -->
        <div class="cardContainer">
          <Card class="card" v-for="item in hospitalCardInfo"  :key="item.id" :hospitalInfo="item" />
        </div>
        <el-pagination class="pagination"
          v-model:current-page="curPage"
          v-model:page-size="pageSize"
          :page-sizes="[10, 20, 30, 40]"
          :background="true"
          layout=" prev, pager, next, sizes,->,total"
          :total="total"
          @current-change="getHospitalCardInfo"
          @size-change="getHospitalCardInfo"
        />
      </el-col>
      <el-col :span="4">111</el-col>
    </el-row>
  </div>
</template>

<script setup lang="ts">
import Carousel from "./carousel/index.vue";
import Search from "./search/index.vue";
import Level from "./level/index.vue";
import Region from "./region/index.vue";
import Card from "./card/index.vue";
import { onMounted,ref } from "vue";
import { reqHospital } from "@/api/home/index";
import { Content } from "@/api/home/type";

//分页器
let curPage = ref<number>(1);
let pageSize = ref<number>(10);
//存储已有的医院卡片数据
let hospitalCardInfo = ref<Content>([]);
//存储医院总数
let total = ref<number>(0);

onMounted(() => {
  //getHospitalCardInfo();
});

//获取分页里的医院数据
 const getHospitalCardInfo=async()=> {
  
  let res:any = await reqHospital(curPage.value,pageSize.value);
  //console.log(res);
  if(res.code == 200)
  {
    hospitalCardInfo.value = res.data.content
    total.value=res.data.totalElements
  }
}





</script>

<style scoped lang="scss">
.cardContainer {
  width: 100%;
  margin-top: 20px;
  display: flex;
  flex-wrap: wrap;
  justify-content: space-between;
  .card {
    width: 48%;
    margin: 10px 0;
  }
}
.pagination{
  width: 100%;
}
</style>
