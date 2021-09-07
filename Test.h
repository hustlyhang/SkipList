#pragma once
#include "CSkiplist.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <time.h>
#include <thread>

#define NUM_THREADS 4400
#define TEST_COUNT 1000000

const char* testFile = "testFile";
const int testLayer = 18;

class CTest {
public:
    CTest(){};
    ~CTest() {}
    static void TestInsertNode(int);
    static void TestSearchNode(int);
    void Test(int);
    void TestInterface();
public:
    static CSkipList<int, std::string>* skipList;
};

inline void CTest::TestInsertNode(int threadid) {
    int tmp = TEST_COUNT / NUM_THREADS;
    for (int i = threadid * tmp, count = 0; count < tmp; i++) {
        count++;
        skipList->InsertNode(rand() % TEST_COUNT, "a");
    }
}

inline void CTest::TestSearchNode(int threadid) {
    int tmp = TEST_COUNT / NUM_THREADS;
    for (int i = threadid * tmp, count = 0; count < tmp; i++) {
        count++;
        skipList->SearchNode(rand() % TEST_COUNT, 0);
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

CSkipList<int, std::string>* CTest::skipList = new CSkipList<int, std::string>(testLayer, testFile);