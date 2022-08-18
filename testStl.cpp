#include <algorithm>
#include <iostream>

using namespace std;

void display(int a){
    cout << a << " ";
}

int main(){
    int ia[] = {1,2,3,4,5};
    for_each(ia, ia + 3, display);
    cout << endl;
}
