#include "types.h"

//Declara��o fila de aptos

f_aptos_t readyQueue;

void os_config(void){
    readyQueue.readyQueueSize   = 0;
    readyQueue.taskRunning      = &readyQueue.readyQueue[0];
}

void os_start(void){
    
    
    
}
