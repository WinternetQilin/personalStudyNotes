<template>
	<uv-overlay :show="carShow" @click="clickCarIcon" z-index="9"></uv-overlay>
	<view class="carLayout">
		<!-- 点击购物车打开的弹出层 -->
		<view class="goods" v-if="carShow">
			<!-- 头部选项 -->
			<view class="head">
				<view class="text">已选商品</view>
				<view class="empty">清空</view>
			</view>
			<!-- 已选商品列表 -->
			<scroll-view scroll-y class="body">
				<view class="sContent">
					<view class="caritem" v-for="i in car.getCarList" :key="i.id">
						<car-pro-item :item="i"></car-pro-item>
					</view>
				</view>
			</scroll-view>
		</view>
		<!-- 底部购物车条 -->
		<view class="content">
			<view class="left">
				<view v-if="!props.type" class="icon" @tap="clickCarIcon" hover-class="iconhover" hover-stay-time="50">
					<uv-icon name="shopping-cart" size="34" color="#EC544F"></uv-icon>
					<view class="num">{{car.buyNum}}</view>
				</view>
				<view class="price">
					合计
					<text class="text">￥{{car.totalPrice}}</text>
				</view>
			</view>
			<view class="right">
				<view class="btn" v-if="!props.type" @click="goPay">选好了</view>
				<view class="btn" v-else @click="confirmPay">支付</view>
			</view>
		</view>
		<!-- 底部安全区域（针对iOS手机） -->
		<view class="safe-area-bottom"></view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import useCar from '../../store/car';

	const car = useCar()

	let props = defineProps({
		type: {
			type: String,
			default: ""
		}
	})

	let carShow = ref(false)

	function clickCarIcon() {
		carShow.value = !carShow.value
		// console.log(carShow.value)
	}

	function goPay() {
		uni.navigateTo({
			url: '/pages/paypage/paypage'
		})
	}

	function confirmPay() {

	}
</script>

<style lang="scss" scoped>
	.carLayout {
		position: relative;
		z-index: 10;

		.goods {
			border-bottom: 1px solid $border-color-light;
			padding: 30rpx 30rpx 0;
			border-radius: 20rpx 20rpx 0 0;
			background: #fff;

			.head {
				@include flex-box();
				color: $text-font-color-3;
				padding: 25rpx 0;

				.empty {
					color: $brand-theme-color-aux;
				}
			}

			.body {
				height: 550rpx;
			}
		}


		.content {
			@include flex-box();
			padding: 0 30rpx;
			height: 140rpx;
			background: #fff;

			.left {
				@include flex-box();

				.icon {
					width: 80rpx;
					height: 80rpx;
					background: #EEEFEE;
					border-radius: 10rpx;
					@include flex-box-set();
					position: relative;
					margin-right: 30rpx;

					.num {
						width: 36rpx;
						height: 36rpx;
						background: $brand-theme-color;
						border-radius: 50%;
						color: #fff;
						position: absolute;
						right: -18rpx;
						top: -18rpx;
						font-size: 22rpx;
						@include flex-box-set();
					}
				}

				.iconhover {
					transform: scale(0.9);
				}

				.price {
					font-size: 28rpx;

					.text {
						font-size: 32rpx;
						font-weight: bold;
					}
				}
			}

			.right {
				.btn {
					width: 210rpx;
					height: 75rpx;
					background: $brand-theme-color;
					@include flex-box-set();
					color: #fff;
					border-radius: 10rpx;

					&.disable {
						opacity: 0.6;
					}
				}
			}
		}

		.safe-area-bottom {
			width: 100%;
			height: env(safe-area-inset-bottom);
			background-color: #fff;
		}

	}
</style>