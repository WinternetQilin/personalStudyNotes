<template>
	<view class="user">
		<view class="top">
			<view class="group">
				<view class="userinfo" @click="OnClickToUserInfo">
					<view class="pic">
						<image v-if="hasLogin&&userInfo.avatar_file&&userInfo.avatar_file.url"
							:src="userInfo.avatar_file.url" mode="aspectFill">
						</image>
						<image v-else src="../../static/images/user-default.jpg" mode="aspectFill"></image>
					</view>
					<view class="text" v-if="true">
						<view class="nickname">{{userInfo.nickname||userInfo.username||userInfo.mobile||"匿名用户"}}</view>
						<view class="year" v-if="userInfo.register_date">
							<uni-dateformat :date="userInfo.register_date"
								:threshold="[3600,99*365*24*60*60*1000]"></uni-dateformat>
							注册
						</view>
					</view>
					<view class="text" v-else>
						<view class="nickname">点击登录</view>
					</view>

				</view>

				<view class="more">
					<text class="iconfont icon-a-10-you"></text>
				</view>
			</view>

			<view class="bg">
				<image v-if="hasLogin&&userInfo.avatar_file&&userInfo.avatar_file.url" :src="userInfo.avatar_file.url"
					mode="aspectFill">
				</image>
				<image v-else src="../../static/images/user-default.jpg" mode="aspectFill"></image>
			</view>
		</view>



		<view class="main">
			<view class="info">
				<view class="item"><text>{{totalObj.likeNum}}</text>获赞</view>
				<view class="item"><text>{{totalObj.commentNum}}</text>评论</view>
				<view class="item"><text>{{totalObj.artNum}}</text>发文</view>
			</view>

			<view class="list">
				<view class="group">
					<view class="item" @click="onClickToList">
						<view class="left"><text class="iconfont icon-a-24-bianji"></text><text class="text">我的长文</text>
						</view>
						<view class="right"><text class="iconfont icon-a-10-you"></text></view>
					</view>
					<view class="item" @click="onClickToLike">
						<view class="left"><text class="iconfont icon-a-106-xihuan"></text><text
								class="text">我的点赞</text></view>
						<view class="right"><text class="iconfont icon-a-10-you"></text></view>
					</view>
					<view class="item">
						<view class="left"><text class="iconfont icon-a-21-xiugai"></text><text class="text">评论过的</text>
						</view>
						<view class="right"><text class="iconfont icon-a-10-you"></text></view>
					</view>
				</view>

				<view class="group">
					<view class="item">
						<view class="left"><text class="iconfont icon-a-32-wenjian"></text><text class="text">关于</text>
						</view>
						<view class="right"><text class="iconfont icon-a-10-you"></text></view>
					</view>
					<view class="item">
						<view class="left"><text class="iconfont icon-a-5-xinxi"></text><text class="text">意见反馈</text>
						</view>
						<view class="right"><text class="iconfont icon-a-10-you"></text></view>
					</view>
				</view>

				<view class="group">
					<view class="item" @click="onClickLogout">
						<view class="left"><text class="iconfont icon-a-73-tuichu"></text><text class="text">退出登录</text>
						</view>
						<view class="right"><text class="iconfont icon-a-10-you"></text></view>
					</view>
				</view>
			</view>
		</view>


	</view>
</template>

<script setup>
	import {
		ref,
		computed
	} from 'vue';
	import {
		onLoad
	} from "@dcloudio/uni-app"
	import {
		store,
		mutations
	} from '@/uni_modules/uni-id-pages/common/store.js'
	const forumCloudObj = uniCloud.importObject("forumCloudObj")

	let hasLogin = null
	let userInfo = null
	let totalObj = ref({})

	onLoad(async () => {
		hasLogin = computed(() => store.hasLogin)
		userInfo = computed(() => store.userInfo)
		// console.log(userInfo.value._id)

		//获取用户的评论数、获赞数、发文数
		if (hasLogin.value) {
			totalObj.value = await forumCloudObj.getTotal()
			console.log(totalObj.value)
		}
	})

	function onClickLogout() {
		uni.showModal({
			title: '提示',
			content: '确定退出登录吗？',
			success: function(res) {
				if (res.confirm) {
					mutations.logout()
				}
			},
		})
	}

	// 我的长文列表
	function onClickToList() {
		uni.navigateTo({
			url: "/pages/forum_article/list"
		})
	}

	// 我的点赞列表
	function onClickToLike() {
		uni.navigateTo({
			url: "/pages/forum_like/list"
		})
	}

	function OnClickToUserInfo() {
		uni.navigateTo({
			url: '/uni_modules/uni-id-pages/pages/userinfo/userinfo'
		})
	}
</script>

<style lang="scss" scoped>
	.user {

		.top {
			height: 300rpx;
			background: #bbb;
			padding: 0 30rpx;
			padding-top: var(--status-bar-height);
			position: relative;
			display: flex;
			align-items: center;

			.group {
				position: relative;
				z-index: 10;
				display: flex;
				align-items: center;
				justify-content: space-between;
				width: 100%;
				color: #fff;

				.userinfo {
					display: flex;
					width: 100%;
					align-items: center;

					.pic {
						width: 120rpx;
						height: 120rpx;
						border-radius: 50%;
						overflow: hidden;
						border: 2px solid #fff;

						image {
							width: 100%;
							height: 100%;
						}
					}

					.text {
						padding-left: 20rpx;

						.nickname {
							font-size: 44rpx;
							font-weight: 600;
						}

						.year {
							font-size: 26rpx;
							opacity: 0.6;
							padding-top: 5rpx;
						}
					}
				}

				.more {
					.iconfont {
						font-size: 40rpx;
					}
				}

			}

			.bg {
				position: absolute;
				top: 0;
				left: 0;
				width: 100%;
				height: 100%;
				overflow: hidden;

				image {
					width: 100%;
					height: 100%;
					filter: blur(20px);
					transform: scale(2);
					opacity: 0.5;
				}
			}
		}

		.main {
			width: 100%;
			min-height: 200rpx;
			background: #fff;
			border-radius: 30rpx;
			transform: translateY(-30rpx);
			padding: 30rpx 0;

			.info {
				padding: 10rpx 30rpx;
				display: flex;
				font-size: 30rpx;

				.item {
					padding-right: 20rpx;
					color: #888;

					text {
						font-weight: 600;
						color: #333;
					}
				}
			}

			.list {
				.group {
					padding: 15rpx 30rpx;
					border-bottom: 15rpx solid #f4f4f4;

					.item {
						display: flex;
						justify-content: space-between;
						align-items: center;
						padding: 25rpx 0;
						font-size: 36rpx;
						color: #555;
						border-bottom: 1rpx solid #f8f8f8;

						.left {
							display: flex;
							align-items: center;

							.iconfont {
								font-size: 38rpx;
								margin-right: 10rpx;
							}
						}

						.right {
							.iconfont {
								font-size: 26rpx;
							}
						}
					}

					.item:last-child {
						border: none;
					}
				}

				.group:last-child {
					border: none;
				}
			}
		}

	}
</style>