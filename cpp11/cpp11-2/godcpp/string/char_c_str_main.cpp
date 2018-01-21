#include <string>
#include <iostream>
#include <cstring>
using namespace std;

int main() {
//	char& string::operator[] (size_type nIndex)
//	const char& string::operator[] (size_type nIndex) const
    string source("abcdefg");
    cout << source[2] << endl;
    source[0] = 'A';
    cout << source << endl;

//	char& string::at (size_type nIndex)
//	const char& string::at (size_type nIndex) const
    cout << source.at(5) << endl;
    source.at(5) = 'F';
    cout << source << endl;

    //-----------------to c_str()
    string original("original");
    const char *cstr = original.c_str();
    cout << "cstr: " << cstr << ", length:" << strlen(cstr) << endl;

//	const char* string::data () const  // !!! get only the data part and exclude 'null'
//	Returns the contents of the string as a const C-style string
//	A null terminator is not appended
//	The C-style string is owned by the std::string and should not be delete
    string str1("China Shanghai");
    char *str2 = "China Shanghai";
    if (memcmp(str1.data(), str2, str1.length()) == 0) {
        cout << "str1 and str2 are equal" << endl;
    } else {
        cout << "not equal" << endl;
    }

//	size_type string::copy(char *szBuf, size_type nLength) const
//	size_type string::copy(char *szBuf, size_type nLength, size_type nIndex) const
    string test("China Shanghai Beijing");
    char result[20];
    int length = test.copy(result, 8, 6);
    result[length] = '\0';
    cout << result << endl;

    return 0;
}
