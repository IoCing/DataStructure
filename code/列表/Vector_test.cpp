#include "Vector.h"

int main(){
    Vector<int> v(10);
    v.print();
    for(int i=0;i<10;i++)
        v[i]=i;
    v.print();
    v.push_back(11);
    v.print();
    v.remove(0);
    v.print();

    for (int i=0;i<999;i++){
        v.push_back(i);
        v.remove(0);
    }
    v.print();
    
}