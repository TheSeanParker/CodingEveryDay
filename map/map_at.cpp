
#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
    map<string, string> tempMap = {{"china", "Apple",},
                                                                {"japan", "Banana",},
                                                                {"korea", "Mango",},};
   std::cout<<tempMap.at("china");
//    std::cout<<tempMap.at<string>("china");//左侧是错误的
}