/* 
 * File:   kernel.h
 * Author: augustodaleffe
 *
 * Created on August 27, 2025, 3:22 PM
 */

#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"


void os_config(void);
void os_start(void);
void os_idle_task(void);

//Salvar e restaurar o contexto (usar \ para pular linha já que é um macro)

#define SAVE_CONTEXT(state_t new_state) \
do {\
    if (readyQueue.taskRunning->task_state == RUNNING) {\
        readyQueue.taskRunning->BSR_reg     = BSR; \
        readyQueue.taskRunning->STATUS_reg     = STATUS; \
        readyQueue.taskRunning->WORK_reg     = WREG; \
        /*Pilha */ \
        while (STKPTR) { \
            readyQueue.taskRunning->task_sp = TOS; \
            readyQueue.taskRunning->task_sp++; \
            asm("POP"); \
        } \
        readyQueue.taskRunning->task_state  = new_state; \
    } \
} while (0);\

        
#define RESTORE_CONTEXT() \
do { \
    if (readyQueue.taskRunning->task_state == READY) {\
        BRS     = readyQueue.taskRunning->BSR_reg; \
        STATUS  = readyQueue.taskRunning->STATUS_reg; \
        WREG    = readyQueue.taskRunning->WORK_reg; \
        /*Pilha */ \
        STKPTR = 0; \
        do { \
            asm("PUSH"); \
            if (readyQueue.taskRunning->task_sp == &readyQueue.taskRunning->STACK[0]){ \
                TOS = readyQueue.taskRunning->task_func; \
            } \
            else { \
                readyQueue.taskRunning->task_sp--; \
                TOS = readyQueue.taskRunning->task_sp; \
            } \
        } while (readyQueue.taskRunning->task_sp != &readyQueue.taskRunning->STACK[0]); \
        readyQueue.taskRunning->task_state  = RUNNING; \
    } \
} while (0);\

#endif	/* KERNEL_H */

