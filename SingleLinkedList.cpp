/* C++ Implementation of Memory 
efficient Doubly Linked List */
#include <bits/stdc++.h>
#include <cinttypes> 

using namespace std;

template <class T>
class SLinkedList {
public:
    class Iterator; //forward declaration
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList(): head(NULL), tail(NULL), count(0){};
    ~SLinkedList() { };
    void    add(const T& e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T       removeAt(int index);
    bool    removeItem(const T& item);
	string toString();
    SLinkedList(const SLinkedList &list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
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
    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index; // corresponding with current node
    public:
        Iterator(SLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void remove();
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
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
    else{
        int i = 0;
        Node *temp = head;
        while(temp!=NULL && i != index){
            temp = temp->next;
            i++;
        }
        if(i == index) return temp->data;
        else return -1;
    }
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if(index<0||index>=this->count)
        throw std::out_of_range("Index is out of range");
    else {
        int i = 0;
        Node *temp = head;
        while(temp!=NULL && i != index){
            temp = temp->next;
            i++;
        }
        if(i == index) {
            temp->data = e;
            return;
        }
        else return;
    }
	
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (count == 0);
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item ap  1234 pears in list, otherwise return -1 */
    int i = 0;
	Node *temp = head;
	while(temp!=NULL && temp->data != item){
		temp = temp->next;
		i++;
	}
	if(temp != NULL) return i;
	else return -1;
}
template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true: 
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false: 
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
   this->pList = pList;
   if(begin == true){
       if(this->pList != NULL){
            this->current = pList->head;
            this->index = 0;
       }
       else{
           this->current = NULL;
           this->index = -1;
       }
   }
   else if(begin == false){
       this->current = NULL;
       if(this->pList != NULL){
           this->index = pList->count;
       }
       else{
           this->index = 0;
       }
   }
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
   this->current = iterator.current;
   this->index = iterator.index;
   this->pList = iterator.pList;
   return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
   if(this->current == NULL) throw std::out_of_range("Segmentation fault!");
   else if(this->index == 0){
       pList->removeAt(index);
       this->current = NULL;
       this->index = -1;
   }
   else{
       Node* p = pList->head;
       int vt = index;
       while(vt > 1){
           p = p->next;
           vt -= 1;
       }
       this->current = p;
       pList->removeAt(index);
       this->index -= 1;
    }
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
   if(current == NULL) throw std::out_of_range("Segmentation fault!");
   else pList->set(index, e);
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if(this->current == NULL) throw std::out_of_range("Segmentation fault!");
    return this->current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns true if two iterators points the same node and index
    */
   if(this->current == iterator.current){
       if(this->index == iterator.index) return true;
   }
   return false;
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
   this->current = this->current->next;
   return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
   Iterator i = *this;
   ++*this;
   return i;
}
template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    int i = 0;
	Node *temp = head;
	while(temp!=NULL && temp->data != item){
		temp = temp->next;
		i++;
	}
	if(temp!=NULL) return 1;
	else return 0;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
        T result;
    if(index<0||index>=this->count)
        throw std::out_of_range("Index is out of range");
    else {
        Node *temp = this->head, *delNode = temp;

        int i = 0;
        while(temp!=NULL && i < index){
            delNode = temp;
            temp = temp->next;
            i++;
        }
        if(i == index) {
            if(i==0){
                result = head->data;
                delNode = head;
                head = head->next;
                delete delNode;
                count--;
            }
            else{
                if(temp!=NULL){
                result = temp->data;
                delNode->next = temp->next;
                } 
                count--;        
                if(count == 1) {
                    head = temp;
                    tail = temp;
                }
            }
            
            return result;
        }
        else result = -1;
    }
    return result;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node *temp = head;
    int i = 0;
    while(temp!= NULL && temp->data != item){
        temp = temp->next;
        i++;
    }
    if(temp->data == item) {
        removeAt(i);
        return 1;
    }
    else return 0;
}

template<class T>
void SLinkedList<T>::clear(){
    /* Remove all elements in list */
    Node * temp = head;
    while(temp != NULL) {
        Node *free = temp;
        temp = free->next;

        delete free;
    }
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
int main () 
{ 
    SLinkedList<int> list;
    
    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }
            
    int expvalue = 0;
    for(SLinkedList<int>::Iterator it = list.begin(); it != list.end(); it++){
        assert(*it == expvalue);
        expvalue += 1;
    }       
}
