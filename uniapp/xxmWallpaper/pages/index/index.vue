<template>
	<view class="container commonPageBg">
		<!-- 头部 -->
		<custom-nav-bar class="customNavBar" title="推荐"></custom-nav-bar>
		<!-- 轮播图 -->
		<view class="banner">
			<swiper indicator-dots indicator-color="rgba(255,255,255,.3)" indicator-active-color="#fff" autoplay
				interval="3000" circular>
				<swiper-item v-for="item in bannerPics" :key="item._id">
					<image :src="item.picurl" mode="aspectFill"></image>
				</swiper-item>
			</swiper>
		</view>
		<!-- 公告 -->
		<view class="notice">
			<view class="left">
				<uni-icons type="sound-filled" size="25" color="#28B48F"></uni-icons>
				<text>公告</text>
			</view>
			<view class="center">
				<swiper interval="3000" circular autoplay vertical>
					<swiper-item v-for="item in noticeList" :key="item._id">
						{{item.title}}
					</swiper-item>
				</swiper>

			</view>
			<view class="right">
				<uni-icons type="right" size="20" color="#A7A7A7"></uni-icons>
			</view>
		</view>
		<!-- 推荐 -->
		<view class="recommend">
			<common-title>
				<template #left>每日推荐</template>
				<template #right>
					<view style="display: flex;align-items: center;">
						<uni-icons type="calendar" size="30"></uni-icons>
						<view class="date" style="display: flex;">
							<uni-dateformat :date="Date.now()" format="dd" :threshold="[0,0]"></uni-dateformat>
							日
						</view>
					</view>
				</template>
			</common-title>
			<view class="content">
				<scroll-view scroll-x>
					<view v-for="item in recommendPics" :key="item._id">
						<navigator :url="'/pages/preview/preview?id='+item._id" @click="goPreview">
							<image :src="item.smallPicurl" mode="aspectFill"></image>
						</navigator>
					</view>
				</scroll-view>
			</view>
		</view>
		<!-- 专题 -->
		<view class="classify" v-if="themeList">
			<common-title>
				<template #left>专题精选</template>
				<template #right>
					<navigator url="">More+</navigator>
				</template>
			</common-title>
			<view class="content">
				<template v-for="item in themeList" :key="item._id">
					<theme-item v-if="item.name !='AI美图'" :item="item"></theme-item>
				</template>

				<theme-item :isMore="true"></theme-item>
			</view>
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue'
	import {
		apiGetBannerPics,
		apiGetRecommendPics,
		apiGetNoticeList,
		apiGetThemeList
	} from "@/api/apis.js"
	import {
		onLoad,
		onShareAppMessage,
		onShareTimeline
	} from "@dcloudio/uni-app"

	let bannerPics = ref([])
	let recommendPics = ref([])
	let noticeList = ref([])
	let themeList = ref([])

	function goPreview() {
		uni.setStorageSync('classifyPicList', recommendPics.value)
	}

	//分享给好友
	onShareAppMessage(() => {
		return {
			title: "xxm壁纸",
			path: "/pages/index/index"
		}
	})

	//分享到朋友圈
	onShareTimeline(() => {
		return {
			title: "xxm壁纸!!!"
		}
	})

	//获取轮播图图片
	async function getBannerPics() {
		let temp = await apiGetBannerPics()
		bannerPics.value = temp.data
	}
	//获取每日推荐
	async function getRecommendPics() {
		let temp = await apiGetRecommendPics()
		recommendPics.value = temp.data
	}
	//获取公告列表
	async function getNoticeList() {
		let temp = await apiGetNoticeList()
		noticeList.value = temp.data
	}
	//获得专题分类
	async function getThemeList() {
		let temp = await apiGetThemeList()
		themeList.value = temp.data
		console.log(themeList.value)
	}

	onLoad(() => {
		getBannerPics()
		getRecommendPics()
		getNoticeList()
		getThemeList()
	})
</script>

<style lang="scss" scoped>
	.container {
		.customNavBar {
			:deep() {
				.navBar {
					padding-left: 30rpx;
				}
			}
		}

		.banner {
			swiper {
				swiper-item {
					padding: 0 30rpx;
					width: 690rpx;
					height: 340rpx;

					image {
						width: 100%;
						height: 100%;
						border-radius: 20rpx;
					}
				}
			}

			// background-color: #bfa;

		}

		.notice {
			display: flex;
			background-color: #F9F9F9;
			width: 690rpx;
			height: 80rpx;
			line-height: 80rpx;
			border-radius: 45rpx;
			margin: 0 auto;
			margin-top: 30rpx;

			.left {
				display: flex;
				justify-content: center;
				width: 140rpx;

				text {
					font-size: 25rpx;
					color: $common-color-green;
				}
			}

			.center {
				flex: 1;

				swiper {
					height: 100%;
					color: #585858;

					swiper-item {
						height: 100%;
						font-size: 30rpx;
						overflow: hidden;
						white-space: nowrap;
						text-overflow: ellipsis;
					}
				}
			}

			.right {
				width: 70rpx;
				text-align: center;
			}
		}

		.recommend {
			margin-top: 60rpx;

			view {
				:deep() {
					.uni-icons {
						color: $common-color-green !important;
					}

					.date {
						color: $common-color-green;
					}
				}
			}

			.content {
				width: 720rpx;
				margin-top: 30rpx;
				margin-left: 30rpx;

				scroll-view {
					white-space: nowrap;

					view {
						display: inline-block;
						margin-right: 20rpx;

						image {
							width: 200rpx;
							height: 440rpx;
							border-radius: 15rpx;
						}
					}

					view:last-child {
						margin-right: 30rpx;
					}
				}

			}
		}

		.classify {
			margin-top: 60rpx;
			padding-bottom: 50rpx;

			.content {
				margin-top: 30rpx;
				display: grid;
				gap: 13rpx;
				grid-template-columns: repeat(3, 1fr);
				padding-left: 30rpx;
				padding-right: 30rpx;
				// background-color: red;
			}
		}


	}
</style>