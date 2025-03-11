<template>
	<view class="pronumbox">
		<uv-number-box v-model="props.item.numvalue" @change="numChange" min="0" max="99">
			<template v-slot:minus>
				<view class="minus numbtn" :class="props.item.numvalue<=0?'none':''">
					<uv-icon name="minus" size="12" color="#ccc"></uv-icon>
				</view>
			</template>
			<template v-slot:input>
				<text class="input" :class="props.item.numvalue<=0?'none':''">
					{{props.item.numvalue}}
				</text>
			</template>
			<template v-slot:plus>
				<view class="plus numbtn">
					<uv-icon name="plus" color="#FFFFFF" size="12"></uv-icon>
				</view>
			</template>
		</uv-number-box>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import useCar from '../../store/car';

	const car = useCar()

	let props = defineProps({
		// 商品信息
		item: {
			type: Object,
			default: () => ({})
		}
	})

	// let value = props.item.num || ref(0)

	function numChange(e) {
		console.log(e)
		car.setCarList({
			item: props.item,
			num: e.value
		})
		console.log(props.item.numvalue)
	}
</script>

<style lang="scss" scoped>
	.pronumbox {
		.numbtn {
			width: 40rpx;
			height: 40rpx;
			@include flex-box-set();
		}

		.minus {
			border: 1px solid #ccc;
		}

		.plus {
			background: $brand-theme-color;
		}

		.input {
			width: 60rpx;
			height: 40rpx;
			font-size: 26rpx;
			color: #888;
			@include flex-box-set();
		}

		.none {
			display: none;
		}
	}
</style>