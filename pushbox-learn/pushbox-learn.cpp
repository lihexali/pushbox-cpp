// pushbox-learn.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)? true : false)

//位置信息结构体
struct sPos {
	int nRow;
	int nCol;
	int nRowBk;
	int nColBk;
};

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
	sPos player;
	player.nRow = 5;
	player.nCol = 6;
	player.nRowBk = player.nRow;
	player.nColBk = player.nCol;

	//箱子位置
	sPos box;
	box.nRow = 3;
	box.nCol = 10;
	box.nRowBk = box.nRow;
	box.nColBk = box.nCol;


	//箱子目标位置
	sPos boxDst;
	boxDst.nRow = 3;
	boxDst.nCol = 11;

	//游戏状态标志
	bool isGameOver = false;
	bool isWin = false;
	while (!isGameOver) {
		system("cls");

		//备份玩家坐标
		player.nRowBk = player.nRow;
		player.nColBk = player.nCol;

		//备份箱子坐标
		box.nRowBk = box.nRow;
		box.nColBk = box.nCol;

		//玩家控制
		if (KEY_DOWN(VK_UP)) {
			player.nRow--;
		}
		if (KEY_DOWN(VK_DOWN)) {
			player.nRow++;
		}
		if (KEY_DOWN(VK_LEFT)) {
			player.nCol--;
		}
		if (KEY_DOWN(VK_RIGHT)) {
			player.nCol++;
		}

		//玩家撞箱子
		if (player.nRow == box.nRow && player.nCol == box.nCol) {
			//箱子的坐标=箱子坐标+玩家坐标的偏移量
			box.nRow += player.nRow - player.nRowBk;
			box.nCol += player.nCol - player.nColBk;
		}


		//撞墙判断
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]
					&& (player.nRow == row && player.nCol == col)) { //玩家撞墙了
					//还原玩家坐标
					player.nRow = player.nRowBk;
					player.nCol = player.nColBk;
				}
				if (1 == arrMap[row][col]
					&& (box.nRow == row && box.nCol == col)) { //箱子撞墙了
					//还原箱子坐标
					box.nRow = box.nRowBk;
					box.nCol = box.nColBk;
					//还原玩家坐标
					player.nRow = player.nRowBk;
					player.nCol = player.nColBk;
				}
			}
		}

		//箱子移动到目标位置判断
		if (box.nRow == boxDst.nRow && box.nCol == boxDst.nCol) {
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
					if (player.nRow == row && player.nCol == col) {
						cout << "♀";
					}
					else if (box.nRow == row && box.nCol == col) { //画箱子
						cout << "★";
					}
					else if (boxDst.nRow == row && boxDst.nCol == col) { //画箱子位置
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
