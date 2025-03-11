<template>
	<view class="addressForm">
		<uv-form labelPosition="top" :model="addressForm" :rules="addressRules" labelWidth="100" ref="uForm">

			<uv-form-item label="姓名" prop="username">
				<uv-input v-model="addressForm.username" placeholder="请输入姓名"></uv-input>
			</uv-form-item>


			<uv-form-item label="联系电话" prop="mobile">
				<uv-input v-model="addressForm.mobile" placeholder="请输入联系电话"></uv-input>
			</uv-form-item>

			<uv-form-item label="选择地区">
				<uni-data-picker v-model="addressForm.area_code" placeholder="请选择地址" popup-title="请选择所在地区"
					collection="opendb-city-china" field="code as value, name as text" orderby="value asc"
					self-field="code" parent-field="parent_code" @change="pickerChange">
				</uni-data-picker>
			</uv-form-item>


			<uv-form-item label="详细地址" prop="address">
				<uv-input v-model="addressForm.address" placeholder="请输入街道门牌号"></uv-input>
			</uv-form-item>

			<uv-form-item label="是否默认">
				<uv-switch v-model="addressForm.selected" inactiveColor="#eee"></uv-switch>
			</uv-form-item>

			<uv-form-item></uv-form-item>

			<uv-form-item>
				<uv-button type="primary" @click="onSubmit">提交</uv-button>
			</uv-form-item>

		</uv-form>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		func
	} from '../../uni_modules/uv-ui-tools/libs/function/test';

	let uForm = ref(null)
	let addressForm = ref({
		username: "",
		mobile: "",
		address: "",
		selected: false,
		area_code: "",
		area_name: ""
	})
	let addressRules = {
		username: [{
			required: true,
			message: '姓名是必填的',
			trigger: ['blur', 'change']
		}, {
			min: 2,
			max: 8,
			message: '长度在2-8个字符之间',
			trigger: ['blur', 'change']
		}],
		mobile: [{
			required: true,
			message: '电话是必填的',
			trigger: ['blur', 'change']
		}, {
			validator: (rule, value, callback) => {
				return uni.$uv.test.mobile(value);
			},
			message: '手机号格式不正确',
			trigger: ['change', 'blur']
		}],
		address: [{
			required: true,
			message: '地址是必填的',
			trigger: ['blur', 'change']
		}]
	}

	function onSubmit() {
		uForm.value.validate().then(async res => {
			let title;
			if (this.addressForm._id) {
				let resData = await addressCloudObj.updateOne(this.addressForm)
				title = "修改成功"
			} else {
				let resData = await addressCloudObj.add(this.addressForm)
				title = "新增成功"
			}
			uni.showToast({
				title,
				mask: true
			})
			setTimeout(() => {
				uni.navigateBack()
			}, 1000)


		}).catch(errors => {
			uni.$uv.toast('校验失败')
		})
	}
</script>

<style lang="scss" scoped>
	.addressForm {
		padding: 30rpx;
	}
</style>