#include <stdio.h>
#include <sys/time.h>
#include "timer.h"


double getWallTime(void)  //Antall sekunder siden 1.januar 1970
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}



double timer() {

    double start = getWallTime();

   do {

    //printf("Time: %f\n", getWallTime()-start);

   }  while ((getWallTime() - start) < 2);

    start = 0;

    return 1;
}
