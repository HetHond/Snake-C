#include <time.h>

void sleep(int millis) {
  clock_t start_time = clock();
  clock_t end_time = millis * (CLOCKS_PER_SEC / 1000);
  while (clock() - start_time < end_time)
    ;
};