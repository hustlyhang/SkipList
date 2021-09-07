#pragma once
#include "CSkiplist.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <time.h>
#include <thread>

#define NUM_THREADS 4400
#define TEST_COUNT 1000000

//#define INT
//#define STRING
#define STRUCT

const char* testFile = "testFile";
const int testLayer = 18;

// 自定义结构体为key，需要自定义<比较符，重载<<;必须有无参构造函数，因为跳表在创建头节点的时候会
// 创建key对象
struct KeyNode{
	KeyNode() {};
	KeyNode(int _a, int _b) :a(_a), b(_b) {}
	int a, b;
	bool operator < (const KeyNode& N) {
		return a < N.a;
	}
	bool operator == (const KeyNode& N) {
		return a == N.a;
	}
	bool operator != (const KeyNode& N) {
		return a != N.a;
	}
	friend std::ostream& operator << (std::ostream& os, const KeyNode& KN) {
		os << "Key Struct :" << KN.a << ' ' << KN.b;
		return os;
	}
};

class CTest {
public:
    CTest(){};
    ~CTest() {}
    static void TestInsertNode(int);
    static void TestSearchNode(int);
    void Test(int);
    void TestInterface();
public:
#ifdef INT
	static CSkipList<int, std::string>* skipList;
#endif // INT

#ifdef STRING
	static CSkipList<std::string, std::string>* skipList;
#endif // String

#ifdef STRUCT
	static CSkipList<KeyNode, std::string>* skipList;
#endif // STRUCT

};


inline void CTest::TestInsertNode(int threadid) {
	int tmp = TEST_COUNT / NUM_THREADS;
	for (int i = threadid * tmp, count = 0; count < tmp; i++) {
		count++;
#ifdef INT
		skipList->InsertNode(rand() % TEST_COUNT, "a");
#endif // INT
#ifdef STRING
		skipList->InsertNode(std::to_string(rand() % TEST_COUNT), "a");
#endif // STRING
#ifdef STRUCT
		skipList->InsertNode(KeyNode(rand() % TEST_COUNT, threadid), "a");
#endif // STRUCT
	}
}

inline void CTest::TestSearchNode(int threadid) {
	int tmp = TEST_COUNT / NUM_THREADS;
	for (int i = threadid * tmp, count = 0; count < tmp; i++) {
		count++;
#ifdef INT
		skipList->SearchNode(rand() % TEST_COUNT, 0);
#endif // INT
#ifdef STRING
		skipList->SearchNode(std::to_string(rand() % TEST_COUNT), 0);
#endif // STRING
#ifdef STRUCT
		skipList->SearchNode(KeyNode(rand() % TEST_COUNT, threadid), 0);
#endif // STRUCT
	}
}



inline void CTest::Test(int _mod) {
    srand(time(NULL));
    {
        int i;
        auto start = std::chrono::high_resolution_clock::now();
        if (_mod) {
            std::cout << "Testing Write:" << std::endl;
            std::cout << "Write nodes number : " << TEST_COUNT << std::endl;
        }
        else {
            std::cout << "Testing Read:" << std::endl;
            std::cout << "Read nodes number : " << TEST_COUNT << std::endl;
        }
        for (i = 0; i < NUM_THREADS; i++) {
            if (_mod) {
                std::thread* tmp = new std::thread(&TestInsertNode, i);
                tmp->join();
            }
            else {
                std::thread* tmp = new std::thread(&TestSearchNode, i);
                tmp->join();
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "usetime : " << elapsed.count() << std::endl;
        std::cout << "QPS:" << TEST_COUNT / elapsed.count() << std::endl << std::endl;
    }
}
#ifdef INT
inline void CTest::TestInterface() {
	skipList->InsertNode(1, "学习");
	skipList->InsertNode(2, "使");
	skipList->InsertNode(3, "我");
	skipList->InsertNode(4, "快乐");
	skipList->InsertNode(19, "算法");
	skipList->InsertNode(19, "真难");
	std::cout << "skipList size:" << skipList->Size() << std::endl;
	//skipList.LoadFile();
	// skipList.DumpFile();

	skipList->DisplayList();
	skipList->SearchNode(19, 1);
	skipList->DeleteNode(19);
	skipList->DisplayList();
	std::cout << std::endl << std::endl;
}
#endif // INT

#ifdef STRING
inline void CTest::TestInterface() {
	skipList->InsertNode("1", "学习");
	skipList->InsertNode("2", "使");
	skipList->InsertNode("3", "我");
	skipList->InsertNode("4", "快乐");
	skipList->InsertNode("19", "算法");
	skipList->InsertNode("19", "真难");
	std::cout << "skipList size:" << skipList->Size() << std::endl;
	//skipList.LoadFile();
	// skipList.DumpFile();

	skipList->DisplayList();
	skipList->SearchNode("19", 1);
	skipList->DeleteNode("19");
	skipList->DisplayList();
	std::cout << std::endl << std::endl;
}
#endif // STRING

#ifdef STRUCT
inline void CTest::TestInterface() {
	skipList->InsertNode(KeyNode(1, 0), "学习");
	skipList->InsertNode(KeyNode(2, 0), "使");
	skipList->InsertNode(KeyNode(3, 0), "我");
	skipList->InsertNode(KeyNode(4, 0), "快乐");
	skipList->InsertNode(KeyNode(19, 0), "算法");
	skipList->InsertNode(KeyNode(19, 0), "真难");
	std::cout << "skipList size:" << skipList->Size() << std::endl;
	//skipList.LoadFile();
	// skipList.DumpFile();

	skipList->DisplayList();
	skipList->SearchNode(KeyNode(19, 0), 1);
	skipList->DeleteNode(KeyNode(19, 0));
	skipList->DisplayList();
	std::cout << std::endl << std::endl;
}
#endif // STRUCT

#ifdef INT
CSkipList<int, std::string>* CTest::skipList = new CSkipList<int, std::string>(testLayer, testFile);
#endif // INT

#ifdef STRING
CSkipList<std::string, std::string>* CTest::skipList = new CSkipList<std::string, std::string>(testLayer, testFile);
#endif // STRING

#ifdef STRUCT
CSkipList<KeyNode, std::string>* CTest::skipList = new CSkipList<KeyNode, std::string>(testLayer, testFile);
#endif // STRUCT

