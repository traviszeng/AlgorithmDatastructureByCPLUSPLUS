#include<unordered_map>
#include<unordered_set>
#include<iostream>
using namespace std;

//dfs+backtrace
unordered_map<int,int> count1;
unordered_map<int, unordered_set<int>> cand;
int res = 0;
int numSquarefulPerms(vector<int> &A) {
	//统计A中所有数字出现的次数
	for (int &a : A)
		count1[a]++;
	for (auto &i : count1) {
		for (auto &j : count1) {
			int x = i.first, y = j.first, s = sqrt(x + y);
			if (s * s == x + y)
				cand[x].insert(y);
		}
	}

	for (auto e : count1)
		dfs(e.first, A.size() - 1);
	return res;

}


void dfs(int x, int left) {
	count1[x]--;
	if (!left) res++;
	for (int y : cand[x])
		if (count1[y] > 0)
			dfs(y, left - 1);
	count1[x]++;
}

