#时间

##1 ratio
分数定义在`#include <ratio>`, 分子和分母的类型为`std::intmax_t`， 定义分数用`typedef`来完成，例如: `typedef std::ratio<1, 60> my_ratio;` 表示1/60；可通过`my_ratio::num`来查看分子，`my_ratio::den`来查看分母。

分数求和也用`typedef`来完成，有个特殊的`ratio_add<ratio1， ratio2>`来定义，例如：`typedef std::ratio_add<my_ratio1, my_ratio2> my_ratio_sum;` 则`my_ratio_sum`即为求得的和。

分数比较也用`typedef`来完成，有个特殊的`ratio_less<ratio1， ratio2>`来判定是否小于，例如`typedef std::ratio_less<my_ratio1, my_ratio2> is_less_result;`，`is_less_result::value`即为判定是否小于，其值为1或者0，通过`std::boolalpha`可转换为`true`或`false`。

* 简写： 以1做分母时，可以省略,例如`typedef std::ratio<10,1> ten;` 可以省略为`typedef std::ratio<10> ten;`。

###1.1 例子
	
	const std::intmax_t numerator = 1;   	//分子
    const std::intmax_t denominator = 60;	//分母
    
	//typedef一个分数，::num为分子，::den为分母
    typedef std::ratio<numerator, denominator>  my_ratio1;
    std::cout << my_ratio1::num << ":" << my_ratio1::den << std::endl;

    typedef std::ratio<1, 30>  my_ratio2;
    std::cout << my_ratio2::num << ":" << my_ratio2::den << std::endl;

    //ratio_add<f1, f2>::type f3;
    typedef std::ratio_add<my_ratio1, my_ratio2> my_ratio_sum; 
    std::cout << my_ratio_sum::num << ":" << my_ratio_sum::den << std::endl; 

    //ratio_less<f1, f2> is_less_result;
    typedef std::ratio_less<my_ratio1, my_ratio2> is_less_result;
    std::cout << std::boolalpha << is_less_result::value << std::endl;

###1.2 `#include <ratio>`中已定义好的常用分数

	typedef ratio<1, 1000000000000000000000000> yocto; 
    typedef ratio<1, 1000000000000000000000> zepto; 
    typedef ratio<1, 1000000000000000000> atto; 
    typedef ratio<1, 1000000000000000> femto; 
    typedef ratio<1, 1000000000000> pico; 
    typedef ratio<1, 1000000000> nano; 
    typedef ratio<1, 1000000> micro; 
    typedef ratio<1, 1000> milli; 
    typedef ratio<1, 100> centi; 
    typedef ratio<1, 10> deci; 
    typedef ratio<10, 1> deca; 
    typedef ratio<100, 1> hecto; 
    typedef ratio<1000, 1> kilo; 
    typedef ratio<1000000, 1> mega; 
    typedef ratio<1000000000, 1> giga; 
    typedef ratio<1000000000000, 1> tera; 
    typedef ratio<1000000000000000, 1> peta; 
    typedef ratio<1000000000000000000, 1> exa; 
    typedef ratio<1000000000000000000000, 1> zetta; 
    typedef ratio<1000000000000000000000000, 1> yotta;

##2 duration
`duration`表示一段时间，定义在`#include <chrono>`，通过模板`std::chrono::duration<tick_num_type, tick_period> my(num)；`定义，`tick_num_type`可以是long或者double， 而`tick_peroid`一般为通过ratio定义的分数常量， 如ratio(1)表示周期为1秒，ratio(60)表示周期60秒即1分钟，ratio(1,60)表示周期为1/60秒。

count()获取该duration包含多少个tick。

duration支持`+,-,*,/,%,++,--,+=,-=,*=,/=,%=,`比较运算符`>,>=,<,<=`。

##2.1  `typedef定义好的duration`
	
	typedef duration<X 64 bits, nano> nanoseconds; 
	typedef duration<X 55 bits, micro> microseconds;
	typedef duration<X 45 bits, milli> miliseconds;
	typedef duration<x 35 bits>	seconds;
	typedef duration<X 29 bits, ratio<60>>  minutes;
	typedef duration<X 23 bits, ratio<3600>> hours;

示例：

	using std::chrono::hours;
    using std::chrono::minutes;
    using std::chrono::seconds;
    auto t = hours(1) + minutes(20) + seconds(30);
    std::cout << seconds(t).count() << std::endl; //output: 4830

