<template>
	<view class="pro-item">
		<!-- 左侧商品图片 -->
		<view class="pic">
			<image class="img" :src="props.item.thumb" mode="aspectFill"></image>
		</view>
		<!-- 右侧文字区域 -->
		<view class="text">
			<!-- 标题行 -->
			<view class="title">{{props.item.name}}</view>
			<!-- 价格行 big是现价 small是原价 -->
			<view class="price">
				<view class="big">￥{{props.item.price}}</view>
				<view class="small">￥{{props.item.before_price}}</view>
			</view>
			<!-- 打折价格-->
			<view class="discount">5折</view>
			<!-- 右下角数量选择框 -->
			<view class="numbox">
				<view class="skuSelect" v-if="false">选规格</view>
				<view class="uNum" v-else>
					<pro-num-box :item="props.item"></pro-num-box>
				</view>
			</view>
		</view>
	</view>
</template>

<script setup>
	let props = defineProps({
		// 商品信息
		item: {
			type: Object,
			default: () => ({})
		}
	})
</script>

<style lang="scss" scoped>
	.pro-item {
		width: 100%;
		padding: 25rpx 0;
		display: flex;
		// background-color: orange;

		.pic {
			width: 170rpx;
			height: 170rpx;
			border-radius: 20rpx;
			overflow: hidden;

			.img {
				width: 100%;
				height: 100%;
			}
		}

		.text {
			flex: 1;
			padding-left: 20rpx;
			position: relative;

			.title {
				font-size: 34rpx;
				font-weight: bold;
				@include ellipsis();
			}

			.price {
				@include flex-box-set(start, end);
				font-weight: bold;
				padding: 20rpx 0;

				.big {
					font-size: 34rpx;
					color: $brand-theme-color;
				}

				.small {
					font-size: 26rpx;
					opacity: 0.4;
					text-decoration: line-through;
					padding-left: 10rpx;
				}
			}

			.discount {
				font-size: 22rpx;
				color: $brand-theme-color;
				padding: 3rpx 8rpx;
				border: 1rpx solid $brand-theme-color;
				display: inline-block;
				border-radius: 6rpx;
			}

			.numbox {
				position: absolute;
				right: 0;
				bottom: 0;

				.skuSelect {
					height: 40rpx;
					padding: 0 10rpx;
					background: $brand-theme-color;
					font-size: 28rpx;
					color: #fff;
				}
			}
		}
	}
</style>