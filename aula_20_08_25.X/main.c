//Algoritmo RR simplificado

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define FCY 10000000UL

#include <libpic30.h>


typedef void (*f_ptr)(void);

typedef enum {READY = 0, RUNNING, WAITING} state_t;

typedef struct tcb {
    unsigned int id;
    state_t task_state;
    f_ptr   task_ptr;
    struct tcb *next;
} tcb_t;


// Fila de aptos
tcb_t *aptos_queue[2];
unsigned int qtd_tasks, task_running;    


void config_os();
void create_task(unsigned int id, f_ptr task_f);
void change_state(unsigned int id, state_t new_state);
unsigned int rr_scheduler();
void include_new_task_on_ready_queue(tcb_t *new);

void tarefa_led_vermelho();
void tarefa_led_amarelo();

void config_ports();
void config_timer1();

// Tratador de interrupção
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);

int main()
{
    config_ports();
    config_os();
    
    // Criar tarefas
    create_task(1, tarefa_led_vermelho);
    create_task(2, tarefa_led_amarelo);

    config_timer1();
    __builtin_enable_interrupts();
    
    
    while (1);
    
    return 0;
}

void config_os()
{
    qtd_tasks     = 0;
    task_running  = 0;
}

void tarefa_led_vermelho()
{
    LATCbits.LATC1 = ~PORTCbits.RC1;    
}

void tarefa_led_amarelo()
{
    LATCbits.LATC2 = ~PORTCbits.RC2;
}

void config_ports()
{
    TRISCbits.TRISC1    = 0;
    TRISCbits.TRISC2    = 0;
}

void config_timer1()
{
    T1CONbits.TCKPS     = 0b11;     // Preescaler 1:255
    IFS0bits.T1IF       = 0;        // Flag da interrupção do timer 1
    IEC0bits.T1IE       = 1;        // Habilita a interrupção por timer
    PR1                 = 10;
    T1CONbits.TON       = 1;        // Liga o periférico de timer (1)
}

// Tratador de interrupção
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
   
    if (IFS0bits.T1IF == 1) {
        IFS0bits.T1IF = 0;
        
        task_running = rr_scheduler();
        
        aptos_queue[task_running]->task_ptr();
        
        PR1 = 10;
    }
}

void create_task(unsigned int id, f_ptr task_f)
{
    tcb_t *new = NULL;
    
    new = (tcb_t*)malloc(sizeof(tcb_t));
    
    new->id             = id;
    new->task_ptr       = task_f;
    new->task_state     = READY;
    new->next           = NULL;
   
    include_new_task_on_ready_queue(new);    
}

void include_new_task_on_ready_queue(tcb_t *new)
{
    aptos_queue[qtd_tasks++] = new;    
}

void change_state(unsigned int id, state_t new_state)
{

}

unsigned int rr_scheduler()
{
    do {
        task_running = (task_running+1) % qtd_tasks;
        if (aptos_queue[task_running]->task_state == READY) return task_running;
        
    } while (1);
    
    // Volta a executar a primeira tarefa
    return 0;
}