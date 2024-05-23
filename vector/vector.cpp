

// #include<iostream>
// using namespace std;
// int a=1;
// int main(int argc, char const *argv[])
// {
//     a=2;
//     cout<<"a="<<a<<endl;
//     return 0;
// }

    #include<iostream>  
    #include<vector>  
    using namespace std;  
    void fun(vector<char>& test)
    {
        for(int i=0;i<test.size();i++)  
        {
                cout<<test.back()<<"---"<<test.size()<<std::endl;  
                test.pop_back();
        }
    }
    int main()  
    {  
        vector<char> v;  
        v.push_back('j');  
        v.push_back('s');  
        v.push_back('v');  
        v.push_back('a');  
        // fun(v);        
        float a=1.1;
        float b=1.6;
        float c=2.0;
        cout<<int(a)<<""<<int(b)<<""<<int(c)<<endl;
        return 0;  
    }  