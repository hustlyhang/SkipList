#include "Test.h"

int main() {
	CTest test;
	// test.TestInterface();// ²âÊÔ½Ó¿Ú
	test.Test(1);// write
	test.Test(0);// read
	return 0;
}