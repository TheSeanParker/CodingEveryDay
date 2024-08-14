
#include <iostream>
#include <map>
using namespace std;
int main() {
    // 创建一个 map，键为 int，值为 string
    std::multimap<int, std::string> myMap;

    // 插入一些键值对
    myMap.insert(make_pair(1,"one"));
    myMap.insert(make_pair(2,"two"));
    myMap.insert(make_pair(3,"three"));
    myMap.insert(make_pair(4,"four"));
    myMap.insert(make_pair(4,"five"));
    // 打印所有元素
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    // 删除键为1的元素
    myMap.erase(1);
    // 再次打印所有元素
    std::cout << "After erasing key 1:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}