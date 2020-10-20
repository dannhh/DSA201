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
    int capacity = 2;

public:
    FragmentLinkedList(int fragmentMaxSize = 5) 
    {                                           
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers  = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    //===============================================================================
    virtual ~FragmentLinkedList(){
        this->count = 0;
        this->fragmentMaxSize = 0;
        for (int i = 0; i < capacity; i++)
        {
            delete[] fragmentPointers[i];
        }
        delete[] fragmentPointers;

    }
    //===============================================================================
    virtual void add(const T& element){
        Node *newNode = new Node(element, NULL, NULL);

        if(count == 0) {
            fragmentPointers[0] = newNode;
            count++;
            return;
        }
        // Mo rong fragment
        if(count == capacity) {
            int newcapacity = capacity*3/2;
            Node ** newfragmentPointers = new Node *[newcapacity];
            for(int j = 0; j < capacity; j++){
                newfragmentPointers[j] = fragmentPointers[j];
            }
            this->capacity = newcapacity;
            delete this->fragmentPointers;
            this->fragmentPointers = newfragmentPointers;
        }

        // Add into NULL fragment Pointer
        int i = count/fragmentMaxSize;
        if(fragmentPointers[i] == NULL) {
            fragmentPointers[i] = newNode;
            if(i>0) {
                Node* temp = fragmentPointers[i-1];
                //Move to the end of previous Fragment Linked List
                while(temp->next!=NULL) temp = temp->next;
                temp->next = fragmentPointers[i];
                //Point newnode to last node of previous Fragment Linked List
                newNode->prev = temp;
            }
        }
        // Add into the end of list
        else {
            Node *last  = fragmentPointers[i];
                while(last->next!=NULL) last = last->next;
                last->next = newNode;
                newNode->prev = last;
        }
        //Updating count
        count++;
    }
    //=======================================================================================
    virtual void add(int index, const T& element){
        //check index constraints
        if(index > count || index < 0) throw std::out_of_range("The index is out of range!");
        else {
            if(index == count) {
                this->add(element);
                return;
            }

            int i = index/fragmentMaxSize;

            //Insert newNode as doubly linked list
            Node *temp = fragmentPointers[i];
            for(int j = fragmentMaxSize*i; j < index - 1; j++){
                // j is node before index
                temp = temp->next;
            }
            Node *newNode = new Node(element, NULL, NULL);

            //Add in the first node of a fragment 
            if(index == i*fragmentMaxSize){
                if(index != 0){
                    Node *tempFirst = fragmentPointers[i-1];
                    for(int j = 0; j < fragmentMaxSize-1; j++){
                        tempFirst = tempFirst->next;
                    }
                    newNode->prev = tempFirst;
                    newNode->next = tempFirst->next;
                    tempFirst->next = newNode;
                    fragmentPointers[i] = newNode;
                }
                else {
                    newNode->next = fragmentPointers[0];
                    fragmentPointers[0] = newNode;
                    newNode->prev = NULL;                    
                }
                // fragmentPointers[i] = newNode;
                // newNode->next = tempFirst->next;
                // tempFirst->next = fragmentPointers[i];
                // newNode->prev = tempFirst;
                // tempFirst->next->next->prev = newNode;
            }
            else{
                newNode->next = temp->next;
                temp->next = newNode;
                newNode->prev = temp;
            }

            i++; // Update from fragment next to i
            while(i*fragmentMaxSize <= count){
                Node* temp2 = fragmentPointers[i-1];
                //Move to the end of previous Fragment Linked List
                int j = 0;
                while(j < fragmentMaxSize-1 && (i-1)*fragmentMaxSize+j < count) {
                    temp2 = temp2->next;
                    j++;
                }
                fragmentPointers[i] = temp2->next;
                temp2->next = fragmentPointers[i];
                fragmentPointers[i]->prev = temp2;

                i++;
            }
            count ++;
            return;
        }
    }
    //===============================================================================
    virtual T removeAt(int index){
        //check index constraints
        if(index >= count || index < 0) throw std::out_of_range("The index is out of range!");
        else {
            int i = index/fragmentMaxSize;
            //Go to node has index
            Node *temp = fragmentPointers[i];
            for(int j = fragmentMaxSize*i; j < index; j++){
                temp = temp->next;
            }
            Node *result = temp;
            //Deleting
            if(i*fragmentMaxSize == index){
                if(index == 0) {
                    Node *tmp = fragmentPointers[0];
                    fragmentPointers[0] = tmp->next;
                    fragmentPointers[0]->prev = NULL;
                }
                else{
                    Node* preNode = fragmentPointers[i-1];
                int j = 0;
                while(j < fragmentMaxSize-1){
                    preNode = preNode->next;
                    j++;
                }
                Node *tmp = fragmentPointers[i];
                fragmentPointers[i] = tmp->next;
                preNode->next = fragmentPointers[i];
                if(fragmentPointers[i]) fragmentPointers[i]->prev = preNode;
                }                
            }
            else{
                Node *tempToDel = temp;
                temp = tempToDel->next;
                tempToDel->prev->next = temp;
                if(temp) temp->prev = tempToDel->prev;
                
                result = tempToDel;
            }            
            // Update pointer to fragments
            i++; // Update from fragment next to i
            while(i*fragmentMaxSize < count){
                //Move to the end of previous Fragment Linked List
                fragmentPointers[i] = fragmentPointers[i]->next;
                i++;
            }

            count--;
            return result->data;
        }
        //Return if index out of bound
        return this->fragmentPointers[0]->data;
    }
    //===============================================================================
    virtual bool removeItem(const T& item){
        int i = 0;
        Node *temp = fragmentPointers[0];
        while(i < count && temp->data!=item){
            temp = temp->next;
            i++;
        }
        if(temp!=NULL){
            this->removeAt(i);
            return 1;
        }
        else return 0;
    }
    //=================================================================================
    virtual bool empty(){
        return (this->count == 0);
    }
    virtual int size(){
        return this->count;
    }
    //=================================================================================
    virtual void clear(){
        Node * temp = fragmentPointers[0];
        while(temp != NULL) {
            Node *free = temp;
            temp = free->next;

            delete free;
        }
        // this->fragmentMaxSize = 0;              
        // for (int i = 0; i < capacity; i++)
        // {
        //     delete[] fragmentPointers[i];
        // }
        count = 0;
    }
    //=================================================================================
    virtual T get(int index){
        if(index < 0 || index >= count) throw std::out_of_range("The index is out of range!");
        int i = index/fragmentMaxSize;
        Node *temp = fragmentPointers[i];
        int j = 0;
        while(i*fragmentMaxSize+j < index) {
            temp = temp->next;
            j++;
        }
        return temp->data;
    }
    //=================================================================================
    virtual void set(int index, const T& element){
        if(index < 0 || index >= count) throw std::out_of_range("The index is out of range!");
        int i = index/fragmentMaxSize;
        Node *temp = fragmentPointers[i];
        int j = 0;
        while(i*fragmentMaxSize+j < index) {
            temp = temp->next;
            j++;
        }
        temp->data = element;
        return ;
    }
    //=================================================================================
    virtual int indexOf(const T& item){
        Node* temp = fragmentPointers[0];
        int i = 0;
        while(temp->data != item && temp->next != NULL){
            temp=temp->next;
            i++;
        }
        if(temp->next == NULL && temp->data !=item) return -1;
        else return i;
    }
    //=================================================================================
    virtual bool contains(const T& item){
        Node* temp = fragmentPointers[0];
        while(temp->data != item && temp->next != NULL){
            temp=temp->next;
        }
        if(temp->next == NULL && temp->data !=item) return false;
        else return true;
    }
    //=================================================================================
    virtual string toString();
    Iterator begin(int index = 0){
        Iterator result = Iterator(index, this, true);
        return result;
    }
    //=================================================================================
    Iterator end(int index = -1){
        if(index == -1) {
            Iterator result = Iterator(this, false);
            return result;
        }
        else {
            Iterator result = Iterator(index, this, false);
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
        // Duyet tren FLL va tra ve FLL tuong ung voi Iterator
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;

    public:
        //==========================  Iterator ============================================
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true){
            this->pList = pList;
            if(begin){
                this->pNode = pList->fragmentPointers[0];
            }
            else{
                this->pNode = NULL;
                index = (pList->size()>0)? pList->size():-1;
            }
        }
        //==========================  Iterator ===========================================
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0, bool begin = true){
            this->pList = pList;
            index = 0;
            if(begin) {
                this->pNode  = pList->fragmentPointers[fragmentIndex];
            }
            else this->pNode = pList->fragmentPointers[fragmentIndex+1];
        }
        //==========================     =    ===========================================
        Iterator &operator=(const Iterator &iterator){
            this->pNode = iterator.pNode;
            return *this;
        }
        //==========================     *    ===========================================
        T &operator*(){
            if(this->pNode == NULL) throw std::out_of_range("Segmentation fault!");
            else return pNode->data;
        }
        //==========================    !=    ==========================================
        bool operator!=(const Iterator &iterator){
            return (this->pNode != iterator.pNode)||(this->index != iterator.index);
        }
        //==========================   remove  =========================================
        void remove(){
            Node *temp = this->pNode;
            Node *curr = this->pList->fragmentPointers[0];

            int i = 0;
            while(curr->next!=NULL && curr != temp){
                curr = curr->next;
                i++;
            }
            if(curr == temp) this->pList->removeAt(i);
            this->pNode = this->pNode->prev;
            index--;
        }
        //==========================    set    ===========================================
        void set(const T& element){
            this->pNode->data = element;
        }
        //==========================     ++    ===========================================
        Iterator &operator++(){
            if(pNode) pNode = pNode->next;
            index++;
            return *this;
        }
        //==========================     ++    =========================================
        Iterator operator++(int){
            Iterator iterator = *this;
            ++*this;
            index++;
            return iterator;
        }
        //===============================================================================
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

    else{//------------------------ List not empty---------------------------------------
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
//=======================================================================================
#endif
// END: STUDENT ANSWER

int main()
{
    /*
    // FragmentLinkedList<int> test;
    
    // int j = 0;
    // for (int i = 0; i < 21; i++) {
    //     test.add(i, i);
    // }
    // cout << test.toString() << endl;

    // FragmentLinkedList<int>::Iterator it = test.begin();

    // int option;
    // int index, element;
    // int check = 1;
    // while (check) {
    //     cout << "1. ++it    2. it++          3. remove it        4. to remove item        5. clear data\n";
    //     cout << "6. to get index       7. to set index    8. to check index of element        9. to check contains\n";
    //     cin >> option;
    //     switch (option) {
    //     case 1:
    //         cout << "++it: ";
    //         it++;
    //         break;
    //     case 2:
    //         cout << "it++: ";
    //         ++it;
    //         break;
    //     case 3:
    //         cout << "remove it: ";
    //         it.remove();
    //         break;
    //     case 4:
    //         cout << "Input the element: ";
    //         cin >> element;
    //         cout << "Remove complete: " << test.removeItem(element) << endl;
    //         break;
    //     case 5:
    //         test.clear();
    //         break;
    //     case 6:
    //         cout << "Input the index: ";
    //         cin >> index;
    //         cout << "The element at index: " << test.get(index) << endl;
    //         break;
    //     case 7:
    //         cout << "Input the index and element: ";
    //         cin >> index >> element;
    //         test.set(index, element);
    //         break;
    //     case 8:
    //         cout << "Input the element: ";
    //         cin >> element;
    //         cout << "The index of element: " << test.indexOf(element) << endl;
    //         break;
    //     case 9:
    //         cout << "Input the element: ";
    //         cin >> element;
    //         cout << "The list has the element: " << test.contains(element) << endl;
    //         break;
    //     default:
    //         break;
    //     }
    //     cout << test.toString() << endl;
    //     cout << "Continues ?";
    //     cin >> check;
    // }
    */

    // // https://www.geeksforgeeks.org/implementing-iterator-pattern-of-a-single-linked-list/

    // // https://stackoverflow.com/questions/43728706/custom-implementation-of-iterator-erase-c

    // TESTCASE INPUT
    // === Example

    FragmentLinkedList<int> fList;
    for(int i = 0; i < 20 ; i++)
        fList.add(i, i * i);
        
    for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
        cout << *it << " ";

    FragmentLinkedList<int>::Iterator it = fList.begin();
    it.remove();
    // === END: Example
    // END: TESTCASE INPUT

    return 0;
}
