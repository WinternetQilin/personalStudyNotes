<template>
  <div class="container">
    <div class="loginContainer">
      <!-- 顶部手机号/用户名登录按钮 -->
      <div class="loginTop">
        <div
          class="left"
          @click="selectFlag = 1"
          :class="{ active: selectFlag === 1 }"
        >
          手机号
        </div>
        <div
          class="right"
          @click="selectFlag = 2"
          :class="{ active: selectFlag === 2 }"
        >
          用户名
        </div>
      </div>

      <!-- 下面 手机号登录信息 -->
      <div class="loginBottom" v-if="selectFlag === 1">
        <el-form :model="loginFormPhone" :rules="rules">
          <!-- 手机号输入框 -->
          <el-form-item prop="inPhone">
            <el-input
              v-model="loginFormPhone.inPhone"
              style="width: 240px"
              placeholder="请输入手机号"
              clearable
            />
          </el-form-item>
          <!-- 密码输入框 -->
          <el-form-item prop="inPaswd">
            <el-input
              v-model="loginFormPhone.inPaswd"
              style="width: 240px"
              placeholder="请输入密码"
              clearable
              show-password
            />
          </el-form-item>
        </el-form>

        <div class="btns">
          <el-button @click="onLogin" type="primary" style="width: 120px"
            >登录</el-button
          >
          <el-button
            @click="register_dialogFormVisible = true"
            type="primary"
            plain
            style="width: 120px"
            >注册</el-button
          >
        </div>
      </div>

      <!-- 用户名登录信息 -->
      <div class="loginBottom" v-else>
        <el-form :model="loginFormUsername" :rules="rules">
          <!-- 用户名输入框 -->
          <el-form-item prop="inUsername">
            <el-input
              v-model="loginFormUsername.inUsername"
              style="width: 240px"
              placeholder="请输入用户名"
              clearable
            />
          </el-form-item>
          <!-- 密码输入框 -->
          <el-form-item prop="inPaswd">
            <el-input
              v-model="loginFormUsername.inPaswd"
              style="width: 240px"
              placeholder="请输入密码"
              clearable
              show-password
            />
          </el-form-item>
        </el-form>

        <div class="btns">
          <el-button @click="onLogin" type="primary" style="width: 120px"
            >登录</el-button
          >
          <el-button
            @click="register_dialogFormVisible = true"
            type="primary"
            plain
            style="width: 120px"
            >注册</el-button
          >
        </div>
      </div>
    </div>

    <!-- 注册提示框 -->
    <el-dialog
      v-model="register_dialogFormVisible"
      title="欢迎注册"
      width="35%"
    >
      <!-- 输入内容表单 -->
      <el-form label-position="top" :model="registerForm" :rules="rules">
        <el-form-item label="用户名" prop="inUsername">
          <el-input v-model="registerForm.inUsername" clearable />
        </el-form-item>
        <el-form-item label="手机号" prop="inPhone">
          <el-input v-model="registerForm.inPhone" clearable />
        </el-form-item>
        <el-form-item label="密码" prop="inPaswd">
          <el-input v-model="registerForm.inPaswd" clearable show-password />
        </el-form-item>
      </el-form>
      <!-- 确认按钮 -->
      <template #footer>
        <el-button type="primary" @click="onRegister">确认</el-button>
      </template>
    </el-dialog>
  </div>
</template>

<script lang="ts">
export default { name: "Login" };
</script>
<script setup lang="ts">
import { ref } from "vue";
import { useRouter } from "vue-router";
import request from "@/Utils/request";
import { triggerEvent } from "element-plus/es/utils/index.mjs";
const $router = useRouter();

//控制注册对话框的显示与隐藏
let register_dialogFormVisible = ref(false);
//注册输入表单数据变量
let registerForm = ref({
  inUsername: "",
  inPhone: "",
  inPaswd: "",
});
//手机号登录输入表单数据变量
let loginFormPhone = ref({
  inPhone: "",
  inPaswd: "",
});
//用户名登录输入表单数据变量
let loginFormUsername = ref({
  inUsername: "",
  inPaswd: "",
});
//切换手机号登录和用户名登录界面
let selectFlag = ref(1);

const checkPassword = /^\S{6,16}$/;
const checkTelephone = /^1[3-9]\d{9}$/;
const checkUname = /^[a-zA-Z][a-zA-Z0-9_]{0,14}$/;

