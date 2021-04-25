#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

void fun(double x,double *y,double *z){
    *y = *y-x; *z = *z+*y;
}
int main(){
    double a=2.5, b=9.0,*pa,*pb;
    pa =&a;pb=&b;
    fun(b-a,pa,pb);
    cout<<a<<" "<<b<<endl;
    return 0;
}