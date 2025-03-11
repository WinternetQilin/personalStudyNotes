<template>
	<view class="classifycontainer commonPageBg">
		<!-- 头部 -->
		<custom-nav-bar class="customNavBar" title="分类"></custom-nav-bar>
		<view class="classifyLayout">
			<theme-item v-for="item in themeList" :key="item._id" :item="item"></theme-item>
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue'
	import {
		apiGetThemeList
	} from "@/api/apis.js"

	let themeList = ref([])

	//获得专题分类
	async function getThemeList() {
		let temp = await apiGetThemeList({
			pageSize:16
		})
		themeList.value = temp.data
	}

	getThemeList()
</script>

<style lang="scss" scoped>
	.classifycontainer {
		.customNavBar {
			:deep() {
				.navBar {
					padding-left: 30rpx;
				}
			}
		}

		padding: 30rpx;

		.classifyLayout {
			// background-color: #bfa;
			display: grid;
			gap: 15rpx;
			grid-template-columns: repeat(3, 1fr);
		}
	}
</style>