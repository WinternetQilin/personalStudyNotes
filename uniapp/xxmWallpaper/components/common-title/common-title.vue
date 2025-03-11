<template>
	<view class="container">
		<view class="left">
			<slot name="left"></slot>
		</view>
		<view class="right">
			<slot name="right"></slot>
		</view>
	</view>
</template>

<script setup>
	
</script>

<style lang="scss" scoped>
.container{
	display: flex;
	justify-content: space-between;
	align-items: center;
	padding: 0 30rpx;
	.left{
		font-size: 38rpx;
	}
	.right{
		display: flex;
		font-size: 28rpx;
		color: #999;
		align-items: center;
	}
}
</style>