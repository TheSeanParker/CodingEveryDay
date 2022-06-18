#include<vector>
#include<iostream>
#include<climits>
#include<algorithm>
#include<sstream>
//coding 在精简的基础上要进行必要的炫技
using namespace std;
class Solution {
    vector<int>count;
    int minCount(vector<int>& coins, int rem) 
    {
        if (rem <  0) return -1;
        if (rem == 0) return 0;
        if (count[rem - 1] != 0) return count[rem - 1];
        int Min = INT_MAX;
        for (int coin:coins) 
        {
            int res = minCount(coins, rem - coin);
            if (res >= 0 && res < Min) {
                Min = res + 1;
            }
        }
        count[rem - 1] = Min == INT_MAX ? -1 : Min;
        return count[rem - 1];
    }
 public:
    int coinChange(vector<int>& coins, int amount) 
    {
        if (amount < 1) return 0;
        count.resize(amount);
        return minCount(coins, amount);
    }
};
//下面是封装的部分

void trimLeftTrailingSpaces(string &input) 
{
    input.erase( input.begin(), find_if(input.begin(), input.end(), [](int ch) {return !isspace(ch);}) );
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

int stringToInteger(string input) {
    return stoi(input);//string 2 int
}
//主函数
int main() {
    string line;
    while (getline(cin, line)) //将第一行输入，赋值到line里面，同时判断输入流是否正确
    {
        vector<int> coins = stringToIntegerVector(line);
        getline(cin, line);
        int amount = stringToInteger(line);
        int ret = Solution().coinChange(coins, amount);

        string out = to_string(ret);
        cout << "最终结果="<<out << endl;
    }
    return 0;
}
//测试用例 [1,2,5]
//        11
//最终结果=3