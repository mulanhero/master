#include <cstdarg>
#include <iostream>

using namespace std;

double findAverage(int count, ...) {
    long total = 0;
    va_list list;
    /*
     * We initialize the va_list using va_start. 
     * The first parameter is the list to initialize. 
     * The second parameter is the last non-ellipse parameter.
     */
    va_start(list, count);
    for (int i = 0; i < count; i++) {
    total += va_arg(list, int);
}
//	Cleanup the va_list when we're done.
va_end(list);
return static_cast<double>(total) / count;
}

int main() {
cout << findAverage(5, 1, 2, 3, 4, 5) << endl;
cout << findAverage(6, 1, 2, 3, 4, 5, 6) << endl;
return 0;
}
