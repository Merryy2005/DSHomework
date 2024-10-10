#include <iostream>
#include <queue>

int main()
{
    std::queue<int> q1({5,3,7,5,10,2,3});
    std::queue<int> q2;
    while (!q1.empty())
    {
        std::queue<int> tmp;
        int el = q1.front();
        q1.pop();
        while (!q2.empty() && q2.front() < el)
        {
            tmp.push(q2.front());
            q2.pop();
        }
        tmp.push(el);
        while(!q2.empty())
        {
            tmp.push(q2.front());
            q2.pop();
        }
        q2 = tmp;
    }
    while (!q2.empty())
    {
        std::cout << q2.front() << " ";
        q2.pop();
    }
    std::cout << std::endl;
    return 0;
}
