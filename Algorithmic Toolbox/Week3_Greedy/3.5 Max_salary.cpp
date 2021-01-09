#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#define INT_MIN -2147483648
using namespace std;
/* -----------------------------PROBLEM DESCRIPTION ---------------------------- *
 * TASK:           Compose the largest number out of a set of integers.          *
 * Input Format:                                                                 *
 *                 The first line of the input contains an integer n.            *
 *                 The second line contains integers a1, a2,.. an.               *
 * Constraints:    1 <= 𝑛 <= 100;1 <= ai <= 10^3 for all 1 <= i <= n.            *
 * Output Format:  Output the largest number that can be                         *
 *                 composed out of a1, a2,..., an.                               *
 * ---------------------------------------------------------------------------- */

bool greaterDigit(int a, int b){
    ostringstream convert1;
    convert1 << a;
    string a_ = convert1.str();
    ostringstream convert2;
    convert2 << b;
    string b_ = convert2.str();
    cout << "1.\n" << b_+a_ << "\n2. \n" << a_+b_ << endl;
    return b_+a_ < a_+b_;
}
long long int maxSalary(vector<int> arrNum){
    string result = "";
    sort(arrNum.begin(), arrNum.end(), greaterDigit);
    for(int i = 0; i < arrNum.size(); i++){
        ostringstream convert;
        convert << arrNum[i];
        result.append(convert.str());
    }
    return atoi(result.c_str());
}
/* ------------------- SAMPLE TEST -------------------- *
 * 2                  |   4                             *
 * 21                 |    34                           *
 * 2                  |   341                           *
 * Result: 221        |   23                            *
 *                    |   5                             *
 *                    |   Result: 53434123              *
 * -----------------------------------------------------*/
int main() {
    int n;
    cin >> n;
    vector<int> input;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        input.push_back(a);
    }
    cout << maxSalary(input);
}
