<template>
	<view class="home">
		<!-- 顶部商店信息栏 -->
		<custom-topBar id="customTopBar" :foldState="foldState"></custom-topBar>
		<!-- 菜单和底部操作栏 -->
		<view class="wrapper">
			<!-- 配送信息弹窗和订单弹窗 -->
			<view class="infoModel">
				<view class="left">
					免费配送
				</view>
				<navigator url="/pages/order/order" class="right">
					<uv-icon name="order" color="#576b95" size="22"></uv-icon>
					我的订单
				</navigator>
			</view>
			<!-- 整体滑动区域 -->
			<view class="scrollLayout">
				<!-- 左半边菜单 -->
				<view class="leftScroll">
					<scroll-view :scroll-top="leftScrollValue" scroll-y class="sContent">
						<view class="navItem" :class="index==navIdx?'active':''" v-for="(i,index) in dataList"
							:key="i.id" @click="clickNav(index)">{{i.name}}</view>
					</scroll-view>
				</view>

				<!-- 右半边商品列表 -->
				<view class="rightScroll">
					<navigator url="/pages/search/search" class="searchView">
						<uv-icon name="search" size="22" color="#576b95"></uv-icon>
						<text>搜索</text>
					</navigator>
					<scroll-view @scroll="rightScrollEnt" :scroll-top="rightScrollValue" scroll-with-animation scroll-y
						class="sContent">
						<!-- 每一个模块 -->
						<view class="productView" v-for="i in dataList" :key="i.id">
							<!-- 模块标题 -->
							<uv-sticky customNavHeight="0" zIndex="2">
								<view class="proTitle">{{i.name}}</view>
							</uv-sticky>
							<!-- 模块里的items -->
							<view class="proContent">
								<!-- 每一个item选项 -->
								<view class="proitem" v-for="ii in i.children" :key="ii.id">
									<product-item :item="ii"></product-item>
								</view>
							</view>
						</view>
					</scroll-view>
				</view>
			</view>
			<!--  -->
		</view>
		<!-- 购物车 -->
		<car-layout v-if="carStore.buyNum>0"></car-layout>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		onReady
	} from '@dcloudio/uni-app'
	import useSystem from "../../store/system.js"
	import useCar from '../../store/car.js';

	const systemStore = useSystem()
	const carStore = useCar()

	let navIdx = ref(0)
	let rightScrollValue = ref(0)
	let leftScrollValue = ref(0)
	let leftHitArr = ref([])
	let rightHitArr = ref([])
	let foldState = ref(false) //顶部信息栏折叠状态

	let dataList = ref([{
		id: 1,
		name: "豆干制品",
		children: [{
			id: 11,
			name: "卫龙辣条",
			price: 10,
			before_price: 22,
			thumb: "https://mp-c422c6b7-799d-4ff5-9531-5051a0481131.cdn.bspapp.com/cloudstorage/83562e26-cfac-4cec-8f51-9ae6986942af.jpg",
			numvalue: 0
		}, {
			id: 12,
			name: "卫龙大面筋",
			price: 5,
			before_price: 12,
			thumb: "https://mp-c422c6b7-799d-4ff5-9531-5051a0481131.cdn.bspapp.com/cloudstorage/30569d48-bb94-40de-8d2b-a3be99d710cd.jpg",
			numvalue: 0
		}]
	}, {
		id: 2,
		name: "饼干糕点",
		children: [{
			id: 21,
			name: "丹麦曲奇",
			price: 25,
			before_price: 36,
			thumb: "https://mp-3309c116-4743-47d6-9979-462d2edf878c.cdn.bspapp.com/cloudstorage/6758e11c-949b-48c5-ae69-ddad030c2f94.png",
			numvalue: 0
		}]
	}, {
		id: 3,
		name: "酒水饮料",
		children: [{
			id: 31,
			name: "韩国烧酒",
			price: 18,
			before_price: 29,
			thumb: "https://mp-3309c116-4743-47d6-9979-462d2edf878c.cdn.bspapp.com/cloudstorage/b1a12bee-0602-4cb5-927d-b2b246700e89.jpeg",
			numvalue: 0
		}]
	}])


	// 在页面渲染好后，获取右侧滚动条中每条内容的高度
	onReady(() => {
		getHeightArr()
	})

	// 点击左侧菜单栏事件
	function clickNav(index) {
		// 防抖，防止来回点击
		if (navIdx.value == index) return
		let timeout;
		if (timeout) {
			clearTimeout(timeout)
		}

		timeout = setTimeout(() => {
			//设置导航栏选中
			navIdx.value = index
			//设置右侧滚动条位置
			rightScrollValue.value = rightHitArr.value[index]
			// 设置左侧滚动条位置(让选中的选项自动滚动到第一个)
			leftScrollValue.value = leftHitArr.value[index]
		}, 100)


	}
	//获取右侧滚动条内容的高度
	function getHeightArr() {
		let selectQuery = uni.createSelectorQuery()
		let customTopBarHeight = 0

		// 获取顶部自定义导航栏高度
		selectQuery.select("#customTopBar").boundingClientRect(rect => {
			customTopBarHeight = rect.height
		}).exec()

		// 左侧滚动区域节点组
		selectQuery.selectAll(".navItem").boundingClientRect(rects => {
			// console.log(rects)
			leftHitArr.value = rects.map(item => {
				return item.top - customTopBarHeight - 50 + 10
			})
		}).exec()
		// console.log(leftHitArr.value)
		// 右侧滚动区域节点组
		selectQuery.selectAll(".productView").boundingClientRect(rects => {
			// console.log(rects)
			rightHitArr.value = rects.map(item => {
				return item.top - customTopBarHeight - 50 + 10
			})
		}).exec()
		// console.log(rightHitArr.value)
	}
	// 右侧滚动条滚动事件
	function rightScrollEnt(e) {
		// 向上取整，避免H5页面滚动条误差
		let scrollTop = Math.ceil(e.detail.scrollTop)
		// 判断目前的高度属于哪个模块的idx
		let idx = rightHitArr.value.findIndex((item, index, arr) => {
			return scrollTop >= item && scrollTop < arr[index + 1]
		})
		navIdx.value = idx
		leftScrollValue.value = leftHitArr.value[idx]
		// 如果滚动高度大于某个值，就折叠顶部导航栏
		if (scrollTop > 400) {
			systemStore.setFoldState(true)
			// foldState.value = true
		} else {
			systemStore.setFoldState(false)
			// foldState.value = false
		}
	}
