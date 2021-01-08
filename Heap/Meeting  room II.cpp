#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>
using namespace std;

class Interval {
public:
    int start;
    int end;
    
    Interval(int start = 0, int end = 0) {
        this->start = start;
        this->end = end;
    }
};
int minPark(vector<Interval> lInterval) {
    vector<Interval> end = lInterval;
    sort(lInterval.begin(), lInterval.end(), [](Interval i1, Interval i2){
        return (i1.start < i2.start);
    }); 
    sort(end.begin(), end.end(), [](Interval i1, Interval i2){
        return (i1.end < i2.end);
    }); 

    int size = lInterval.size();
    int max = 1, max_num = 1;

        for(int i = 1, j = 0; j < size && i < size; i++,j++){
            if(lInterval[i].start < end[j].end){
                max++;
                j--;
            }
            else if(lInterval[i].start < end[j].end) {
                max--;
                i--;
            }
            if(max_num < max) max_num = max;
        }

    return max_num;
}

void print(vector<Interval> l){
    for(int i = 0; i < l.size(); i++){
        for(int j = 0; j < l[i].start; j++){
            cout << " ";
        }
        for(int j = l[i].start; j < l[i].end; j++){
            cout << "=";
        }
        cout << endl;
    }
}
class BusParking {
public: 
    class Node;
private:
    Node* root;
public:
    int height(Node *N){
        if (N == NULL)
            return 0;
        return N->height;
    }
    int getBalance(Node *N){
        if (N == NULL)  
            return 0;  
        return height(N->right) - height(N->left);  
    }  
public:

    void v_m(Node*&_root){
        if(_root->left && _root->right){
            _root->v = _root->left->v + _root->mode + _root->right->v;
            int a = max(_root->left->m, _root->left->v + _root->mode);
            _root->m = max(a, _root->left->v + _root->mode + _root->right->m);
        }
        else if(_root->left == NULL){
            if(_root->right == NULL){
                _root->v = _root->mode;
                _root->m = _root->mode;
            }
            else {
                _root->v = _root->mode + _root->right->v;
                _root->m = max(_root->mode, _root->mode + _root->right->m);
            }
        }
        else {
             _root->v = _root->left->v + _root->mode;
            _root->m = max(_root->left->m, _root->left->v + _root->mode);
        }

        return;
    }

    Node* rotateRight(Node* root){
        Node *_root = root->left;
        Node *_right = _root->right;
        _root->right = root;
        root->left = _right;

        root->height = max(height(root->left), height(root->right)) + 1;  
        _root->height = max(height(_root->left), height(_root->right)) + 1;
        v_m(_root);
        v_m(root);

        return _root;
    }

    Node* rotateLeft(Node* root){
        Node *_root = root->right;
        Node *_left = _root->left;
        _root->left = root;
        root->right = _left;

        root->height = max(height(root->left), height(root->right)) + 1;  
        _root->height = max(height(_root->left), height(_root->right)) + 1;
        v_m(_root);
        v_m(root);
        return _root;
    }

    Node *add(Node *&root, int time, int end, int mode){
        if(root==NULL){
            Node *newNode = new Node(time, end, mode, NULL, NULL);
            v_m(newNode);
            root = newNode;
            return root;
        }
        if(time < root->time){
            root->left = add(root->left, time, end, mode);
        }
        else root->right = add(root->right, time, end, mode);
        root->height = 1 + max(height(root->left), height(root->right));  
        int balance = getBalance(root);
        v_m(root);
        if(root->left) v_m(root->left);
        if(root->right) v_m(root->right);
        if (balance < -1){
            if(time < root->left->time)
                return rotateRight(root);
            else{
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        } 
        else if(balance > 1){
            if(time >= root->right->time)
                return rotateLeft(root);
            else {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }
        v_m(root);
        if(root->left) v_m(root->left);
        if(root->right) v_m(root->right);

        return root;
    }

    int getMax(Node*root) {
        Node *temp = root;
        while(temp->right != NULL){
            temp = temp->right;
        }

        return temp->time;
    }
    Node* _remove(Node *&root, int value, int value2){
        if(root == NULL) return NULL;
        if(value < root->time) root->left = _remove(root->left, value, value2);
        else if(root->time < value) root->right = _remove(root->right, value, value2);
        else
        {
            if(root->end == value2){
                if(root->left == NULL){
                    return root->right;
                }
                else {
                    int max_left = getMax(root->left);
                    root->time = max_left;
                    root->left = _remove(root->left, max_left, value2);
                }
            }
        }
        int balance = getBalance(root);
        v_m(root);
        root->height = 1 + max(height(root->left), height(root->right));  
        if(root->left) v_m(root->left);
        if(root->right) v_m(root->right);
        if(balance < -1 || balance > 1){
            Node *next;
            if(height(root->left) > height(root->right))
                next = root->left;
            else next = root->right;
            Node *nextnext;
            if(height(next->left) > height(next->right))
                nextnext = next->left;
            else nextnext = next->right;

            if(next == root->left){
                if(nextnext == next->left) return rotateRight(root);
                else {
                    root->left = rotateLeft(next);
                    return rotateRight(root);
                }
            }
            else{
                if(nextnext == next->right) return rotateLeft(root);
                else {
                    root->right = rotateRight(next);
                    return rotateLeft(root);
                }
            }
        }
        v_m(root);
        if(root->left) v_m(root->left);
        if(root->right) v_m(root->right);
        return root;
    }

    void add(int s, int t) {
        root = add(root, s, t, 1);
        root = add(root, t, s, -1);
    }

    void remove(int s, int t) {
        root = _remove(root, s, t);
        root = _remove(root, t, s);
    }
    
    void calc(Node *root, int& max, int& result){
        if(root == NULL) return;
        calc(root->left, max, result);
        if(root->mode == 1) max++;
        else max--;
        if(max > result) result = max;
        calc(root->right, max, result); 
    }
    
    int minPark() {
       return root->m;
    }

    class Node{
        int time;
        int end;
        Node* left;
        Node* right;
        int height;
        int v;
        int m;
        int mode; 

        friend class BusParking;
        Node(){
            this->time = 0;
            this->end = 0;
            this->left = this->right = NULL;
            this->mode = 0;
            this->height = 0;
        }
        Node(int time, int end, int mode, Node* left, Node* right){
            this->time = time;
            this->end = end;
            this->mode = mode;
            this->left = left;
            this->right = right;
            this->height = 0;
        }
    };
};
int main(){
    clock_t start, end;
    double cpu_time_used;    

    cout << "Start: \n";
    start = clock();
    vector<Interval> intervals;
    for(int i = 0; i < 46000; i++){
        intervals.push_back(Interval(i,i*i));
        //cout << minPark(intervals);
    }
    
    cout << minPark(intervals) << endl;
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << cpu_time_used << "\n\nStart:\n";
    start = clock();
    BusParking *b = new BusParking();
    for(int i = 0; i < 46000; i++){
        b->add(i,i*i);
        //cout << b->minPark();
    }
    for(int i = 0; i < 46000; i++){
        b->remove(i,i*i);
        //cout << b->minPark();
    }
    cout << b->minPark() << endl;
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << cpu_time_used;
} 