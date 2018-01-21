g++ -shared -o libcall.so cpp.cpp student.cpp
g++ helloC.c ./libcall.so  -o helloC
g++ student_main.cpp ./libcall.so -o main