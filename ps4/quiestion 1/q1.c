#include <stdbool.h>
#include <stdint.h>

typedef void (*task)(void);

void task1(void) { printf("t1\n"); }
void task2(void) { printf("t2\n"); }
void task3(void) { printf("t3\n"); }

void main(void) {
    task sch[] = { task1, task2, task1, task3, task1, task2 };
    uint8_t index = 0;
    while(true) {
        sch[index]();
        index += 1;
        usleep(2000);
    }
}