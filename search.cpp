#include<iostream>
#include<math.h>

using namespace std;
int jumpSearch(int arr[], int x, int n) {
   int step = sqrt(n); 
   int i = 0;
   cout << i << " ";
   if(arr[0] == x) return 0;
   while(arr[step] <= x && step < n) { 
      i = step;  
      cout << i << " ";
      if(arr[i] == x) return i;
      step += sqrt(n);
      if(step > n - 1) 
         break;
   }
    cout << step << " ";
    if(arr[i] == x) return i;
    for(int j = i; j < step && j < n; j++) { 
      cout << j << " " ;
      if(arr[j] == x)
         return j;  
   }
   return -1;
}

int foldShift(long long key, int addressSize)
{
    long long n = key;
    int num = 0;
    while(n != 0){
        n = n/10;
        num += 1;
    }
    int m = pow(10, num%addressSize);
    long long result = key%m;
    int size = pow(10, addressSize);
    key = key/m;
    while(key!=0){
        result += key%size;
        key = key/size;
    }
    if(result >= size) {
        result = result%size;
    }
    return result;
}

int rotation(long long key, int addressSize)
{
    long long result = key%10;
    key = key/10;
    int size = 0;
    long long n = key;
    while(n!=0){
        n/=10;
        size++;
    }
    result = result*pow(10, size) + key;
    long long k = foldShift(result, addressSize);
        
    return k;
}

long int midSquare(long int seed)
{
    long int seed_2 = seed*seed;
    seed_2 = seed_2/100;
    return seed_2%10000;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}
#include <sstream>
long int digitExtraction(long int seed,int* extractDigits,int size)
{
    int result = 0;
    std::string s;
    std::stringstream out;
    out << seed;
    s = out.str();

    int i = 0;
    while(i < size){
        result = result*10+(s[extractDigits[i]]-48);
        i++;
    }
    return result;
    // string str = to_string(seed);
    // string res = "";
    // for (int i = 0; i < size; i++) {
    //     res += str[extractDigits[i]];
    // }
    // int result = atoi(res.c_str());
    // return result;
}

#include <algorithm>
bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
    int i = 0;
    int j = n-1;
    sort(arr, arr + n);
    while(i+1 < n && j-1 >= 0){
        int sum = arr[i] + arr[j];
        if (arr[i + 1] + arr[j - 1] == sum && i!=j && i+1 != j-1 && i+1 != j) {
            pair1 = pair<int, int>(arr[i], arr[j]);
            pair2 = pair<int, int>(arr[i + 1], arr[j - 1]);
            return true;
        }
        j--;
        if(j == i+1) {
            i++;
            j = n-1;
        } 
    }
    return false;
}
int binarySearch(int arr[], int left, int right, int x)
{
    if(right-left < 0) return -1;
    int middle = left + (right-left)/2;
    cout << "We traverse on index: " << middle << endl;
    if(arr[middle] == x) return middle;
    else if(arr[middle] < x) return 1*binarySearch(arr, middle+1, right, x);
    else return 1* binarySearch(arr, left, middle-1, x);
}

int interpolationSearch(int arr[], int left, int right, int x)
{
    if(right-left < 0) return -1;
    if(right == left) {
        if(arr[left] == x) {
            cout << "We traverse on index: " << left << endl;
            return arr[left];
        }
        else 
            return -1;
    }
    int middle = (left + ((x-arr[left])*(right-left))/(arr[right]-arr[left]));
    if(middle < 0) return -1;
    cout << "We traverse on index: " << middle << endl;
    if(arr[middle] == x) return middle;
    else if(arr[middle] < x) return interpolationSearch(arr, middle+1, right, x);
    else return interpolationSearch(arr, left, middle-1, x);
}
int main(){
 	
 	
if(0){
    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
    int x = 55;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }
}
if(0)
    {
        int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binarySearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                    : cout << "Element is present at index " << result;
    }

    if(0){
        int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,14,15,16};
        int x = 13;
        int n = sizeof(arr) / sizeof(arr[0]);
        int index = jumpSearch(arr, x, n);

        if (index != -1) {
            cout << "\nNumber " << x << " is at index " << index;
        }
        else {
            cout << "\n" << x << " is not in array!";
        }
    }
    //cout << rotation(600102, 2);

    if(0){
        int a[]={0,1,4,5};
        cout << digitExtraction(122443,a,4);
    }
    if(0){
        int arr[] = {3,4,7};
        int n = sizeof arr / sizeof arr[0];
        pair<int, int> pair1, pair2;
        if (findPairs(arr, n, pair1, pair2)) {
           cout << pair1.first << " + ";
           cout << pair1.second << " = ";
           cout << pair2.first << " + ";
           cout << pair2.second;
        }
        else printf("No pair found.\n");
    }
    if(1){
        int arr[] = { 1,2,3,4,5,6,7,8,9 };
        int n = sizeof(arr) / sizeof(arr[0]);
        int x = 9;
        int result = interpolationSearch(arr, 0, n - 1, x);
        (result == -1) ? cout << "Element is not present in array"
                    : cout << "Element is present at index " << result;
    }
}