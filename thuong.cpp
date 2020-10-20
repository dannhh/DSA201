#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;
#ifndef ILIST_H
#define ILIST_H
template <class T>
class IList
{
public:
    virtual void add(const T& element) = 0;
    virtual void add(int index, const T& element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T& item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T& element) = 0;
    virtual int indexOf(const T& item) = 0;
    virtual bool contains(const T& item) = 0;
    virtual string toString() = 0;
};
#endif
// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;
protected:
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;
public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual ~FragmentLinkedList()
    {
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual void create() {
		Node** newfragmentPointers = new Node*[count / fragmentMaxSize + 2];
        newfragmentPointers[0] = fragmentPointers[0];
		for (int i = 1; i < count / fragmentMaxSize + 1; i++) {
			newfragmentPointers[i] = fragmentPointers[i]->next;
		}
		newfragmentPointers[count / fragmentMaxSize + 1] = fragmentPointers[count / fragmentMaxSize]->next;
        
		this->fragmentPointers = newfragmentPointers;
		// for (int i = 0; i < count / fragmentMaxSize + 2; i++) {
		// 	delete[] newfragmentPointers[i];
		// }
		// delete[] newfragmentPointers;
	}
    virtual void add(const T& element)
    {
        Node* temp = this->fragmentPointers[0];
        if (temp == NULL) {
            temp = new Node(element, NULL, NULL);
            this->fragmentPointers[0] = temp;
        }
        else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new Node(element, NULL, temp);
            this->fragmentPointers[count/fragmentMaxSize+1] = temp->next;
            if (this->count % this->fragmentMaxSize == 0) create();
            
        }
        this->count++;
    }
    virtual void add(int index, const T& element)
    {
        if (index > count) throw out_of_range("The index is out of range!");
        else if (index == count) {
            add(element);
        }
        else if (index == 0) {
            Node* temp = new Node(element, fragmentPointers[0], NULL);
            fragmentPointers[0]->prev = temp;
            fragmentPointers[0] = temp;
            if (this->count % this->fragmentMaxSize == 0) create();
            this->count++;
        }
        else {
            Node* temp = this->fragmentPointers[0];
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            Node* tmp = new Node(element, temp->next, temp);
            temp->next = tmp;
            temp->next->next->prev = tmp;
            if (this->count % this->fragmentMaxSize == 0) create();
            this->count++;
        }
    }
    virtual T removeAt(int index)
    {
        if (index >= count) throw out_of_range("The index is out of range!");
        else if (index == 0) {
            Node* temp = this->fragmentPointers[0];
            temp->next->prev = temp->prev;
            this->fragmentPointers[0] = temp->next;
            T res = temp->data;
            delete(temp); 
            this->count--;
            return res;
        }
        else if (index == count - 1) {
            Node* temp = this->fragmentPointers[0];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            T res = temp->data;
            this->fragmentPointers[1] = temp->prev;
            temp->prev->next = temp->next;
            delete(temp);
            this->count--;
            return res;
        }
        else {
            Node* temp = this->fragmentPointers[0];
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            T res = temp->data;
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete(temp);
            this->count--;
            return res;
        }
    }
    virtual bool removeItem(const T& item)
    {
        int index = indexOf(item);
        if (index == -1) return false;
        else {
            removeAt(index);
            return true;
        }
    }
    virtual bool empty()
    {
        if (this->count == 0) return true;
        else return false;
    }
    virtual int size()
    {
        return this->count;
    }
    virtual void clear()
    {
        this->count = 0;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual T get(int index)
    {
        Node* temp = this->fragmentPointers[0];
        if (index >= count) throw out_of_range("The index is invalid!");
        else {
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
        }
        return temp->data;
    }
    virtual void set(int index, const T& element)
    {
        Node* temp = this->fragmentPointers[0];
        if (index >= count) throw out_of_range("The index is invalid!");
        else {
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
        }
        temp->data = element;
    }
    virtual int indexOf(const T& item)
    {
        int res = 0;
        Node* temp = this->fragmentPointers[0];
        while (temp != NULL) {
            if (temp->data == item) break;
            res++;
            temp = temp->next;
        }
        if (res < count) return res;
        else return -1;
    }
    virtual bool contains(const T& item)
    {
        if (indexOf(item) == this->count) return false;
        return true;
    }
    virtual string toString();
    Iterator begin(int index = 0)
    {
        Iterator result = Iterator(this, index, true);
        return result;
    }
    Iterator end(int index = -1)
    {
        if (index == -1) {
            Iterator result = Iterator(this, false);
            return result;
        }
        else {
            Iterator result = Iterator(this, index, false);
            return result;
        }
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;
    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };
    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            this->pList = pList;
            this->pNode = (begin) ? pList->fragmentPointers[0] : NULL;
        }
        Iterator(FragmentLinkedList<T> *pList = 0, int fragmentIndex = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin) {
                this->pNode = pList->fragmentPointers[fragmentIndex];
            }
            else this->pNode = pList->fragmentPointers[fragmentIndex + 1];
        }
        Iterator &operator=(const Iterator &iterator)
        {
            this->pNode = iterator.pNode;
            return *this;
        }
        T &operator*()
        {
            return pNode->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return (this->pNode != iterator.pNode);
        }
        void remove()
        {
            Node* temp = this->pNode;
        }
        void set(const T& element)
        {
            this->pNode->data = element;
        }
        Iterator &operator++()
        {
            if (pNode) pNode = pNode->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
};
template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];
    if (this->count == 0)
        ss << "]";
    // TODO
    else {
        ss << ptr->data;
        ptr = ptr->next;
        while (ptr != NULL) {
            ss << ", " << ptr->data;
            ptr= ptr->next;
        }
        ss << "]";
    }
    // END: TODO
    return ss.str();
}
#endif
// END: STUDENT ANSWER
int main()
{
    // TESTCASE INPUT
    // === Example
    FragmentLinkedList<int> fList;
    for(int i = 0; i < 20 ; i++)
        fList.add(i, i * i);
    cout << fList.toString() << endl;
    fList.set(3, 500);
    cout << fList.removeAt(2) << endl;
    cout << fList.toString() << endl;
    for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
        cout << *it << " ";
    cout << endl;
    // === END: Example
    // END: TESTCASE INPUT
    return 0;
}