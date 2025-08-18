#include <xc.h>


void tarefa_led_vermelho();
void tarefa_led_amarelo();

void config_ports();
void config_timer1();

// Tratador de interrupções
void __attribute__((interrupt_no_auto_psv)) _T1Interrupt(void);

int vez = 0; 

int main(){
    
    config_ports();
    config_timer1();
    
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
        IFS0bits.T1IF == 0;
        
        switch(vez){
            
            case 0: tarefa_led_vermelho();
                    break;
            case 1: tarefa_led_amarelo();
                    break;
        }
        vez = (vez+1) % 2 ;
        PR1 = 10;
    }
    
}