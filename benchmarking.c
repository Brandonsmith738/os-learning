#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argsc, char *argv[])
{
    float startTime = (float)clock() / CLOCKS_PER_SEC;

    for (int i = 0; i < 10000000; i++)
    {
        read(0, NULL, 0);
    }
    float endTime = (float)clock() / CLOCKS_PER_SEC;

    float timeElapsed = (endTime - startTime);
    printf("Average time elapsed per call: %f\n", timeElapsed);
    return 0;
}
