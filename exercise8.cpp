#include <iostream>
#include <fstream>

int add(int a, int b) {
    return a + b;
}
int minus(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    return a / b;
}
void calculate(int a, int b, int opt)
{
    int (*myfunc)(int, int);
      
    // STUDENT ANSWER BEGIN
    if(opt == 0) myfunc = add;
    else if(opt == 1) myfunc = minus;
    else if(opt == 2) myfunc = multiply;
    else myfunc = divide;

    // STUDENT ANSWER END

    int ans = (*myfunc)(a, b);
    printf("Output of calculation is %d.\n", ans);
}
int main() {
    <TEST>
    return 0;
}