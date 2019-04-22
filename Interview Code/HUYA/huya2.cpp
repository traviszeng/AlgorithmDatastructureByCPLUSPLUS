#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<algorithm>

struct ServerSelector
{
	// 下游服务器编号(从0起)
	typedef int server_index_t;

	// 权重
	typedef size_t weight_t;

	std::vector<weight_t>  myWeight;
	std::vector<weight_t>  myWeightTemp;


	size_t weightSum=0;
	size_t weightSumTemp = 0;

	// 下游服务器列表或权重变更或初始化时被调用
	// @servers：下游服务器权重列表 (第一个元素代表编号为0的服务器权重, 第二个元素代表编号为1的服务器权重, 以此类推)
	void updateServerList(std::vector<weight_t> & servers) {
		myWeight = servers;
		myWeightTemp = myWeight;
		weightSum = 0;
		for (int i = 0; i < servers.size(); i++) {
			weightSum += servers[i];
		}
		weightSumTemp = weightSum;
		
	}

	// 每次发送请求前调用这个函数获取应该指向的下游服务器编号
	server_index_t selectServer() {
		if (weightSumTemp == 0) {
			//重新初始化temp
			weightSumTemp = weightSum;
			myWeightTemp = myWeight;
			
		}
		//每次寻找最大权值
		auto maxPosition = max_element(myWeightTemp.begin(), myWeightTemp.end());
		(*maxPosition)--;

		weightSumTemp--;
		return maxPosition - myWeightTemp.begin();
	}
};

int main()
{
	// 处理输入
	int numServer = 0;
	std::cin >> numServer;
	std::vector<ServerSelector::weight_t> servers(numServer);
	for (int i = 0; i < numServer; ++i) {
		std::cin >> servers[i];
	}
	int numRequests = 0;
	std::cin >> numRequests;

	// 模拟服务器间调用
	std::vector<int> requests(numServer);
	ServerSelector ss;
	ss.updateServerList(servers);
	for (int i = 0; i < numRequests; ++i) {
		ServerSelector::server_index_t serverIndex = ss.selectServer();
		if (serverIndex >= numServer)
			return 1;

		requests[serverIndex]++;
	}

	// 输出结果
	for (int v : requests) {
		std::cout << v << std::endl;
	}
	system("pause");
	return 0;
}