#include <iostream>
#include <string>
#include <cmath>

using namespace std;
struct Node {
    string lastName, firstName, phoneNum;
    Node* next;
};
class PhoneList {
private:
    Node* head;
    int   count;
public:
    PhoneList() : head(NULL), count(0) {}
    ~PhoneList() {
        delete[] head;
        this->count = 0;
    }
    void append(string s1, string s2, string s3) {
        Node* tmp = new Node;
        tmp->lastName = s1;
        tmp->firstName = s2;
        tmp->phoneNum = s3;
        tmp->next = NULL;
        if (this->head == NULL) {
            this->head = tmp;
            ++count;
        }
        else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = tmp;
            ++count;
        }
    }
    void display() {
        if (!this->head) cout << "Phone list is empty" << endl;
        else {
            while(head != NULL) {
                cout << head->lastName << " " << head->firstName << " " << head->phoneNum << endl;
                head = head->next;
            }
        }
    }
    bool remove(string s) {
        if (this->head == NULL) return 0;
        if (head->phoneNum == s) {
            head = head->next;
            count--;
            return 1;
        }
        else {
            Node* temp = this->head;
            Node* pre = temp;
            while(temp->phoneNum != s && temp->next != NULL) {
                pre = temp;
                temp = temp->next;
            }
            if (temp->next == NULL && temp->phoneNum != s) return 0;
            pre->next = pre->next->next;
        }
        count--;
        return 1;
    }
    void swap (Node* a, Node* b) {
        Node* temp = a;
        a = b;
        b = temp;
        cout << 1;
    }
    int checkLastName (Node* a, Node* b) {
        if ((a->lastName[0] == b->lastName[0]) && (b->lastName[0] >= 'a' && b->lastName[0] <= 'z') && (a->lastName[0] >= 'A' && a->lastName[0] <= 'Z')) return 1;
        int x = a->lastName.size() > b->lastName.size() ? a->lastName.size() : b->lastName.size();
        for (int i = 0; i < x; i++) {
            if (a->lastName[i] < b->lastName[i]) return 0;
        }
    }
    int checkFirstName (Node* a, Node* b) {
        if ((a->firstName[0] == b->firstName[0]) && (b->firstName[0] >= 'a' && b->firstName[0] <= 'z') && (a->firstName[0] >= 'A' && a->firstName[0] <= 'Z')) return 1;
        int x = a->firstName.size() > b->firstName.size() ? a->firstName.size() : b->firstName.size();
        for (int i = 0; i < x; i++) {
            if (a->firstName[i] < b->firstName[i]) return 0;
        }
    }
    void reOrder() {
        Node* temp = this->head;
        for (temp = head; temp != NULL; temp = temp->next) {
            Node* tmp = temp;
            for (tmp = temp->next; tmp != NULL; tmp = tmp->next) {
                if ((temp->lastName[0] >= 'A' && temp->lastName[0] <= 'Z') && (tmp->lastName[0] >= 'a' && tmp->lastName[0] <= 'z')) { 
                    swap(temp, tmp);
                    cout << 2;
                }
                else if (temp->lastName == tmp->lastName) {
                    if (checkFirstName(temp, tmp) == 1) swap(temp, tmp);
                    else if (checkFirstName(temp, tmp) == 0) swap(temp, tmp);
                }
                else {
                    if (checkLastName(temp, tmp) == 1) swap(temp, tmp);
                    else if (checkLastName(temp, tmp) == 0) swap(temp, tmp);
                }
            }
        }
    }
};

int main()
{
    PhoneList list;
    list.append("alexander", "Depp", "012345678");
    list.append("alexander", "rybak", "123456790");
    list.reOrder();
    list.display();
    return 0;
}