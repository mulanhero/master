#在mac上安装tensorflow
##1. 安装pip
* https://pip.pypa.io/en/stable/installing/ 下载get-pip.py
* python get-pip.py

##2. 安装virtualenv
```
$ sudo pip install --upgrade virtualenv
$ virtualenv --system-site-packages ~/tensorflow
$ cd ~/tensorflow
$ source bin/activate 
(tensorflow)$  # 终端提示符应该发生变化
$ deactivate
```
##3. 安装tensorflow
```
$ pip install --upgrade tensorflow 
```
##4. 卸载tensorflow
```
$ rm -r ~/tensorflow
```
##5. 运行第一个程序
```
$ python
>>> import tensorflow as tf
>>> hello = tf.constant('Hello, TensorFlow!')
>>> sess = tf.Session()
>>> print(sess.run(hello))
Hello, TensorFlow
>>> a = tf.constant(10)
>>> b = tf.constant(32)
>>> print sess.run(a+b)
42
>>> 
```
