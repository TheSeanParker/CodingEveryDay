#include <iostream>
  
int factor(int, int*, int*);
  
int main()
{
    int number, squared, cubed;
    int error;
  
    std::cout << "Enter a number (0 - 20): ";
    std::cin >> number;
  
    error = factor(number, &squared, &cubed);
  
    if (!error)
    {
        std::cout << "number: " << number << "\n";
        std::cout << "square: " << squared << "\n";
        std::cout << "cubed: "  << cubed   << "\n";
    }
    else
        std::cout << "Error encountered!!\n";
    return 0;
}
  
int factor(int n, int *pSquared, int *pCubed)
{
    int value = 0;
    if (n > 20)
    {
        value = 1;
    }
    else
    {
        *pSquared = n*n;
        *pCubed = n*n*n;
        value = 0;
    }
    return value;
}
