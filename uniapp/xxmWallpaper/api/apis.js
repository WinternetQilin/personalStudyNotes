import {
	request
} from "@/utils/request.js"

export function apiGetBannerPics() {
	return request({
		url: "/homeBanner"
	})
}

export function apiGetRecommendPics() {
	return request({
		url: "/randomWall"
	})
}

export function apiGetNoticeList() {
	return request({
		url: "/wallNewsList"
	})
}

export function apiGetThemeList(data={}) {
	return request({
		url: "/classify",
		data
	})
}

export function apiGetClassifyPicList(data={}) {
	return request({
		url: "/wallList",
		data
	})
}

export function apiGetSetupScore(data={}) {
	return request({
		url: "/setupScore",
		data
	})
}

export function apiWriteDownload(data={}) {
	return request({
		url: "/downloadWall",
		data
	})
}

export function apiGetUserInfo(data={}) {
	return request({
		url: "/userInfo",
		data
	})
}

export function apiSearchData(data={}) {
	return request({
		url: "/searchWall",
		data
	})
}