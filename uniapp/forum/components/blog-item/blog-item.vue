<template>
	<view class="blogitem">
		<view class="head">
			<view class="userinfo">
				<view class="avatar">
					<image :src="getAvatar(articleItem)" mode="aspectFill">
					</image>
				</view>
				<view class="name">{{getNickName(articleItem)}}</view>
				<view class="time">
					<uni-dateformat :date="articleItem.publish_date" format="MM月dd hh:mm"
						:threshold="[60000,3600000*24*30]"></uni-dateformat>
				</view>
			</view>

			<view class="more" @click="onClickActionSheet">
				<text class="iconfont icon-ellipsis"></text>
			</view>
		</view>

		<view class="body">
			<view class="title" @click="onClickToDetail">{{articleItem.title}}</view>
			<view class="text" @click="onClickToDetail" v-if="articleItem.description">
				<view class="t">{{articleItem.description}}</view>
			</view>
			<view class="piclist" v-if="articleItem.picUrls.length">
				<view class="pic" :class="articleItem.picUrls.length==1 ? 'only': ''"
					v-for="(pic,index) in articleItem.picUrls" :key="index">
					<image @click="onClickImg(index)" :src="pic" mode="aspectFill"></image>
				</view>
			</view>
		</view>

		<view class="info">
			<view class="box"><text class="iconfont icon-a-27-liulan"></text>
				<text>{{articleItem.view_count?articleItem.view_count:"抢首览"}}</text>
			</view>
			<view class="box"><text class="iconfont icon-a-5-xinxi"></text>
				<text>{{articleItem.comment_count?articleItem.comment_count:"抢首评"}}</text>
			</view>
			<view class="box" @click="onClickLike"><text class="iconfont icon-a-106-xihuan "
					:class="articleItem.isLike?'active':''"></text>
				<text>{{articleItem.like_count?articleItem.like_count:"抢首攒"}}</text>
			</view>
		</view>

		<uv-action-sheet class="test" ref="actionSheet" :actions="actionList" :closeOnClickOverlay="true"
			:safeAreaInsetBottom="true" @select="onSheetSelect" @close="onSheetClose">
		</uv-action-sheet>

	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		getNickName,
		getAvatar
	} from '@/utils/tools.js'
	import {
		store
	} from '@/uni_modules/uni-id-pages/common/store.js'
	const forumCloudObj = uniCloud.importObject("forumCloudObj")
	let props = defineProps({
		articleItem: {
			type: Object
		}
	})
	let actionSheet = ref(null)
	let actionList = ref([{
			name: '修改',
			type: 'edit',
			disabled: true
		}, {
			name: '删除',
			type: 'delete',
			color: 'red',
			disabled: true
		},
		{
			name: '填充'
		}
	])

	function onClickActionSheet() {
		let uid = uniCloud.getCurrentUserInfo().uid
		if (uid == props.articleItem.user_id[0]._id) {
			actionList.value[0].disabled = false
			actionList.value[1].disabled = false
		}
		for (let role of uniCloud.getCurrentUserInfo().role) {
			if (role == 'admin' || role == 'webMaster') {
				actionList.value[0].disabled = false
				actionList.value[1].disabled = false
			}
		}
		actionSheet.value.open()
	}

	function onSheetSelect(e) {
		console.log(e.type)
		if (e.type == 'edit') {

		} else if (e.type == 'delete') {
			uni.showModal({
				title: '提示',
				content: '确定删除吗？',
				success: async function(res) {
					if (res.confirm) {
						forumCloudObj.deleteArticle(props.articleItem._id)
						uni.reLaunch({
							url: '/pages/index/index'
						})
					}
				}
			})
		}
	}

	function onSheetClose() {}

	// console.log(props.articleItem)
	function onClickImg(index) {
		uni.previewImage({
			urls: props.articleItem.picUrls,
			current: index
		})
	}
	//在文章列表中点击喜欢
	let isClickedLike = false
	async function onClickLike() {
		// console.log(props.articleItem)
		// console.log("props.articleItem._id", props.articleItem._id)
		// console.log(" props.articleItem.user_id[0]._id", props.articleItem.user_id[0]._id)

		//检查一下有没有登录
		if (!store.hasLogin) {
			uni.navigateTo({
				url: '/uni_modules/uni-id-pages/pages/login/login-withpwd'
			})
			return
		}

		if (isClickedLike) {
			return
		}
		isClickedLike = true
		props.articleItem.isLike = await forumCloudObj.likeArticle(props.articleItem._id, uniCloud.getCurrentUserInfo()
			.uid)
		console.log(props.articleItem.isLike)
		if (props.articleItem.isLike) {
			// 点赞成功 点赞次数+1
			forumCloudObj.operation("forum_article", "like_count", props.articleItem._id, 1)
			props.articleItem.like_count++
			uni.showToast({
				title: '点赞成功',
				icon: 'success'
			})
		} else {
			forumCloudObj.operation("forum_article", "like_count", props.articleItem._id, -1)
			props.articleItem.like_count--
			uni.showToast({
				title: '已取消',
				icon: 'none'
			})
		}
		isClickedLike = false
	}

	// 点击文章跳转到详情页
	function onClickToDetail() {
		uni.navigateTo({
			url: '/pages/detail/detail?id=' + props.articleItem._id
		})
	}
</script>

<style lang="scss" scoped>
	.blogitem {
		.head {
			display: flex;
			font-size: 32rpx;
			align-items: center;
			justify-content: space-between;

			.userinfo {
				display: flex;
				align-items: center;

				.avatar {
					width: 40rpx;
					height: 40rpx;
					border-radius: 50%;
					border-radius: 50%;
					overflow: hidden;

					image {
						width: 100%;
						height: 100%;
						display: block;
					}
				}

				.name {
					color: #222;
					padding-left: 10rpx;
				}

				.time {
					color: #888;
					font-size: 22rpx;
					padding-left: 20rpx;
				}
			}

			.more {
				padding: 5rpx;

				.iconfont {
					font-size: 50rpx;
					color: #888;
				}
			}
		}



		.body {
			padding: 15rpx 0 30rpx;

			.title {
				font-size: 44rpx;
				color: #000;
				font-weight: 600;
				text-align: justify;
			}

			.text {
				padding-top: 10rpx;
				padding-bottom: 10rpx;
				font-size: 30rpx;
				text-align: justify;
				color: #888;

				.t {
					text-overflow: -o-ellipsis-lastline;
					overflow: hidden;
					text-overflow: ellipsis;
					display: -webkit-box;
					-webkit-line-clamp: 2;
					line-clamp: 2;
					-webkit-box-orient: vertical;
				}
			}

			.piclist {
				display: flex;
				padding-top: 20rpx;

				.pic {
					width: 225rpx;
					height: 225rpx;
					margin-right: 6rpx;
					overflow: hidden;

					image {
						width: 100%;
						height: 100%;
					}

					&:first-child {
						border-radius: 20rpx 0 0 20rpx;
					}

					&:last-child {
						border-radius: 0 20rpx 20rpx 0;
					}

					&.only {
						border-radius: 20rpx;
					}

				}

			}
		}




		.info {
			display: flex;
			align-items: center;
			justify-content: space-around;
			font-size: 26rpx;
			color: #333;

			.box {
				display: flex;
				align-items: center;
				padding: 15rpx 0 5rpx;
				flex: 1;
				display: flex;
				justify-content: center;

				.iconfont {
					font-size: 40rpx;
					padding-right: 10rpx;
				}
			}

			.box .active {
				color: #0199fe;
			}

		}


	}
</style>