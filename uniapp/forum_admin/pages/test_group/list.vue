<template>
  <view>
    <view class="uni-header">
      <view class="uni-group">
        <view class="uni-title"></view>
        <view class="uni-sub-title"></view>
      </view>
      <view class="uni-group">
        <input class="uni-search" type="text" v-model="query" @confirm="search" placeholder="请输入搜索内容" />
        <button class="uni-button" type="default" size="mini" @click="search">搜索</button>
        <button class="uni-button" type="default" size="mini" @click="navigateTo('./add')">新增</button>
        <button class="uni-button" type="default" size="mini" :disabled="!selectedIndexs.length" @click="delTable">批量删除</button>
        <download-excel class="hide-on-phone" :fields="exportExcel.fields" :data="exportExcelData" :type="exportExcel.type" :name="exportExcel.filename">
          <button class="uni-button" type="primary" size="mini">导出 Excel</button>
        </download-excel>
      </view>
    </view>
    <view class="uni-container">
      <unicloud-db ref="udb" :collection="collectionList" field="appid,name,description,creator_uid,owner_type,owner_id,managers,members,icon_url,introduction,screenshot,store_list,remark" :where="where" page-data="replace"
        :orderby="orderby" :getcount="true" :page-size="options.pageSize" :page-current="options.pageCurrent"
        v-slot:default="{data,pagination,loading,error,options}" :options="options" loadtime="manual" @load="onqueryload">
        <uni-table ref="table" :loading="loading" :emptyText="error.message || '没有更多数据'" border stripe type="selection" @selection-change="selectionChange">
          <uni-tr>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'appid')" sortable @sort-change="sortChange($event, 'appid')">AppID</uni-th>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'name')" sortable @sort-change="sortChange($event, 'name')">应用名称</uni-th>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'description')" sortable @sort-change="sortChange($event, 'description')">应用描述</uni-th>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'creator_uid')" sortable @sort-change="sortChange($event, 'creator_uid')">creator_uid</uni-th>
            <uni-th align="center" filter-type="range" @filter-change="filterChange($event, 'owner_type')" sortable @sort-change="sortChange($event, 'owner_type')">owner_type</uni-th>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'owner_id')" sortable @sort-change="sortChange($event, 'owner_id')">owner_id</uni-th>
            <uni-th align="center" sortable @sort-change="sortChange($event, 'managers')">managers</uni-th>
            <uni-th align="center" sortable @sort-change="sortChange($event, 'members')">members</uni-th>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'icon_url')" sortable @sort-change="sortChange($event, 'icon_url')">应用图标</uni-th>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'introduction')" sortable @sort-change="sortChange($event, 'introduction')">应用简介</uni-th>
            <uni-th align="center" sortable @sort-change="sortChange($event, 'screenshot')">应用截图</uni-th>
            <uni-th align="center" sortable @sort-change="sortChange($event, 'store_list')">应用市场</uni-th>
            <uni-th align="center" filter-type="search" @filter-change="filterChange($event, 'remark')" sortable @sort-change="sortChange($event, 'remark')">备注</uni-th>
            <uni-th align="center">操作</uni-th>
          </uni-tr>
          <uni-tr v-for="(item,index) in data" :key="index">
            <uni-td align="center">{{item.appid}}</uni-td>
            <uni-td align="center">{{item.name}}</uni-td>
            <uni-td align="center">
              <textarea :disabled="true" :value="item.description"></textarea>
            </uni-td>
            <uni-td align="center">{{item.creator_uid}}</uni-td>
            <uni-td align="center">{{item.owner_type}}</uni-td>
            <uni-td align="center">{{item.owner_id}}</uni-td>
            <uni-td align="center">{{item.managers}}</uni-td>
            <uni-td align="center">{{item.members}}</uni-td>
            <uni-td align="center">{{item.icon_url}}</uni-td>
            <uni-td align="center">{{item.introduction}}</uni-td>
            <uni-td align="center">{{item.screenshot}}</uni-td>
            <uni-td align="center">{{item.store_list}}</uni-td>
            <uni-td align="center">
              <textarea :disabled="true" :value="item.remark"></textarea>
            </uni-td>
            <uni-td align="center">
              <view class="uni-group">
                <button @click="navigateTo('./edit?id='+item._id, false)" class="uni-button" size="mini" type="primary">修改</button>
                <button @click="confirmDelete(item._id)" class="uni-button" size="mini" type="warn">删除</button>
              </view>
            </uni-td>
          </uni-tr>
        </uni-table>
        <view class="uni-pagination-box">
          <uni-pagination show-icon :page-size="pagination.size" v-model="pagination.current" :total="pagination.count" @change="onPageChanged" />
        </view>
      </unicloud-db>
    </view>
  </view>
