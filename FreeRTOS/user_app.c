#include <p24FJ128GA010.h>

#include "user_app.h"
#include "FreeRTOS.h"
#include <xc.h>
#include "semphr.h"



SemaphoreHandle_t s[5];

void config_user_app()
{
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    for(int i = 0; i<sizeof(s); i++){
        s[i] = xSemaphoreCreateBinary();
    }
    
}

void task_1()
{
    while (1) {
        LATDbits.LATD0 = ~PORTDbits.RD0;
        
    }
}
