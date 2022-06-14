
class Solution {
public:
    string longestPalindrome(string s) {
           int len=s.size();
           int maxlen=1;
           int start=0;
           string tep;
           bool result[len][len];
           if(len==0||len==1)
             return s;

           for(int i=0;i<len;i++)
           {
               result[i][i]=true;
           }
           //2个的时候
           for(int i=0;i<len;i++)
           {
               if(s[i]==s[i+1])
               {
                   result[i][i+1]=true;
                   start=i;
                   maxlen=2;
               }
           }
           std::cout<<"start=" <<start <<std::endl;
           std::cout<<"maxlen="<<maxlen<<std::endl;
           //3个及以上
           for(int l=3;l<=len;l++)
           {
                for(int i=0;i<len;i++)//i+l-1<len
                {
                    int j=i+l-1;
                    if(s[i]==s[j] && result[i+1][j-1]==true)
                    {
                     result[i][j]=true;
                     start=i;
                     maxlen=l;
                    }
                }
           }
           std::cout<<"start=" <<start <<std::endl;
           std::cout<<"maxlen="<<maxlen<<std::endl;
           return s.substr(start,maxlen);//String containing the substring [start, start+maxlen)
    }
};
//Line 37: Char 38: runtime error: load of value 254, which is not a valid value for type 'bool' (solution.cpp)
//SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:46:38