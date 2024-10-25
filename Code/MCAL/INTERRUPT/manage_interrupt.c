#include "manage_interrupt.h"

#ifdef INTERRUPT_PRIORITY_LEVELS
void __interrupt() InterruptManagerHigh(void)
{
    if(INTERRUPT_ENABLE == PIE1bits.TXIE && INTERRUPT_OCCUR == PIR1bits.TXIF){
        ISR_TX_EUSART();
    }
    else{
        /*Nothing*/
    }
    
    if(INTERRUPT_ENABLE == PIE1bits.RCIE && INTERRUPT_OCCUR == PIR1bits.RCIF){
        ISR_RX_EUSART();
    }
    else{
        /*Nothing*/
    }
}

void __interrupt(low_priority) InterruptManagerLow(void)
{   
    if(INTERRUPT_ENABLE == PIE1bits.TXIE && INTERRUPT_OCCUR == PIR1bits.TXIF){
        ISR_TX_EUSART();
    }
    else{
        /*Nothing*/
    }
    
    if(INTERRUPT_ENABLE == PIE1bits.RCIE && INTERRUPT_OCCUR == PIR1bits.RCIF){
        ISR_RX_EUSART();
    }
    else{
        /*Nothing*/
    }
}

#else

void  __interrupt() InterruptManagerHigh(void)
{   
    if(INTERRUPT_ENABLE == PIE1bits.TXIE && INTERRUPT_OCCUR == PIR1bits.TXIF){
        ISR_TX_EUSART();
    }
    else{
        /*Nothing*/
    }
    
    if(INTERRUPT_ENABLE == PIE1bits.RCIE && INTERRUPT_OCCUR == PIR1bits.RCIF){
        ISR_RX_EUSART();
    }
    else{
        /*Nothing*/
    }
}
#endif
