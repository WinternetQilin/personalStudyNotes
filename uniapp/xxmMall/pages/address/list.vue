<template>
	<view class="selfAddress">
		<view class="headTop">
			<view class="title">地址簿</view>
			<navigator class="addressBtn" url="/pages/address/edit">
				+ 添加地址
			</navigator>
		</view>

		<view class="list" v-if="addressList.length">
			<view class="item" v-for="item in addressList" :key="item._id" @longpress="goUpdate(item._id)"
				@click="selectAddress(item)">
				<view class="head">
					<view class="user">{{item.username}},{{item.mobile}}</view>
					<view class="select">
						<uv-button v-if="item.selected" color="#EC544F" plain size="mini" text="默认地址"></uv-button>
						<uv-button color="#666" v-else plain size="mini" text="设为默认"
							@click="setDefault(item._id)"></uv-button>
					</view>
				</view>
				<view class="more">
					{{item.area_name+item.address}}
				</view>
			</view>
		</view>

		<view v-else>
			<uv-empty text="还未添加过地址" icon="http://cdn.uviewui.com/uview/empty/message.png">
			</uv-empty>
		</view>
	</view>
</template>

<script setup>
	async function getAddressData() {
		let res = await addressCloudObj.getList();
		this.addressList = res.data
	}
	//设置默认地址
	async function setDefault(id) {
		let res = await addressCloudObj.updateDef(id);
		this.getAddressData()
	}
	//跳转到修改页面
	function goUpdate(id) {
		uni.navigateTo({
			url: "./edit?id=" + id
		})
	}
	//用户选择地址
	function selectAddress(item) {
		let {
			address,
			area_name,
			username,
			mobile
		} = item;
		let deliveryData = {
			address: area_name + address,
			username,
			mobile
		}
		uni.$emit("selectAddressEvent", deliveryData)
		uni.navigateBack();
	}
</script>

<style lang="scss" scoped>
	page {
		background: $page-bg-color;
	}

	.selfAddress {
		padding: 30rpx;

		.headTop {
			@include flex-box();
			font-size: 30rpx;
			font-weight: bold;

			.addressBtn {
				border: 1px solid #000;
				border-radius: 50rpx;
				padding: 6rpx 15rpx;
			}
		}

		.list {
			padding-top: 30rpx;

			.item {
				background: #fff;
				padding: 40rpx 20rpx;
				margin-bottom: 30rpx;
				border-radius: 15rpx;

				.head {
					@include flex-box();
					font-weight: bold;
				}

				.more {
					font-size: 28rpx;
					color: $text-font-color-3;
					padding-top: 10rpx;
				}
			}
		}
	}
</style>