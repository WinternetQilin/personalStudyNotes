<template>
	<view>
		<view class="searchLayout">
			<uv-search placeholder="请输入搜索内容" v-model="searchStr" clearabled showAction actionText="搜索" animation
				@search="onSearch" @custom="onSearch" @clear="onClear"></uv-search>

			<view class="historyList" v-if="goodsData.length==0">
				<view class="item" v-for="(item,index) in historyList" :key="item">
					<view class="text" @click="clickHitText(item)">{{item}}</view>
					<view class="close" @click="onClose(index)">
						<uv-icon name="close" size="16" color="#999"></uv-icon>
					</view>
				</view>
			</view>

			<view class="goodsLayout">
				<view class="item" v-for="item in goodsData" :key="item._id">
					<product-item :item="item"></product-item>
				</view>
			</view>

			<view v-if="noData">
				<uv-empty mode="search" icon="https://cdn.uviewui.com/uview/empty/search.png">
				</uv-empty>
			</view>
		</view>


		<pro-detail-popup></pro-detail-popup>
		<pro-select-specs></pro-select-specs>

		<view class="carOut">
			<car-layout v-if="buyNum>0"></car-layout>
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		onLoad
	} from '@dcloudio/uni-app'

	let searchStr = ref('')
	let historyList = ref([])

	onLoad(() => {
		historyList.value = uni.getStorageSync('historyList') || []
	})

	function onSearch() {
		if (searchStr.value.trim() === '')
			return
		historyList.value.unshift(searchStr.value)
		historyList.value = [...new Set(historyList.value)]
		uni.setStorageSync('historyList', historyList.value)
	}

	function onClose(idx) {
		historyList.value.splice(idx, 1)
		uni.setStorageSync('historyList', historyList.value)
	}
</script>

<style lang="scss" scoped>
	.searchLayout {
		padding: 30rpx;
		padding-bottom: 150rpx;

		.historyList {
			margin-top: 30rpx;

			.item {
				@include flex-box();
				font-size: 32rpx;
				padding: 30rpx 0;
				color: #333;
				border-bottom: 1px solid $border-color-light;
			}
		}
	}

	.carOut {
		position: fixed;
		bottom: 0;
		left: 0;
		width: 100%;
	}
</style>