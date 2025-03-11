<template>
	<navigator :url="jumpUrl">
		<view class="optionItemContainer">
			<view class="left">
				<!-- <uni-icons type="download-filled" size="30" color="#28B38C"></uni-icons> -->
				<slot name="leftIcon"></slot>
				<view>{{optionName}}</view>
			</view>
			<view class="right">
				<view v-if="props.number!=-114514">{{props.number}}</view>
				<uni-icons type="arrowright" size="22" color="#999"></uni-icons>
			</view>
		</view>
	</navigator>
</template>

<script setup>
	let props = defineProps({
		optionName: {
			type: String,
			required: true
		},
		jumpUrl: {
			type: String
		},
		number: {
			type: Number,
			default: -114514
		}
	})

	function onClicked() {
		console.log("点击了")
	}
</script>

<style lang="scss" scoped>
	navigator {
		border-bottom: 1px solid #ccc;
	}

	.optionItemContainer {
		width: 100%;
		height: 100rpx;
		display: flex;
		justify-content: space-between;

		.left {
			// background-color: #bfa;
			display: flex;
			text-align: center;
			justify-content: center;
			align-items: center;
			color: gray;
			padding-left: 33rpx;

			view {
				margin-left: 24rpx;
			}
		}

		.right {
			// background-color: cadetblue;
			display: flex;
			text-align: center;
			justify-content: center;
			align-items: center;
			color: #999;
		}
	}
</style>