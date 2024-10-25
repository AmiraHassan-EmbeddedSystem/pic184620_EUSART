#include "hal_eusart.h"

static void Eusart_Async_Calc_BaudRate(const eusart_t *eusart);
static void Eusart_Async_Tx_Init(const eusart_t *eusart);
static void Eusart_Async_Rx_Init(const eusart_t *eusart);

#ifdef EUSRAT_INTERRUPT_FEATURE_ENABLE
    #ifdef EUSRAT_Tx_INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_TXInterruptHandler)(void) = NULL;
    #endif
    #ifdef EUSRAT_Rx_INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_RXInterruptHandler)(void) = NULL;
    static void (*EUSART_FraminErrorInterruptHandler)(void) = NULL;
    static void (*EUSART_OverrunErrorInterruptHandler)(void) = NULL;
    #endif
#endif

Std_ReturnType EUSART_Async_Init(const eusart_t *eusart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == eusart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = EUSART_ENABLE; 
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        Eusart_Async_Calc_BaudRate(eusart);
        Eusart_Async_Tx_Init(eusart);
        Eusart_Async_Rx_Init(eusart);
        ret = E_OK;
    }
}

Std_ReturnType EUSART_Async_DeInit(const eusart_t *eusart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == eusart){
        ret = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = EUSART_DISABLE;
    }
}

