#include "FreeRTOS.h"
#include "user_app.h"

int main()
{
    #if EXAMPLE_1 == 1
    config_user_app();
    
    xTaskCreate(task_1, "T1", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(task_2, "T2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    #elif FILOSOFOS == 1
    config_user_app();
    xTaskCreate(f_0, "f0", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    // Para os demais filósofos
    
    #endif    
    
    vTaskStartScheduler();
    
    while (1) {
        
    }
    
    return 0;
}