##2.2 直升机: duration示例
###2.2.1 eg1
	
	std::chrono::duration<long, std::ratio<1>> d1(123)；
	//表示123个tick,每个tick的周期为1秒；即总duration为123秒。
	//另外，当周期为1秒std::ratio<1>时可省略，即等同于std::chrono::duration<long> d1(123);

	std::chrono::duration<double, std::ratio<1,60>> d2;//1/60秒
	std::chrono::duration<long long, std::milli> d3; //毫秒

	
###2.2.2 eg1
	
	std::chrono::duration<long, std::ratio<60>> d1(123); 
    std::cout << d1.count() << std::endl;

    std::chrono::duration<double> d2;
    d2 = d2.max();
    std::cout << d2.count() << std::endl;

    std::chrono::duration<long, std::ratio<60>> d3(10); //10minutes
    std::chrono::duration<long, std::ratio<1>> d4(14); //14 seconds
    if (d3 > d4) {
        std::cout << "d3 > d4" << std::endl;
    } else {
        std::cout << "d3 <= d4" << std::endl;
    }
    ++d4;
    d4 *= 2;
    std::cout << d4.count() << " seconds"<< std::endl;

    std::chrono::duration<long, std::ratio<1>> d5 = d3 + d4;
    std::cout << "d5:" << d5.count() << " seconds"<< std::endl;
    std::chrono::duration<double, std::ratio<60>> d6 = d3 + d4;
    std::cout << "d6:" << d6.count() << " minutes" << std::endl;

    std::chrono::duration<long> d7(30);
    std::chrono::duration<double, std::ratio<60>> d8 = d7;
    std::cout << d8.count() << " minutes"<< std::endl;

	
##3 time
clock有三个实现，且有`time_point`和`duration`。目前定义的三个实现为：

* `system_clock`表示系统walltime
* `steady_clock`表示保证其`time_point`绝不衰减的时钟。
* `high_resolution_clock`表示具有最小tick周期分辨度的时钟,其有可能是`system_clock`或者`steady_clock`的别名。这取决于编译器的实现。

*  now()可以获取类型time_point的当前时间。

###3.1 system_clock

####3.1.1 `to_time_t()`和`from_time_t()`
`system_clock::to_time_t()`把`time_point`类型转换为c风格的`time_t`类型
`system_clock::from_time_t()`则相反。
	
	#include <ctime>
	#include <chrono>

	using std::chrono::system_clock;
    system_clock::time_point tpoint = system_clock::now();
    time_t tt = system_clock::to_time_t(tpoint); 
    struct tm* timeinfo = localtime(&tt);

	//convert to readable format
    char buffer[80] = {0};
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    std::cout << buffer << std::endl;

    //printf("Current local time: %s", asctime(timeinfo));
	//put_time will be in #include <iomanip>, but has not been implemented util gcc-4.9 yet 
	//std::cout << std::put_time(timeinfo, "%H:%M:%S") << std::endl;


####3.1.2 timecost

	#include <iostream>
	#include <cmath>
	#include <chrono>
	
	int main() {
	    using std::chrono::system_clock;
	    using std::chrono::duration;
	
	    auto start = system_clock::now();
	    
	    double d = 0;
	    for (int i = 0; i < 100000; ++i) {
	        d += sqrt(sin(i)*cos(i));
	    }
	
	    auto end = system_clock::now();
	    auto diff = end - start;
	    
	    double time_cost_ms = duration<double, std::milli>(diff).count();
	    std::cout << "timecost : " << time_cost_ms << " ms" << std::endl;
	}

###3.2 time_point

`time_point`表示从某个epoch到目前的duration。一个`time_point`总是和一个clock关联，epoch为原点，duration用秒来度量。

####3.2.1 `time_since_epoch()`

	#include <iostream>
	#include <chrono>
	#include <ctime>
	
	int main ()
	{
	  using namespace std::chrono;
	
	  system_clock::time_point tp_epoch; //设置epoch值
	  std::time_t t = system_clock::to_time_t(tp_epoch);
	  std::cout << "tp_epoch is: " << ctime(&t);
	 
      //这里time_point是std::chrono::time_point，而不是system_clock::time_point
	  time_point<system_clock,duration<int>> tp_seconds(duration<int>(1));
	  system_clock::time_point tp(tp_seconds);
	
	  std::cout << "1 second since system_clock epoch = ";
	  std::cout << tp.time_since_epoch().count();
	  std::cout << " system_clock periods." << std::endl;
	
	  // display time_point:
	  std::time_t tt = system_clock::to_time_t(tp);
	  std::cout << "time_point tp is: " << ctime(&tt);
	
	  return 0;
	}

	//output
	tp_epoch is: Thu Jan  1 08:00:00 1970
	1 second since system_clock epoch = 1000000000 system_clock periods.
	time_point tp is: Thu Jan  1 08:00:01 1970
