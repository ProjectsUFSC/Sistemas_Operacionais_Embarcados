/* 
 * File:   scheduler.h
 * Author: augustodaleffe
 *
 * Created on September 1, 2025, 3:29 PM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "types.h"

tcb_t *rr_scheduler();
tcb_t *priority_scheduler();
tcb_t *scheduler();





#ifdef	__cplusplus
}
#endif

#endif	/* SCHEDULER_H */

