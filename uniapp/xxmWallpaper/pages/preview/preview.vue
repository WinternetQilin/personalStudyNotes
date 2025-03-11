<template>
	<view class="previewContainer">
		<swiper :current="currentIdx" @change="onSwiperChange">
			<swiper-item v-for="(item,index) in bigPicList" :key="item._id">
				<image v-if="index==currentIdx||index==currentIdx-1||index==currentIdx+1"
					@click="isShowMask=!isShowMask" :src="item.picurl" mode="aspectFill"></image>
			</swiper-item>
		</swiper>
		<view class="mask" v-if="isShowMask">
			<view class="backBtn" @click="onClickedBackBtn" :style="{top:getStatusBarHeight() + 'px'}">
				<uni-icons type="left" size="30" color="#fff"></uni-icons>
			</view>
			<view class="picCount">{{currentIdx + 1}} / {{bigPicList.length}}</view>
			<view class="time">
				<uni-dateformat :date="new Date()" format="hh:mm"></uni-dateformat>
			</view>
			<view class="date">
				<uni-dateformat :date="new Date()" format="MM月dd日"></uni-dateformat>
			</view>
			<view class="footer">
				<view class="btn" @click="onClickedInfo">
					<uni-icons type="info" size="30" color="black"></uni-icons>
					<view class="text">详情</view>
				</view>
				<view class="btn" @click="onClickedRateSource">
					<uni-icons type="star" size="30" color="black"></uni-icons>
					<view class="text">{{currentInfo.score}}分</view>
				</view>
				<view class="btn" @click="onClickedDownLoadBtn">
					<uni-icons type="download" size="30" color="black"></uni-icons>
					<view class="text">下载</view>
				</view>
			</view>
		</view>

		<!-- 信息弹出窗 -->
		<uni-popup ref="infoPopup" type="bottom">
			<view class="infoPopup">
				<view class="infoHeader">
					<view></view>
					<view class="text">壁纸信息</view>
					<uni-icons @click="onClickedInfoCloseBtn" type="closeempty" size="20" color="#999"></uni-icons>
				</view>
				<scroll-view class="infoBody" scroll-y>
					<view class="content">
						<view class="item">
							<view class="key">壁纸ID：</view>
							<view class="value" selectable>{{currentInfo._id}}</view>
						</view>
						<view class="item">
							<view class="key">发布者：</view>
							<view class="value" selectable>{{currentInfo.nickname}}</view>
						</view>
						<view class="item">
							<view class="key">评分：</view>
							<view class="value rateBox">
								<uni-rate readonly :value="currentInfo.score" />
								<text class="text">{{currentInfo.score}}分</text>
							</view>
						</view>
						<view class="item">
							<view class="key">摘要：</view>
							<view class="value" selectable>{{currentInfo.description}}</view>
						</view>
						<view class="item">
							<view class="key">标签：</view>
							<view class="value tabs">
								<view class="tab" selectable v-for="item in currentInfo.tabs" :key="item">{{item}}
								</view>
							</view>

						</view>
					</view>
				</scroll-view>
			</view>
		</uni-popup>

		<!-- 评分弹出窗 -->
		<uni-popup ref="rateSourcePopup" :is-mask-click="false">
			<view class="rateSourcePopup">
				<view class="header">
					<view></view>
					<view class="text">{{isRated?"已经评过分了":"壁纸评分"}}</view>
					<uni-icons @click="onClickedRateSourceCloseBtn" type="closeempty" size="20"
						color="#999"></uni-icons>
				</view>
				<view class="rateBox">
					<uni-rate :readonly="isRated" allowHalf v-model="userRate" />
					<view class="text">{{userRate}}分</view>
				</view>
				<view class="footer">
					<button @click="onClickedConfirmBtn" :disabled="!userRate||isRated" size="mini" plain>确认评分</button>
				</view>
			</view>
		</uni-popup>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		getStatusBarHeight
	} from '@/utils/system.js'
	import {
		onLoad
	} from "@dcloudio/uni-app"
	import {
		apiGetSetupScore,
		apiWriteDownload
	} from '@/api/apis.js'
	import classifyListVue from '../classifyList/classifyList.vue';

	let isShowMask = ref(true)
	let infoPopup = ref(null)
	let rateSourcePopup = ref(null)
	let userRate = ref(0)
	let bigPicList = ref([])
	let currentId = ref(null)
	let currentIdx = ref(-1)
	let currentInfo = ref({
		score: 0
	})
	let isRated = ref(false)

	onLoad((e) => {
		currentId.value = e.id
		currentIdx.value = bigPicList.value.findIndex(item => item._id == currentId.value)
		currentInfo.value = bigPicList.value[currentIdx.value]
	})

	//点击下载
	async function onClickedDownLoadBtn() {
		// #ifdef H5
		uni.showModal({
			content: "请长按图片保存",
			showCancel: false
		})
		return
		// #endif

		//先检查是否多次重复下载
		let res = await apiWriteDownload({
			classid: currentInfo.value.classid,
			wallId: currentInfo.value._id
		})
		if (res.errCode != 0) {
			uni.hideLoading()
			return
		}

		uni.getImageInfo({
			src: currentInfo.value.picurl
		}).then(imageInfo => {
			uni.showLoading({
				title: '正在保存',
				mask: true
			})

			uni.saveImageToPhotosAlbum({
				filePath: imageInfo.path
			}).then(saveImageInfo => {
				uni.hideLoading()
				uni.showToast({
					title: '保存成功',
					icon: 'none'
				})
			}).catch(saveImageInfo => {
				uni.hideLoading()
				console.log(saveImageInfo)
				if (saveImageInfo.errMsg == "saveImageToPhotosAlbum:fail auth deny") {
					uni.showModal({
						title: '提示',
						content: '保存失败，请开启保存到相册权限'
					}).then(res => {
						if (res.confirm) {
							uni.openSetting().then(settings => {
								if (settings.authSetting["scope.writePhotosAlbum"]) {
									uni.showToast({
										title: '获取授权成功',
										icon: 'none'
									})
								} else {
									uni.showToast({
										title: '获取授权失败',
										icon: 'none'
									})
								}
							})
						}
					})
				} else {
					uni.showToast({
						title: '保存失败,请重试',
						icon: 'none'
					})
				}
			})
		})
	}

	//点击图片显示/隐藏遮罩
	function onClickedImg() {
		isShowMask.value = !isShowMask.value
	}
	//打开壁纸信息弹窗
	function onClickedInfo() {
		infoPopup.value.open()
	}
	//关闭壁纸信息弹窗
	function onClickedInfoCloseBtn() {
		infoPopup.value.close()
	}
	//打开评分弹窗
	function onClickedRateSource() {
		if (currentInfo.value.userScore) {
			isRated.value = true
			userRate.value = currentInfo.value.userScore
		}
		rateSourcePopup.value.open()
	}
	//关闭评分弹窗
	function onClickedRateSourceCloseBtn() {
		rateSourcePopup.value.close()
		isRated.value = false
		userRate.value = 0
	}
	//点击确认评分按钮
	async function onClickedConfirmBtn() {
		let {
			classid,
			_id: wallId
		} = currentInfo.value
		let res = await apiGetSetupScore({
			classid,
			wallId,
			userScore: userRate.value
		})
		if (res.errCode == 0) {
			uni.showToast({
				title: '评分成功',
				icon: 'success'
			})

			bigPicList.value[currentIdx.value].userScore = userRate.value

			uni.setStorageSync('classifyPicList', bigPicList.value)

			onClickedRateSourceCloseBtn()
			userRate.value = 0
		}

	}
	//点击返回按钮
	function onClickedBackBtn() {
		uni.navigateBack({
			fail: () => {
				uni.reLaunch({
					url: '/pages/index/index'
				})
			}
		})
	}
	//从缓存中读取图片信息
	let classifyPicList = uni.getStorageSync('classifyPicList') || []
	bigPicList.value = classifyPicList.map(item => {
		return {
			...item,
			picurl: item.smallPicurl.replace("_small.webp", ".jpg")
		}
	})
	//左右滑动
	function onSwiperChange(e) {
		currentIdx.value = e.detail.current
		currentInfo.value = bigPicList.value[currentIdx.value]
	}
