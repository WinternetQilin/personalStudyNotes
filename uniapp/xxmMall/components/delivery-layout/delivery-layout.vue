<template>
	<view class="delivery">
		<view class="headNav">外送</view>
		<view class="body">
			<view class="box" @click="goAddress">
				<view class="left">收货地址</view>
				<view class="center">
					<view v-if="deliveryInfo.address">
						<view class="detail">{{deliveryInfo.address}}</view>
						<view class="userinfo">{{deliveryInfo.username + "-" + deliveryInfo.mobile}}</view>
					</view>
					<view class="addressTxt" v-else>请添加收货地址</view>
				</view>
				<view class="right">
					<uv-icon name="arrow-right" color="#999" size="18"></uv-icon>
				</view>
			</view>
		</view>
	</view>

</template>

<script setup>
	let props = defineProps({
		deliveryInfo: {
			type: Object,
			default () {
				return {
					address: "",
					username: "",
					mobile: null
				}
			}
		}

	})

	function goAddress() {
		uni.navigateTo({
			url: "/pages/address/list"
		})
	}
</script>

<style lang="scss" scoped>
	.delivery {
		.headNav {
			width: 100%;
			height: 78rpx;
			background: #fff;
			@include flex-box-set();
			color: $brand-theme-color;
			border-radius: 15rpx 15rpx 0 0;
		}

		.body {
			background: #fff;
			padding: 25rpx;

			.box {
				padding: 40rpx 20rpx;
				background: $page-bg-color;
				border-radius: 10rpx;
				font-size: 30rpx;
				@include flex-box();

				.center {
					flex: 1;
					padding: 0 30rpx;
					font-size: 30rpx;

					.userinfo {
						padding-top: 10rpx;
					}
				}
			}
		}
	}
</style>