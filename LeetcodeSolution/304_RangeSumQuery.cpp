#include<iostream>
#include<vector>

class NumMatrix {
public:
	vector<vector<int>> M;
	int row;
	int col;
	NumMatrix(vector<vector<int>> matrix) {
		if (!matrix.size() == 0)
		{
			//initialize
			for (int i = 0; i<matrix.size(); i++)
			{
				vector<int> tmp;
				for (int j = 0; j<matrix[i].size(); j++)
					tmp.push_back(matrix[i][j]);
				M.push_back(tmp);

			}


			row = M.size();
			col = M[0].size();

		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		if (M.size() == 0)
			return 0;
		if (M[0].size() == 0)
			return 0;
		if (row1<0 || row1>row || row2<0 || row2>row)
			return 0;
		if (col1<0 || col1>col || col2<0 || col2>col)
			return 0;
		int sum = 0;
		for (int i = row1; i <= row2; i++)
			for (int j = col1; j <= col2; j++)
				sum += M[i][j];
		return sum;
	}
};

/**
* Your NumMatrix object will be instantiated and called as such:
* NumMatrix obj = new NumMatrix(matrix);
* int param_1 = obj.sumRegion(row1,col1,row2,col2);
*/