#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

namespace mystl
{
    template<typename T>
    class Queue
    {
        private:
            T* m_data;
            int m_front;
            int m_back;
            int m_capacity;

            void resize(int new_capacity);

        public:
            Queue();
            Queue(const Queue&);
            Queue(Queue&&) noexcept;
            Queue& operator=(const Queue&);
            Queue& operator=(Queue&&) noexcept;
            ~Queue();
            void push(const T& value);
            void pop();
            T& front();
            const T& front() const;
            T& back();
            const T& back() const;
            bool empty() const;
            int size() const;
            void print() const;
    };
}

template<typename T>
mystl::Queue<T>::Queue() : m_data(nullptr), m_front(0), m_back(0), m_capacity(0) {}

template<typename T>
mystl::Queue<T>::Queue(const Queue& other) : m_front(other.m_front), m_back(other.m_back), m_capacity(other.m_capacity)
{
    m_data = new T[m_capacity];
    for (int i = 0; i < m_back; ++i)
    {
        m_data[i] = other.m_data[i];
    }
}

template<typename T>
mystl::Queue<T>::Queue(Queue&& other) noexcept : m_data(other.m_data), m_front(other.m_front), m_back(other.m_back), m_capacity(other.m_capacity)
{
    other.m_data = nullptr;
    other.m_front = other.m_back = other.m_capacity = 0;
}

template<typename T>
mystl::Queue<T>& mystl::Queue<T>::operator=(const Queue& other)
{
    if (this != &other)
    {
        delete[] m_data;
        m_front = other.m_front;
        m_back = other.m_back;
        m_capacity = other.m_capacity;
        m_data = new T[m_capacity];
        for (int i = 0; i < m_back; ++i)
        {
            m_data[i] = other.m_data[i];
        }
    }
    return *this;
}

template<typename T>
mystl::Queue<T>& mystl::Queue<T>::operator=(Queue&& other) noexcept
{
    if (this != &other)
    {
        delete[] m_data;
        m_data = other.m_data;
        m_front = other.m_front;
        m_back = other.m_back;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_front = other.m_back = other.m_capacity = 0;
    }
    return *this;
}

template<typename T>
mystl::Queue<T>::~Queue()
{
    delete[] m_data;
}

template<typename T>
void mystl::Queue<T>::push(const T& value)
{
    if (m_back >= m_capacity)
    {
        resize(m_capacity == 0 ? 1 : 2 * m_capacity);
    }
    m_data[m_back++] = value;
}

template<typename T>
void mystl::Queue<T>::pop()
{
    if (empty())
    {
        throw std::out_of_range("Queue is empty, can't pop");
    }
    m_front++;
    if (m_front == m_back)
    {
        m_front = 0;
        m_back = 0;
    }
}

template<typename T>
T& mystl::Queue<T>::front()
{
    if (empty())
    {
        throw std::out_of_range("Queue is empty, can't access front");
    }
    return m_data[m_front];
}

template<typename T>
const T& mystl::Queue<T>::front() const
{
    if (empty())
    {
        throw std::out_of_range("Queue is empty, can't access front");
    }
    return m_data[m_front];
}

template<typename T>
T& mystl::Queue<T>::back()
{
    if (empty())
    {
        throw std::out_of_range("Queue is empty, can't access back");
    }
    return m_data[m_back - 1];
}

template<typename T>
const T& mystl::Queue<T>::back() const
{
    if (empty())
    {
        throw std::out_of_range("Queue is empty, can't access back");
    }
    return m_data[m_back - 1];
}

template<typename T>
bool mystl::Queue<T>::empty() const
{
    return m_front == m_back;
}

template<typename T>
int mystl::Queue<T>::size() const
{
    return m_back - m_front;
}

template<typename T>
void mystl::Queue<T>::resize(int new_capacity)
{
    T* new_data = new T[new_capacity];
    int j = 0;
    for (int i = m_front; i < m_back; ++i)
    {
        new_data[j++] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
    m_back -= m_front;
    m_front = 0;
    m_capacity = new_capacity;
}

template<typename T>
void mystl::Queue<T>::print() const
{
    for (int i = m_front; i < m_back; ++i)
    {
        std::cout << m_data[i] << " ";
    }
    std::cout << std::endl;
}

#endif //QUEUE_H
