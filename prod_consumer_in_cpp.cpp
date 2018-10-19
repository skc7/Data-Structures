
//////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>

using namespace std;

mutex mx;
condition_variable cv;
queue<int> Q;

bool finished = false;

int size = 3;
int buf[3];

int add = 0;
int rem = 0;
int num = 0;


void producer(){

    for(auto i=0;i<9;i++){
        unique_lock<mutex> lk(mx);

        if(num > size) exit(1);

        while(num == size) cv.wait(lk);


        buf[add] = i;
        add = (add+1) % size;
        num++;
        cv.notify_all();

        cout << "\nProducer inserted " << i << endl;
    }

    return;

}



void consumer(){

    while(1){
        unique_lock<mutex> lk2(mx);

        if(num == 0) cv.wait(lk2);

        if(num < 0) exit(1);

        int i = buf[rem];
        rem = (rem+1) % size;

        num -- ;

        cv.notify_all();
        cout << "\nCOnsumed value " << i << endl;
        if(i == 8) break;
    }
}








int main(){

    thread tobj1(producer);
    thread tobj2(consumer);

    tobj1.join();
    tobj2.join();



    return 0;
}
