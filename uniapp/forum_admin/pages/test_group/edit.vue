<template>
  <view class="uni-container">
    <uni-forms ref="form" :model="formData" validateTrigger="bind">
      <uni-forms-item name="appid" label="AppID" required>
        <uni-easyinput :disabled="true" placeholder="应用的AppID" v-model="formData.appid"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="name" label="应用名称" required>
        <uni-easyinput :disabled="true" placeholder="应用名称" v-model="formData.name"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="description" label="应用描述">
        <textarea placeholder="应用描述" @input="binddata('description', $event.detail.value)" class="uni-textarea-border" v-model="formData.description"></textarea>
      </uni-forms-item>
      <uni-forms-item name="creator_uid" label="">
        <uni-easyinput placeholder="创建者的user_id，创建者必然是用户，不随应用转让而改变" v-model="formData.creator_uid"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="owner_type" label="">
        <uni-easyinput placeholder="应用当前归属者类型，1：个人，2：企业" type="number" v-model="formData.owner_type"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="owner_id" label="">
        <uni-easyinput placeholder="应用当前归属者的id，user_id or enterprise_id" v-model="formData.owner_id"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="managers" label="">
        <uni-data-checkbox :multiple="true" v-model="formData.managers"></uni-data-checkbox>
      </uni-forms-item>
      <uni-forms-item name="members" label="">
        <uni-data-checkbox :multiple="true" v-model="formData.members"></uni-data-checkbox>
      </uni-forms-item>
      <uni-forms-item name="icon_url" label="应用图标">
        <uni-easyinput placeholder="应用图标链接" v-model="formData.icon_url" trim="both"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="introduction" label="应用简介">
        <uni-easyinput disabled="true" placeholder="应用简介" v-model="formData.introduction" trim="both"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="screenshot" label="应用截图">
        <uni-data-checkbox :multiple="true" v-model="formData.screenshot"></uni-data-checkbox>
      </uni-forms-item>
      <uni-forms-item name="store_list" label="应用市场">
        <uni-data-checkbox :multiple="true" v-model="formData.store_list"></uni-data-checkbox>
      </uni-forms-item>
      <uni-forms-item name="remark" label="备注">
        <textarea placeholder="备注" @input="binddata('remark', $event.detail.value)" class="uni-textarea-border" v-model="formData.remark"></textarea>
      </uni-forms-item>
      <view class="uni-button-group">
        <button type="primary" class="uni-button" style="width: 100px;" @click="submit">提交</button>
        <navigator open-type="navigateBack" style="margin-left: 15px;">
          <button class="uni-button" style="width: 100px;">返回</button>
        </navigator>
      </view>
    </uni-forms>
  </view>
</template>

<script>
  import { validator } from '../../js_sdk/validator/test_group.js';

  const db = uniCloud.database();
  const dbCmd = db.command;
  const dbCollectionName = 'test_group';

  function getValidator(fields) {
    let result = {}
    for (let key in validator) {
      if (fields.includes(key)) {
        result[key] = validator[key]
      }
    }
    return result
  }

  

  export default {
    data() {
      let formData = {
        "appid": "",
        "name": "",
        "description": "",
        "creator_uid": "",
        "owner_type": null,
        "owner_id": "",
        "managers": [],
        "members": [],
        "icon_url": "",
        "introduction": "",
        "screenshot": [],
        "store_list": [],
        "remark": ""
      }
      return {
        formData,
        formOptions: {},
        rules: {
          ...getValidator(Object.keys(formData))
        }
      }
    },
    onLoad(e) {
      if (e.id) {
        const id = e.id
        this.formDataId = id
        this.getDetail(id)
      }
    },
    onReady() {
      this.$refs.form.setRules(this.rules)
    },
    methods: {
      
      /**
       * 验证表单并提交
       */
      submit() {
        uni.showLoading({
          mask: true
        })
        this.$refs.form.validate().then((res) => {
          return this.submitForm(res)
        }).catch(() => {
        }).finally(() => {
          uni.hideLoading()
        })
      },

      /**
       * 提交表单
       */
      submitForm(value) {
        // 使用 clientDB 提交数据
        return db.collection(dbCollectionName).doc(this.formDataId).update(value).then((res) => {
          uni.showToast({
            title: '修改成功'
          })
          this.getOpenerEventChannel().emit('refreshData')
          setTimeout(() => uni.navigateBack(), 500)
        }).catch((err) => {
          uni.showModal({
            content: err.message || '请求服务失败',
            showCancel: false
          })
        })
      },

      /**
       * 获取表单数据
       * @param {Object} id
       */
      getDetail(id) {
        uni.showLoading({
          mask: true
        })
        db.collection(dbCollectionName).doc(id).field("appid,name,description,creator_uid,owner_type,owner_id,managers,members,icon_url,introduction,screenshot,store_list,remark").get().then((res) => {
          const data = res.result.data[0]
          if (data) {
            this.formData = data
            
          }
        }).catch((err) => {
          uni.showModal({
            content: err.message || '请求服务失败',
            showCancel: false
          })
        }).finally(() => {
          uni.hideLoading()
        })
      }
    }
  }
</script>
