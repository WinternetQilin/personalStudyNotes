"use strict";
const validator = {
  "name": {
    "rules": [
      {
        "format": "string"
      }
    ],
    "title": "用户名",
    "label": "用户名"
  },
  "age": {
    "rules": [
      {
        "format": "int"
      }
    ],
    "title": "年龄",
    "label": "年龄"
  },
  "gender": {
    "rules": [
      {
        "format": "int"
      },
      {
        "range": [
          {
            "text": "男",
            "value": 0
          },
          {
            "text": "女",
            "value": 1
          },
          {
            "text": "保密",
            "value": 2
          }
        ]
      }
    ],
    "title": "性别",
    "defaultValue": 2,
    "label": "性别"
  }
};
const enumConverter = {
  "gender_valuetotext": {
    "0": "男",
    "1": "女",
    "2": "保密"
  }
};
exports.enumConverter = enumConverter;
exports.validator = validator;
