#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

/* --------------------------------- PROBLEM DESCRIPTION ---------------------------------- *
 * TASK: The goal of this code problem is to implement an algorithm for the                 *
 *       fractional knapsack problem.                                                       *
 *                                                                                          *
 * Input Format: The first line of the input contains the number n of items and             *
 *               the capacity W of a knapsack. The next n lines define the values           *
 *               and weights of the items. The i-th line contains integers vi and           *
 *               wi, the value and the weight of i-th item, respectively.                   *
 *                                                                                          *
 * Constraints: 1 <= n <= 1000,0 <= W <= 2*10^6, 0 <= vi <= 2*10^6, 0 < wi <= 2*10^6        *
 *              for all 1 <= i <= n. All the numbers are integers.                          *
 *                                                                                          *
 * Output Format: Output the maximal value of fractions of items that fit into the          *
 *                knapsack. The absolute value of the difference between the answer         *
 *                of your program and the optimal value should be at most 10−3.             *
 *                                                                                          *
 *                To ensure this, output your answer with at least four digits after        *
 *                the decimal point (otherwise your answer, while being computed correctly, *
 *                can turn out to be wrong because of rounding issues).                     *
 * ---------------------------------------------------------------------------------------- */
int fractionalKnapsack(int weight, vector<pair<int, int>> v, int size){
    sort(v.begin(), v.end(), [](pair<int, int> p1, pair<int, int> p2){
        return ((double)p1.first/p1.second > (double)p2.first/p2.second);
    });
    int currWeight = 0;
    double result = 0.0;
    int i = 0;
    while(currWeight + v[i].second <= weight && i < size){
        currWeight += v[i].second;
        result += v[i].first;
        i++;
    }
    if(i < size){
        int remain = weight - currWeight;
        double fraction = (double)remain/(double)v[i].second;
        result += v[i].first*fraction;
    }
    return result;
}
int main(){
    int Weight = 50;
    vector<pair<int, int>> v;
    v.push_back({60,10});
    v.push_back({100,20});
    v.push_back({120,30});

    int size = sizeof(v)/sizeof(int);
    cout << "Maximum value we can obtain: " << fractionalKnapsack(Weight, v, size);
}
