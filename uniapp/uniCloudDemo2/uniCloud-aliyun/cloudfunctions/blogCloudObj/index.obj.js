module.exports = {
	_before: function() { // 通用预处理器

	},
	async add(params = {}) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		});
		return await dbJQL.collection("pro-blog").add(params)
	},
	async list() {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		});

		let blog = dbJQL.collection("pro-blog").getTemp()
		let user = dbJQL.collection("uni-id-users").field("_id,nickname").getTemp()
		return await dbJQL.collection(blog, user).orderBy("publish_date desc").get()
	}
}