</script>

<style lang="scss" scoped>
	.home {
		height: 100vh;
		display: flex;
		flex-direction: column;

		.wrapper {
			flex: 1;
			background: #fff;
			border-radius: 10px 10px 0 0;
			margin-top: -10px;
			position: relative;
			z-index: 2;
			overflow: hidden;

			.infoModel {
				color: $text-font-color-1;
				@include flex-box();
				height: 50px;
				background: #fff;
				padding: 0 30rpx;
				font-size: 32rpx;
				border-bottom: 1px solid $border-color;

				.right {
					@include flex-box();
					color: $brand-theme-color-aux;
				}
			}

			.scrollLayout {
				height: calc(100% - 100rpx);
				@include flex-box();
				// background-color: #bfa;



				.leftScroll {
					height: 100%;
					width: 190rpx;
					border-right: 1rpx solid $border-color;
					background: $page-bg-color;

					.navItem {
						font-size: 30rpx;
						padding-left: 30rpx;
						line-height: 100rpx;
						color: $text-font-color-2;
						position: relative;

						&.active {
							color: $text-font-color-1;
							background: #fff;

							&::after {
								content: "";
								width: 6rpx;
								height: 30rpx;
								background: $brand-theme-color;
								position: absolute;
								left: 0;
								top: 50%;
								transform: translateY(-50%);
							}
						}


					}
				}

				.rightScroll {
					height: 100%;
					flex: 1;
					position: relative;

					.searchView {
						position: absolute;
						top: 0;
						right: 30rpx;
						z-index: 3;
						@include flex-box-set();
						height: 90rpx;
						color: $brand-theme-color-aux;
					}

					.productView {
						padding: 0 30rpx;

						.proTitle {
							line-height: 90rpx;
							font-size: 30rpx;
							background: #fff;
						}
					}

				}

				.sContent {
					height: 100%;
				}
			}

		}

	}
</style>