<template>
	<view class="container">
		<navigator :url="'/pages/classifyList/classifyList?id='+item._id+'&name='+item.name" class="bgImg"
			v-if="!isMore">
			<image :src="item.picurl" mode="aspectFill"></image>
			<view class="maskText">{{item.name}}</view>
			<view class="timebar" v-if="compareTimestamp(item.updateTime)">· {{compareTimestamp(item.updateTime)}}前更新
			</view>
		</navigator>

		<navigator url="/pages/classify/classify" open-type="reLaunch" class="bgImg more" v-if="isMore">
			<image src="../../common/images/more.jpg" mode="aspectFill"></image>
			<view class="maskText">
				<uni-icons type="more-filled" size="36" color="#fff"></uni-icons>
				<view>更多</view>
			</view>
		</navigator>
	</view>
</template>

<script setup>
	import {
		compareTimestamp
	} from "@/utils/common.js"

	defineProps({
		isMore: {
			type: Boolean,
			default: false
		},
		item: {
			type: Object,
			default () {
				return {
					name: '分类名称',
					picurl: "../../common/images/classify1.jpg",
					updateTime: Date.now()
				}
			}
		}
	})
</script>

<style lang="scss" scoped>
	.container {
		width: 222rpx;
		height: 342rpx;
		// background-color: red;

		.bgImg {
			width: 100%;
			height: 100%;
			position: relative;
			border-radius: 20rpx;
			overflow: hidden;

			image {
				width: 100%;
				height: 100%;
				// border-radius: 20rpx;
			}

			.maskText {
				position: absolute;
				display: flex;
				justify-content: center;
				align-items: center;
				bottom: 0;
				width: 100%;
				height: 70rpx;
				background-color: rgba(0, 0, 0, .2);
				backdrop-filter: blur(20rpx);
				color: #fff;
				font-size: 30rpx;

			}

			.timebar {
				position: absolute;
				top: 0;
				left: 0;
				background-color: rgba(230, 150, 117, .7);
				backdrop-filter: blur(20rpx);
				padding: 7rpx 13rpx;
				border-radius: 0 0 20rpx 0;
				font-size: 18rpx;
				color: #fff;
				transform: scale(.8);
				transform-origin: left top;
			}
		}

		.bgImg.more {
			.maskText {
				height: 100%;
				// background-color: #bfa;
				flex-direction: column;
			}
		}
	}
</style>