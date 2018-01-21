#随机数

##1 c风格的随机数

在cpp11之前，只能用srand()和rand()来生产随机数，srand()用来seeding，一般用时间time(nullptr)做参数。 实质上，这是一种伪随机数。
	
	#include <iostream>
	#include <ctime>
	
	int get_random(int min, int max) {
	    srand(time(nullptr));
	    return rand() % (max-min+1) + min;
	} 
	
	int main() {
	    std::cout << RAND_MAX << std::endl;
	    int result = get_random(1, 10000);
	    std::cout << result << std::endl;
	}

##2 cpp11提供的随机数产生engine

cpp11定义了engine， engine adapter，distribution。 `#include <random>`

###2.1 `random_device`

random_device可以通过硬件engine来产生一个随机数。如果没有硬件，则通过软件模拟。 
易用，不需要其他参数。

	#include <random>
	std::random_device rd;
    std::cout << "entropy:" << rd.entropy() << std::endl; //entropy熵
    std::cout << "min:" << rd.min() << std::endl;
    std::cout << "max:" << rd.max() << std::endl;
    std::cout << "random number:" << rd() << std::endl;

###2.1 `mt19937`
mt19937为Mersenne_twister_engine(梅森旋转)的一个特例，生产的随机数质量最高。

####2.1.1 一个简单例子

	std::mt19937 engine(time(nullptr)); //初始化engine
    std::uniform_int_distribution<int> dist(1, 10000); //申明分布
    int random_num = dist(engine);  //以engine作参，分布同名函数产生随机数
    std::cout << random_num << std::endl;

####2.1.2 用`std::bind`把dist和engine绑定
为了能在算法中使用，可以用`std::bind`把dist和engine绑定，例如：

	std::mt19937 engine(time(nullptr));
    std::uniform_int_distribution<int> dist(1, 10000);
    
    std::vector<int> vec(10);
    auto gen =  std::bind(dist, engine);  //#include <algorithm>
	//generate会改写现有元素，但不会新增或插入元素
    std::generate(vec.begin(), vec.end(), gen); //#incude <algorithm>

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, "\n"));

##3 cpp11提供的随机数产生分布distribution
###3.1 均匀分布`uniform_int_distribution`和`uniform_real_distribution`

	const unsigned int START = 1;
    const unsigned int END = 99;
    const size_t ITERATIONS = 1000000;

    std::mt19937 engine(time(nullptr));
    std::uniform_int_distribution<int> dist(START, END);
    auto gen = std::bind(dist, engine);

    std::map<int, int> num2appears;

    for (size_t i = 0; i < ITERATIONS; ++i) {
        auto rd = gen();   //生产随机数
        ++num2appears[rd];  //cool!
    }

    for (int tmp = START; tmp <= END; ++tmp) {
        if (num2appears.find(tmp) != num2appears.end()) {
            std::cout << tmp << ":" << num2appears[tmp] << std::endl;
        } else {
            std::cout << tmp << ": not appeared" << std::endl;
        }
    }
 
###3.2 正态分布`normal_distribution<double> dist(u, e)`

	const unsigned int START = 1;
    const unsigned int END = 99;
    const size_t ITERATIONS = 1000000;

    std::mt19937 engine(time(nullptr));
    std::normal_distribution<double> dist(50, 10); //double, u, e
    auto gen = std::bind(dist, engine);

    std::map<int, int> num2appears;

    for (size_t i = 0; i < ITERATIONS; ++i) {
 		//gen()将产生double，故static_cast<int>()之
        auto rd = static_cast<int>(gen());  
        ++num2appears[rd];
    }

    for (int tmp = START; tmp <= END; ++tmp) {
        if (num2appears.find(tmp) != num2appears.end()) {
            std::cout << tmp << ":" << num2appears[tmp] << std::endl;
        } else {
            std::cout << tmp << ": not appeared" << std::endl;
        }
    }


