#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;
using namespace boost;

int main() {
    string str = "  hello world!";
    cout << str << endl;

    to_upper(str);
    cout << str << endl;

    trim(str);
    cout << str << endl;

    return 0;
}