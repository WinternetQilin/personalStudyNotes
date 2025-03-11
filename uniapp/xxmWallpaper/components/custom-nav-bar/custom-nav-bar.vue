<template>
	<view class="customNavBarContainer">
		<view class="navBar commonPageBg">
			<view class="statusBar" :style="{height:statusBarHeight + 'px'}"></view>
			<view class="titleBar" :style="{height:titleBarHeight + 'px'}">
				<view class="title">{{title}}</view>
				<navigator url="/pages/search/search" class="search">
					<uni-icons class="icon" type="search" color="#888" size="18"></uni-icons>
					<text>搜索</text>
				</navigator>
			</view>
		</view>
		<view class="fill" :style="{height:titleBarHeight + statusBarHeight + 'px'}"></view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		getStatusBarHeight,
		getTitleBarHeight
	} from "@/utils/system.js"

	defineProps({
		title: {
			type: String,
			default: '标题'
		}
	})

	let statusBarHeight = ref(getStatusBarHeight())
	let titleBarHeight = getTitleBarHeight()
</script>

<style lang="scss" scoped>
	.customNavBarContainer {
		.navBar {
			position: fixed;
			top: 0;
			left: 0;
			width: 100%;
			z-index: 10;

			.statusBar {}

			.titleBar {
				display: flex;
				align-items: center;

				.title {
					font-size: 35rpx;
					font-weight: 700;
					color: black;
				}

				.search {
					width: 220rpx;
					height: 50rpx;
					border-radius: 60rpx;
					background: rgba(255, 255, 255, 0.4);
					border: 1px solid #fff;
					margin-left: 30rpx;
					color: #999;
					display: flex;
					align-items: center;
					font-size: 28rpx;

					.icon {
						padding: 0 12rpx;
					}
				}
			}
		}

		.fill {}
	}
</style>