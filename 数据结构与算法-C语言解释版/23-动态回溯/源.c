﻿/*
动态回溯算法思想：
	1 寻路
		深度寻路算法 回退
	2 货物装载
	3 0-1背包问题
	4 涂格子（图的着色问题）
	5 电路排版问题
	6 旅行者售后问题
	7 N皇后问题
特性在于回溯：
	1 针对问题来解空间：根据实际需求来描述空间
		二维数组描述地图 记录当前试探方向 标记是否走过
	2 确定易于搜索的解空间结构
	3 用深度优先搜索的方式来解决问题并有合适的回溯方式
		比如用栈实现回溯

八皇后问题：
	国际象棋棋盘 8*8
	国际象棋皇后 走米字格
	要摆下8个皇后 并且互相不能接触 有多少种摆法？

同理可得，四皇后问题：
	4*4的棋盘 摆下四个皇后 有多少种摆法？

解法：
	拜访一个皇后，找位置摆下一个皇后，如果摆下N个，可行的摆法+1并且继续换位置摆
	摆不下就回退，换位置重新摆

	因为一行只能放一个
	所以第一个皇后的y坐标必定是0
	第二个皇后的y坐标必定是1
	第N个皇后的y坐标必定是N-1
*/
