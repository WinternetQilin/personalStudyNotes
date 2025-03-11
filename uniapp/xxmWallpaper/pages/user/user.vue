<template>
	<view class="userContainer commonPageBg" v-if="userInfo">
		<view :style="{height:getStatusBarHeight() + 'px'}"></view>
		<view class="userInfo">
			<view class="avatar">
				<image src="../../static/images/xxmLogo.png" mode="aspectFill"></image>
			</view>
			<view class="ip">{{userInfo.IP}}</view>
			<view class="address">来自于：{{userInfo.address.city || userInfo.address.province || userInfo.address.country}}
			</view>
		</view>
		<view class="section">
			<option-item optionName="我的下载" jumpUrl="/pages/classifyList/classifyList" :number="userInfo.downloadSize">
				<template #leftIcon>
					<uni-icons type="download-filled" size="30" color="#28B38C"></uni-icons>
				</template>
			</option-item>
			<option-item optionName="我的评分" jumpUrl="/pages/classifyList/classifyList" :number="userInfo.scoreSize">
				<template #leftIcon>
					<uni-icons type="star-filled" size="30" color="#28B38C"></uni-icons>
				</template>
			</option-item>
			<view class="contact">
				<option-item class="lastItem" optionName="联系客服">
					<template #leftIcon>
						<uni-icons type="chatboxes-filled" size="30" color="#28B38C"></uni-icons>
					</template>
				</option-item>
				<!-- #ifdef MP-WEIXIN -->
				<button open-type="contact"></button>
				<!-- #endif -->
				<!-- #ifndef MP-WEIXIN -->
				<button @click="onClickContact"></button>
				<!-- #endif -->
			</view>
		</view>
		<view class="section">
			<option-item optionName="订阅更新">
				<template #leftIcon>
					<uni-icons type="notification-filled" size="30" color="#28B38C"></uni-icons>
				</template>
			</option-item>
			<option-item class="lastItem" optionName="常见问题">
				<template #leftIcon>
					<uni-icons type="flag-filled" size="30" color="#28B38C"></uni-icons>
				</template>
			</option-item>
		</view>
	</view>
</template>

<script setup>
	import {
		getStatusBarHeight
	} from '@/utils/system.js'
	import {
		apiGetUserInfo
	} from "@/api/apis.js"
	import {
		ref
	} from 'vue';

	let userInfo = ref(null)

	function onClickContact() {
		uni.makePhoneCall({
			phoneNumber: "114514"
		})
	}

	async function getUserInfo() {
		let temp = await apiGetUserInfo()
		userInfo.value = temp.data
	}

	getUserInfo()
</script>

<style lang="scss" scoped>
	.lastItem {
		border-bottom: none;
	}

	.userContainer {
		// min-height: 100vh;
		padding: 0 30rpx;
		padding-top: 64rpx;

		.userInfo {
			display: flex;
			flex-direction: column;
			align-items: center;
			padding-bottom: 50rpx;

			.avatar {
				width: 160rpx;
				height: 160rpx;
				border-radius: 50%;
				overflow: hidden;

				image {
					width: 100%;
					height: 100%;
				}
			}

			.ip {
				font-size: 44rpx;
				margin-top: 36rpx;
			}

			.address {
				color: #999;
				margin-top: 24rpx;
			}
		}

		.section {
			background-color: #fff;
			margin-top: 50rpx;
			border-radius: 20rpx;
			border: 1px solid #eee;
			box-shadow: 0 0 30rpx rgba(0, 0, 0, .1);



			.contact {
				position: relative;

				button {
					position: absolute;
					top: 0;
					left: 0;
					width: 100%;
					height: 100%;
					opacity: 0;
				}
			}
		}

	}
</style>