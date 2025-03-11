<template>
	<view class="category">
		<view class="row add" @click="clickAdd">
			<view class="left">
				<uv-icon name="plus" color="#576b95" size="22"></uv-icon>
				<text class="text">新增分类</text>
			</view>
		</view>
		<view class="row" v-for="(item,index) in categoryList" :key="item._id">
			<view class="left">
				<view class="name">{{item.name}}</view>
			</view>
			<view class="right">
				<uv-icon name="edit-pen" size="26" color="#576b95" @click="updateData(item._id,item.name)"></uv-icon>
				<uv-icon name="trash" size="26" color="#EC544F" @click="deleteData(item._id)"></uv-icon>
			</view>
		</view>

		<uni-popup ref="inputDialog">
			<uni-popup-dialog mode="input" :value="iptValue" placeholder="请输入分类名称" title="分类名称"
				@confirm="dialogConfirm"></uni-popup-dialog>
		</uni-popup>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue'

	let categoryList = [{
		name: '1'
	}]
	let iptValue = ref('')
	let updateID = ref(null)

	let inputDialog = ref(null)

	function getCateGory() {
		db.collection("kt-mall-category").get().then(res => {
			console.log(res);
			this.categoryList = res.result.data
		})
	}
	//添加分类
	function clickAdd() {
		iptValue.value = ""
		updateID.value = null;
		inputDialog.value.open();
	}
	//点击确认按钮
	async function dialogConfirm(e) {
		iptValue.value = e;
		if (this.updateID) {
			await db.collection("kt-mall-category").doc(this.updateID).update({
				name: this.iptValue
			})
		} else {
			await db.collection("kt-mall-category").add({
				name: this.iptValue
			})
		}
		this.getCateGory();
	}

	//修改一条分类
	function updateData(id, name) {
		// this.iptValue = name;
		// this.updateID = id;
		// this.$refs.inputDialog.open();
	}

	//删除一条分类
	function deleteData(id) {
		uni.showModal({
			content: "是否删除该分类?",
			success: res => {
				if (res.confirm) {
					// db.collection("kt-mall-category").doc(id).remove().then(res => {
					// 	this.getCateGory();
					// })
				}
			},
			fail: err => {
				console.log(err);
			}
		})
	}
</script>

<style lang="scss" scoped>
	.category {
		padding: 30rpx;

		.row {
			@include flex-box();
			border-bottom: 1px solid $border-color-light;
			padding: 26rpx 0;

			.left {
				font-size: 34rpx;
			}

			.right {
				@include flex-box();

				.uv-icon {
					margin-left: 30rpx;
				}
			}
		}

		.row.add {
			.left {
				color: $brand-theme-color-aux;
				@include flex-box();

				.text {
					font-size: 36rpx;
					padding-left: 10rpx;
				}
			}
		}
	}
</style>