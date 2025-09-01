/* 
 * File:   syscall.h
 * Author: augustodaleffe
 *
 * Created on August 27, 2025, 3:23 PM
 */

#ifndef SYSCALL_H
#define	SYSCALL_H

#include "types.h"

void os_create_task(uint8_t id, f_ptr task_f, uint8_t prior);
void os_delay(uint8_t time);
void os_yield();
void os_change_state(state_t new_state);

#endif	/* SYSCALL_H */

