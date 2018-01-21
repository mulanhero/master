#glog

##0 介绍
Google log提供了一种应用级的日志库。该库基于C++ stream和各种helper宏定义。例如：

	#include <glog/logging.h>
	int main() {
		google::InitGoogleLogging(argv[0]);
		//...
		LOG(INFO) << "Found " << num_cookies << " cookies"; 		
	}

Google log定义了一系列宏来简化日志编码:

* 指定severity级别
* 通过命令行控制日志行为
* 根据条件判断打印日志
* 如果某个条件没有满足，则abort进程
* 引入自定义的日志级别

##1 severity level

INFO，WARNING，ERROR，FATAL.

对fatal来说，打印日志后，将终止进程。注意：severity level高的日志不仅仅将出现在本severity的日志中，也将出现在**低**级别的日志中。例如：FATAL将出现在FATAL，ERROR，WARNING，INFO所有的日志。

DFATAL: 将会像ERROR一样记录日志但不会像FATAL一样导致进程退出；一般用于production环境。注意：没有NDEBUG级别。

如果没有特别指明，glog将会把日志输出到`/tmp/<program_name>.<hostname>.<user_name>.log.<severity_level>.<data>.<time>.<pid>`,例如：`/tmp/hello_world.example.com.hamaji.log.INFO.20080709-222411.10474`。

默认情况下，除了输出到文件，glog还会把ERROR/FATAL同时输出到标准错误输出(stderr)。

##2 Setting flags

* logtostderr:　把日志输出到stderr而不是logfile
	* 对于binary flag，可以设值为：1, true,yes 或者 0, flase, no
	* ./your_appliction --logtosterr=1 
	* GLOG_logtostderr=1 ./your_application
* stderrthreshold : 把该threshold级别**以上**的日志除了输出到logfile，也输出到stderr
	* (int, default=2, //ERROR)
	* INF，WARNING，ERROR，FATAL对应0，1，2，3
* minloglevel:  (int, default=0, which is INFO)
	* 只输出该级别以上的日志
* log_dir (string, default="")
	* 如果指明log_dir，则日志会输出到该目录而不是缺省目录。
* v (int, default=0)
	* VLOG(m) 显示m值小于等于v值的日志。 
	* 可通过--vmodule覆盖
* vmodule (string, default="")
	* 按模块设置verbose level。
	* `--vmodule gfs*=1 hdfs*=2`

也可以在代码行中修改设置，设置完成后，记得通过`google::InitGoogleLogging(argv[0])`

	LOG(INFO) << "file";
   	// Most flags work immediately after updating values.
   	FLAGS_logtostderr = 1;
  	LOG(INFO) << "stderr";
   	FLAGS_logtostderr = 0;
   	// This won't change the log destination. If you want to set this
   	// value, you should do this before google::InitGoogleLogging .
   	FLAGS_log_dir = "/some/log/directory";
   	LOG(INFO) << "the same file";

##3 Conditional / Occasional Logging


