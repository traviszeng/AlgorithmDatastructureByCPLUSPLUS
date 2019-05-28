#include<unordered_map>
#include<iostream>
using namespace std;

/**
数据同时保存在hashmap和双向链表中
*/

class LRUCache {
private:
	struct LRUNode {
		LRUNode *pre;
		LRUNode *next;
		int val;
		LRUNode(int v) :val(v),pre(nullptr),next(nullptr) {}
	};
	int num = 0;
	int capacity;
	LRUNode *head = nullptr;
	LRUNode *tail = nullptr;
	unordered_map<int, int> map;
	void moveToTail(LRUNode* node) {
		if (head == tail)
			return;
		if (head == node)
		{
			head = head->next;
			head->pre = nullptr;
			node->next = nullptr;
			node->pre = tail;
			tail->next = node;
			tail = node;
		}
		else if (node != tail) {
			if (node->pre)
				node->pre->next = node->next;
			if (node->next)
				node->next->pre = node->pre;
			node->pre = tail;
			tail->next = node;
			node->next = nullptr;
			tail = node;
		}
		else {
		}
	}

	void deleteHead() {
		if (head == nullptr)
			return;
		if (head->next == nullptr)
		{
			unordered_map<int, int>::iterator iter = map.find(head->val);
			map.erase(iter);
			tail = nullptr;
			head = nullptr;
			delete head;
			return;
		}
		LRUNode* temp = head;
		unordered_map<int, int>::iterator iter = map.find(head->val);
		map.erase(iter);
		head = head->next;
		head->pre = nullptr;
		temp = nullptr;
		delete temp;
	
	}

	LRUNode* findNode(int val) {
		LRUNode* temp = head;
		while (temp)
		{
			if (temp->val == val)
				break;
			temp = temp->next;
		}
		return temp;
	}
	
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}

	int get(int key) {
		if (map.find(key) == map.end())
			return -1;
		LRUNode* temp = findNode(key);
		moveToTail(temp);
		return map[key];
	}

	void put(int key, int value) {
		if (num == 0) {
			head = new LRUNode(key);
			tail = head;
			map[key] = value;
			num++;
		}
		else if (num < capacity) {
			if (map.find(key) != map.end()) { //更新
				LRUNode* temp = findNode(key);
				moveToTail(temp);
				map[key] = value;
				
			}
			else{
				LRUNode* temp = new LRUNode(key);
				tail->next = temp;
				temp->pre = tail;
				tail = temp;
				map[key] = value;
				num++;
			}
		}
		else {
			if (map.find(key) != map.end()) { //更新
				LRUNode* temp = findNode(key);
				moveToTail(temp);
				map[key] = value;
				
			}
			else{
				deleteHead();
				
				LRUNode* temp = new LRUNode(key);
				if (tail) {
					tail->next = temp;
					temp->pre = tail;
					tail = temp;
					map[key] = value;
				}
				else {
					num--;
					put(key, value);
				}
				
				

			}
		}
	}
};

int main() {
	LRUCache* cache = new LRUCache(2 /* capacity */);

	/*cout << cache->get(2) << endl;
	cache->put(2, 6);
	cout << cache->get(1) << endl;
	cache->put(1, 5);
	cache->put(1, 2);
	cache->put(1, 5);
	cache->put(1, 2);
	cout << cache->get(1) << endl;
	cout << cache->get(2) << endl;
	cout << cache->get(3) << endl;
	cout << cache->get(4) << endl;*/

	cache->put(1, 1);
	cache->put(2, 2);
	cout << cache->get(1) << endl;
	cache->put(3, 3);
	cout << cache->get(2) << endl;
	cache->put(4, 4);
	cout << cache->get(1) << endl;
	cout << cache->get(2) << endl;
	cout << cache->get(3) << endl;
	cout << cache->get(4) << endl;

	system("pause");
	}