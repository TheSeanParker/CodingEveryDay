#include <iostream>
  
enum ERR_CODE { SUCCESS, ERROR };
  
ERR_CODE factor(int, int&, int&);// 这个枚举类型设计的非常好!
  
int main()
{
    int number, squared, cubed;
    ERR_CODE result;//枚举类型
  
    std::cout << "Enter a number (0 - 20): ";
    std::cin >> number;
  
    result = factor(number, squared, cubed);
  
    if (result == SUCCESS)
    {
        std::cout << "number: " << number << "\n";
        std::cout << "square: " << squared << "\n";
        std::cout << "cubed: "  << cubed   << "\n";
    }
    else
    {
        std::cout << "Error encountered!!\n";
    }
    return 0;
    // 此函数主要为了表达返回多个数值
}
  
ERR_CODE factor(int n, int &rSquared, int &rCubed)
{
    if (n > 20)
    {
        return ERROR;   // simple error code
    }
    else
    {
        rSquared = n*n;
        rCubed = n*n*n;
        return SUCCESS;
    }
}

