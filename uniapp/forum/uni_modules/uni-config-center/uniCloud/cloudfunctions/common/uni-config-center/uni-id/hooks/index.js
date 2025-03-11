function beforeRegister({
	userRecord,
	clientInfo
} = {}) {
	if (!userRecord.nickmame) {
		userRecord.nickmame = "默认名称" + Math.random().toString(36).substr(2, 6)
	}
	return userRecord // 务必返回处理后的userRecord
}

module.exports = {
	beforeRegister
}