#include "CSkiplist.h"
#include <iostream>

const char* filePath = "testfile";

int main() {
	CSkipList<int, std::string> skipList(6, filePath);
	//skipList.InsertNode(1, "1");
	/*skipList.InsertNode(1, "学");
	skipList.InsertNode(3, "算法");
	skipList.InsertNode(7, "认准");
	skipList.InsertNode(8, "微信公众号：代码随想录");
	skipList.InsertNode(9, "学习");
	skipList.InsertNode(19, "算法不迷路");
	skipList.InsertNode(19, "赶快关注吧你会发现详见很晚！");*/
	std::cout << "skipList size:" << skipList.Size() << std::endl;

	//skipList.DisplayList();
	//skipList.DumpFile();
	skipList.LoadFile();
	skipList.DisplayList();
	// printf("sizeof unsigned short:%d", sizeof(unsigned short));
	return 0;
}