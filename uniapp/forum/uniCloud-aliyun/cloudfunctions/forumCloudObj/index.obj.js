const db = uniCloud.database()
const dbCmd = db.command
module.exports = {
	_before: function() { // 通用预处理器

	},
	// 新增一篇文章
	async createArticle(article = {}) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		return await dbJQL.collection("forum_article").add(article)
	},
	// 获取文章列表
	async getArticleList(type) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		let list = dbJQL.collection("forum_article").where(`delStatus != true`).field(
				"user_id,_id,view_count,like_count,comment_count,publish_date,title,description,picUrls")
			.getTemp()
		let user = dbJQL.collection("uni-id-users").field("_id,nickname,avatar_file,mobile").getTemp()
		return await dbJQL.collection(list, user).orderBy(type, "desc").get()
	},
	// 根据文档_id获取文章详情
	async getArticleDetail(id) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		let article = dbJQL.collection("forum_article").where({
				_id: id
			}).field(
				"user_id,_id,view_count,like_count,comment_count,publish_date,title,content,province")
			.getTemp()
		let user = dbJQL.collection("uni-id-users").field("_id,nickname,avatar_file").getTemp()
		return await dbJQL.collection(article, user).get({
			getOne: true
		})
	},
	// 自定义 自增减
	async operation(table, attr, id, num) {
		let obj = {}
		obj[attr] = dbCmd.inc(num)
		return await db.collection(table).doc(id).update(obj)
	},
	// 用户点赞操作
	async likeArticleStatus(articleId, userId) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		let count = await dbJQL.collection("forum_like").where(
			`article_id == '${articleId}' && user_id == '${userId}'`).count()
		if (count.total) {
			return true
		}
		return false
	},
	async likeArticle(articleId, userId) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		// 先去找一下有没有点赞过
		let count = await dbJQL.collection("forum_like").where(
			`article_id == '${articleId}' && user_id == '${userId}'`).count()

		if (count.total) {
			// 点赞过就删除点赞记录
			await dbJQL.collection("forum_like").where(`article_id == '${articleId}' && user_id == '${userId}'`)
				.remove()
			return false
		} else {
			// 没有点赞过就新增一条点赞记录
			await dbJQL.collection("forum_like").add({
				article_id: articleId
			})
			return true
		}
	},
	//删除文章
	async deleteArticle(id) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		await dbJQL.collection("forum_article").doc(id).update({
			delStatus: true
		})
	},
	//查询文章是否点过赞，返回uid点过赞的文章id数组
	async isArticleLike(idArr, uid) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})

		return await dbJQL.collection("forum_like").where({
			article_id: dbCmd.in(idArr),
			user_id: uid
		}).get()
	},
	//查询uid获赞数、评论数、文章数
	async getTotal() {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		let totalObj = {
			artNum: 0, //文章数
			likeNum: 0, //获赞数
			commentNum: 0 //评论数
		}

		totalObj.artNum = (await dbJQL.collection("forum_article").where(`user_id == $cloudEnv_uid`).count())
			.total

		totalObj.likeNum = (await dbJQL.collection("forum_article").where(`user_id == $cloudEnv_uid`).groupBy(
			'user_id').groupField(
			'sum(like_count) as likeSum').get()).data[0].likeSum

		return totalObj
	},
	//查询文章最新点赞的五个用户头像
	async getArticleLikedUserAvatars(artId) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})

		let likeTemp = dbJQL.collection("forum_like").where(`article_id == "${artId}"`).getTemp()

		let userTemp = dbJQL.collection("uni-id-users").field("_id,avatar_file").getTemp()

		return await dbJQL.collection(likeTemp, userTemp).orderBy("create_date", "desc").limit(5).get()

	},
	//新增一条评论
	async submitComment(type, artID, content, province) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})
		dbJQL.collection("forum_comment").add({
			"article_id": artID,
			"comment_content": content,
			"comment_type": type,
			province
		})
	},
	//获取指定文章id的评论
	async getComment(artID) {
		const dbJQL = uniCloud.databaseForJQL({
			clientInfo: this.getClientInfo()
		})

		let comment = dbJQL.collection("forum_comment").where(`article_id == "${artID}"`).orderBy(
			"comment_date desc").getTemp()
		let user = dbJQL.collection("uni-id-users").field("_id,avatar_file,nickname").getTemp()
		return await dbJQL.collection(comment, user).get()

	}

}