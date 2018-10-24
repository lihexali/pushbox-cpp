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

	//箱子数量
	int const nBoxCount = 3;

	//箱子位置
	sPos arrBox[nBoxCount];
	for (int i = 0; i < nBoxCount; i++)
	{
		arrBox[i].nRow = 3 + i;
		arrBox[i].nCol = 10;
		arrBox[i].nRowBk = arrBox[i].nRow;
		arrBox[i].nColBk = arrBox[i].nCol;
	}
	

	//箱子目标位置
	sPos arrBoxDst[nBoxCount];
	for (int i = 0; i < nBoxCount; i++)
	{
		arrBoxDst[i].nRow = 3 + i;
		arrBoxDst[i].nCol = 11;
		arrBoxDst[i].nRowBk = arrBoxDst[i].nRow;
		arrBoxDst[i].nColBk = arrBoxDst[i].nCol;
	}

	//游戏状态标志
	bool isGameOver = false;
	bool isWin = false;
	while (!isGameOver) {
		system("cls");


		
		//备份玩家坐标
		player.nRowBk = player.nRow;
		player.nColBk = player.nCol;

		//备份箱子坐标
		for (size_t i = 0; i < nBoxCount; i++) {
			arrBox[i].nRowBk = arrBox[i].nRow;
			arrBox[i].nColBk = arrBox[i].nCol;
		}


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
		for (int i = 0; i < nBoxCount; i++) {
			if (player.nRow == arrBox[i].nRow && player.nCol == arrBox[i].nCol) {
				//箱子的坐标=箱子坐标+玩家坐标的偏移量
				arrBox[i].nRow += player.nRow - player.nRowBk;
				arrBox[i].nCol += player.nCol - player.nColBk;
				break;
			}
		}

		//箱子撞箱子
		for (int i = 0; i < nBoxCount -1; i++) {
			for (int j = i+1; j < nBoxCount; j++) {
				//不允许箱子重叠的情况
				if (arrBox[i].nRow == arrBox[j].nRow && arrBox[i].nCol == arrBox[j].nCol) {
					//还原箱子坐标
					arrBox[i].nRow = arrBox[i].nRowBk;
					arrBox[i].nCol = arrBox[i].nColBk;
					arrBox[j].nRow = arrBox[j].nRowBk;
					arrBox[j].nCol = arrBox[j].nColBk;
					//还原玩家坐标
					player.nRow = player.nRowBk;
					player.nCol = player.nColBk;
				}
			}
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
				
				
				if (1 == arrMap[row][col]) {
					for (int i = 0; i < nBoxCount; i++) {
						if (arrBox[i].nRow == row && arrBox[i].nCol == col) { //箱子撞墙了
							//还原箱子坐标
							arrBox[i].nRow = arrBox[i].nRowBk;
							arrBox[i].nCol = arrBox[i].nColBk;
							//还原玩家坐标
							player.nRow = player.nRowBk;
							player.nCol = player.nColBk;
						}
					}
				}
			}
		}

		//箱子移动到目标位置判断
		int fishCount = 0;
		for (int i = 0; i < nBoxCount; i++) {
			if (arrBox[i].nRow == arrBoxDst[i].nRow && arrBox[i].nCol == arrBoxDst[i].nCol) {
				fishCount++;
				isGameOver = fishCount >= nBoxCount;
				isWin = fishCount >= nBoxCount;
			}
		}
		

		//画地图
		for (int row = 0; row < iMapRow; row++) {
			for (int col = 0; col < iMapCol; col++) {
				if (1 == arrMap[row][col]) {
					cout << "■";
				}
				else {
					//判断该位置是否需要画箱子
					bool drawBox = false;
					for (int i = 0; i < nBoxCount; i++) {
						if (arrBox[i].nRow == row && arrBox[i].nCol == col) {
							drawBox = true;
						}
					}


					//判断该位置是否需要画箱子目标位置
					bool drawBoxDst = false;
					for (int i = 0; i < nBoxCount; i++) {
						if (arrBoxDst[i].nRow == row && arrBoxDst[i].nCol == col) {
							drawBoxDst = true;
						}
					}

					//画玩家
					if (player.nRow == row && player.nCol == col) {
						cout << "♀";
					}
					else if (drawBox) { //画箱子
						cout << "★";
					}
					else if (drawBoxDst) { //画箱子目标位置
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
