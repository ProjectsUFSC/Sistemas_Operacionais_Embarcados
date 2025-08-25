//Algoritmo RR simplificado


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>


typedef void(*f_ptr)(void);

typedef enum {READY = 0, RUNNING, WAITING} state_t;

typedef struct tcb{
    unsigned int id;
    state_t task_state;
    f_ptr   task_ptr;
    struct tcb *next;
    
} tcb_t;


tcb_t *f_aptos  = NULL ;
tcb_t *task_running;       

//Chamadas de sistema
void create_task(unsigned int id, f_ptr task_f);
void change_state(unsigned int id, state_t new_state);
tcb_t *rr_scheduler();                                 
void include_new_task_on_ready_queue(tcb_t *new);


//Funções 
void tarefa_led_vermelho();
void tarefa_led_amarelo();

//Configs
void config_ports();
void config_timer1();

// Tratador de interrupções
void __attribute__((interrupt_no_auto_psv)) _T1Interrupt(void);


int main(){
    tcb_t *task_running = f_aptos; 
    config_ports();
    config_timer1();
    
    //Criar tarefas
    create_task(1, tarefa_led_vermelho);
    create_task(2, tarefa_led_amarelo);
    
    
    __builtin_enable_interrupts();
    
    while(1);
    
    
    return 0;
}


void tarefa_led_vermelho(){
    
    LATCbits.LATC1 = ~PORTCbits.RC1;
}


void tarefa_led_amarelo(){
    
    LATCbits.LATC2 = ~PORTCbits.RC2;
}


void config_ports(){
    TRISCbits.TRISC1    = 0;
    TRISCbits.TRISC2    = 0;
    
}

void config_timer1(){
    
    T1CONbits.TCKPS = 0b01;     // Pré-scaler 1:8
    IFS0bits.T1IF   = 0;        //Flag do timer da interrupção 1
    IEC0bits.T1IE   = 1;        // Habilita a interrupção por timer
    PR1             = 10;       // Valor de ajuste do timer, valor de defasagem ( 65535 (valor total 2^16) - 10 (valor utilizado)
    T1CONbits.TON   = 1;        //Liga o periférico de timer
}

// Tratador de interrupçõe
void __attribute__((interrupt_no_auto_psv)) _T1Interrupt(void){


    if(IFS0bits.T1IF == 1){
        IFS0bits.T1IF = 0;
        
        task_running = rr_scheduler();
        
        //Executa a tarefa
        
        task_running->task_ptr();
    
        PR1 = 10;
    }
    
}


void create_task(unsigned int id, f_ptr task_f){
    
    tcb_t *new = NULL; 
    
    new = (tcb_t*)malloc(sizeof(tcb_t)); 
    
    new->id             = id;
    new->task_ptr       = task_f;
    new->task_state     = READY;
    new->next           = NULL;
    
    
    include_new_task_on_ready_queue(new);
}

void include_new_task_on_ready_queue(tcb_t *new){
    
    if(f_aptos){
        new->next = f_aptos;
        
    }
    f_aptos = new; 
    
}

void change_state(unsigned int id, state_t new_state){
    
    tcb_t *task = f_aptos; 
    
    do {
        
        if(task->id == id){
            task->task_state = new_state;
            break;
        }
        
     }while(task);
    
}

tcb_t *rr_scheduler(){
    
    
    
    tcb_t *next_task = task_running; 
    
    do{
        next_task = next_task->next;
                
        if(next_task->task_state == READY) return next_task;
        
    } while(next_task);
    
    return next_task;               // Retorna NULL 
}                                 