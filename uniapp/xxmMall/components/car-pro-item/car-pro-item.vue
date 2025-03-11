<template>
	<view class="carProItem">
		<!-- 左侧商品图片 -->
		<view class="left">
			<view class="pic">
				<image class="img" :src="props.item.thumb" mode="aspectFill"></image>
			</view>
			<view class="text">
				<view class="title">{{props.item.name}}</view>
				<view class="sku">微辣/10包</view>
				<view class="price">
					<view class="big">￥{{props.item.price}}</view>
					<view class="small">￥{{props.item.before_price}}</view>
				</view>
			</view>
		</view>
		<!-- 右侧步进器 -->
		<view class="right">
			<pro-num-box :item="props.item"></pro-num-box>
		</view>
	</view>
</template>

<script setup>
	let props = defineProps({
		item: {
			type: Object,
			default: () => ({})
		}
	})
</script>

<style lang="scss" scoped>
	.carProItem {
		padding: 20rpx 0;
		border-bottom: 1px solid $border-color-light;
		position: relative;

		.left {
			width: 500rpx;
			@include flex-box-set(start, stretch);

			.pic {
				width: 110rpx;
				height: 110rpx;

				.img {
					width: 100%;
					height: 100%;
				}
			}

			.text {
				flex: 1;
				padding-left: 20rpx;

				.title {
					font-size: 28rpx;
					@include ellipsis(2);
				}

				.sku {
					font-size: 22rpx;
					color: #999;
					padding: 5rpx 0;
				}

				.price {
					@include flex-box-set(start);

					.big {
						font-weight: bold;
						font-size: 28rpx;
						color: $brand-theme-color;
					}

					.small {
						font-size: 26rpx;
						color: $text-font-color-3;
					}
				}
			}
		}

		.right {
			position: absolute;
			right: 0;
			bottom: 20rpx;
		}
	}
</style>