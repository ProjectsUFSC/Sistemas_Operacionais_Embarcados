#include <xc.h> 

void led_amarelo();

void led_vermelho();

void setup_int0();

void setup_ports();

// Tratador de interrupção ( declaração)
void __attribute__((interrupt(auto_psv))) _INT0Interrupts(void);

int vez = 0;


int main(){
    
    setup_int0();
    
    while(1){
        
    }
    
    
    
    
    
    return 0;
}

void led_amarelo(){
    
    LATCbits.LATC1  =   ~PORTCbits.RC1;
    
}

void led_vermelho(){
    
    LATCbits.LATC2  =   ~PORTCbits.RC2;
    
}

void setup_int0(){
    
    INTCON2bits.INT0EP  = 0;            // Polaridade Positiva ( Borda positiva)
    IFS0bits.INT0IF     = 0;            // Flag de Interrupção, se setar em 1 ele fica em loop infinito
    IEC0bits.INT0IE     = 1;            // Abilitando a interrupção 0
    IPC0bits.T1IP       = 0b100;        // Prioridade da interrupção (3 de uma vez, mas pode ser feito individualmente) escala de 0 a 6
    
    __builtin_enable_interrupts();
    
    
    
    
}

void setup_ports(){
    
    TRISCbits.TRISC1    = 0;
    TRISCbits.TRISC2    = 0;
}


// Tratador de interrupção ( função)
void __attribute__((interrupt(auto_psv))) _INT0Interrupts(void){
    
    if(IFS0bits.INT0IF == 1){
        IFS0bits.INT0IF = 0;
        
        //Lógica de ISR
        switch(vez){
            case 0: led_amarelo();
                     break;
           
            case 1: led_vermelho();
                    break;
        }
        
        vez = (vez+1) % 2 ; 
    }
}