Std_ReturnType EUSART_Async_ReadCharBlocking(uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
//        EUSRAT_Rx_INTERRUPT_ENABLE();
        *data = RCREG;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_Async_ReadCharNotBlocking(uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if(PIR1bits.RCIF == 1){
        *data = RCREG;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType EUSART_Async_Rx_Restart(){
    Std_ReturnType ret = E_NOT_OK;
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
    return ret;
}

Std_ReturnType EUSART_Async_WriteCharBlocking(uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    while(!TXSTAbits.TRMT);
    #ifdef EUSRAT_Tx_INTERRUPT_FEATURE_ENABLE
    EUSRAT_Tx_INTERRUPT_ENABLE();
    #endif
    TXREG = data;
    return ret;
}

Std_ReturnType EUSART_Async_WriteStringBlocking(uint8 *data, uint16 lenStr){
    Std_ReturnType ret = E_OK;
    for(uint8 i=0; i<lenStr; i++){
        ret &= EUSART_Async_WriteCharBlocking(data[i]);
    }
    return ret;
}

Std_ReturnType EUSART_Async_WriteCharNonBlocking(uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(TXSTAbits.TRMT == 1){
        TXREG = data;
    }
    ret = E_OK;
    return ret;
}

Std_ReturnType EUSART_Async_WriteStringNonBlocking(uint8 *data, uint16 lenStr){
    Std_ReturnType ret = E_NOT_OK;
    static uint8 current_index = 0;
    if(current_index < lenStr){
        if(EUSART_Async_WriteCharNonBlocking(data[current_index]) == E_OK){
            current_index++;
        }
    }
    else{
        current_index = 0;
        ret = E_OK;
    }
    return ret;
}


static void Eusart_Async_Calc_BaudRate(const eusart_t *eusart){
    float baudRate_formula;
    switch(eusart->baud_rate_config){
        case ASYNC_8BIT_LOW:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_8BAUD_RATE_GEN;
            TXSTAbits.BRGH = EUSAR_LOW_SPEED;
            baudRate_formula = ((_XTAL_FREQ / (float)eusart->baudrate) / 64) - 1;
            break;
            
        case ASYNC_8BIT_HIGH:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_8BAUD_RATE_GEN;
            TXSTAbits.BRGH = EUSAR_HIGH_SPEED;
            baudRate_formula = ((_XTAL_FREQ / (float)eusart->baudrate) / 16) - 1;
            break;
            
        case ASYNC_16BIT_LOW:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BAUD_RATE_GEN;
            TXSTAbits.BRGH = EUSAR_LOW_SPEED;
            baudRate_formula = ((_XTAL_FREQ / (float)eusart->baudrate) / 16) - 1;
            break;
            
        case ASYNC_16BIT_HIGH:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BAUD_RATE_GEN;
            TXSTAbits.BRGH = EUSAR_HIGH_SPEED;
            baudRate_formula = ((_XTAL_FREQ / (float)eusart->baudrate) / 4) - 1;
            break;
            
        case SYNC_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_8BAUD_RATE_GEN;
            baudRate_formula = ((_XTAL_FREQ / (float)eusart->baudrate) / 4) - 1;
            break;
            
        case SYNC_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BAUD_RATE_GEN;
            baudRate_formula = ((_XTAL_FREQ / (float)eusart->baudrate) / 4) - 1;
            break;
        
        default:
            break;
    };
    
    SPBRG = (uint8)((uint32)baudRate_formula);
    SPBRGH = (uint8) (((uint32)baudRate_formula) >> 8);
}

static void Eusart_Async_Tx_Init(const eusart_t *eusart){
    if(EUSART_TRANSMIT_ENABLE == eusart->tx.transmit_enable){
        TXSTAbits.TXEN = EUSART_TRANSMIT_ENABLE;
        
        if(EUSART_TRANSMIT_INTERRUPT_ENABLE == eusart->tx.transmit_interrupt_enable){
            #ifdef EUSRAT_Tx_INTERRUPT_FEATURE_ENABLE
                EUSRAT_Tx_INTERRUPT_ENABLE();
                EUSART_TXInterruptHandler = eusart->EUSART_TXDefaultInterruptHandler;
                
                
                #ifdef INTERRUPT_PRIORITY_LEVELS
                    Interrupt_priorityLevelEnable();
                    if(HIGH_PRIORITY == eusart->tx.tx_interrupt_priority){
                        EUSRAT_Tx_INTERRUPT_HIGH_PRIORITY();
                    }
                    else if(LOW_PRIORITY == eusart->tx.tx_interrupt_priority){
                        EUSRAT_Tx_INTERRUPT_LOW_PRIORITY();
                    }
                    else{/*Nothing*/}
                #else
                    Interrupt_globalInterruptEnable();
                    Interrupt_prepheralInterruptEnable();
                #endif      
            #endif
        }
        else if(EUSART_TRANSMIT_INTERRUPT_DISABLE == eusart->tx.transmit_interrupt_enable){
            EUSRAT_Tx_INTERRUPT_DISABLE();
        }
        else{
            /*Nothing*/
        }
        
        if(EUSART_SELECT_9BIT_TRANSMIT_ENABLE == eusart->tx.select_9bit_transmit){
            TXSTAbits.TX9 = EUSART_SELECT_9BIT_TRANSMIT_ENABLE;
        }
        else if(EUSART_SELECT_9BIT_TRANSMIT_DISABLE == eusart->tx.select_9bit_transmit){
            TXSTAbits.TX9 = EUSART_SELECT_9BIT_TRANSMIT_DISABLE;
        }
        else{
            /*Nothing*/
        }
    }
    else if(EUSART_TRANSMIT_DISABLE == eusart->tx.transmit_enable){
        TXSTAbits.TXEN = EUSART_TRANSMIT_DISABLE;
    }
    else{
        /*Nothing*/
    }

}

static void Eusart_Async_Rx_Init(const eusart_t *eusart){
    if(EUSART_RECEIVE_ENABLE == eusart->rx.receive_enable){
        RCSTAbits.CREN = EUSART_RECEIVE_ENABLE;
        
        if(EUSART_RECEIVE_INTERRUPT_ENABLE == eusart->rx.receive_interrupt_enable){
            #ifdef EUSRAT_Rx_INTERRUPT_FEATURE_ENABLE
                EUSRAT_Rx_INTERRUPT_ENABLE();
                EUSART_RXInterruptHandler = eusart->EUSART_RXDefaultInterruptHandler;
                EUSART_FraminErrorInterruptHandler = eusart->EUSART_FraminErrorInterruptHandler;
                EUSART_OverrunErrorInterruptHandler = eusart->EUSART_OverrunErrorInterruptHandler;

                
                #ifdef INTERRUPT_PRIORITY_LEVELS
                    Interrupt_priorityLevelEnable();
                    if(HIGH_PRIORITY == eusart->rx.rx_interrupt_priority){
                        EUSRAT_Rx_INTERRUPT_HIGH_PRIORITY();
                    }
                    else if(LOW_PRIORITY == eusart->rx.rx_interrupt_priority){
                        EUSRAT_Rx_INTERRUPT_LOW_PRIORITY();
                    }
                    else{/*Nothing*/}
                #else
                    Interrupt_globalInterruptEnable();
                    Interrupt_prepheralInterruptEnable();
                #endif      
            #endif
        }
        else if(EUSART_RECEIVE_INTERRUPT_DISABLE == eusart->rx.receive_interrupt_enable){
            EUSRAT_Rx_INTERRUPT_DISABLE();
        }
        else{
            /*Nothing*/
        }
        
        if(EUSART_SELECT_9BIT_RECEIVE_ENABLE == eusart->rx.select_9bit_receive){
            RCSTAbits.RX9 = EUSART_SELECT_9BIT_RECEIVE_ENABLE;
        }
        else if(EUSART_SELECT_9BIT_RECEIVE_DISABLE == eusart->rx.select_9bit_receive){
            RCSTAbits.RX9 = EUSART_SELECT_9BIT_RECEIVE_DISABLE;
        }
        else{
            /*Nothing*/
        }
    }
    else if(EUSART_RECEIVE_DISABLE == eusart->rx.receive_enable){
        RCSTAbits.CREN = EUSART_RECEIVE_DISABLE;
    }
    else{
        /*Nothing*/
    }
}

#ifdef EUSRAT_INTERRUPT_FEATURE_ENABLE
    #ifdef EUSRAT_Tx_INTERRUPT_FEATURE_ENABLE
void ISR_TX_EUSART(void){
    EUSRAT_Tx_INTERRUPT_DISABLE();
    if(EUSART_TXInterruptHandler){
        EUSART_TXInterruptHandler();
    }
    else{/*Nothing*/}
}
    #endif

    #ifdef EUSRAT_Rx_INTERRUPT_FEATURE_ENABLE
void ISR_RX_EUSART(void){
    if(EUSART_RXInterruptHandler){
        EUSART_RXInterruptHandler();
    }
    else{/*Nothing*/}
    
    if(EUSART_FraminErrorInterruptHandler){
        EUSART_FraminErrorInterruptHandler();
    }
    else{/*Nothing*/}
    
    if(EUSART_OverrunErrorInterruptHandler){
        EUSART_OverrunErrorInterruptHandler();
    }
    else{/*Nothing*/}
}
    #endif
#endif