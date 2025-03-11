export function isPermission(_id) {
	const {
		uid
	} = uniCloud.getCurrentUserInfo()
	return uid == _id
}