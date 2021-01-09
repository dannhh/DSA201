#include <iostream>
using namespace std;
/*----------------------- PROBLEM DISCRIPTION ----------------------------- *
 * Egyptian Fraction Representation of 2/3 is 1/2 + 1/6                     *
   Egyptian Fraction Representation of 6/14 is 1/3 + 1/11 + 1/231           *
   Egyptian Fraction Representation of 12/13 is 1/2 + 1/3 + 1/12 + 1/156    *
 * -------------------------------------------------------------------------*/

/* ---------------------- SOLUTION DESCRIPTION ---------------------------- *
 * For a given number of the form ‘nr/dr’ where dr > nr, first find the     *
 * greatest possible unit fraction, then recur for the remaining part.      * 
 * For example, consider 6/14, we first find ceiling of 14/6, i.e., 3.      * 
 * So the first unit fraction becomes 1/3,                                  *
 * then recur for (6/14 – 1/3) i.e., 4/42.                                  *
 * ------------------------------------------------------------------------ */
void printEgyptian(int nr, int dr){
    if(nr == 0 || dr == 0) return;
    if(dr%nr == 0){
        cout << "1/" << dr/nr;
        return;
    }
    if(nr%dr == 0){
        cout << nr/dr;
        return;
    }
    if(nr > dr) {
        cout << nr/dr << "+";
        printEgyptian(nr%dr, dr);
        return;
    }
    // dr > nr and dr%nr != 0
    int n = dr/nr + 1;
    cout << "1/" << n << "+";
    printEgyptian(nr*n-dr, n*dr); // Quy dong
    return;
}

int main() {
    int nr, dr;
    cin >> nr >> dr;
    cout << nr << "/" << dr << " = ";
    printEgyptian(nr, dr);
}
