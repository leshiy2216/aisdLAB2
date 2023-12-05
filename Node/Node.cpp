#include <iostream>
#include <cstdlib>


struct Student {
    std::string lastName;
    std::string firstName;
    int course;
    float average;

    Student(const std::string& last, const std::string& first, int crs, float avg)
        : lastName(last), firstName(first), course(crs), average(avg) {}

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Student: " << student.lastName << student.firstName << ", Course: " << student.course << ", Average: " << student.average;
        return os;
    }

    bool operator==(const Student& other) const
    {
        return lastName == other.lastName && firstName == other.firstName && course == other.course && average == other.average;
    }
};


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

    const T& operator[](int index) const
    {
        Node<T>* current = head;
        int i = 0;
        while (current != nullptr && i < index)
        {
            current = current->next;
            ++i;
        }

        if (current == nullptr)
        {
            throw std::out_of_range("Index out of range");
        }

        return current->data;
    }

    T& operator[](int index)
    {
        Node<T>* current = head;
        int i = 0;
        while (current != nullptr && i < index)
        {
            current = current->next;
            ++i;
        }

        if (current == nullptr)
        {
            throw std::out_of_range("Index out of range");
        }

        return current->data;
    }

    int countStudents() const
    {
        int count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data.course >= 4 && current->data.average > 4.5)
            {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    void print() const
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main()
{
    LinkedList<Student> studentList;
    LinkedList<Student> studentList2;

    studentList.push_tail(Student("Andreev", "Daniil", 3, 4.8));
    studentList.push_tail(Student("Danilov", "Petr", 4, 4.8));
    studentList.push_tail(Student("Petrov", "Maksim", 5, 2.4));
    studentList.push_tail(Student("Maksimov", "Alexander", 2, 2.1));
    studentList.push_tail(Student("Alexandrov", "Fedor", 4, 4.7));
    int count = studentList.countStudents();
    std::cout << std::endl;
    studentList.print();
    std::cout << "The number of students who meet the requirements: " << count << std::endl;

    count = 0;

    studentList.pop_tail();
    studentList.push_tail(Student("Fedorov", "Artem", 1, 3.9));
    studentList.pop_head();
    studentList.push_head(Student("Artemov", "Vladimir", 5, 3.1));
    std::cout << std::endl;

    Student a = Student("Sidorov", "Andrey", 5, 4.6);
    Student b = Student("Sidorov", "Arkadiy", 4, 4.9);
    Student c = Student("Sidorov", "Arseniy", 1, 4.5);
    studentList2.push_tail(a);
    studentList2.push_tail(b);
    studentList2.push_tail(c);
    studentList2.print();
    std::cout << std::endl;

    studentList.push_head(studentList2);
    count = studentList.countStudents();
    studentList.print();
    std::cout << "The number of students who meet the requirements: " << count << std::endl;

    studentList2.delete_node(c);
    studentList2.print();

    return 0;
}
