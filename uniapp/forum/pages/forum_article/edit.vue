<template>
  <view class="uni-container">
    <uni-forms ref="form" :model="formData" validate-trigger="submit" err-show-type="toast">
      <uni-forms-item name="user_id" label="" required>
        <uni-easyinput placeholder="文章作者ID， 参考`uni-id-users` 表" v-model="formData.user_id"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="title" label="标题" required>
        <uni-easyinput placeholder="标题" v-model="formData.title" trim="both"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="description" label="文章摘要">
        <uni-easyinput placeholder="文章摘要" v-model="formData.description" trim="both"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="province" label="发布省份">
        <uni-easyinput placeholder="发布省份" v-model="formData.province" trim="both"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="content" label="文章内容">
        <uni-easyinput placeholder="文章内容" v-model="formData.content" trim="right"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="view_count" label="阅读数量">
        <uni-easyinput placeholder="阅读数量" type="number" v-model="formData.view_count"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="like_count" label="">
        <uni-easyinput placeholder="喜欢数、点赞数" type="number" v-model="formData.like_count"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="comment_count" label="">
        <uni-easyinput placeholder="评论数量" type="number" v-model="formData.comment_count"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="picUrls" label="封面大图">
        <uni-data-checkbox :multiple="true" v-model="formData.picUrls"></uni-data-checkbox>
      </uni-forms-item>
      <uni-forms-item name="publish_date" label="发表时间">
        <uni-datetime-picker return-type="timestamp" v-model="formData.publish_date"></uni-datetime-picker>
      </uni-forms-item>
      <uni-forms-item name="publish_ip" label="发布文章时IP地址">
        <uni-easyinput placeholder="发表时 IP 地址" v-model="formData.publish_ip"></uni-easyinput>
      </uni-forms-item>
      <uni-forms-item name="last_modify_date" label="最后修改时间">
        <uni-datetime-picker return-type="timestamp" v-model="formData.last_modify_date"></uni-datetime-picker>
      </uni-forms-item>
      <uni-forms-item name="last_modify_ip" label="">
        <uni-easyinput placeholder="最后修改时 IP 地址" v-model="formData.last_modify_ip"></uni-easyinput>
      </uni-forms-item>
      <view class="uni-button-group">
        <button type="primary" class="uni-button" @click="submit">提交</button>
      </view>
    </uni-forms>
  </view>
</template>

<script>
  import { validator } from '../../js_sdk/validator/forum_article.js';

  const db = uniCloud.database();
  const dbCollectionName = 'forum_article';

  function getValidator(fields) {
    let result = {}
    for (let key in validator) {
      if (fields.indexOf(key) > -1) {
        result[key] = validator[key]
      }
    }
    return result
  }

  

  export default {
    data() {
      let formData = {
        "user_id": "",
        "title": "",
        "description": "",
        "province": "",
        "content": "",
        "view_count": 0,
        "like_count": 0,
        "comment_count": 0,
        "picUrls": [],
        "publish_date": null,
        "publish_ip": "",
        "last_modify_date": null,
        "last_modify_ip": ""
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
            icon: 'none',
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
        db.collection(dbCollectionName).doc(id).field("user_id,title,description,province,content,view_count,like_count,comment_count,picUrls,publish_date,publish_ip,last_modify_date,last_modify_ip").get().then((res) => {
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

<style>
  .uni-container {
    padding: 15px;
  }

  .uni-input-border,
  .uni-textarea-border {
    width: 100%;
    font-size: 14px;
    color: #666;
    border: 1px #e5e5e5 solid;
    border-radius: 5px;
    box-sizing: border-box;
  }

  .uni-input-border {
    padding: 0 10px;
    height: 35px;

  }

  .uni-textarea-border {
    padding: 10px;
    height: 80px;
  }

  .uni-button-group {
    margin-top: 50px;
    /* #ifndef APP-NVUE */
    display: flex;
    /* #endif */
    justify-content: center;
  }

  .uni-button {
    width: 184px;
  }
</style>
