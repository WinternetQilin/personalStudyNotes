import {
	defineStore
} from 'pinia'

const useCar = defineStore("car", {
	state: () => ({
		carList: []
	}),
	getters: {
		getCarList(state) {
			return state.carList
		},
		totalPrice(state) {
			return state.carList.reduce((prev, next) => {
				return prev += (next.price * next.numvalue)
			}, 0)
		},
		buyNum(state) {
			return state.carList.reduce((prev, next) => {
				return prev += next.numvalue
			}, 0)
		}
	},
	actions: {
		setCarList(params) {
			let {
				item,
				num
			} = params
			let caritem = {
				goodsid: item.id || item.goodsid,
				numvalue: num,
				name: item.name,
				price: item.price,
				before_price: item.before_price,
				thumb: item.thumb
			}

			let idx = this.carList.findIndex(i => i.goodsid == caritem.goodsid)
			if (idx >= 0) {
				this.carList[idx].numvalue = caritem.numvalue
				if (caritem.numvalue <= 0) {
					this.carList.splice(idx, 1)
				}
			} else {
				this.carList.unshift(caritem)
			}

		}
	}
})

export default useCar