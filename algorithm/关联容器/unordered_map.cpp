
#include <iostream>
#include <unordered_map>
#include <map>
int main() {
    // 创建一个 unordered_map，键为 int，值为 string
    std::unordered_map<int, std::string> myUnordered_Map;
    // 插入一些键值对
  
    myUnordered_Map[1] = "one";
    myUnordered_Map[2] = "two";
    myUnordered_Map[3] = "three";
    myUnordered_Map[4] = "four";
    myUnordered_Map[5] = "five";
    myUnordered_Map[6] = "six";
    myUnordered_Map[7] = "seven";

    // 打印所有元素
    for (const auto& pair : myUnordered_Map) {
        std::cout << "unordered Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    // 访问特定键的值
    // std::cout << "Value for key 2: " << myUnordered_Map[2] << std::endl;

    // 删除键为1的元素
    // myUnordered_Map.erase(1);
    // std::cout << "After erasing key 1:" << std::endl;
    // for (const auto& pair : myUnordered_Map) {
    //     std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    // }

    std::cout << "*************************************** " << std::endl;
    std::map<int, std::string> myMap;
    myMap[1] = "one";
    myMap[2] = "two";
    myMap[3] = "three";
    myMap[4] = "four";
    myMap[5] = "five";
    myMap[6] = "six";
    myMap[7] = "seven";

    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
    return 0;
}