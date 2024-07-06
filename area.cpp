#include <iostream>
#include <math.h>
using namespace std;

int area(int a, int b){
    return a*b;
}
double area(double a,double b, double c){
    double s = a+b+c;
    s /= 2;
    double sum = s*(s-a)*(s-b)*(s-c);
    return sqrt(sum);
}
double area(int r){
    double halfpi = acos(0);
    return 2*halfpi*r*r;
}
int main(){
    int recSide1, recSide2;
    cin>>recSide1>>recSide2;
    cout<<"area of rectangle:- "<<area(recSide1, recSide2)<<endl;

    double triSide1, triSide2, triSide3;
    cin>>triSide1>>triSide2>>triSide3;
    cout<<"area of triangle:- "<<area(triSide1, triSide2, triSide3)<<endl;

    double radius; 
    cin>>radius;
    cout<<"area of circle:- "<<area(radius)<<endl;
}