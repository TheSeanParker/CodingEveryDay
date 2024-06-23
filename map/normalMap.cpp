#include <iostream>
#include <map>
#include <utility>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;

int main() {
    map<int, string> tempMap = {{7, "Apple",},
                                                                {2, "Banana",},
                                                                {3, "Mango",},
                                                                {4, "Raspberry",},
                                                                {5, "Blackberry",},
                                                                {6, "Cocoa",}};
cout<<"tempMap[1]="<<tempMap[10]<<endl;
// 索引一个不存在的位置,它的字符串是0,也相当于向这个字符串里添加字符了
    //范围for循环
    // for (const auto &item : tempMap) {
    //     cout << "[" << item.first << "," << item.second << "]\n";
    // }
    tempMap.insert(std::make_pair(8, "Jack"));
   auto iter_1= tempMap.begin();
   cout<<"输出 first="<<(iter_1->first)<<endl;
   cout<<"输出 second="<<(iter_1->second)<<endl;
    for (auto iter = tempMap.begin(); iter != tempMap.end(); ++iter){
        cout << "[" << iter->first << ","
                    << iter->second << "]\n";
    }
    cout << endl;
    return 0;
}
