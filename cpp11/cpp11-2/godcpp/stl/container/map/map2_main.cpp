#include <iostream>
#include <map>
#include <list>

using namespace std;
int main() {
    map<string, list<string>*> jobId2ResGroupIds;

    list < string > *resGroupIds = new list<string>;
    resGroupIds->push_back(string("value11"));
    resGroupIds->push_back(string("value12"));
    jobId2ResGroupIds[string("key1")] = resGroupIds;

    list < string > *resGroupIdsBak = jobId2ResGroupIds[string("key1")];
    cout << "original:" << endl;
    for (list<string>::iterator it = resGroupIdsBak->begin(); it != resGroupIdsBak->end(); it++) {
        cout << *it << endl;
    }

    resGroupIdsBak->push_back(string("value13"));

    list < string > *resGroupIdsBak2 = jobId2ResGroupIds[string("key1")];
    cout << "after insert:" << endl;
    for (list<string>::iterator it = resGroupIdsBak2->begin();
            it != resGroupIdsBak2->end(); it++) {
        cout << *it << endl;
    }

    //-----------------check if has key
    list < string > *rgids = jobId2ResGroupIds[string("key3")];
    if (!rgids) {
        cout << "no key3 in map" << endl;
    } else {
        cout << "has key3 in map" << endl;
    }

    return 0;
}
