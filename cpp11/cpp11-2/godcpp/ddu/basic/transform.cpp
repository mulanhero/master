#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string orig("node[11-14].hust.cn");
    auto dash_pos = orig.find('-');
    auto left_pos = orig.find('[');
    auto right_pos = orig.find(']');

    string prefix = orig.substr(0, left_pos);
    string postfix = orig.substr(right_pos + 1);

    auto start = atoi(orig.substr(left_pos + 1, dash_pos - left_pos - 1).c_str());
    auto end = atoi(orig.substr(dash_pos + 1, right_pos - dash_pos - 1).c_str());

    cout << "dash_pos-left_pos" << dash_pos - left_pos << endl;

    stringstream target;
    for (auto i = start; i <= end; i++) {
        target << prefix << i << postfix << ",";
    }

    cout << target.str() << endl;

    cout << "prefix:" << prefix << ", start:" << start << ", end:" << end << ", postfix:" << postfix
            << endl;

    return 0;
}
