<template>
	<view>
		<uv-notice-bar text="本商城产品为学习交流使用, 下单概不发货, 请谨慎下单~~"></uv-notice-bar>
		<view class="paypage">
			<!-- 配送方式选择组件 -->
			<delivery-layout :deliveryInfo="deliveryInfo"></delivery-layout>

			<view class="goodsList">
				<goods-list :goodsList="carsList" :totalPrice="totalPrice" :prePrice="preferentialPrice"></goods-list>
			</view>
			<!-- #ifndef MP-WEIXIN -->
			<view class="paytype">
				<view class="box" :class="item.value == payDefValue ? 'active':''" v-for="item in payType"
					@click="clickPayBtn(item.value)">
					<uv-icon :name="item.icon" :color="item.color" class="icon" size="26"></uv-icon>
					<text class="font">{{item.name}}</text>
				</view>
			</view>
			<!-- #endif -->
			<view class="payTabbar">
				<car-layout type="pay" :payBtnState="payBtnState" @confirmPay="onConfirmPay"></car-layout>
			</view>
			<uni-pay ref="uniPay" returnUrl="/pages/order/order" @success="paySuccess" @cancel="payCancel"
				@create="payCreate"></uni-pay>
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';

	// #ifdef APP || H5
	let payDefValue = ref("alipay");
	// #endif
	// #ifdef MP-WEIXIN
	let payDefValue = ref("wxpay");
	// #endif

	let payType = ref([{
		name: "支付宝",
		value: "alipay",
		color: "#1578FF",
		icon: "zhifubao-circle-fill"
	}, {
		name: "微信",
		value: "wxpay",
		color: "#04C15F",
		icon: "weixin-fill"
	}])

	function clickPayBtn(value) {
		payDefValue.value = value;
	}
</script>

<style lang="scss" scoped>
	page {
		background: $page-bg-color;
	}

	.paypage {
		padding: 30rpx;

		.goodsList {
			margin-top: 30rpx;
		}

		.paytype {
			@include flex-box();

			.box {
				width: 49%;
				height: 75rpx;
				background: #fff;
				border-radius: 10rpx;
				@include flex-box-set();
				border: 1px solid #fff;
				filter: grayscale(100%);

				.font {
					padding-left: 10rpx;
				}
			}

			.box:first-child.active {
				border-color: #1578FF;
				color: #1578FF;
				filter: grayscale(0%);
			}

			.box:last-child.active {
				border-color: #04C15F;
				color: #04C15F;
				filter: grayscale(0%);
			}
		}

		.payTabbar {
			position: fixed;
			width: 100%;
			bottom: 0;
			left: 0;
		}
	}
</style>