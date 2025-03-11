<template>
	<view class="container">
		<view class="menu">
			<uni-segmented-control :current="menuItemsCur" :values="menuItems.map(item=>item.value)" @clickItem="onClickItem" styleType="button" activeColor="#4cd964"></uni-segmented-control>
		</view>
		<view class="layout">
			<view class="box" v-for="(item,index) in catPicArr" :key="item._id">
				<view class="pic">
					<image lazy-load mode="widthFix" :src="item.url" @click="onImgClicked(index)"></image>
				</view>
				<view class="text">{{item.content}}</view>
			</view>
			<uni-load-more status="loading"></uni-load-more>
		</view>
		
		<view class="floatTools">
			<view @click="onClickedRefresh">
				<uni-icons type="refreshempty" size="25" ></uni-icons>
			</view>
			<view @click="onClickedBackTop">
				<uni-icons type="arrow-up" size="25" ></uni-icons>
			</view>
		</view>
	</view>
</template>

<script setup>
	//菜单选项卡
	let menuItems=[{key:"all",value:"猫狗"},{key:"cat",value:"猫"},{key:"dog",value:"狗"}]
	let menuItemsCur = ref(0)
	uni.showLoading()
	let catPicArr = ref([])
	//get请求方法
	function getCatPic() {
		uni.request({
			url: "https://tea.qingnian8.com/tools/petShow",
			data: {
				size: 7,
				type:menuItems[menuItemsCur.value].key
			},
			header:{
				"access-key":"1261338615"
			}
		}).then(res => {
			console.log(res.data.data)
			if(res.data.errCode===0)
			{
				// catPicArr.value=res.data.data
				catPicArr.value = [...catPicArr.value,...res.data.data]
				
			}
			else if(res.data.errCode===400)
			{
				uni.showToast({
					title:res.data.errMsg,
					icon:"none"
				})
			}
			
		}).finally(()=>{
			uni.hideLoading()
			uni.stopPullDownRefresh()
		})
	}

	getCatPic()
	
	//触底刷新
	onReachBottom(()=>{
		getCatPic()
	})
	//下拉刷新
	onPullDownRefresh(()=>{
		catPicArr.value=[]
		getCatPic()
	})
	//点击刷新
	function onClickedRefresh()
	{
		uni.startPullDownRefresh()
	}
	//点击返回顶部
	function onClickedBackTop()
	{
		uni.pageScrollTo({
			scrollTop:0,
			duration:100
		})
	}
	//点击菜单选项
	function onClickItem(e)
	{
		console.log(e)
		menuItemsCur.value = e.currentIndex
		onClickedRefresh()
	}
	
	//点击图片放大预览
	function onImgClicked(idx)
	{
		let urls = catPicArr.value.map(item=>item.url)
		uni.previewImage({
			current:idx,
			urls
		})
	}
</script>

<style lang="scss" scoped>
	.container {
		.layout {
			padding-left: 50rpx;
			padding-right: 50rpx;

			.box {
				// background-color: #bfa;
				margin-bottom: 20rpx;

				.pic {
					image {
						width: 100%;
					}
				}

				.text {
					text-align: center;
				}
			}
		}
		
		.menu{
			margin-top: 10rpx;
			margin-bottom: 10rpx;
		}
		
		.floatTools{
			display: inline-block;
			position: fixed;
			right: 50rpx;
			bottom: 50rpx;
			padding-bottom: env(safe-area-inset-bottom);
			view{
				display: flex;
				justify-content: center;
				align-items: center;
				width: 60rpx;
				height: 60rpx;
				box-shadow: 5rpx 5rpx 7rpx #888888;
				margin-bottom: 20rpx;
				background-color: rgba(255, 255, 255, .7);
				border-radius: 50%;
			}
		}
	}
</style>