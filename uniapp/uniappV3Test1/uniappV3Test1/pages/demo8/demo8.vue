<template>
	<view class="list">
		<checkbox-group name="cg1" @change="cbClicked">
			<view class="good" v-for="g in goods" :key="g.id">
				<checkbox :value="g.id.toString()"></checkbox>
				<text>{{g.name}}：</text>
				<text>{{g.price}}元</text>
				<navigator @click="onDelete(g.id)">删除</navigator>
			</view>
		</checkbox-group>
	</view>
	<view>选中{{selectedNum}}个产品，总计{{sumMoney}}元</view>
	<UserInfo></UserInfo>
</template>

<script setup>
	import {
		ref
	} from 'vue'

	let goods = ref([{
			id: 1,
			name: '商品1',
			price: 100
		},
		{
			id: 2,
			name: '商品2',
			price: 200
		},
		{
			id: 3,
			name: '商品3',
			price: 300
		},
		{
			id: 4,
			name: '商品4',
			price: 400
		},
		{
			id: 5,
			name: '商品5',
			price: 500
		},
		{
			id: 6,
			name: '商品6',
			price: 600
		}
	])
	let selectedNum = ref(0)
	let sumMoney = ref(0)

	function onDelete(id) {
		// console.log(id)
		goods.value.splice(goods.value.findIndex(g => g.id == id), 1)
	}

	function cbClicked(e) {
		console.log(e)
		let selectArr = e.detail.value
		selectedNum.value = selectArr.length
		let temp = 0;
		console.log("selectArr: "+selectArr)
		
		for (let i of selectArr) {
			// console.log("i: "+i)
			// 通过id拿到index
			let index = goods.value.findIndex(item => item.id == i)
			// 通过index拿到金额并加到temp
			temp += goods.value[index].price
		}
		sumMoney = temp
	}
</script>

<style lang="scss" scoped>
	.list {
		.good {
			margin-top: 5px;
			margin-bottom: 5px;
			border: 1px solid green;

			text {
				display: inline-block;
			}

			navigator {
				display: inline-block;
				margin-left: 5px;
				color: red;
			}
		}
	}
</style>