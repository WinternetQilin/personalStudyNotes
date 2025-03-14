const BASE_URL = 'https://tea.qingnian8.com/api/bizhi'
export function request(config = {}) {
	let {
		url,
		method = "GET",
		header = {},
		data = {}
	} = config
	header["access-key"] = "1261338615"
	return new Promise((resolve, reject) => {
		uni.request({
			url: BASE_URL + url,
			method,
			header,
			data,
			success: res => {
				if (res.data.errCode == 0) {
					resolve(res.data)
				} else if (res.data.errCode == 400) {
					uni.showModal({
						title: res.data.errMsg,
						showCancel: false
					})
					reject(res.data)
				} else {
					uni.showToast({
						title: res.data.errMsg,
						icon: "none"
					})
					reject(res.data)
				}
			},
			fail: err => {
				reject(err)
			}
		})
	})

}