#include <stdio.h>
#include <stdlib.h>

#include <time.h>
//#include <sys/time.h>

#include <unistd.h>

/***
    Delay execution of a certain amount of milli seconds
*/
void delay(int milli_seconds)
{
    struct timespec ts;
    timespec_get(&ts, 1);

    long start_time = ((ts.tv_sec*1000) + (ts.tv_nsec / 1000000));
    long t = start_time;

    // looping till required time is not achieved
    while ( t< start_time + milli_seconds)
    {
        timespec_get(&ts, TIME_UTC); // instead of TIME_UTC, you can write 1
        t= ((ts.tv_sec*1000) + (ts.tv_nsec / 1000000));
    }
}

/***
    Get current Time in milli seconds
*/
int getMillisecs()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);

    long t = ((ts.tv_sec*1000) + (ts.tv_nsec / 1000000));

    return t;
}

void Test_clock()
{
    /*
        clock() -> returns number of clock ticks

        Divide by CLOCKS_PER_SEC is not a solution to calculate the time

        time(NULL) --> returns number of seconds since 1970-01-01
    */

    double ct1=clock();
    time_t t1=time(NULL);
    sleep(2);
    time_t t2=time(NULL);
    time_t t3 = t2 - t1;
    double ct2=clock();
    double ct3=ct2-ct1;

    printf("\n time_1 = %ld, \n time_2 = %ld, \n time_3 = %ld", t1, t2, t3);

    printf("\n clock_1 = %f, \n clock_2  = %f, \n clock_3  = %f", ct1, ct2, ct3);
}

void Test_getMillisecs()
{
    int t1 = getMillisecs();
    sleep(2);
    int t2 = getMillisecs();
    int t3 = t2-t1;

    printf("\n time_1 = %ld, \n time_2 = %ld, \n time_3 = %ld", t1, t2, t3);
}
void Test_delay()
{
    int t1 = getMillisecs();
    delay(2500);
    int t2=getMillisecs();

    printf("\n time_1 = %ld, \n time_2 = %ld, \n time_3 = %ld", t1, t2, t2-t1);
}

int main()
{
    struct timeval t;


    printf("get time of day \n");
    gettimeofday(&t, NULL);
    printf("done\n");

    printf("\n %ld - %ld", t.tv_sec, t.tv_usec/1000);

    //Test_clock();
    //Test_getMillisecs();
    Test_delay();


    return 0;
}
