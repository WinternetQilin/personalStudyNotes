<template>
	<view class="classifyListContainer">
		<!-- <view class="loadingContainer" v-if="classifyPicList.length==0&&!noData">
			<uni-load-more status="loading" />
		</view> -->
		<view class="listContent">
			<navigator class="item" :url="'/pages/preview/preview?id='+item._id" v-for="item in classifyPicList"
				:key="item._id">
				<image :src="item.smallPicurl" mode="aspectFill"></image>
			</navigator>
		</view>
		<view class="loadingContainer">
			<uni-load-more :status="noData?'noMore':'loading'" />
		</view>
		<view class="safe-area-inset-bottom"></view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		apiGetClassifyPicList
	} from "@/api/apis.js"
	import {
		onLoad,
		onUnload,
		onReachBottom
	} from "@dcloudio/uni-app"

	let queryParams = {}
	let classifyPicList = ref([])
	let noData = ref(false)

	onLoad((e) => {
		let {
			id = null, name = "分类"
		} = e
		queryParams.classid = id
		queryParams.pageNum = 1
		uni.setNavigationBarTitle({
			title: name
		})
		getClassifyPicList()
	})

	onUnload(() => {
		uni.removeStorageSync("classifyPicList")
	})

	onReachBottom(() => {
		if (noData.value) return
		queryParams.pageNum++
		getClassifyPicList()
	})

	async function getClassifyPicList() {
		let res = await apiGetClassifyPicList(queryParams)
		if (res.data.length <= 0) {
			noData.value = true
		}
		console.log(res)
		classifyPicList.value = [...classifyPicList.value, ...res.data]
		//将最新的数据放入缓存
		uni.setStorageSync('classifyPicList', classifyPicList.value)
	}
</script>

<style lang="scss" scoped>
	.classifyListContainer {
		padding: 5rpx;

		.listContent {
			display: grid;
			grid-template-columns: repeat(3, 1fr);
			gap: 5rpx;

			.item {
				display: block;
				height: 440rpx;

				image {
					width: 100%;
					height: 100%;
				}
			}
		}
	}
</style>