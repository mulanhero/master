#gtest

##0 背景
unzip后，进入代码目录，`cd make`; 这里有个`Makefile`给出了一个模板，默认把`sample/sample1.cc sample1.h spamle1_unittest.cc`编译成bin`sample1_unittest`。

执行`make`得到`*.o, gtest_main.a, sample1_unittest`。

	[jimmy@centos7 make]$ ./sample1_unittest 
	Running main() from gtest_main.cc
	[==========] Running 6 tests from 2 test cases.
	[----------] Global test environment set-up.
	[----------] 3 tests from FactorialTest
	[ RUN      ] FactorialTest.Negative
	[       OK ] FactorialTest.Negative (0 ms)
	[ RUN      ] FactorialTest.Zero
	[       OK ] FactorialTest.Zero (0 ms)
	[ RUN      ] FactorialTest.Positive
	[       OK ] FactorialTest.Positive (0 ms)
	[----------] 3 tests from FactorialTest (0 ms total)
	
	[----------] 3 tests from IsPrimeTest
	[ RUN      ] IsPrimeTest.Negative
	[       OK ] IsPrimeTest.Negative (0 ms)
	[ RUN      ] IsPrimeTest.Trivial
	[       OK ] IsPrimeTest.Trivial (0 ms)
	[ RUN      ] IsPrimeTest.Positive
	[       OK ] IsPrimeTest.Positive (0 ms)
	[----------] 3 tests from IsPrimeTest (0 ms total)
	
	[----------] Global test environment tear-down
	[==========] 6 tests from 2 test cases ran. (0 ms total)
	[  PASSED  ] 6 tests.


##1 示例

###1.1 eg1

把gtest/include 和 gtest_main.a分别拷贝到当前目录

	#include <gtest/gtest.h>
	#include <iostream>
	
	int add(int a, int b) {
	    return a + b;
	}
	
	std::string concat(std::string str1, std::string str2) {
	    return str1 + str2;
	}
	
	TEST(addTestSuite, addTestCase1) {
	    EXPECT_EQ(10, add(4, 6));
	    EXPECT_EQ(100, add(40, 60));
	}
	
	//测试用例的名字，测试名称
	//类名， 方法名
	//文件名，函数名
	TEST(concatTestSuite, concatTestCase1) {
	    ASSERT_STREQ("jimmycao", concat("jimmy", "cao").c_str());
	}
	
	int main(int argc, char* argv[]) {
	    testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
	}
	
	g++ sample_01.cpp -o sample-01 -I ./include lib/gtest_main.a
	[jimmy@centos7 gtest]$ ./sample-01 
	[==========] Running 2 tests from 2 test cases.
	[----------] Global test environment set-up.
	[----------] 1 test from addTestSuite
	[ RUN      ] addTestSuite.addTestCase1
	[       OK ] addTestSuite.addTestCase1 (0 ms)
	[----------] 1 test from addTestSuite (0 ms total)
	
	[----------] 1 test from concatTestSuite
	[ RUN      ] concatTestSuite.concatTestCase1
	[       OK ] concatTestSuite.concatTestCase1 (0 ms)
	[----------] 1 test from concatTestSuite (0 ms total)
	
	[----------] Global test environment tear-down
	[==========] 2 tests from 2 test cases ran. (0 ms total)
	[  PASSED  ] 2 tests.


###1.2 eg2

