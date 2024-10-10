#include <iostream>
#include <queue>

bool contains(std::queue<int> q , int v)
{
    while(!q.empty())
    {
        if(q.front() == v)
        {
            return true;
        }
        q.pop();
    }
    return false;
}

int main()
{
    std::queue<int> q1({5,3,7,5,10,2,3});
    std::queue<int> q2;
    while (!q1.empty())
    {
        if(!contains(q2 , q1.front()))
        {
            q2.push(q1.front());
        }
        q1.pop();
    }
    while (!q2.empty())
    {
        std::cout << q2.front() << " ";
        q2.pop();
    }
    std::cout << std::endl;
    return 0;
}
