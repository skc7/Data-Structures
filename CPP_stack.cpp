#include<iostream>
using namespace std;
#define max 1000

class stack{
public:
    int top;



    int a[max];
    stack(){top = -1;}
    bool push(int x);
    int pop();
    bool isEmpty();

};

bool stack::push(int x){

    if(top > max){
        cout << "\nstack overflow" << endl;
        return false;
    }

    else{
        top = top + 1;
        a[top] = x;
        return true;
    }
}

int stack::pop(){
    if(top < 0){
        cout << "\nstack underflow" << endl;
        return 0;
    }
    else{
        int x;
        x = a[top];
        top = top - 1;
        return x;
    }
}

bool stack::isEmpty(){
    return (top < 0);
}

int main(){

    stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    for(int j=0; j<=s.top; j++){
        cout << "\n" << s.a[j] << endl;
    }

    cout << "\n" << s.pop() << " popped from stack";

    return 0;
}

