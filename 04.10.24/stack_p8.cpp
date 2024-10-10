#include <iostream>
#include <stack>

bool contains(std::stack<int> s , int v)
{
    while(!s.empty())
    {
        if(s.top() == v)
        {
            return true;
        }
        s.pop();
    }
    return false;
}

int main()
{
    std::stack<int> s1({5,3,7,5,10,2,3});
    std::stack<int> s2;
    while (!s1.empty())
    {
        if(!contains(s2 , s1.top()))
        {
            s2.push(s1.top());
        }
        s1.pop();
    }
    while (!s2.empty())
    {
        std::cout << s2.top() << " ";
        s2.pop();
    }
    std::cout << std::endl;
    return 0;
}