</template>

<script>
  import { enumConverter, filterToWhere } from '../../js_sdk/validator/test_group.js';

  const db = uniCloud.database()
  // 表查询配置
  const dbOrderBy = '' // 排序字段
  const dbSearchFields = [] // 模糊搜索字段，支持模糊搜索的字段列表。联表查询格式: 主表字段名.副表字段名，例如用户表关联角色表 role.role_name
  // 分页配置
  const pageSize = 20
  const pageCurrent = 1

  const orderByMapping = {
    "ascending": "asc",
    "descending": "desc"
  }

  export default {
    data() {
      return {
        collectionList: "test_group",
        query: '',
        where: '',
        orderby: dbOrderBy,
        orderByFieldName: "",
        selectedIndexs: [],
        options: {
          pageSize,
          pageCurrent,
          filterData: {},
          ...enumConverter
        },
        imageStyles: {
          width: 64,
          height: 64
        },
        exportExcel: {
          "filename": "test_group.xls",
          "type": "xls",
          "fields": {
            "AppID": "appid",
            "应用名称": "name",
            "应用描述": "description",
            "creator_uid": "creator_uid",
            "owner_type": "owner_type",
            "owner_id": "owner_id",
            "managers": "managers",
            "members": "members",
            "应用图标": "icon_url",
            "应用简介": "introduction",
            "应用截图": "screenshot",
            "应用市场": "store_list",
            "备注": "remark"
          }
        },
        exportExcelData: []
      }
    },
    onLoad() {
      this._filter = {}
    },
    onReady() {
      this.$refs.udb.loadData()
    },
    methods: {
      onqueryload(data) {
        this.exportExcelData = data
      },
      getWhere() {
        const query = this.query.trim()
        if (!query) {
          return ''
        }
        const queryRe = new RegExp(query, 'i')
        return dbSearchFields.map(name => queryRe + '.test(' + name + ')').join(' || ')
      },
      search() {
        const newWhere = this.getWhere()
        this.where = newWhere
        this.$nextTick(() => {
          this.loadData()
        })
      },
      loadData(clear = true) {
        this.$refs.udb.loadData({
          clear
        })
      },
      onPageChanged(e) {
        this.selectedIndexs.length = 0
        this.$refs.table.clearSelection()
        this.$refs.udb.loadData({
          current: e.current
        })
      },
      navigateTo(url, clear) {
        // clear 表示刷新列表时是否清除页码，true 表示刷新并回到列表第 1 页，默认为 true
        uni.navigateTo({
          url,
          events: {
            refreshData: () => {
              this.loadData(clear)
            }
          }
        })
      },
      // 多选处理
      selectedItems() {
        var dataList = this.$refs.udb.dataList
        return this.selectedIndexs.map(i => dataList[i]._id)
      },
      // 批量删除
      delTable() {
        this.$refs.udb.remove(this.selectedItems(), {
          success:(res) => {
            this.$refs.table.clearSelection()
          }
        })
      },
      // 多选
      selectionChange(e) {
        this.selectedIndexs = e.detail.index
      },
      confirmDelete(id) {
        this.$refs.udb.remove(id, {
          success:(res) => {
            this.$refs.table.clearSelection()
          }
        })
      },
      sortChange(e, name) {
        this.orderByFieldName = name;
        if (e.order) {
          this.orderby = name + ' ' + orderByMapping[e.order]
        } else {
          this.orderby = ''
        }
        this.$refs.table.clearSelection()
        this.$nextTick(() => {
          this.$refs.udb.loadData()
        })
      },
      filterChange(e, name) {
        this._filter[name] = {
          type: e.filterType,
          value: e.filter
        }
        let newWhere = filterToWhere(this._filter, db.command)
        if (Object.keys(newWhere).length) {
          this.where = newWhere
        } else {
          this.where = ''
        }
        this.$nextTick(() => {
          this.$refs.udb.loadData()
        })
      }
    }
  }
</script>

<style>
</style>
