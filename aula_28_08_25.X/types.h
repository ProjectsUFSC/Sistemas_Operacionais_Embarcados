/* 
 * File:   types.h
 * Author: augustodaleffe
 *
 * Created on August 27, 2025, 3:21 PM
 */

#ifndef TYPES_H
#define	TYPES_H


#include <stdint.h>
#include "os_config.h"

//Define o ponteiro para a função
typedef void (*f_ptr)(void);

//Define os estados possiveis
typedef enum {READY = 0, RUNNING, WAITING} state_t;

//Define a TCB
typedef struct tcb{
    uint8_t task_id;
    f_ptr   task_func;
    state_t task_state;
    uint8_t task_priority;
    
    //Contexto de hardware
    uint8_t BSR_reg;            // Bank select register
    uint8_t WORK_reg;           // Registrador de trabalho 
    uint8_t STATUS_reg;         // Registrador de status da operação
    uint8_t STACK_reg[32];      // Pilha
    uint8_t *task_sp;           // Ponteiro para pilha 
      
} tcb_t;

//Fila de aptos

typedef struct f_aptos{
    tcb_t   readyQueue[MAX_TASK_ON_READY_QUEUE];
    uint8_t readyQueueSize;
    tcb_t   *taskRunning;
    
}f_aptos_t;


#endif	/* TYPES_H */

