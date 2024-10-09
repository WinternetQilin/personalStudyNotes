import { Hospital } from './type';
import request from '@/utils/request'

//通过枚举管理首页接口的模块地址
enum API{
    //获取已有医院数据（分页用
    HOSPITAL_URL = '/hosp/hospital/',
    HOSPITAL_LEVEL_REGION_URL = '/cmn/dict/findByDictCode/',
}

export const reqHospital=(page:number,limit:number)=>request.get(API.HOSPITAL_URL+`${page}/${limit}`) 

export const reqHospitalLevelRegion=(dictCode:string)=>request.get(API.HOSPITAL_LEVEL_REGION_URL+dictCode)