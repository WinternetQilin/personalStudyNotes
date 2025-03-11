<template>
	<view class="detail" v-if="detail!={}">
		<view class="container">
			<view class="title">{{detail.title}}</view>
			<view class="userinfo">
				<view class="avatar" v-if="detail.user_id">
					<image :src="getAvatar(detail)" mode="aspectFill"></image>
				</view>
				<view class="text">
					<view class="name" v-if="detail.user_id">{{getNickName(detail)}}</view>
					<view class="small"><uni-dateformat :date="detail.publish_date"
							format="yyyy年MM月dd hh:mm"></uni-dateformat> · 发布于{{detail.province}}</view>
				</view>
			</view>
			<view class=" content">
				<uv-parse :content="detail.content"></uv-parse>
			</view>

			<view class="like" @click="onClickLike">
				<view class="btn" :class="likeStatus?'active':''">
					<text class="iconfont icon-good-fill"></text>
					<text>{{detail.like_count}}</text>
				</view>
				<view class="users">
					<template v-for="item in likeUserArr">
						<image :src="getAvatar(item)" mode="aspectFill"></image>
					</template>
				</view>
				<view class="text"><text class="num">{{detail.view_count+1}}</text>人看过</view>
			</view>

		</view>

		<view class="comment">
			<view v-if="!commentList.length">
				<uv-empty mode="comment" icon="https://cdn.uviewui.com/uview/empty/comment.png">
				</uv-empty>
			</view>

			<view class="content" v-if="commentList.length">
				<view class="item" v-for="item in commentList" :key="commentList._id">
					<comment-item :item="item"></comment-item>
				</view>
			</view>

		</view>

		<comment-frame :commentObj="commentObj"></comment-frame>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		onLoad
	} from "@dcloudio/uni-app"
	import {
		getNickName,
		getAvatar
	} from '@/utils/tools.js'
	const forumCloudObj = uniCloud.importObject("forumCloudObj", {
		customUI: true
	})

	let detail = ref({})
	let likeStatus = ref(false)
	let likeUserArr = ref([])
	let commentObj = {
		article_id: "",
		type: 0
	}
	let commentList = ref([])

	onLoad(async (e) => {
		if (!e.id) {
			errFunc()
		}
		// console.log(e)
		let res = null
		try {
			res = await forumCloudObj.getArticleDetail(e.id)
		} catch (e) {
			uni.showModal({
				title: '错误',
				content: e.errMsg,
				showCancel: false
			})
		}
		// console.log(res)
		if (!res.data) {
			errFunc()
		}
		detail.value = res.data
		commentObj.article_id = detail.value._id
		uni.setNavigationBarTitle({
			title: detail.value.title
		})
		//增加阅读量
		forumCloudObj.operation("forum_article", "view_count", detail.value._id, 1)
		//检查当前用户是否点过赞
		likeStatus.value = await forumCloudObj.likeArticleStatus(detail.value._id, detail.value.user_id[0]
			._id)

		//获取点赞用户
		getLikeUser()
		//获取评论
		res = await forumCloudObj.getComment(detail.value._id)
		commentList.value = res.data
		console.log(res.data)
	})
	//参数错误处理
	function errFunc() {
		uni.showToast({
			title: '参数有误',
			icon: 'error'
		})
		setTimeout(() => {
			uni.reLaunch({
				url: '/pages/index/index'
			})
		}, 1500)
	}

	// 点赞操作
	let clickTiming = false //防止频繁点击
	async function onClickLike() {
		if (clickTiming) {
			uni.showToast({
				title: '操作过于频繁',
				icon: 'none'
			})
			return
		}
		//优化操作-无感操作
		likeStatus.value ? detail.value.like_count-- : detail.value.like_count++
		likeStatus.value = !likeStatus.value

		clickTiming = true
		likeStatus.value = await forumCloudObj.likeArticle(detail.value._id, detail.value.user_id[0]._id)
		// console.log(res)
		if (likeStatus.value) {
			// 点赞成功 点赞次数+1
			forumCloudObj.operation("forum_article", "like_count", detail.value._id, 1)
		} else {
			forumCloudObj.operation("forum_article", "like_count", detail.value._id, -1)
		}
		clickTiming = false
	}

	//获取文章最新点赞的五个用户头像
	async function getLikeUser() {
		let res = await forumCloudObj.getArticleLikedUserAvatars(detail.value._id)
		// console.log(res)
		likeUserArr.value = res.data
		console.log(likeUserArr.value)
	}

	//获取文章的评论
</script>

<style lang="scss" scoped>
	.detail {
		background: #f8f8f8;
		min-height: calc(100vh - var(--window-top));

		.container {
			padding: 30rpx;
			background: #fff;

			.title {
				font-size: 46rpx;
				color: #333;
				line-height: 1.4em;
				font-weight: 600;
			}

			.userinfo {
				padding: 20rpx 0 50rpx;
				display: flex;
				align-items: center;

				.avatar {
					width: 60rpx;
					height: 60rpx;
					padding-right: 15rpx;

					image {
						width: 100%;
						height: 100%;
						border-radius: 50%;
					}
				}

				.text {
					font-size: 28rpx;
					color: #555;

					.small {
						font-size: 20rpx;
						color: #999;
					}
				}
			}

			.content {}

			.like {
				display: flex;
				flex-direction: column;
				align-items: center;
				padding: 80rpx 50rpx 50rpx;

				.btn {
					width: 260rpx;
					height: 120rpx;
					background: #e4e4e4;
					border-radius: 100rpx;
					color: #fff;
					display: flex;
					justify-content: center;
					align-items: center;
					flex-direction: column;
					font-size: 28rpx;

					.iconfont {
						font-size: 50rpx;
					}

					&.active {
						background: #0199FE;
					}
				}

				.text {
					font-size: 26rpx;
					color: #666;

					.num {
						color: #0199FE
					}

					.spot {
						padding: 0 10rpx;
					}
				}

				.users {
					display: flex;
					justify-content: center;
					padding: 30rpx 0;

					image {
						width: 50rpx;
						height: 50rpx;
						border-radius: 50%;
						border: 3px solid #fff;
						margin-left: -20rpx;
					}
				}
			}

		}

		.comment {
			padding: 30rpx;
			padding-bottom: 120rpx;

			.item {
				padding: 10rpx 0;
			}
		}

	}
</style>