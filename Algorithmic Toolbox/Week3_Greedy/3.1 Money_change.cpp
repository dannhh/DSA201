#include <iostream>
using namespace std;

/* ------------------------ PROBLEM DESCRIPTION -------------------------- *
 * TASK: The goal in this problem is to find the minimum number            *
 *       of coins needed to change the input value (an integer)            *
 *       into coins with denominations 1, 5, and 10.                       *
 *                                                                         *
 * INPUT FORMAT: The input consists of a single integer m.                 *
 *               1 ≤ m ≤ 1000.                                             *
 * OUTPUT FORMAT: Output the minimum number of coins                       *
 *                with denominations 1, 5, 10 that changes m.              *
 * ----------------------------------------------------------------------- */

int main() {
    int min_coin = 0;
    int value;
    cin >> value;
    int change_num[3] = {10, 5, 1};
    for(int i = 0; i < 3; i++){
        min_coin += value/change_num[i];
        value %= change_num[i]; 
    }
    cout << min_coin << endl;
    return 0;
}