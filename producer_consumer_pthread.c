#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define BUF_SIZE 3

int buffer[BUF_SIZE];
int add = 0;
int rem = 0;
int num = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;

void *producer (void *param);
void *consumer (void *param);

void* producer(void* param){
    int i;
    for(i=0;i<20;i++){

        pthread_mutex_lock(&m);
            if(num > BUF_SIZE){
                exit(1);
            }

            while(num == BUF_SIZE){
                pthread_cond_wait(&c_prod, &m);
            }
            buffer[add] = i;
            add = (add+1) % BUF_SIZE;
            num++;
        pthread_mutex_unlock(&m);

        pthread_cond_signal(&c_cons);
        printf("\nproducer: inserted %d",i);
        
    }

    printf("\nproducer quitting");
    return 0;
}


void* consumer(void* param){

    int i;

    while(1){
        pthread_mutex_lock(&m);
        if(num < 0){
            exit(1);
        }

        if(num == 0){
            pthread_cond_wait(&c_cons,&m);
        }

        i = buffer[rem];
        rem = (rem+1)%BUF_SIZE;
        num--;
        pthread_mutex_unlock(&m);

        pthread_cond_signal(&c_prod);
        printf("\nconsume value %d",i);
    }
}






int main(){

    pthread_t tid1, tid2;
    int i;

    pthread_create(&tid1,NULL,producer,NULL);
    pthread_create(&tid2,NULL,consumer,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("\nParent quitting");
}



/*
OUTPUT:


producer: inserted 0
producer: inserted 1
producer: inserted 2
consume value 0
consume value 1
consume value 2
producer: inserted 3
producer: inserted 4
producer: inserted 5
producer: inserted 6
consume value 3
consume value 4
consume value 5
consume value 6
producer: inserted 7
consume value 7
consume value 8
producer: inserted 8
producer: inserted 9
producer: inserted 10
producer: inserted 11
producer: inserted 12
consume value 9
consume value 10
consume value 11
consume value 12
producer: inserted 13
producer: inserted 14
producer: inserted 15
consume value 13
consume value 14
consume value 15
consume value 16
producer: inserted 16
producer: inserted 17
producer: inserted 18
producer: inserted 19
producer quitting
consume value 17
consume value 18



*/

















/*
void* hello0(void* parg){
    int* p = (int*)parg;
    int myNum = *p;
    printf("\nhello0 Thread number %d\n",myNum);
    return 0;
}

void* hello1(void* parg){
    int* p = (int*)parg;
    int myNum = *p;
    printf("\nhello1 Thread number %d\n",myNum);
    return 0;
}




int main(){
    int i;
    pthread_t tid[2];

    
        pthread_create(&tid[0],NULL,hello0,&i);
        pthread_create(&tid[1],NULL,hello1,&i);
    

        //pthread_exit(NULL);
   
        
        pthread_join(tid[1],NULL);
        pthread_join(tid[0],NULL);
    



    return 0;
}
*/
