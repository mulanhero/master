#include <string>
#include <iostream>
#include <sstream>

using namespace std;
int main() {
    //1. string::string(const string& strString)
    string orig("China Shanghai");
    string target(orig);
    cout << target << endl;

    //	string::string(const string& strString, size_type unIndex)
    //	string::string(const string& strString, size_type unIndex, size_type unLength)
    string source("China Shanghai Beijing");
    string target1(source, 6);
    cout << target1 << endl;
    string target2(source, 6, 8);
    cout << target2 << endl;

//-------------from c-style ------------
//	string::string(const char *szCString)
    const char *name = "China Shanghai";
    string name2(name);
    cout << name2 << endl;

//	string::string(const char *szCString, size_type unLength)
    const char *src1 = "China Shanghai";
    string src2(src1, 5);
    cout << src2 << endl;
//------------------with char
    string src3(4, 'S');
    cout << src3 << endl;

    //--------------int,double => string
    double pi = 3.14;
    ostringstream oss;
    oss << pi;
    string pi_str(oss.str());
    cout << pi_str << endl;

    //-------------string => double, int
    string myPiStr("3.1415");
    double myPi;
    istringstream iss(myPiStr);
    iss >> myPi;
    cout << myPi << endl;
}
