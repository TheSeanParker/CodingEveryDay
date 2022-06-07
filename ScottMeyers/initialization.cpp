
#include <string>
#include <iostream>
class initialization
{
private:
    /* data */
    int a;
    bool b;
    std::string c;
public:
    initialization(/* args */)
                 :a(2),b(false),c("asd")
    {

    }
    void getValue() const
    {
        std::cout<<"Output int="<<a*10<<std::endl;
        std::cout<<"Output bool="<<b<<std::endl;
        std::cout<<"Output string="<<c<<std::endl;
    }
    ~initialization();
};
initialization::~initialization()
{
}
int main(int argc, char const *argv[])
{
    /* code */
    initialization i;
    i.getValue();
    return 0;
}

