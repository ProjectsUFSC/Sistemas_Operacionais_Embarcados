#include <p24FJ128GA010.h>

#include "user_app.h"
#include "FreeRTOS.h"
#include <xc.h>


void config_user_app()
{
    TRISDbits.TRISD0 = 0;
}

void task_1()
{
    while (1) {
        LATDbits.LATD0 = ~PORTDbits.RD0;
    }
}
