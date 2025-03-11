<template>
	<view class="layout">
		<navigator class="toPiclist" url="/pages/wallpaper/piclist">点击前往壁纸列表</navigator>
		<view class="add">
			<input class="ipt" type="text" v-model="classname" placeholder="请输入分类名称" @confirm="onConfirm">
		</view>
		<view class="list">
			<view class="item" v-for="item in classList" :key="item._id">
				<view class="name">{{item.name}}</view>
				<view class="status">
					<switch :checked="item.status" style="transform:scale(0.6)"
						@change="(e)=>switchChange(e,item._id)" />
				</view>
				<view class="remove">
					<uni-icons type="trash" size="26" @click="handleRemove(item._id)"></uni-icons>
				</view>
			</view>
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	const demoObj = uniCloud.importObject("demoObj")
	const classname = ref("");
	const classList = ref([]);
	const db = uniCloud.database();


	const getClassify = async () => {
		console.log("获取分类");
		// let res = await db.collection("demo-classify").orderBy("createTime desc").field("_id,name,status").get()
		let res = await demoObj.getClassify()
		console.log(res.data);
		classList.value = res.data
	}

	const switchChange = async (e, classId) => {
		console.log(e, classId);
		let res = await db.collection("demo-classify").doc(classId).update({
			status: e.detail.value
		})
		console.log(res);
		uni.showToast({
			title: '修改成功',
			icon: 'success'
		})
	}


	const handleRemove = async (classId) => {
		console.log("删除方法", classId);
		let res = await db.collection("demo-classify").doc(classId).remove()
		console.log(res);
		getClassify();
	}

	const onConfirm = async () => {
		console.log("确认提交添加");
		let res = await db.collection("demo-classify").add({
			name: classname.value
		})
		console.log(res);
		classname.value = "";
		getClassify();
	}

	getClassify();
</script>

<style lang="scss" scoped>
	.layout {
		padding: 30rpx;

		.add {
			margin-bottom: 30rpx;
			display: flex;
			gap: 20rpx;

			.ipt {
				width: 100%;
				border: 1px solid #eee;
				height: 70rpx;
				padding: 0 20rpx;
				box-sizing: border-box;
			}
		}

		.item {
			display: flex;
			padding: 10rpx 0;
			align-items: center;
			justify-content: space-between;

			.name {
				color: #007AFF;
				flex: 1;
			}

			.status {
				width: 100rpx;
			}

			.remove {
				width: 100rpx;
				display: flex;
				justify-content: flex-end;
			}
		}
	}
</style>