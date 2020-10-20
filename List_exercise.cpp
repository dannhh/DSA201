#include<iostream>
#include<string>
#include<cmath>
#include <fstream>

using namespace std;

class Node{
	public:
	string Ho;
    string Ten;
    string Sodienthoai;

	public:
	Node(string a, string b, string c){
		this->Ho = a;
		this->Ten = b;
		this->Sodienthoai = c;
	}
	Node* next;
};
class PhoneList{
    private:
		Node*head;
		int count;        
    public:
        PhoneList(){
            head = NULL;
			count = 0;
        }
        ~PhoneList(){
            head = NULL;
			count = 0;
        }
        void append(string a, string b, string c){
			Node *pNew = new Node(a,b,c);
			pNew->next = NULL;
			if(this->head==NULL){
        		this->head = pNew;
				count = 1;
				return;
			}
			Node*temp = this->head;
			while(temp->next!=NULL){
				temp = temp->next;
			} 
			temp->next = pNew;
			this->count++;
			return;
        }
		bool remove(string a){
			if(head == NULL) return 0;
			if(head->Sodienthoai == a) {
				head = head->next;
				count--;
				return 1;
			}
			else{
				Node*temp = this->head;
				Node*pre = temp;
				while(temp->Sodienthoai!= a && temp->next!=NULL){
					pre = temp;
					temp = temp->next;
				}
				if(temp->next == NULL && temp->Sodienthoai!=a) return 0;
				pre->next = pre->next->next;
			}
			count--;
			return 1;
		}
		void change(string& a, string& b){
			string temp;
			temp = a;
			a = b;
			b = temp;
		}
		int min_value(int a, int b){
			if(a < b) return a;
			else return b;
		}
		//if a < b return 1, a > b return -1, a = b return 0;
		int compare(string a, string b){
				int length_a = a.length();
				int length_b = b.length();

				int i = 0;
				while((a[i] == b[i]) && i < min_value(length_a, length_b)){
					i++;
				}
				if(a[i] < b[i]) {
					if(a[i] + 32 == b[i] || (a[i] <= 90 && b[i] >= 97 && a[i]+32 > b[i])) return -1;
					else return 1;
				}
				else if(a[i] > b[i]) {
					if(a[i] == b[i] + 32 || (b[i] <= 90 && a[i] >= 97 && b[i] > a[i]-32)) return 1;
					return -1;
				}
				return 0;
		}
		void swap(Node*&a, Node*&b){
			change(a->Ho, b->Ho);
			change(a->Ten, b->Ten);
			change(a->Sodienthoai, b->Sodienthoai);
		}
		void reOrder(){
			Node *temp = head;
			Node *temp2 = head;
			for(temp = head; temp!=NULL; temp = temp->next){
				for(temp2 = temp->next; temp2!=NULL; temp2 = temp2->next){
					if(compare(temp->Ho, temp2->Ho)== -1){
						swap(temp, temp2);
					}
        	else if(compare(temp->Ho, temp2->Ho) == 0){
            if(compare(temp->Ten, temp2->Ten) == -1) {
              swap(temp, temp2);
            }
          }
				}
			}
		}

		void display(){
			if(head==NULL) cout << "Phone list is empty\n";
			while(head!=NULL){
				cout << head->Ho << " " <<head->Ten << " " << head->Sodienthoai << endl;
				head = head->next;
			}
		}
};
int main(){
PhoneList list;
list.append("Johnny", "Depp", "012345678");
list.append("alexander", "rybak", "123456790");
list.append("alexander", "sitcom", "saturday");

list.reOrder();
list.display();
}