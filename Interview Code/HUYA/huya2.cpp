#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<algorithm>

struct ServerSelector
{
	// ���η��������(��0��)
	typedef int server_index_t;

	// Ȩ��
	typedef size_t weight_t;

	std::vector<weight_t>  myWeight;
	std::vector<weight_t>  myWeightTemp;


	size_t weightSum=0;
	size_t weightSumTemp = 0;

	// ���η������б��Ȩ�ر�����ʼ��ʱ������
	// @servers�����η�����Ȩ���б� (��һ��Ԫ�ش�����Ϊ0�ķ�����Ȩ��, �ڶ���Ԫ�ش�����Ϊ1�ķ�����Ȩ��, �Դ�����)
	void updateServerList(std::vector<weight_t> & servers) {
		myWeight = servers;
		myWeightTemp = myWeight;
		weightSum = 0;
		for (int i = 0; i < servers.size(); i++) {
			weightSum += servers[i];
		}
		weightSumTemp = weightSum;
		
	}

	// ÿ�η�������ǰ�������������ȡӦ��ָ������η��������
	server_index_t selectServer() {
		if (weightSumTemp == 0) {
			//���³�ʼ��temp
			weightSumTemp = weightSum;
			myWeightTemp = myWeight;
			
		}
		//ÿ��Ѱ�����Ȩֵ
		auto maxPosition = max_element(myWeightTemp.begin(), myWeightTemp.end());
		(*maxPosition)--;

		weightSumTemp--;
		return maxPosition - myWeightTemp.begin();
	}
};

int main()
{
	// ��������
	int numServer = 0;
	std::cin >> numServer;
	std::vector<ServerSelector::weight_t> servers(numServer);
	for (int i = 0; i < numServer; ++i) {
		std::cin >> servers[i];
	}
	int numRequests = 0;
	std::cin >> numRequests;

	// ģ������������
	std::vector<int> requests(numServer);
	ServerSelector ss;
	ss.updateServerList(servers);
	for (int i = 0; i < numRequests; ++i) {
		ServerSelector::server_index_t serverIndex = ss.selectServer();
		if (serverIndex >= numServer)
			return 1;

		requests[serverIndex]++;
	}

	// ������
	for (int v : requests) {
		std::cout << v << std::endl;
	}
	system("pause");
	return 0;
}