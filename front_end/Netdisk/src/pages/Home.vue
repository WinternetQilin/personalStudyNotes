<template>
  <div class="container">
    <div class="leftContain">
      <NavBar />
    </div>
    <div class="rightContain">
      <router-view />
    </div>
  </div>
</template>

<script lang="ts">
export default { name: "Home" };
</script>
<script setup lang="ts">
import NavBar from "@/layouts/NavigationBar.vue";
import { useRouter } from "vue-router";

const $router = useRouter();
$router.push("/home/file");
</script>

<style scoped lang="scss">
.container {
  display: flex;
  flex-direction: row;
  height: 100vh;

  .leftContain {
    width: 80px;
    height: 100%;
  }
  .rightContain {
    width: calc(100% - 80px);
    height: 100%;
    background-color: #bfa;
  }
}
</style>
