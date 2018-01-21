ps -ef|grep -i gateway|awk '{print $2}'|xargs kill -9
