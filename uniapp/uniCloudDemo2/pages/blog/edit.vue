<template>
	<view class="layout">
		<view class="content">
			<textarea class="textarea" placeholder="说点什么吧..." auto-height :maxlength="600"
				v-model="formData.content"></textarea>
		</view>

		<view class="pics">
			<uni-file-picker v-model="formData.pics" fileMediatype="image" mode="grid" />
		</view>

		<view class="btns">
			<button type="primary" plain :disabled="btnDisabled" @click="onSubmit">提交</button>
		</view>
	</view>
</template>

<script setup>
	import {
		computed,
		ref
	} from 'vue';
	const blogCloudObj = uniCloud.importObject("blogCloudObj");
	const formData = ref({
		content: "",
		pics: []
	})

	const btnDisabled = computed(() => !(formData.value.content.length > 0 || formData.value.pics.length > 0));

	const onSubmit = async () => {
		// console.log(formData.value);
		let params = {
			...formData.value,
			pics: formData.value.pics.map(item => ({
				name: item.name,
				extname: item.extname,
				url: item.url
			}))
		}
		// console.log(params)
		let res = await blogCloudObj.add(params)
		console.log(res);
		if (res.errCode == 0) {
			uni.showToast({
				title: '发布成功',
				icon: 'success'
			})
			//1.5秒后返回
			setTimeout(() => {
				formData.value = {
					content: "",
					pics: []
				}
				uni.redirectTo({
					url: '/pages/blog/list'
				})
			}, 1500)
		} else {
			uni.showModal({
				title: '发布失败',
				content: res.errMsg,
				showCancel: false
			})
		}

	}
</script>

<style lang="scss" scoped>
	.layout {
		.content {
			padding: 30rpx;

			.textarea {
				font-size: 38rpx;
				width: 100%;
				line-height: 1.7em;
				min-height: 200rpx;
			}
		}

		.pics {
			padding: 30rpx;
		}

		.btns {
			padding: 30rpx;

			button {
				width: 100%;
			}
		}
	}
</style>