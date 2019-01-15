#include <iostream>
#include <thread>

using namespace std;

void tfun(int value){
	cout << "\nInside thread\n";
}


int main(){

	thread t1(tfun, 1);
	
	t1.join();
	
	return 0;
}
