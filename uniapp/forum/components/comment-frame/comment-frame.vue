<template>
	<view>
		<view class="commentFrame">
			<uni-easyinput ref="uipt" @confirm="goComment" suffixIcon="paperplane" v-model="replyContent"
				placeholder="评论点什么吧~" @iconClick="goComment">
			</uni-easyinput>
		</view>
	</view>
</template>

<script setup>
	import {
		ref
	} from 'vue';
	import {
		getProvince
	} from "@/utils/tools.js"
	const forumCloudObj = uniCloud.importObject("forumCloudObj")

	let props = defineProps({
		commentObj: {
			type: Object
		}
	})

	let replyContent = ref("")

	async function goComment() {
		if (!replyContent.value) {
			uni.showToast({
				title: "评论不能为空",
				icon: "none"
			})
			return;
		}
		//获取省份
		let province = await getProvince();

		//添加评论
		let res = await forumCloudObj.submitComment(props.commentObj.type, props.commentObj.article_id, replyContent
			.value, province)
		uni.showToast({
			title: "评论成功",
			icon: "success"
		})

		replyContent.value = ""
	}


	/* export default {
		name: "comment-frame",
		props: {
			commentObj: {
				type: Object,
				default: () => {
					return {

					}
				}
			},

		},
		data() {
			return {

			};
		},
		methods: {
			}
	} */
</script>

<style lang="scss" scoped>
	.commentFrame {
		width: 100%;
		background: #fff;
		padding: 20rpx 30rpx;
		box-sizing: border-box;
		position: fixed;
		bottom: 0;
		left: 0;
		z-index: 100;
	}
</style>