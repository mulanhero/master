#include <iostream>
#include <deque>
#include <algorithm>
#include <string>

using namespace std;

typedef struct FileInfo {
    string filename;
    int size;
} FileInfo_t;

int comp(const FileInfo_t& a, const FileInfo_t& b)  {
    return a.filename > b.filename ? 0 : 1;
}

int main()
{
    deque<FileInfo_t> files;
    files.push_back( { string("kkkkkk"), 12 });
    files.push_back( { string("aaaaa"), 23 });

    for (auto file : files) {
        cout << file.filename << ":" << file.size << endl;
    }

    sort(files.begin(), files.end(), comp);

    for (auto file : files) {
        cout << file.filename << ":" << file.size << endl;
    }

    return 0;
}
