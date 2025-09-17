#include "types.h"
#include "syscall.h"
#include "kernel.h"
#include <xc.h>

//Declaração fila de aptos
f_aptos_t readyQueue;

void os_config(void){
    readyQueue.readyQueueSize   = 0;
    readyQueue.taskRunning      = &readyQueue.readyQueue[0];
    
    //Criar tarefa idle ( primeira a ser criada)
    os_create_task(0, os_idle_task, 1); 
}

void os_start(void){
    
    //Configurar o timer
    
    
    //Configurações de usuário
    
    
}

//Mantem o SO ociosos ( todo sistema deve ter uma função assim)
void os_idle_task(void){
    
    while(1){
        Nop();  // Queima um ciclo de máquina 
    }
}