const checkPhone = (rule: any, value: any, callback: any) => {
  if (!checkTelephone.test(value)) {
    console.log("checkPhone:手机号格式不正确");
    callback(new Error("手机号格式不正确"));
  } else {
    callback();
  }
};
const checkPwd = (rule: any, value: any, callback: any) => {
  if (!checkPassword.test(value)) {
    console.log("checkPwd:密码格式不正确");

    callback(new Error("密码格式不正确"));
  } else {
    callback();
  }
};
const checkUsername = (rule: any, value: any, callback: any) => {
  if (!checkUname.test(value)) {
    console.log("checkUsername:用户名格式不正确");
    callback(new Error("仅含数字、字母和下划线且15个字符以内"));
  } else {
    callback();
  }
};

// 定义校验规则
const rules = {
  inPhone: [{ trigger: "blur", validator: checkPhone }],
  inPaswd: [{ trigger: "blur", validator: checkPwd }],
  inUsername: [{ trigger: "blur", validator: checkUsername }],
};

// 点击登录按钮的事件处理
const onLogin = () => {
  // $router.push("/home");
  if (selectFlag.value == 1) {
    //手机号登录
    //13131086711
    //123456
    if (
      checkPassword.test(loginFormPhone.value.inPaswd) &&
      checkTelephone.test(loginFormPhone.value.inPhone)
    ) {
      request
        .post(
          "/user/loginByPhoneNumber",
          {
            phoneNumber: loginFormPhone.value.inPhone,
            password: loginFormPhone.value.inPaswd,
          },
          { headers: { "Content-Type": "application/json" } }
        )
        .then((res) => {
          console.log(res);
          let data = res.data;
          if (data.code == 2000) {
            $router.push("/home");
          } else {
            alert(data.msg);
          }
        });
    } else {
      alert("手机号或密码格式不正确");
    }
  } else {
    //用户名登录
    //liu
    //123456
    if (
      checkPassword.test(loginFormUsername.value.inPaswd) &&
      checkUname.test(loginFormUsername.value.inUsername)
    ) {
      request
        .post(
          "/user/loginByUserName",
          {
            userName: loginFormUsername.value.inUsername,
            password: loginFormUsername.value.inPaswd,
          },
          { headers: { "Content-Type": "application/json" } }
        )
        .then((res) => {
          console.log(res);
          let data = res.data;
          if (data.code == 2000) {
            $router.push("/home");
          } else {
            alert(data.msg);
          }
        });
    } else {
      alert("用户名或密码格式不正确");
    }
  }

  // $router.push("/home");
};
//点击注册按钮事件处理
const onRegister = () => {
  // console.log(registerForm.value);
  if (
    checkUname.test(registerForm.value.inUsername) &&
    checkTelephone.test(registerForm.value.inPhone) &&
    checkPassword.test(registerForm.value.inPaswd)
  ) {
    request
      .post("/user/register", {
        usname: registerForm.value.inUsername,
        phoneNumber: registerForm.value.inPhone,
        password: registerForm.value.inPaswd,
      })
      .then((res) => {
        console.log(res);
        let data = res.data;
        if (data.code == 2000) {
          alert("注册成功");
          register_dialogFormVisible.value = false;
          registerForm.value.inUsername = "";
          registerForm.value.inPhone = "";
          registerForm.value.inPaswd = "";
        } else {
          alert(data.msg);
        }
      });
  } else {
    alert("您的输入有误");
  }
};
</script>

<style scoped lang="scss">
.container {
  width: 100vw; /* vw 表示视口宽度的百分比 */
  height: 100vh; /* vh 表示视口高度的百分比 */
  background-color: rgb(187, 204, 255);
  display: flex;
  justify-content: space-around;
  align-items: center;
  .loginContainer {
    width: 350px;
    height: 300px;
    background-color: rgb(52, 74, 186);
    border-radius: 5px;
    box-shadow: 0 0 15px rgba(0, 0, 0, 0.5);
    .loginTop {
      display: flex;
      justify-content: space-around;
      margin: 10px 0;
      div {
        cursor: pointer;
        color: #fff;
        text-align: center;
        width: 50px;
      }
      .active {
        border-bottom: rgb(64, 158, 255) 1px solid;
        padding-bottom: 5px;
        transition: border-bottom 0.3s ease-in-out;
      }
    }

    .loginBottom {
      // background-color: aquamarine;
      display: flex;
      flex-direction: column;
      height: calc(100% - 40px);
      justify-content: space-evenly;
      align-items: center;
      .btns {
        display: flex;
        justify-content: space-evenly;
      }
    }
  }
}
</style>
