#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
/* --------------------------------- PROBLEM DESCRIPTION ----------------------------------------- *
 *  Task:                                                                                          *
 *       Given two sequences 𝑎1, 𝑎2, . . . , 𝑎𝑛(𝑎𝑖 is the profit per click of the 𝑖-th ad) and      *
 *       𝑏1, 𝑏2, . . . , 𝑏𝑛(𝑏𝑖 is the average number of clicks per day of the𝑖-th slot), we need to *
 *       partition them into 𝑛 pairs (𝑎𝑖, 𝑏𝑗) such that the sum of their products is maximized.     *
 *                                                                                                 *
 *  Input Format: The first line contains an integer𝑛, the second one contains a sequence of       *
 *                integers 𝑎1, 𝑎2, . . . , 𝑎𝑛, the third one contains a sequence of integers       *
 *                𝑏1, 𝑏2, . . . , 𝑏𝑛                                                               *
 *                                                                                                 *
 *  Constraints: 1≤𝑛≤10^3;−10^5 ≤ 𝑎_𝑖, 𝑏𝑖≤10^5 for all 1≤𝑖≤𝑛.                                       *
 * ------------------------------------------------------------------------------------------------*/
long long max_dot_product(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end(), [](long long a, long long b){
        return a > b;
    });
    sort(b.begin(), b.end(), [](long long a, long long b){
        return a > b;
    });

    long long result = 0;
    for (size_t i = 0; i < a.size(); i++) {
        result += ((long long) a[i]) * b[i];
    }
    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    std::cout << max_dot_product(a, b) << std::endl;
    return 0;
}
