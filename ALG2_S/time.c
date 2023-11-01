#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    time_t mytime;
    mytime = time(NULL);
    printf(ctime(&mytime));
    sleep(5);
    mytime = time(NULL);
    printf(ctime(&mytime));

    return 0;
}