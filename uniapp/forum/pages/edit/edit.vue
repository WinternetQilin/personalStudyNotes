<template>
	<view class="edit">
		<view class="title">
			<input type="text" v-model="articleObj.title" placeholder="请输入完整的标题" placeholder-class="placeholderClass">
		</view>
		<view class="content">
			<editor class="myEdit" placeholder="写点什么吧~~" show-img-size show-img-toolbar show-img-resize
				@focus="onEditFocus" @ready="onEditReady" @statuschange="onStatuschange"></editor>
		</view>
		<view class="btnGroup">
			<uv-button type="primary" @click="getContents" text="确认发表"
				:disabled="!articleObj.title.length "></uv-button>
		</view>
		<view class="tools">
			<view class="item" @click="onClickHead"><text class="iconfont icon-zitibiaoti"
					:class="headShow ? 'active':''"></text> </view>

			<view class="item" @click="onBold"><text class="iconfont icon-zitijiacu"
					:class="boldShow ? 'active':''"></text> </view>

			<view class="item" @click="onItalic"><text class="iconfont icon-zitixieti"
					:class="italiShow ? 'active':''"></text> </view>

			<view class="item" @click="insertDivider"><text class="iconfont icon-fengexian"></text> </view>

			<view class="item" @click="insertImage"><text class="iconfont icon-charutupian"></text> </view>

			<!-- <view class="item"><text class="iconfont icon-duigou_kuai"></text> </view> -->
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue'
	import {
		getImgSrc,
		getProvince
	} from "@/utils/tools.js"
	import {
		onLoad
	} from "@dcloudio/uni-app"
	const forumCloudObj = uniCloud.importObject("forumCloudObj")

	let db = uniCloud.database()
	// let toolShow = ref(false)
	let editorCtx = ref(null)
	let headShow = ref(false)
	let boldShow = ref(false)
	let italiShow = ref(false)
	//存储文章信息
	let articleObj = ref({
		title: '',
		content: '',
		description: '',
		picUrls: [],
		province: ''
	})

	onLoad(async () => {
		articleObj.value.province = await getProvince()
	})



	//editor内容（样式）状态改变时
	function checkStatus(obj, detail, name) {
		if (detail.hasOwnProperty(name)) {
			obj.value = true
		} else {
			obj.value = false
		}
	}

	function onStatuschange(e) {
		console.log(e.detail)
		checkStatus(headShow, e.detail, 'header')
		checkStatus(boldShow, e.detail, 'bold')
		checkStatus(italiShow, e.detail, 'italic')
	}

	//点击发表按钮时
	async function getContents() {
		editorCtx.value.getContents({
			success: async (res) => {
				articleObj.value.content = res.html
				articleObj.value.description = res.text.slice(0, 50)
				articleObj.value.picUrls = getImgSrc(res.html)

				uni.showLoading({
					title: '发布中',
				})
				let dbres = null
				try {
					dbres = await forumCloudObj.createArticle(articleObj.value)
				} catch (e) {
					uni.showModal({
						title: '发布失败',
						content: e.errMsg,
						showCancel: false
					})
					return
				}
				console.log(res)
				uni.hideLoading()
				uni.showToast({
					title: '发布成功',
					icon: 'success'
				})
				setTimeout(() => {
					uni.reLaunch({
						url: '/pages/index/index'
					})
				}, 1500)

			}
		})
	}

	// ======================================

	//标题样式
	function onClickHead() {
		headShow.value = !headShow.value
		editorCtx.value.format('header', headShow.value ? 'H2' : false)

	}

	//加粗
	function onBold() {
		boldShow.value = !boldShow.value
		// editorCtx.value.format('bold', boldShow.value ? 'bold' : false)
		editorCtx.value.format('bold')
	}

	//斜体
	function onItalic() {
		italiShow.value = !italiShow.value
		editorCtx.value.format('italic', italiShow.value ? 'italic' : false)
	}

	//添加分割线
	function insertDivider() {
		editorCtx.value.insertDivider()
	}

	//添加图片
	function insertImage() {
		uni.chooseImage({
			success: async (res) => {
				// console.log(res.tempFiles)
				uni.showLoading({
					title: '上传中',
					mask: true
				})
				for (let f of res.tempFiles) {
					let res = null
					try {
						res = await uniCloud.uploadFile({
							filePath: f.path,
							cloudPath: f.name
						})
					} catch (e) {
						uni.showToast({
							title: '上传失败',
							icon: 'error'
						})
					}
					editorCtx.value.insertImage({
						src: res.fileID
					})
				}
				uni.hideLoading()
				uni.showToast({
					title: '上传成功',
					icon: 'success'
				})
			}
		})
	}

	function onEditFocus() {
		// toolShow.value = true
	}

	function onEditReady() {
		//获取上下文
		uni.createSelectorQuery().in(this).select('.myEdit').fields({
			size: true,
			context: true
		}, res => {
			// console.log(res)
			editorCtx.value = res.context;
		}).exec()
	}
</script>

<style lang="scss" scoped>
	.myEdit ::v-deep .ql-blank::before {
		font-style: normal;
		color: #e0e0e0;
	}


	.edit {
		padding: 30rpx;

		.title {
			input {
				height: 120rpx;
				font-size: 46rpx;
				border-bottom: 1px solid #e4e4e4;
				margin-bottom: 30rpx;
				color: #000;
			}

			.placeholderClass {
				color: #e0e0e0;
			}
		}

		.content {
			.myEdit {
				height: calc(100vh - 500rpx);
				margin-bottom: 30rpx;
			}
		}

		.tools {
			width: 100%;
			height: 80rpx;
			background: #fff;
			border-top: 1rpx solid #f4f4f4;
			position: fixed;
			left: 0;
			bottom: 0;
			display: flex;
			justify-content: space-around;
			align-items: center;

			.iconfont {
				font-size: 36rpx;
				color: #333;

				&.active {
					color: #0199FE;
				}
			}
		}
	}
</style>