</script>

<style lang="scss" scoped>
	.previewContainer {
		position: relative;
		width: 100%;
		height: 100vh;

		swiper {
			width: 100%;
			height: 100%;

			swiper-item {
				width: 100%;
				height: 100%;

				image {
					width: 100%;
					height: 100%;
				}
			}
		}

		.mask {
			// position: absolute;
			// top: 0;
			// left: 0;
			width: 0;
			height: 0;
			background-color: transparent;

			&>view {
				position: absolute;
				left: 0;
				right: 0;
				margin: 0 auto;
				width: fit-content;
			}

			// background-color: #bfa;
			.backBtn {
				// top: 4vh;
				left: 2vw;
				margin: 0;
				display: flex;
				align-items: center;
				justify-content: center;
				width: 75rpx;
				height: 75rpx;
				background-color: rgba(0, 0, 0, .3);
				border-radius: 50%;
				border: 1px solid #ccc;
			}

			.picCount {
				top: 10vh;
				background-color: rgba(0, 0, 0, .3);
				color: #fff;
				font-size: 28rpx;
				border-radius: 40rpx;
				padding: 8rpx 28rpx;
				backdrop-filter: blur(10rpx);
			}

			.time {
				position: absolute;
				top: calc(10vh + 75rpx);
				color: #fff;
				font-size: 110rpx;
				text-shadow: 0 4rpx rgba(0, 0, 0, .3);
			}

			.date {
				color: #fff;
				top: calc(10vh + 75rpx + 145rpx);
				box-shadow: 0 4rpx rgba(0, 0, 0, .3);
				font-size: 34rpx;
			}

			.footer {
				bottom: 10vh;
				width: 490rpx;
				height: 120rpx;
				background-color: rgba(255, 255, 255, .7);
				display: flex;
				align-items: center;
				justify-content: space-around;
				text-align: center;
				border-radius: 60rpx;
				backdrop-filter: blur(12rpx);

				.btn {
					padding: 2rpx 12rpx;

					.text {
						color: gray;
						font-size: 22rpx
					}
				}
			}
		}

		.infoPopup {
			background-color: #fff;

			.infoHeader {
				display: flex;
				align-items: center;
				justify-content: space-between;
				text-align: center;
				padding: 40rpx 40rpx;
				font-size: 24rpx;
				color: #999;
			}

			.infoBody {
				max-height: 60vh;

				.content {
					.item {
						display: flex;
						font-size: 30rpx;
						padding-top: 28rpx;
						padding-bottom: 28rpx;
						padding-left: 54rpx;
						padding-right: 33rpx;

						.key {
							color: #999;
							width: 140rpx;
							text-align: right;
						}

						.value {
							flex: 1;
							width: 0;

							.text {}
						}

						.tabs {
							display: flex;
							flex-wrap: wrap;

							.tab {
								border: 1px solid $common-color-green;
								color: $common-color-green;
								font-size: 22rpx;
								padding: 10rpx 30rpx;
								border-radius: 40rpx;
								line-height: 1em;
								margin: 0 10rpx 10rpx 0;
							}
						}

						.rateBox {
							display: flex;
							align-items: center;
							text-align: center;

							.text {
								padding-left: 15rpx;
								// background-color: #bfa;
								color: #FFCB43;
							}
						}
					}
				}
			}
		}

		.rateSourcePopup {
			background-color: #fff;
			// width: 300rpx;
			// padding: 0 64rpx;
			border-radius: 20rpx;

			.header {
				display: flex;
				align-items: center;
				justify-content: space-between;
				text-align: center;
				padding: 40rpx 30rpx;
				font-size: 24rpx;
				color: #999;
			}

			.rateBox {
				display: flex;
				justify-content: center;
				align-items: center;
				text-align: center;
				padding: 0 64rpx;

				.text {
					padding-left: 48rpx;
					font-size: 28rpx;
					// background-color: #bfa;
					color: #FFCB43;
				}
			}

			.footer {
				display: flex;
				justify-content: center;
				align-items: center;
				text-align: center;
				margin-top: 48rpx;
				padding-bottom: 38rpx;
			}
		}
	}
</style>