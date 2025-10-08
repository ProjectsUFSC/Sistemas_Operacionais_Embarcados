#include "FreeRTOS.h"
#include "user_app.h"

int main()
{
    config_user_app();
    
    xTaskCreate(task_1, "T1", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    
    vTaskStartScheduler();
    
    while (1) {
        
    }
    
    return 0;
}

