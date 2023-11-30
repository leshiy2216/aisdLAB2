#include <iostream>
#include <cstdlib>


template <typename T>
struct Node // узел
{
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};


template <typename T>
class LinkedList
{
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    LinkedList(const LinkedList& other) : head(nullptr)
    {
        Node<T>* otherCurrent = other.head;
        while (otherCurrent != nullptr)
        {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    LinkedList(int size) : head(nullptr)
    {
        for (int i = 0; i < size; ++i)
        {
            push_tail(rand());
        }
    }

    ~LinkedList()
    {
        while (head != nullptr)
        {
            pop_head();
        }
    }

    void push_tail(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node<T>* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void push_tail(const LinkedList& other)
    {
        Node<T>* otherCurrent = other.head;
        while (otherCurrent != nullptr)
        {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

};

int main()
{
    return 0;
}
