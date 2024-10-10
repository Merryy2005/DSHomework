#include <iostream>
#include <stack>

int main()
{
    std::stack<int> s1({5,3,7,5,10,2,3});
    std::stack<int> s2;
    while (!s1.empty())
    {
        int el = s1.top();
        s1.pop();
        while (!s2.empty() && s2.top() < el)
        {
            s1.push(s2.top());
            s2.pop();
        }
        s2.push(el);
    }
    while (!s2.empty())
    {
        std::cout << s2.top() << " ";
        s2.pop();
    }
    std::cout << std::endl;
    return 0;
}
