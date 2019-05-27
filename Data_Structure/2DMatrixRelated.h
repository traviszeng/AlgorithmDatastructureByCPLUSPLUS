#pragma once
#include<vector>
#include<iostream>
using namespace std;
/**
二维数组相关算法
*/
/**
二维数组的搜索
*/
bool searchMatrix(vector<vector<int>>& matrix, int target) {
	if (matrix.empty() || matrix[0].empty())
	{
		return false;
	}
	int row = 0;
	if (matrix[0][0] > target)
		return false;
	for (int i = 1; i < matrix.size(); i++)
	{
		if (matrix[i][0] <= target)
			row = i;
		else
			break;
	}
	bool flag = false;
	for (int i = 0; i < matrix[row].size(); i++)
	{
		if (matrix[row][i] == target)
			flag = true;
	}

	return flag;
}

bool searchMatrixII(vector<vector<int>>& matrix, int target) {
	if (matrix.size() <= 0 || matrix[0].size() <= 0)
		return false;
	int row = matrix.size();
	int col = matrix[0].size();
	int r = 0;
	int c = col - 1;
	while (r < row  && c >= 0)
	{
		if (matrix[r][c] == target)
			return true;
		else if (matrix[r][c] < target)
			r++;
		else
			c--;
	}
	return false;
}

void printNumber(int number) {
	std::cout << number << '\t';
}

/**回字打印数组*/
void printMatrixClockwisely(vector<vector<int>> matrix, int cols, int rows) {
	if (matrix.size() <= 0 || matrix[0].size() <= 0)
		return;

	int start = 0;
	while (cols > start * 2 && rows > start * 2) {
		//从(start,start)开始打印一圈
		printMatrixInCircle(matrix, cols, rows, start);
		start++;
	}
}

void printMatrixInCircle(vector<vector<int>> numbers, int columns, int rows, int start) {
	int endX = columns - 1 - start;
	int endY = rows - 1 - start;

	// 从左到右打印一行
	for (int i = start; i <= endX; ++i)
	{
		int number = numbers[start][i];
		printNumber(number);
	}

	// 从上到下打印一列
	if (start < endY)
	{
		for (int i = start + 1; i <= endY; ++i)
		{
			int number = numbers[i][endX];
			printNumber(number);
		}
	}

	// 从右到左打印一行
	if (start < endX && start < endY)
	{
		for (int i = endX - 1; i >= start; --i)
		{
			int number = numbers[endY][i];
			printNumber(number);
		}
	}

	// 从下到上打印一行
	if (start < endX && start < endY - 1)
	{
		for (int i = endY - 1; i >= start + 1; --i)
		{
			int number = numbers[i][start];
			printNumber(number);
		}
	}
}