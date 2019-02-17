#include<vector>
#include<iostream>

using namespace std;

int bfs(vector<vector<int>>&grid, int x, int y, int day) {

	if (x < 0 || y < 0 || x >= grid.size() || y >= grid[x].size() || grid[x][y] != 1) return 0;
	grid[x][y] = day + 3;
	return 1;
}

int orangesRotting(vector<vector<int>>& grid) {
	int i, j, day = 0, fresh = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++)
			if (grid[i][j] == 1)
				fresh += 1;
	}

	while (fresh > 0) {
		int old_fresh = fresh;
		for (int i = 0; i < grid.size(); i++)
			for (int j = 0; j < grid[i].size(); j++)
				if (grid[i][j] == day + 2)
					fresh -= bfs(grid, i, j + 1, day) + bfs(grid, i, j - 1, day) + bfs(grid, i - 1, j, day) + bfs(grid, i +1, j , day);
	
		if (old_fresh == fresh) return -1;
		day++;
	}
	return day;
}