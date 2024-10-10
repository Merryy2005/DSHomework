#ifndef STACK_H
#define STACK_H

#include "List.hpp"

namespace mystl
{
    template<typename T>
    class Stack : private List<T>
    {
        public:
            Stack();
            Stack(std::size_t);
            Stack(const Stack&);
            Stack(Stack&&) noexcept;
            Stack& operator= (const Stack&);
            Stack& operator= (Stack&&) noexcept;
            void push(const T& value);
            void pop();
            T& top();
            const T& top() const;
            bool empty() const;
            std::size_t size() const;
            void print() const;
    };
}

template<typename T>
mystl::Stack<T>::Stack() : mystl::List<T>() {}

template<typename T>
mystl::Stack<T>::Stack(std::size_t count) : mystl::List<T>(count) {}

template<typename T>
mystl::Stack<T>::Stack(const Stack& other) : mystl::List<T>(other) {}

template<typename T>
mystl::Stack<T>::Stack(Stack&& other) noexcept : List<T>(std::move(other)) {}

template<typename T>
mystl::Stack<T>& mystl::Stack<T>::operator=(const Stack& other)
{
    if (this != &other)
    {
        List<T>::operator=(other);
    }
    return *this;
}

template<typename T>
mystl::Stack<T>& mystl::Stack<T>::operator=(Stack&& other) noexcept
{
    if (this != &other)
    {
        List<T>::operator=(std::move(other));
    }
    return *this;
}

template<typename T>
void mystl::Stack<T>::push(const T& value)
{
    List<T>::push_back(value);
}

template<typename T>
void mystl::Stack<T>::pop()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    List<T>::pop_back();
}

template<typename T>
T& mystl::Stack<T>::top()
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    return List<T>::back();
}

template<typename T>
const T& mystl::Stack<T>::top() const
{
    if (empty())
    {
        throw std::out_of_range("Stack is empty");
    }
    return List<T>::back();
}

template<typename T>
bool mystl::Stack<T>::empty() const
{
    return List<T>::empty();
}

template<typename T>
std::size_t mystl::Stack<T>::size() const
{
    return List<T>::size();
}

template<typename T>
void mystl::Stack<T>::print() const
{
    List<T>::print();
}

#endif //STACK_H