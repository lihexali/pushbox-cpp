// pushbox-learn.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)? true : false)

using namespace std;
int main()
{
	//地图数据
	int const iMapCol = 20;
	int const iMapRow = 15;
	int arrMap[iMapRow][iMapCol] = {
		 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 1
		,1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1
	};

	//玩家位置
	int iPlayerRow = 5;
	int iPlayerCol = 6;
	int iPlayerRowBk = iPlayerRow;
	int iPlayerColBk = iPlayerCol;

	//箱子位置
	int iBoxRow = 3;
	int iBoxCol = 10;
	int iBoxRowBk = iBoxRow;
	int iBoxColBk = iBoxCol;

	//箱子目标位置
	int iBoxDstRow = 3;
	int iBoxDstCol = 11;

	//游戏状态标志
	bool isGameOver = false;
	bool isWin = false;
	while (!isGameOver) {
		system("cls");

		//备份玩家坐标
		iPlayerRowBk = iPlayerRow;
		iPlayerColBk = iPlayerCol;

		//备份箱子坐标
		iBoxRowBk = iBoxRow;
		iBoxColBk = iBoxCol;

		//玩家控制
		if (KEY_DOWN(VK_UP)) {
			iPlayerRow--;
		}
		if (KEY_DOWN(VK_DOWN)) {
			iPlayerRow++;
		}
		if (KEY_DOWN(VK_LEFT)) {
			iPlayerCol--;
		}
		if (KEY_DOWN(VK_RIGHT)) {
			iPlayerCol++;
		}

		//玩家撞箱子
		if (iPlayerRow == iBoxRow && iPlayerCol == iBoxCol) {
			//箱子的坐标=箱子坐标+玩家坐标的偏移量
			iBoxRow += iPlayerRow - iPlayerRowBk;
			iBoxCol += iPlayerCol - iPlayerColBk;
		}


		//撞墙判断
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]
					&& (iPlayerRow == row && iPlayerCol == col)) { //玩家撞墙了
					//还原玩家坐标
					iPlayerRow = iPlayerRowBk;
					iPlayerCol = iPlayerColBk;
				}
				if (1 == arrMap[row][col]
					&& (iBoxRow == row && iBoxCol == col)) { //箱子撞墙了
					//还原箱子坐标
					iBoxRow = iBoxRowBk;
					iBoxCol = iBoxColBk;
					//还原玩家坐标
					iPlayerRow = iPlayerRowBk;
					iPlayerCol = iPlayerColBk;
				}
			}
		}

		//箱子移动到目标位置判断
		if (iBoxRow == iBoxDstRow && iBoxCol == iBoxDstCol) {
			isGameOver = true;
			isWin = true;
		}

		//画地图
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]) {
					cout << "■";
				}
				else {
					//画玩家
					if (iPlayerRow == row && iPlayerCol == col) {
						cout << "♀";
					}
					else if (iBoxRow == row && iBoxCol == col) { //画箱子
						cout << "★";
					}
					else if (iBoxDstRow == row && iBoxDstCol == col) { //画箱子位置
						cout << "☆";
					}
					else {
						cout << "  ";
					}
				}
			}
			cout << endl;
		}
	}

	//游戏胜利
	if (isWin) {
		cout << "Win!" << endl;
	}

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
