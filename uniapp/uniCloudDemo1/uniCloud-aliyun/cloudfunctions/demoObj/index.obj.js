const db = uniCloud.database();
module.exports = {
	_before: function() { // 通用预处理器

	},
	async getClassify() {
		return await db.collection("demo-classify").get()
	}
}