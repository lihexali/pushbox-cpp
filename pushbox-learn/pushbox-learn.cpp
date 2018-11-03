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

//地图数据
int const g_nMapCol = 20;
int const g_nMapRow = 15;
int g_arrMap[g_nMapRow][g_nMapCol] = {
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
sPos g_Player;
//箱子数量
int const g_nBoxCount = 3;
//箱子位置
sPos g_arrBox[g_nBoxCount];
//箱子目标位置
sPos g_arrBoxDst[g_nBoxCount];
//游戏状态标志
bool g_bGameOver = false;
bool g_bWin = false;

using namespace std;

void initGame();
void upData();
void onRender();

int main()
{
	initGame();
	while (!g_bGameOver) {
		system("cls");
		//数据更新
		upData();
		//渲染
		onRender();
	}
	return 0;
}

void initGame()
{
	//初始化玩家位置
	g_Player.nRow = 5;
	g_Player.nCol = 6;
	g_Player.nRowBk = g_Player.nRow;
	g_Player.nColBk = g_Player.nCol;

	//初始化箱子位置
	for (int i = 0; i < g_nBoxCount; i++)
	{
		g_arrBox[i].nRow = 3 + i;
		g_arrBox[i].nCol = 10;
		g_arrBox[i].nRowBk = g_arrBox[i].nRow;
		g_arrBox[i].nColBk = g_arrBox[i].nCol;
	}

	//初始化目标位置
	for (int i = 0; i < g_nBoxCount; i++)
	{
		g_arrBoxDst[i].nRow = 3 + i;
		g_arrBoxDst[i].nCol = 11;
		g_arrBoxDst[i].nRowBk = g_arrBoxDst[i].nRow;
		g_arrBoxDst[i].nColBk = g_arrBoxDst[i].nCol;
	}

}

void upData()
{
	//备份玩家坐标
	g_Player.nRowBk = g_Player.nRow;
	g_Player.nColBk = g_Player.nCol;

	//备份箱子坐标
	for (size_t i = 0; i < g_nBoxCount; i++) {
		g_arrBox[i].nRowBk = g_arrBox[i].nRow;
		g_arrBox[i].nColBk = g_arrBox[i].nCol;
	}


	//玩家控制
	if (KEY_DOWN(VK_UP)) {
		g_Player.nRow--;
	}
	if (KEY_DOWN(VK_DOWN)) {
		g_Player.nRow++;
	}
	if (KEY_DOWN(VK_LEFT)) {
		g_Player.nCol--;
	}
	if (KEY_DOWN(VK_RIGHT)) {
		g_Player.nCol++;
	}

	//玩家撞箱子
	for (int i = 0; i < g_nBoxCount; i++) {
		if (g_Player.nRow == g_arrBox[i].nRow && g_Player.nCol == g_arrBox[i].nCol) {
			//箱子的坐标=箱子坐标+玩家坐标的偏移量
			g_arrBox[i].nRow += g_Player.nRow - g_Player.nRowBk;
			g_arrBox[i].nCol += g_Player.nCol - g_Player.nColBk;
			break;
		}
	}

	//箱子撞箱子
	for (int i = 0; i < g_nBoxCount - 1; i++) {
		for (int j = i + 1; j < g_nBoxCount; j++) {
			//不允许箱子重叠的情况
			if (g_arrBox[i].nRow == g_arrBox[j].nRow && g_arrBox[i].nCol == g_arrBox[j].nCol) {
				//还原箱子坐标
				g_arrBox[i].nRow = g_arrBox[i].nRowBk;
				g_arrBox[i].nCol = g_arrBox[i].nColBk;
				g_arrBox[j].nRow = g_arrBox[j].nRowBk;
				g_arrBox[j].nCol = g_arrBox[j].nColBk;
				//还原玩家坐标
				g_Player.nRow = g_Player.nRowBk;
				g_Player.nCol = g_Player.nColBk;
			}
		}
	}


	//撞墙判断
	for (int row = 0; row < g_nMapRow; row++) {
		for (int col = 0; col < g_nMapCol; col++) {
			if (1 == g_arrMap[row][col]
				&& (g_Player.nRow == row && g_Player.nCol == col)) { //玩家撞墙了
				//还原玩家坐标
				g_Player.nRow = g_Player.nRowBk;
				g_Player.nCol = g_Player.nColBk;
			}


			if (1 == g_arrMap[row][col]) {
				for (int i = 0; i < g_nBoxCount; i++) {
					if (g_arrBox[i].nRow == row && g_arrBox[i].nCol == col) { //箱子撞墙了
						//还原箱子坐标
						g_arrBox[i].nRow = g_arrBox[i].nRowBk;
						g_arrBox[i].nCol = g_arrBox[i].nColBk;
						//还原玩家坐标
						g_Player.nRow = g_Player.nRowBk;
						g_Player.nCol = g_Player.nColBk;
					}
				}
			}
		}
	}

	//箱子移动到目标位置判断
	int fishCount = 0;
	for (int i = 0; i < g_nBoxCount; i++) {
		if (g_arrBox[i].nRow == g_arrBoxDst[i].nRow && g_arrBox[i].nCol == g_arrBoxDst[i].nCol) {
			fishCount++;
			g_bGameOver = fishCount >= g_nBoxCount;
			g_bWin = fishCount >= g_nBoxCount;
		}
	}
}

void onRender()
{
	//画地图
	for (int row = 0; row < g_nMapRow; row++) {
		for (int col = 0; col < g_nMapCol; col++) {
			if (1 == g_arrMap[row][col]) {
				cout << "■";
			}
			else {
				//判断该位置是否需要画箱子
				bool drawBox = false;
				for (int i = 0; i < g_nBoxCount; i++) {
					if (g_arrBox[i].nRow == row && g_arrBox[i].nCol == col) {
						drawBox = true;
					}
				}


				//判断该位置是否需要画箱子目标位置
				bool drawBoxDst = false;
				for (int i = 0; i < g_nBoxCount; i++) {
					if (g_arrBoxDst[i].nRow == row && g_arrBoxDst[i].nCol == col) {
						drawBoxDst = true;
					}
				}

				//画玩家
				if (g_Player.nRow == row && g_Player.nCol == col) {
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
	//游戏胜利
	if (g_bWin) {
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

