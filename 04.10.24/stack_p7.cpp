#include <iostream>
#include <stack>

int main()
{
    std::stack<int> s1;
    std::stack<int> s2;
    s1.push(3);
    s1.push(2);
    s1.push(1);
    s2.push(5);
    s2.push(4);
    s2.push(3);
    s2.push(2);
    s2.push(1);
    std::stack<int> s3,s4;
    while(!s1.empty() && !s2.empty())
    {
        s4.push(s1.top());
        s4.push(s2.top());
        s1.pop();
        s2.pop();
    }
    while(!s1.empty())
    {
        s4.push(s1.top());
        s1.pop();
    }
    while(!s2.empty())
    {
        s4.push(s2.top());
        s2.pop();
    }
    while (!s4.empty())
    {
        s3.push(s4.top());
        s4.pop();
    }
    while (!s3.empty())
    {
        std::cout << s3.top() << " ";
        s3.pop();
    }
    std::cout << std::endl;
    return 0;
}
