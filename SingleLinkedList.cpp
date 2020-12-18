#include<iostream>
#include<cassert>
#include<sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList(): head(NULL), tail(NULL), count(0){};
    ~SLinkedList() { };
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    string toString();
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next = NULL) {
            this->data = data;
            this->next = next;
        }
    };
};
template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    if (count == 0) {
        Node* temp = new Node(e, NULL);
        this->head = temp;
        this->tail = temp;
    }
    else {
        Node* temp = new Node(e, NULL);
        this->tail->next = temp;
        this->tail = temp;
    }
    this->count++;
}
template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    if (index > count) throw out_of_range("the index is out of range!");
    else if (index == count) {
        add(e);
    }
    else if (index == 0) {
        Node* temp = new Node(e, this->head);
        this->head = temp;
        this->count++;
    }
    else {
        Node* temp = this->head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        Node* tmp = new Node(e, temp->next);
        temp->next = tmp;
        this->count++;
    }
}
template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return this->count;
}
template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if(index<0||index>=this->count)
        throw std::out_of_range("Index is out of range");
    else
    {
        Node* temp=this->head;
        for(int i=0;i<index;i++)
        {
            temp=temp->next;
        }
        return temp->data;
    }
}
template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if(index<0||index>=this->count)
        throw std::out_of_range("Index is out of range");
    else{
        Node* temp=this->head;
        for(int i=0;i<index;i++)
        {
            temp=temp->next;
        }
        temp->data=e;
    }
}
template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    if(this->count==0) return true;
    else return false;
}
template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node* temp=this->head;
    int i=0;
    while(temp!=NULL)
    {
        if(temp->data==item) return i;
        else{
            i++;
            temp=temp->next;
        }
    }
    return -1;
}
template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    Node* temp=this->head;
    while(temp!=NULL)
    {
        if(temp->data==item) return true;
        else temp=temp->next;
    }
    return false;
}
template <class T>
string SLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->head;

    if (this->count == 0)
        ss << "]";

    else{//------ List not empty----------
        ss << ptr->data; ptr = ptr->next;
        while(ptr!=NULL){
            ss << ",";
            ss << ptr->data;
            ptr = ptr->next;
        }
        ss << "]";
    }
    return ss.str();
}
int main(){
    SLinkedList<int> list;
    int values[]   = {10, 15, 2,  6,  4,  7,  40,  8};
    int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
    int expvalues[]= {8,  15, 2,  4,  7, 10,  40,  6}; 

    for (int idx = 0; idx < 8; idx++){
    list.add(index[idx], values[idx]);
    }

    assert( list.size() == 8 );
            
    for (int idx = 0; idx < 8; idx++){
        assert( list.get(idx) == expvalues[idx] );
    }

    cout << list.toString();
}
