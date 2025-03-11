<template>
	<view class="orderDetail">
		<view v-if="params">
			<view class="payment">
				<icon type="error" color="#EC544F" size="50" v-if="params.realPrice"></icon>
				<icon type="success" color="#19BE6B" size="50" v-else></icon>
				<view class="text">
					<view class="big">
						实付款￥{{priceFormat(params.total_fee)}}
						<text style="font-size: 26rpx; padding-left:10rpx; color:#EC544F"
							v-if="params.realPrice">应付款￥{{priceFormat(params.realPrice)}}</text>
					</view>
					<view class="small">请等待商家配送</view>
				</view>
				<view class="complete" v-if="params.done">已完成</view>
			</view>

			<view class="info">
				<view class="viewOut">
					<view class="title">订单信息</view>
					<view class="body">
						<view class="row">订单编号： {{params.order_no}}</view>
						<view class="row">下单时间： {{timeFormat(params.createTime)}}</view>
						<view class="row">支付方式： {{params.payType=='alipay'?'支付宝支付':'微信支付'}}</view>
						<view class="row" v-if="params.orderType=='payment'">支付类型： 直接转账给商家</view>
					</view>
				</view>

				<view class="viewOut" v-if="params.orderType!='payment'">
					<view class="title">收货地址</view>
					<view class="body">
						<view class="row">{{params.deliveryInfo.address}}</view>
						<view class="row">{{params.deliveryInfo.username}}-{{params.deliveryInfo.mobile}}</view>
					</view>
				</view>
			</view>

			<view class="goodsList" v-if="params.orderType!='payment'">
				<goods-list :goodsList="params.carsList" :totalPrice="totalPrice" :prePrice="prePrice"></goods-list>
			</view>
		</view>
	</view>

</template>

<script setup>

</script>

<style lang="scss" scoped>
	page {
		background: $page-bg-color;
	}

	.orderDetail {
		.payment {
			@include flex-box-set(start);
			padding: 50rpx 30rpx;
			position: relative;

			.text {
				padding-left: 20rpx;
				color: $text-font-color-1;

				.big {
					font-size: 44rpx;
					font-weight: bold;
				}

				.small {
					font-size: 28rpx;
					color: $text-font-color-3;
				}
			}

			.complete {
				font-size: 32rpx;
				color: $text-font-color-3;
				font-weight: bold;
				border: 6rpx solid $text-font-color-3;
				width: 150rpx;
				height: 150rpx;
				border-radius: 50%;
				@include flex-box-set();
				transform: rotate(-20deg);
				position: absolute;
				right: 100rpx;
				top: 80rpx;

				&::after {
					display: block;
					content: "";
					border: 2rpx solid $text-font-color-3;
					position: absolute;
					width: 100%;
					height: 100%;
					border-radius: 50%;
					transform: scale(0.89);
					top: 0;
					left: 0;
					box-sizing: border-box;
				}
			}
		}

		.info {
			background: #fff;
			padding: 30rpx;
			border-radius: 30rpx 30rpx 0 0;

			.delivery {
				@include flex-box();

				.btn {
					@include flex-box-set();
					width: 250rpx;
					height: 60rpx;
					border-radius: 80rpx;
					background: #19BE6B;
					color: #fff;

					text {
						font-size: 34rpx;
					}
				}

				&.other {
					.btn {
						background: #FF9100;
					}

					.time {
						font-size: 32rpx;
						color: $brand-theme-color-aux;
					}
				}
			}

			.viewOut {
				padding: 30rpx 0;

				.title {
					font-size: 40rpx;
					padding-bottom: 15rpx;
				}

				.row {
					font-size: 30rpx;
					padding: 15rpx 0;
					color: $text-font-color-2;
					@include flex-box();
				}
			}
		}

		.goodsList {
			margin-top: 30rpx;
		}


	}
</style>