#include "CSkiplist.h"
#include <iostream>

const char* filePath = "testfile";

int main() {
	CSkipList<int, std::string> skipList(6, filePath);
	/*skipList.InsertNode(1, "学习");
	skipList.InsertNode(2, "使");
	skipList.InsertNode(3, "我");
	skipList.InsertNode(4, "快乐");
	skipList.InsertNode(19, "算法");
	skipList.InsertNode(19, "真难");*/
	std::cout << "skipList size:" << skipList.Size() << std::endl;
	skipList.LoadFile();
	//skipList.DumpFile();
	skipList.DisplayList();
	return 0;
}