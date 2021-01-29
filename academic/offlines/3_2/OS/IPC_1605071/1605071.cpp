//eita amrta
#include<iostream>
#include<cstdio>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<cstring>
#include <ctime>
#include<queue>
#include<cstdlib>

using namespace std;

#define num_of_cycles 10
#define S 3 // service_size
#define C 2 // paymentroom_capacity

pthread_mutex_t service_lock[S], depart_lock, count_lock, prio_lock;
pthread_mutex_t data, low_prio, next_to_access, check_lock;
sem_t paymentroom;
int dc = 0; // departure_count
int check = 0;

int mySleep()
{
    int stime = (rand() % 3000) + 10; //5000
    return stime;
}

void init_semaphore()
{
    int res;

    res = sem_init(&paymentroom,0,C);
    if(res != 0){
        printf("payment_sema Failed\n");
    }

    res = pthread_mutex_init(&count_lock,NULL);
    if(res != 0){
        printf("count_lock Failed\n");
    }

    res = pthread_mutex_init(&prio_lock,NULL);
    if(res != 0){
        printf("prio_lock Failed\n");
    }

    for(int i=0; i<S; i++)
    { 
        res = pthread_mutex_init(&service_lock[i], NULL);
        if(res != 0){
            printf("serv_lock Failed\n");
        }
    }
}

void init_three_mutex()
{
    int res;

    res = pthread_mutex_init(&next_to_access,NULL);
    if(res != 0){
        printf("next_to_access Failed\n");
    }

    res = pthread_mutex_init(&low_prio,NULL);
    if(res != 0){
        printf("low_prio_access Failed\n");
    }

    res = pthread_mutex_init(&check_lock,NULL);
    if(res != 0){
        printf("check Failed\n");
    }
}

void* service(void* arg)
{
    pthread_mutex_lock(&low_prio);
    pthread_mutex_lock(&count_lock);
    while(true)
    {
        if(dc == 0) 
        {
            //pthread_mutex_unlock(&count_lock);
            break;
        }
        else 
        {
            pthread_mutex_unlock(&count_lock);
            pthread_mutex_unlock(&low_prio);

            usleep(1000 * mySleep());
            pthread_mutex_lock(&low_prio);
            pthread_mutex_lock(&count_lock);
        }
    }
    //pthread_mutex_unlock(&count_lock);

    //pthread_mutex_lock(&low_prio); 
    pthread_mutex_lock(&next_to_access);   
    pthread_mutex_lock(&service_lock[0]);
    pthread_mutex_unlock(&next_to_access);

    for(int i=1; i<S+1; i++)
    {   
        printf("%s started taking service from serviceman %d\n",(char*)arg, i);

        if(i-1 == 0)
        {
            pthread_mutex_unlock(&count_lock);
            //pthread_mutex_unlock(&prio_lock);
        }

        //if(i-1 == 0) pthread_mutex_unlock(&next_to_access);

        usleep(1000 * mySleep());

        printf("%s finished taking service from serviceman %d\n",(char*)arg, i);

        if(i < S)
        {
            pthread_mutex_lock(&service_lock[i]);
        }
        
        pthread_mutex_unlock(&service_lock[i-1]);

        if(i-1 == 0)
        {
            pthread_mutex_unlock(&low_prio);
        }
    }

    return NULL;
} 

void* payment(void* arg)
{
    sem_wait(&paymentroom);
    printf("%s started paying the service bill\n",(char*)arg); 

    usleep(1000 * mySleep());

    //printf("4 %s finished paying the service bill\n",(char*)arg);  
    //sem_post(&paymentroom);  
    pthread_mutex_lock(&count_lock);
    //dc = dc + 1;
    printf("%s finished paying the service bill\n",(char*)arg);  
    sem_post(&paymentroom);

    dc = dc + 1;
    
    if(dc == 1)
    {
        pthread_mutex_lock(&next_to_access);
        pthread_mutex_lock(&service_lock[0]);  
        //pthread_mutex_unlock(&next_to_access);    

        for(int i=1; i<S; i++)
        {
            pthread_mutex_lock(&service_lock[i]);

            pthread_mutex_unlock(&service_lock[i]);
        }
    }
    
    pthread_mutex_unlock(&count_lock);

    return NULL;
}

void* depart(void* arg)
{
    for(int i=S-1; i>0; i--)
    {
        pthread_mutex_lock(&service_lock[i]);

        usleep(mySleep());
        
        pthread_mutex_unlock(&service_lock[i]);
    }

    usleep(1000 * mySleep());

    pthread_mutex_lock(&low_prio);
    pthread_mutex_lock(&count_lock);
    dc = dc - 1; 
    printf("%s has departed\n",(char*)arg);  
    if(dc == 0)
    {
        pthread_mutex_unlock(&next_to_access);
        pthread_mutex_unlock(&service_lock[0]);
        //pthread_mutex_unlock(&next_to_access);
    }
    pthread_mutex_unlock(&count_lock);
    pthread_mutex_unlock(&low_prio);

    return NULL;    
}

void* sync_servTodepart(void* arg)
{
    usleep(mySleep());
    service(arg);
    payment(arg);
    depart(arg);

    pthread_exit((void*)strcat((char*)arg,""));
    //return NULL;
}

void destroy_semaphore()
{
    int res;

    res = sem_destroy(&paymentroom);
    if(res != 0){
        printf("pay_sema_dest Failed\n");
    }

    res = pthread_mutex_destroy(&count_lock);
    if(res != 0){
        printf("count_dest Failed\n");
    }

    res = pthread_mutex_destroy(&prio_lock);
    if(res != 0){
        printf("prio_dest Failed\n");
    }

    for(int i=0; i<S; i++)
    { 
        res = pthread_mutex_destroy(&service_lock[i]);
        if(res != 0){
            printf("%d serv_dest Failed\n", i);
        }
    }
}

void destroy_three_mutex()
{
    int res;

    res = pthread_mutex_destroy(&next_to_access);
    if(res != 0){
        printf("next_to_access_dest Failed\n");
    }

    res = pthread_mutex_destroy(&low_prio);
    if(res != 0){
        printf("low_prio_dest Failed\n");
    }

    res = pthread_mutex_destroy(&check_lock);
    if(res != 0){
        printf("check_dest Failed\n");
    }
}

int main() 
{
    srand(time(NULL)); 
    
    init_semaphore();
    init_three_mutex();

    //int num_of_cycles;
    //cin >> num_of_cycles;
    //num_of_cycles = 10;
    //srand();

  
    pthread_t cycles[num_of_cycles];

    for(int i=0; i<num_of_cycles; i++)
    {
        int res;

        char *id = new char[3];
        strcpy(id,to_string(i+1).c_str());

        res = pthread_create(&cycles[i],NULL,sync_servTodepart,(void *)id);

        if(res != 0){
            printf("Thread creation failed\n");
        }  
    }

    for(int i = 0; i < num_of_cycles; i++){
        void *result;
        pthread_join(cycles[i],&result);
        //printf("5 %s",(char*)result);
    }

    destroy_semaphore();
    destroy_three_mutex();

    //cout << "here";
    return 0;
}