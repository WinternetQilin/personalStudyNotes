<template>
	<view class="layout">
		<view class="list">
			<view class="item" v-for="(item,index) in blogList" :key="index">
				<view class="userinfo">
					<view class="avatar">
						<image class="pic" src="../../static/defAvatar.png" mode="aspectFill"></image>
					</view>
					<view class="username">{{item.user_id[0].nickname}}</view>
				</view>
				<view class="body">
					<view class="text">
						<view class="font">{{item.content}}</view>
					</view>
					<view class="piclist" v-if="item.pics.length">
						<view class="pic" v-for="(pic,index) in item.pics" :key="index">
							<image :src="pic.url" mode="aspectFill"></image>
						</view>
					</view>
				</view>


				<view class="info">
					<view class="left">
						<uni-dateformat :date="item.publish_date" :threshold="[60000,3600000*24*30]"></uni-dateformat>
					</view>
					<view class="right">
						<view class="remove" v-if="isPermission(item.user_id[0]._id)" @click="onClickRemoveBtn">
							<uni-icons type="trash-filled" size="16" color="#999"></uni-icons>删除
						</view>
					</view>
				</view>

			</view>
		</view>


		<uni-fab ref="fab" :pattern="{icon:'compose'}" horizontal="right" vertical="bottom" @fabClick="goAdd" />
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	const blogCloudObj = uniCloud.importObject("blogCloudObj");
	import {
		isPermission
	} from '@/utils/common.js'
	let blogList = ref([])

	const goAdd = () => {
		uni.navigateTo({
			url: "/pages/blog/edit"
		})
	}

	function onClickRemoveBtn() {
		uni.showModal({
			title: '提示',
			content: '确定要删除吗？',
			success: function(res) {
				if (res.confirm) {

				}
			}
		})
	}

	async function getBlogList() {
		let {
			errCode,
			errMsg,
			data
		} = await blogCloudObj.list()
		if (errCode == 0) {
			blogList.value = data
		} else {
			uni.showToast({
				title: errMsg,
				icon: 'error'
			})
		}

		console.log(data)
	}
	getBlogList()
</script>

<style lang="scss" scoped>
	.layout {
		.list {
			.item {
				padding: 40rpx 30rpx;
				border-bottom: 10px solid #f4f4f4;

				.userinfo {
					display: flex;
					align-items: center;
					border-bottom: 1px solid #f4f4f4;
					padding-bottom: 30rpx;

					.avatar {
						width: 50rpx;
						height: 50rpx;
						border-radius: 50%;
						overflow: hidden;
						margin-right: 10rpx;

						.pic {
							width: 100%;
							height: 100%;
						}
					}

					.username {
						font-size: 28rpx;
						color: #333;
					}
				}

				.body {
					padding: 15rpx 0 30rpx;

					.text {
						padding-bottom: 10rpx;
						font-size: 40rpx;
						text-align: justify;
						color: #111;
						line-height: 1.7em;

						.font {
							text-overflow: -o-ellipsis-lastline;
							overflow: hidden;
							text-overflow: ellipsis;
							display: -webkit-box;
							-webkit-line-clamp: 2;
							line-clamp: 2;
							-webkit-box-orient: vertical;
							width: 100%;
							word-break: break-all;
						}
					}

					.piclist {
						display: grid;
						grid-template-columns: repeat(3, 1fr);
						gap: 15rpx;
						padding-top: 20rpx;

						.pic {
							overflow: hidden;
							border-radius: 10rpx;
							aspect-ratio: 1 / 1;
							border-radius: 10rpx;

							image {
								width: 100%;
								height: 100%;
							}
						}

					}
				}


				.info {
					display: flex;
					align-items: center;
					justify-content: space-between;
					font-size: 28rpx;
					color: #999;

					.right {
						display: flex;
						align-items: center;

						.ipname {
							margin-right: 20rpx;
						}
					}
				}
			}
		}
	}
</style>