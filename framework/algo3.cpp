#include<iostream>
#include<vector>
#include<map>
#include<array>

int text_read ()
{

}

int main(int argc, char const *argv[])
{
    int text [10][10];
    int min = 0;
    int a=19;
    std::map <int,int> another;
    
    for(int i=0;i<10;i++)
    {
        if(text[1][i]>0)
        {
          for(auto& i : text)
           {
           //  another[i] = 0;
           } 
    }
        if(text[1][i]<min && text[1][i]!=0)
        {
         min = text[1][i];
        }

    }
    return 0;
}
