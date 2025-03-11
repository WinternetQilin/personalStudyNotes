const system = uni.getSystemInfoSync()
export const getStatusBarHeight = () => system.statusBarHeight || 30

export const getTitleBarHeight = () => {
	if (uni.getMenuButtonBoundingClientRect) {
		const {
			top,
			height
		} = uni.getMenuButtonBoundingClientRect()
		return (top - getStatusBarHeight()) * 2 + height
	} else {
		return 60
	}
}