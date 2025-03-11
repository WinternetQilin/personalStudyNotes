<template>
	<view class="home">
		<view class="topnav">
			<uv-tabs :list="navlist" :activeStyle="{
				color: '#333',
				fontWeight: 'bold',
				transform: 'scale(1.08)'
			}" :inactiveStyle="{
				color: '#888',
				transform: 'scale(1)'
			}" @click="clickNav"></uv-tabs>
		</view>

		<view class="loadingState" v-show="loadState">
			<uv-skeletons :loading="loadState" :skeleton="skeleton"></uv-skeletons>
		</view>

		<view class="content">
			<view class="item" v-for="item in dataList">
				<blog-item :articleItem="item"></blog-item>
			</view>
		</view>

		<navigator url="/pages/edit/edit" class="edit">
			<text class="iconfont icon-a-21-xiugai"></text>
		</navigator>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		onLoad
	} from "@dcloudio/uni-app"
	import {
		store,
		mutations
	} from '@/uni_modules/uni-id-pages/common/store.js'
	const forumCloudObj = uniCloud.importObject("forumCloudObj", {
		customUI: true
	})
	let navlist = ref([{
			name: "最新",
			type: "publish_date"
		},
		{
			name: "热门",
			type: "view_count"
		}
	])
	let dataList = ref([])
	let loadState = ref(false)
	let skeleton = [{
		type: 'line',
		num: 3,
		gap: '20rpx',
		style: ['width: 200rpx;marginBottom: 50rpx;', 'height: 100rpx;', 'width: 500rpx;'],
		// style: 'width: 200rpx;marginBottom: 50rpx;'
		// style: {width: '200rpx',marginBottom: '50rpx'}
	}]

	onLoad(async () => {
		// 获取文章列表数据
		getArticleList()
	})

	// 获取文章列表数据
	async function getArticleList(type = 'publish_date') {
		loadState.value = true
		dataList.value = []
		let res = null
		try {
			res = await forumCloudObj.getArticleList(type)
		} catch (e) {
			uni.showModal({
				title: '错误',
				content: e.errMsg,
				showCancel: false
			})
		}
		// console.log(res.data)
		dataList.value = res.data
		loadState.value = false

		//登录之后多进行一步
		if (!store.hasLogin) {
			return;
		}
		//查询当前登录的用户对哪些文章点过赞
		let idArr = []
		for (let item of dataList.value) {
			idArr.push(item._id)
		}
		let resLike = (await forumCloudObj.isArticleLike(idArr, uniCloud.getCurrentUserInfo().uid)).data
		// console.log(resLike)
		resLike.forEach(item => {
			let findIndex = dataList.value.findIndex(i => {
				return i._id == item.article_id
			})
			if (findIndex != -1) {
				dataList.value[findIndex].isLike = true
			}
		})

	}

	function clickNav(e) {
		console.log(e.type);
		// 重新获取文章列表数据
		getArticleList(e.type)
	}
</script>

<style lang="scss" scoped>
	.home {
		.topnav {
			// margin-bottom: 30rpx;
		}

		.loadingState {
			padding: 30rpx;
		}

		.content {
			.item {
				padding: 30rpx;
				border-bottom: #F7F7F7 15rpx solid
			}
		}

		.edit {
			width: 120rpx;
			height: 120rpx;
			background: #0199FE;
			border-radius: 50%;
			color: #fff;
			position: fixed;
			z-index: 100;
			bottom: 150rpx;
			right: 50rpx;
			display: flex;
			justify-content: center;
			align-items: center;
			box-shadow: 0 0 20rpx rgba(1, 153, 254, 0.8);

			.iconfont {
				font-size: 50rpx;
			}
		}
	}
</style>