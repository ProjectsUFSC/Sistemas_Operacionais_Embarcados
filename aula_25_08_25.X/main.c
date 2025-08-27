#include <xc.h>
#include <stdint.h>

#define QUANTUM 10  

typedef void (*task_ptr)(void);

typedef enum {READY = 0, RUNNING, WAITING} state_t;

typedef struct tcb {
    unsigned int id;
    task_ptr func;
    state_t task_state;
} tcb_t;

//Chamadas de sistema
unsigned int rr_scheduler();
void create_task(unsigned int id, task_ptr task);
void change_state(state_t new_state);

// Configuração
void config_timer(void);
void config_ports(void);



// Tarefas
void task_1();
void task_2();
void task_3();

// ISR timer
void __interrupt() ISR_TIMER();

// Variáveis globais
tcb_t f_aptos[3];
unsigned int vez = 0, qtd_tasks = 0, quantum = 0;

asm("GLOBAL _task_1, _task_2, _task_3");

int main()
{
    config_timer();
    config_ports();
    
    // Criar as tarefas
    create_task(1, task_1);
    create_task(2, task_2);
    create_task(3, task_3);
    
    // Define o tempo que cada tarefa vai executar
    quantum = QUANTUM; 
    
    // Habilitar as interrupções globais
    ei();
    
    while (1);
    
    return 0;
}

// Escalonador de processos
unsigned int rr_scheduler(){
    do{
        vez = (vez+1) %3;
        if(f_aptos[vez].task_state == READY) return vez;
        
    } while (1);
}

void create_task(unsigned int id, task_ptr task){
    f_aptos[qtd_tasks].id   = id;
    f_aptos[qtd_tasks].func   = task;
    f_aptos[qtd_tasks++].task_state   = READY;
    
}

void change_state(state_t new_state){
    
    //Desabilitar as interrupções
    di();
    
    f_aptos[vez].task_state = new_state;
    
    // Troca de contexto 
    STKPTR  = 0;
        
    asm("push");

    TOS     = (uint24_t)f_aptos[rr_scheduler()].func;
    
    // Habilita as interrupções
    ei();
    
    
}

// Configuração
void config_timer()
{
    T0CONbits.T0CS      = 0;
    T0CONbits.PSA       = 0;
    T0CONbits.T0PS      = 0b110;    // 1:128
    INTCONbits.TMR0IE   = 1;
    INTCONbits.TMR0IF   = 0;
    INTCONbits.PEIE     = 1;
    TMR0L               = 10;
    T0CONbits.TMR0ON    = 1;    
}

void config_ports()
{
    TRISDbits.RD0   = 0;
    TRISDbits.RD1   = 0;
    TRISDbits.RD2   = 0;
}

// Tarefas
void task_1()
{
    while (1) {
        LATDbits.LD0    = ~PORTDbits.RD0;
    }
}

void task_2()
{
    while (1) {
        LATDbits.LD1    = ~PORTDbits.RD1;    
    }
}

void task_3()
{
    while (1) {
        LATDbits.LD2    = ~PORTDbits.RD2;    
        change_state(WAITING);
    }
}

// ISR timer
void __interrupt() ISR_TIMER()
{
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF   = 0;
        TMR0L               = 10;
        quantum--;
        
        if(quantum == 0){
            quantum = QUANTUM;
            
            STKPTR  = 0;
        
            asm("push");

            TOS     = (uint24_t)f_aptos[rr_scheduler()].func;
        }     

    }

}