//定义首页模块ts数据类型
export interface ResponseData {
  code: number
  message: string
  ok: boolean
}

//已有的医院数据的ts类型
export interface Hospital {
    "id":string,
    "createTime":string,
    "updateTime":string,
    "isDeleted":number,
    "param":{
        "hostypeString":string,
        "fullAddress":string
    },
    "hoscode":string,
    "hosname":string,
    "hostype":string,
    "provinceCode":string,
    "cityCode":string,
    "districtCode":string,
    "address":string,
    "logoData":string,
    "intro":string,
    "route":string,
    "status":number
    "boolingRule":{
        "cycle":string,
        "releaseTime":string,
        "stopTime":string
        "quitDay":number,
        "quitTime":string,
        "rule":string[],
        
    }
}

export type Content=Hospital[]