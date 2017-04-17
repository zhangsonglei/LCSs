//LCS算法，动态规划

#include "string.h"
#include <iostream>
using namespace std;

// 最长公共子序列的生成方向｛初始化为0，左，上，左上｝
enum decreaseDir { kInit = 0, kLeft, kUp, kLeftUp };

void LCS_Print(int **LCS_direction, char* pStr1, char* pStr2, size_t row, size_t col);

// 获取两个字符串的最长公共子序列, 并打印一个最长公共子序列
// 输入: pStr1         - 第一个string
//        pStr2         - 第二个string
// 输出: 两个字符串的公共子序列的长度
int LCS(char* pStr1, char* pStr2)
{
	//任何一个指针为空就返回0
	if (!pStr1 || !pStr2)
		return 0;

	//任何一个长度为0就返回0
	size_t length1 = strlen(pStr1);
	size_t length2 = strlen(pStr2);
	if (!length1 || !length2)
		return 0;

	size_t i, j;

	// 初始化长度矩阵为0
	int **LCS_length;
	LCS_length = (int**)(new int[length1]);
	for (i = 0; i < length1; ++i)
		LCS_length[i] = (int*)new int[length2];

	for (i = 0; i < length1; ++i)
		for (j = 0; j < length2; ++j)
			LCS_length[i][j] = 0;
	// 初始化长度矩阵结束
	
	// 初始化方向矩阵为0
	int **LCS_direction;
	LCS_direction = (int**)(new int[length1]);
	for (i = 0; i < length1; ++i)
		LCS_direction[i] = (int*)new int[length2];

	for (i = 0; i < length1; ++i)
		for (j = 0; j < length2; ++j)
			LCS_direction[i][j] = kInit;
	// 初始化方向矩阵结束

	for (i = 0; i < length1; ++i)
	{
		for (j = 0; j < length2; ++j)
		{
			if (i == 0 || j == 0)
			{
				if (pStr1[i] == pStr2[j])
				{
					LCS_length[i][j] = 1;
					LCS_direction[i][j] = kLeftUp;
				}
				else
				{
					if (i > 0)
					{
						LCS_length[i][j] = LCS_length[i - 1][j];
						LCS_direction[i][j] = kUp;
					}
					if (j > 0)
					{
						LCS_length[i][j] = LCS_length[i][j - 1];
						LCS_direction[i][j] = kLeft;
					}
				}
			}

			// 找到最长公共子序列的一个字符 
			else if (pStr1[i] == pStr2[j])
			{//该字符在方向矩阵的左上方
				LCS_length[i][j] = LCS_length[i - 1][j - 1] + 1;
				LCS_direction[i][j] = kLeftUp;
			}
			
			else if (LCS_length[i - 1][j] > LCS_length[i][j - 1])
			{//该字符在方向矩阵的上方
				LCS_length[i][j] = LCS_length[i - 1][j];
				LCS_direction[i][j] = kUp;
			}
			else
			{//该字符在方向矩阵的左方
				LCS_length[i][j] = LCS_length[i][j - 1];
				LCS_direction[i][j] = kLeft;
			}
		}
	}
	LCS_Print(LCS_direction, pStr1, pStr2, length1 - 1, length2 - 1); //调用下面的LCS_Pring 打印出所求子串。
	return LCS_length[length1 - 1][length2 - 1];                      //返回长度。
}

// 打印两个字符串的一个最大公共子序列
// 输入: LCS_direction  -方向矩阵——记录了最大公共子序列的生成方向的二维矩阵
//        pStr1         - 第一个字符串
//        pStr2         - 第二个字符串
//        row           - 方向矩阵的行数
//        col           - 方向矩阵的列数
void LCS_Print(int **LCS_direction,	char* pStr1, char* pStr2, size_t row, size_t col)
{
	if (pStr1 == NULL || pStr2 == NULL)
		return;

	size_t length1 = strlen(pStr1);
	size_t length2 = strlen(pStr2);

	if (length1 == 0 || length2 == 0 || !(row < length1 && col < length2))
		return;

	// kLeftUp 表示最长公共子序列中的一个字符已找到
	if (LCS_direction[row][col] == kLeftUp)
	{
		if (row > 0 && col > 0)
			LCS_Print(LCS_direction, pStr1, pStr2, row - 1, col - 1);

		// 打印该字符
		printf("%c", pStr1[row]);
	}
	else if (LCS_direction[row][col] == kLeft)
	{
		// 方向矩阵中的记录向左移
		if (col > 0)
			LCS_Print(LCS_direction, pStr1, pStr2, row, col - 1);
	}
	else if (LCS_direction[row][col] == kUp)
	{
		// 方向矩阵中的记录向上移
		if (row > 0)
			LCS_Print(LCS_direction, pStr1, pStr2, row - 1, col);
	}
}

int main()
{
	char* pStr1 = "华中科技大学";
	char* pStr2 = "我在华科上大学";
	LCS(pStr1, pStr2);
	printf("\n");
	system("pause");
	return 0;
}
