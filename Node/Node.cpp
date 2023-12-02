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

    LinkedList& operator=(const LinkedList& other)
    {
        if (this != &other)
        {
            while (head != nullptr)
            {
                pop_head();
            }

            Node<T>* otherCurrent = other.head;
            while (otherCurrent != nullptr)
            {
                push_tail(otherCurrent->data);
                otherCurrent = otherCurrent->next;
            }
        }
        return *this;
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

    void push_head(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    void push_head(const LinkedList& other)
    {
        Node<T>* otherCurrent = other.head;
        while (otherCurrent != nullptr)
        {
            push_head(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    void pop_head()
    {
        if (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void pop_tail()
    {
        if (head != nullptr)
        {
            if (head->next == nullptr)
            {
                delete head;
                head = nullptr;
            }
            else
            {
                Node<T>* current = head;
                while (current->next->next != nullptr)
                {
                    current = current->next;
                }
                delete current->next;
                current->next = nullptr;
            }
        }
    }

    void delete_node(const T& value)
    {
        while (head != nullptr && head->data == value)
        {
            pop_head();
        }

        if (head != nullptr)
        {
            Node<T>* current = head;
            while (current->next != nullptr)
            {
                if (current->next->data == value)
                {
                    Node<T>* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                }
                else
                {
                    current = current->next;
                }
            }
        }
    }
};

int main()
{
    return 0;
}
