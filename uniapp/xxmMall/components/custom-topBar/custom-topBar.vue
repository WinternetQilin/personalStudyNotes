<template>
	<view class="customHead" :style="{height:systemStore.totalHeight+'px'}">
		<view class="bg">
			<image class="bgimg" src="/static/logo.png" mode="aspectFill"></image>
		</view>
		<view class="container">
			<!-- 小程序端顶部撑开（避开）状态栏 -->
			<view class="statusBar" :style="{height:systemStore.statusBarHeight+'px'}"></view>
			<!-- 客服按钮和后台管理按钮 -->
			<view class="service" v-if="!systemStore.foldState" :style="{height:systemStore.titleBarHeight+'px'}">
				<view class="kefu">
					<uv-icon name="server-fill" color="#fff" size="22"></uv-icon>
				</view>
				<navigator url="/pages_manage/index/index" class="manage">
					<uv-icon name="setting-fill" color="#fff" size="22" style="display: inline-block;"></uv-icon>
					后台管理
				</navigator>
			</view>
			<!-- 店铺信息栏 -->
			<view class="body" :class="systemStore.foldState?'fold':''"
				:style="{height:systemStore.bodyBarHeight+'px'}">
				<view class="brand">
					<!-- 左边店铺图片 -->
					<view class="pic">
						<image class="img" src="/static/logo.png" mode="aspectFill"></image>
					</view>
					<!-- 右侧文字信息 -->
					<view class="text">
						<!-- 上面店铺名称 -->
						<view class="title">
							<text class="font">店铺名称</text>
							<uv-icon name="more-circle" color="#fff" size="22"></uv-icon>
						</view>
						<!-- 下面店铺摘要 -->
						<view class="des">
							店铺信息摘要
						</view>
					</view>
				</view>
				<view class="code">
					<view class="pic">
						<image class="img" src="/static/images/qrcode.png" mode="aspectFill"></image>
					</view>
					<text class="pay">付款</text>
				</view>
			</view>
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import useSystem from "../../store/system.js"

	const systemStore = useSystem()

	let props = defineProps({
		foldState: {
			type: Boolean
		}
	})
</script>

<style lang="scss" scoped>
	.customHead {
		// height: 400rpx;
		overflow: hidden;
		position: relative;
		transition: 0.3s;

		.bg {
			width: 100%;
			height: 100%;
			background: #000;

			.bgimg {
				width: 100%;
				height: 100%;
				filter: blur(30rpx);
				transform: scale(2);
			}
		}

		.container {
			position: absolute;
			top: 0;
			left: 0;
			width: 100%;

			.statusBar {}

			.service {
				padding-left: 30rpx;
				@include flex-box-set(start);
				color: #fff;

				.kefu {
					position: relative;
					padding: 0 20rpx;

					.btn {
						position: absolute;
						top: 0;
						left: 0;
						opacity: 0;
						width: 80rpx;
						height: 50rpx;
					}
				}

				.kefuHover {
					transform: scale(0.9);
				}

				.manage {
					margin-left: 20rpx;
					@include flex-box-set(start);
					align-items: center;
					justify-content: center;
				}
			}

			.body {
				@include flex-box();
				padding: 0 45rpx;
				// height: 100px;
				// border: 1px solid red;
				transition: 0.3s;

				.brand {
					width: 580rpx;
					@include flex-box-set(start);

					.pic {
						width: 110rpx;
						height: 110rpx;
						border-radius: 50%;
						overflow: hidden;
						transition: 0.3s;

						.img {
							width: 100%;
							height: 100%;
						}
					}

					.text {
						flex: 1;
						padding: 0 30rpx;
						color: #fff;

						.title {
							font-size: 36rpx;
							font-weight: 800;
							display: flex;
							align-items: center;

							.font {
								margin-right: 10rpx;
							}
						}

						.des {
							font-size: 26rpx;
							width: 100%;
							opacity: 0.8;
							padding-top: 5rpx;
							@include ellipsis()
						}
					}
				}

				.code {
					width: 80rpx;
					height: 80rpx;
					border-left: 1px solid rgba(255, 255, 255, 0.6);
					@include flex-box-set(between);
					flex-direction: column;

					.pic {
						width: 40rpx;
						height: 40rpx;

						.img {
							width: 100%;
							height: 100%;
						}
					}

					.pay {
						font-size: 22rpx;
						color: #fff;
						text-align: center;
					}
				}

				&.fold {
					padding: 0 30rpx;

					.brand {
						.pic {
							width: 60rpx;
							height: 60rpx;
						}

						.text {
							padding-left: 15rpx;

							.title {
								font-size: 28rpx;

								.icon {
									transform: scale(0.9);
								}
							}

							.des {
								display: none;
							}
						}

					}

					.code {
						display: none;
					}
				}

			}

		}

	}

	.brandWrapper {
		padding: 30rpx;
		border-radius: 20rpx 20rpx 0 0;
		background: #fff;
		@include flex-box();
		flex-direction: column;

		.close {
			background: $page-bg-color;
			padding: 5rpx 20rpx;
			border-radius: 30rpx;
		}

		.brand {
			@include flex-box();
			flex-direction: column;
			padding: 30rpx 0;

			.pic {
				width: 100rpx;
				height: 100rpx;
				border-radius: 50%;
				overflow: hidden;

				.img {
					width: 100%;
					height: 100%;
				}
			}

			.title {
				font-size: 34rpx;
				color: $text-font-color-1;
				padding: 10rpx 0;
			}

			.des {
				font-size: 28rpx;
				color: $text-font-color-2;
			}

		}

		.cell {
			width: 100%;
			padding: 30rpx 0 100rpx;
		}
	}

	.brandLayout {
		.noBrand {
			background: linear-gradient(45deg, #9C9EFE, #6FCF97);
			height: 220rpx;
			@include flex-box-set();
			flex-direction: column;
			color: #fff;

			.text {
				padding-bottom: 10rpx;
			}

			.btnGroup {
				@include flex-box-set();
			}
		}
	}
</style>