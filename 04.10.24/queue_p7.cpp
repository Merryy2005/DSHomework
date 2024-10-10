#include <iostream>
#include <queue>

int main()
{
    std::queue<int> q1({1,2,3});
    std::queue<int> q2({1,2,3,4,5});
    std::queue<int> q3;
    while(!q1.empty() && !q2.empty())
    {
        q3.push(q1.front());
        q3.push(q2.front());
        q1.pop();
        q2.pop();
    }
    while(!q1.empty())
    {
        q3.push(q1.front());
        q1.pop();
    }
    while(!q2.empty())
    {
        q3.push(q2.front());
        q2.pop();
    }
    while (!q3.empty())
    {
        std::cout << q3.front() << " ";
        q3.pop();
    }
    std::cout << std::endl;
    return 0;
}
