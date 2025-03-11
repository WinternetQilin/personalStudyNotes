<template>
	<view class="goodsLayout">
		<view class="wrapper">
			<view class="title">共{{goodsList.length}}件商品</view>

			<view class="list">
				<view class="row" v-for="item in goodsList">
					<view class="left">
						<image :src="item.thumb[0].url" mode="aspectFill" class="img"></image>
						<view class="name">{{item.name}}</view>
					</view>
					<view class="center">×{{item.numvalue}}</view>
					<view class="right">
						<view class="big">￥{{priceFormat(item.price)}}</view>
						<view class="small" v-if="item.before_price">￥{{priceFormat(item.before_price)}}</view>
					</view>
				</view>
			</view>

			<view class="total">
				<text>
					已优惠￥{{priceFormat(prePrice)}}，
				</text> 合计 <text class="big">￥{{priceFormat(totalPrice)}}</text>
			</view>
		</view>
	</view>
</template>

<script>
	export default {
		name: "goods-list",
		data() {
			return {

			};
		}
	}
</script>

<style lang="scss">
	.goodsLayout {
		.wrapper {
			background: #fff;
			padding: 30rpx;
			margin-bottom: 25rpx;
			border-radius: 15rpx;

			.title {
				font-size: 38rpx;
			}

			.list {
				.row {
					@include flex-box();
					padding: 25rpx 0;

					.left {
						@include flex-box();
						width: 400rpx;

						.img {
							width: 64rpx;
							height: 64rpx;
							border-radius: 10rpx;
						}

						.name {
							padding-left: 15rpx;
							flex: 1;
							font-size: 30rpx;
						}
					}

					.center {
						width: 100rpx;
						text-align: center;
					}

					.right {
						flex: 1;
						text-align: right;
						font-weight: bold;

						.big {
							font-size: 34rpx;
						}

						.small {
							font-size: 22rpx;
							color: $text-font-color-3;
							text-decoration: line-through;
						}
					}
				}
			}

			.total {
				padding: 30rpx 0;
				text-align: right;
				font-size: 30rpx;
				color: $text-font-color-3;

				.big {
					font-size: 36rpx;
					font-weight: bold;
					color: #000;
				}
			}
		}
	}
</style>