#pragma once

#include <stdexcept>
#include <iostream>

template<class T>
class LinkedList
{
private:
    struct Node
    {
        Node() = default;
        explicit Node(const T& data) : _data(data) { }
        explicit Node(T&& data) : _data(std::move(data)) { }
        ~Node() = default;

        T _data;
        Node* _next = nullptr;
    };

    Node* _head = nullptr;
    Node* _tail = nullptr;
    size_t _size = 0;
public:
    LinkedList() = default;
    LinkedList(const LinkedList& ll);
    ~LinkedList();

    void push_back(const T& data);
    void push_back(T&& data);

    void push_front(const T& data);
    void push_front(T&& data);

    void insert(const T& data, size_t index);
    void insert(T&& data, size_t index);

    void pop_back();
    void pop_front();
    void erase(size_t index);

    bool find(const T& data) const;
    
    void print_list() const;
private:
    void push_back(Node* node);
    void push_front(Node* node);
    void insert(Node* node, size_t index);
};

template<class T>
LinkedList<T>::LinkedList(const LinkedList& ll)
{
    Node* tmp = ll._head;
    push_back(tmp->_data);
    while (tmp != ll._tail)
    {
        tmp = tmp->_next;
        push_back(tmp->_data);
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    Node* tmp = _head;
    while (tmp != nullptr)
    {
        Node* next = tmp->_next;
        delete tmp;
        tmp = next;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

template<class T>
void LinkedList<T>::push_back(Node* node)
{
    if (!node)
        throw std::invalid_argument("NodePtr is nullptr!");
    
    if (_head)
    {
        _tail->_next = node;
        _tail = node;
    } else {
        _head = node;
        _tail = node;
    }
    _size++;
}

template<class T>
void LinkedList<T>::push_back(const T& data)
{
    Node* tmp = new Node(data);
    push_back(tmp);
}

template<class T>
void LinkedList<T>::push_back(T&& data)
{
    Node* tmp = new Node(data);
    push_back(tmp);
}

template<class T>
void LinkedList<T>::push_front(Node* node)
{
    if (!node)
        throw std::invalid_argument("NodePtr is nullptr!");
    
    if (_head)
    {
        node->_next = _head;
        _head = node;
    } else {
        _head = node;
        _tail = node;
    }
    _size++;
}

template<class T>
void LinkedList<T>::push_front(const T& data)
{
    Node* tmp = new Node(data);
    push_front(tmp);
}

template<class T>
void LinkedList<T>::push_front(T&& data)
{
    Node* tmp = new Node(data);
    push_front(tmp);
}

template<class T>
void LinkedList<T>::insert(Node* node, size_t index)
{   
    if (!node)
        throw std::invalid_argument("NodePtr is nullptr!");
    
    if (index > _size)
        throw std::invalid_argument("Index is bigger than size!");
    
    if (index == 0)
    {
        push_front(node);
    } else if (index == _size) {
        push_back(node);
    } else {
        Node* tmp = _head;
        for (size_t i = 0; i < index-1; i++)
            tmp = tmp->_next;
        node->_next = tmp->_next;
        tmp->_next = node;
        _size++;
    }
}

template<class T>
void LinkedList<T>::insert(const T& data, size_t index)
{
    Node* tmp = new Node(data);
    insert(tmp, index);
}

template<class T>
void LinkedList<T>::insert(T&& data, size_t index)
{
    Node* tmp = new Node(data);
    insert(tmp, index);
}

template<class T>
void LinkedList<T>::pop_back()
{
    if (!_head)
        throw std::logic_error("Empty list can't pop!");
    
    if (_size == 1)
    {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    } else {
        Node* tmp = _head;
        while (tmp->_next != _tail)
            tmp = tmp->_next;
        tmp->_next = nullptr;
        delete _tail;
        _tail = tmp;
        _size--;
    }
}

template<class T>
void LinkedList<T>::pop_front()
{
    if (!_head)
        throw std::logic_error("Empty list can't pop!");
    
    if (_size == 1)
    {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    } else {
        Node* tmp = _head->_next;
        delete _head;
        _head = tmp;
        _size--;
    }
}

template<class T>
void LinkedList<T>::erase(size_t index)
{
    if (!_head)
        throw std::logic_error("Nothing can be erased from empty list!");

    if (index >= _size)
        throw std::invalid_argument("No node with such index to erase!");

    if (index == 0)
    {
        pop_front();
    } else if (index == _size-1) {
        pop_back();
    } else {
        Node* tmp = _head;
        for (size_t i = 0; i < index-1; i++)
            tmp = tmp->_next;
        Node* next = tmp->_next;
        tmp->_next = next->_next;
        delete next;
        _size--;
    }
}

template<class T>
bool LinkedList<T>::find(const T& data) const
{
    Node* tmp = _head;
    if (tmp->_data == data)
        return true;
    while (tmp != _tail)
    {
        tmp = tmp->_next;
        if (tmp->_data == data)
            return true;
    }
    return false;
}

template<class T>
void LinkedList<T>::print_list() const
{
    if (!_head)
        throw std::logic_error("Nothing to print! Empty list!");
    
    Node* tmp = _head;
    std::cout << "Head: " << tmp->_data << std::endl;
    while (tmp != _tail)
    {
        tmp = tmp->_next;
        std::cout << tmp->_data << std::endl;
    }
    std::cout << "Size: " << _size << std::endl;
}