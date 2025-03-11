<template>
	<view>
		<uni-nav-bar title="我的订单" :border="false" backgroundColor="#fff" leftIcon="left" @clickLeft="clickLeft"
			statusBar></uni-nav-bar>

		<view class="orderPage" v-if="orderList.length">
			<view class="row" v-for="item in orderList" :key="item._id" @click="goDetail(item)">
				<view class="head">
					<view class="number" v-if="true">编号{{item.order_no}}</view>

					<view class="state">
						<uv-icon name="weixin-fill" size="22" color="#04C15F" v-if="item.payType == 'wxpay'"></uv-icon>
						<uv-icon name="zhifubao" size="22" color="#1578FF" v-if="item.payType == 'alipay'"></uv-icon>
						<text :class="item.status==-2?'err':''">
							{{statusText(item.status)}}
						</text>
					</view>
				</view>
				<view class="body" v-if="item.orderType!='payment'">{{getCarsListName(item.carsList)}}</view>
				<view class="body" v-else>直接转账给商家</view>
				<view class="footer">
					<view class="time">{{timeFormat(item.createTime,'yyyy-MM-dd hh:mm')}}</view>
					<view class="count" v-if="item.orderType!='payment'">
						共{{item.carsList.length}}件商品 ，实付<text class="price">￥{{priceFormat(item.total_fee)}}</text>
					</view>
				</view>
			</view>
		</view>

		<view v-else class="noOrder">
			<uv-empty text="没有订单" icon="http://cdn.uviewui.com/uview/empty/data.png">
			</uv-empty>
		</view>

		<view v-if="noData && orderList.length" class="pageNoData">没有更多数据了</view>

	</view>

</template>

<script setup>
	function goDetail(item) {
		uni.navigateTo({
			url: '/pages/order/detail?item=' + item
		})
	}
</script>

<style lang="scss" scoped>
	page {
		background: $page-bg-color;
	}

	.orderPage {
		padding: 30rpx;

		.row {
			background: #fff;
			padding: 40rpx 20rpx;
			border-radius: 20rpx;
			margin-bottom: 30rpx;

			.head {
				@include flex-box();
				font-size: 32rpx;

				.number {
					@include flex-box-set(start);

					.way {
						background: #19be6b;
						color: #fff;
						font-size: 22rpx;
						padding: 6rpx 20rpx;
						border-radius: 30rpx;
						margin-left: 10rpx;

						&.self {
							background: #FF9100;
						}
					}
				}

				.state {
					color: $brand-theme-color-aux;
					@include flex-box-set(start);

					.err {
						color: #F56C6C;
					}
				}
			}

			.body {
				border: 1px solid $border-color;
				padding: 60rpx 20rpx;
				border-radius: 10rpx;
				background: #F9F9F9;
				font-size: 34rpx;
				margin: 30px 0;
			}

			.footer {
				@include flex-box();
				font-size: 26rpx;
				color: #a5a5a5;

				.price {
					font-weight: bold;
					color: #000;
				}
			}
		}
	}

	.pageNoData {
		padding: 10rpx 0 50rpx;
		text-align: center;
		color: #666;
	}
</style>