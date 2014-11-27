/*
 * File:    mcf5213_uart.h
 * Purpose: Register and bit definitions
 */

#ifndef __MCF5213_UART_H__
#define __MCF5213_UART_H__

/*********************************************************************
*
* Universal Asynchronous Receiver Transmitter (UART)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_UART0_UMR                 (*(vuint8 *)(&__IPSBAR[0x000200]))
#define MCF_UART0_USR                 (*(vuint8 *)(&__IPSBAR[0x000204]))
#define MCF_UART0_UCSR                (*(vuint8 *)(&__IPSBAR[0x000204]))
#define MCF_UART0_UCR                 (*(vuint8 *)(&__IPSBAR[0x000208]))
#define MCF_UART0_URB                 (*(vuint8 *)(&__IPSBAR[0x00020C]))
#define MCF_UART0_UTB                 (*(vuint8 *)(&__IPSBAR[0x00020C]))
#define MCF_UART0_UIPCR               (*(vuint8 *)(&__IPSBAR[0x000210]))
#define MCF_UART0_UACR                (*(vuint8 *)(&__IPSBAR[0x000210]))
#define MCF_UART0_UISR                (*(vuint8 *)(&__IPSBAR[0x000214]))
#define MCF_UART0_UIMR                (*(vuint8 *)(&__IPSBAR[0x000214]))
#define MCF_UART0_UBG1                (*(vuint8 *)(&__IPSBAR[0x000218]))
#define MCF_UART0_UBG2                (*(vuint8 *)(&__IPSBAR[0x00021C]))
#define MCF_UART0_UIP                 (*(vuint8 *)(&__IPSBAR[0x000234]))
#define MCF_UART0_UOP1                (*(vuint8 *)(&__IPSBAR[0x000238]))
#define MCF_UART0_UOP0                (*(vuint8 *)(&__IPSBAR[0x00023C]))
#define MCF_UART1_UMR                 (*(vuint8 *)(&__IPSBAR[0x000240]))
#define MCF_UART1_USR                 (*(vuint8 *)(&__IPSBAR[0x000244]))
#define MCF_UART1_UCSR                (*(vuint8 *)(&__IPSBAR[0x000244]))
#define MCF_UART1_UCR                 (*(vuint8 *)(&__IPSBAR[0x000248]))
#define MCF_UART1_URB                 (*(vuint8 *)(&__IPSBAR[0x00024C]))
#define MCF_UART1_UTB                 (*(vuint8 *)(&__IPSBAR[0x00024C]))
#define MCF_UART1_UIPCR               (*(vuint8 *)(&__IPSBAR[0x000250]))
#define MCF_UART1_UACR                (*(vuint8 *)(&__IPSBAR[0x000250]))
#define MCF_UART1_UISR                (*(vuint8 *)(&__IPSBAR[0x000254]))
#define MCF_UART1_UIMR                (*(vuint8 *)(&__IPSBAR[0x000254]))
#define MCF_UART1_UBG1                (*(vuint8 *)(&__IPSBAR[0x000258]))
#define MCF_UART1_UBG2                (*(vuint8 *)(&__IPSBAR[0x00025C]))
#define MCF_UART1_UIP                 (*(vuint8 *)(&__IPSBAR[0x000274]))
#define MCF_UART1_UOP1                (*(vuint8 *)(&__IPSBAR[0x000278]))
#define MCF_UART1_UOP0                (*(vuint8 *)(&__IPSBAR[0x00027C]))
#define MCF_UART2_UMR                 (*(vuint8 *)(&__IPSBAR[0x000280]))
#define MCF_UART2_USR                 (*(vuint8 *)(&__IPSBAR[0x000284]))
#define MCF_UART2_UCSR                (*(vuint8 *)(&__IPSBAR[0x000284]))
#define MCF_UART2_UCR                 (*(vuint8 *)(&__IPSBAR[0x000288]))
#define MCF_UART2_URB                 (*(vuint8 *)(&__IPSBAR[0x00028C]))
#define MCF_UART2_UTB                 (*(vuint8 *)(&__IPSBAR[0x00028C]))
#define MCF_UART2_UIPCR               (*(vuint8 *)(&__IPSBAR[0x000290]))
#define MCF_UART2_UACR                (*(vuint8 *)(&__IPSBAR[0x000290]))
#define MCF_UART2_UISR                (*(vuint8 *)(&__IPSBAR[0x000294]))
#define MCF_UART2_UIMR                (*(vuint8 *)(&__IPSBAR[0x000294]))
#define MCF_UART2_UBG1                (*(vuint8 *)(&__IPSBAR[0x000298]))
#define MCF_UART2_UBG2                (*(vuint8 *)(&__IPSBAR[0x00029C]))
#define MCF_UART2_UIP                 (*(vuint8 *)(&__IPSBAR[0x0002B4]))
#define MCF_UART2_UOP1                (*(vuint8 *)(&__IPSBAR[0x0002B8]))
#define MCF_UART2_UOP0                (*(vuint8 *)(&__IPSBAR[0x0002BC]))
#define MCF_UART_UMR(x)               (*(vuint8 *)(&__IPSBAR[0x000200+((x)*0x040)]))
#define MCF_UART_USR(x)               (*(vuint8 *)(&__IPSBAR[0x000204+((x)*0x040)]))
#define MCF_UART_UCSR(x)              (*(vuint8 *)(&__IPSBAR[0x000204+((x)*0x040)]))
#define MCF_UART_UCR(x)               (*(vuint8 *)(&__IPSBAR[0x000208+((x)*0x040)]))
#define MCF_UART_URB(x)               (*(vuint8 *)(&__IPSBAR[0x00020C+((x)*0x040)]))
#define MCF_UART_UTB(x)               (*(vuint8 *)(&__IPSBAR[0x00020C+((x)*0x040)]))
#define MCF_UART_UIPCR(x)             (*(vuint8 *)(&__IPSBAR[0x000210+((x)*0x040)]))
#define MCF_UART_UACR(x)              (*(vuint8 *)(&__IPSBAR[0x000210+((x)*0x040)]))
#define MCF_UART_UISR(x)              (*(vuint8 *)(&__IPSBAR[0x000214+((x)*0x040)]))
#define MCF_UART_UIMR(x)              (*(vuint8 *)(&__IPSBAR[0x000214+((x)*0x040)]))
#define MCF_UART_UBG1(x)              (*(vuint8 *)(&__IPSBAR[0x000218+((x)*0x040)]))
#define MCF_UART_UBG2(x)              (*(vuint8 *)(&__IPSBAR[0x00021C+((x)*0x040)]))
#define MCF_UART_UIP(x)               (*(vuint8 *)(&__IPSBAR[0x000234+((x)*0x040)]))
#define MCF_UART_UOP1(x)              (*(vuint8 *)(&__IPSBAR[0x000238+((x)*0x040)]))
#define MCF_UART_UOP0(x)              (*(vuint8 *)(&__IPSBAR[0x00023C+((x)*0x040)]))

/* Bit definitions and macros for MCF_UART_UMR */
#define MCF_UART_UMR_BC(x)            (((x)&0x03)<<0)
#define MCF_UART_UMR_PT               (0x04)
#define MCF_UART_UMR_PM(x)            (((x)&0x03)<<3)
#define MCF_UART_UMR_ERR              (0x20)
#define MCF_UART_UMR_RXIRQ            (0x40)
#define MCF_UART_UMR_RXRTS            (0x80)
#define MCF_UART_UMR_SB(x)            (((x)&0x0F)<<0)
#define MCF_UART_UMR_TXCTS            (0x10)
#define MCF_UART_UMR_TXRTS            (0x20)
#define MCF_UART_UMR_CM(x)            (((x)&0x03)<<6)
#define MCF_UART_UMR_PM_MULTI_ADDR    (0x1C)
#define MCF_UART_UMR_PM_MULTI_DATA    (0x18)
#define MCF_UART_UMR_PM_NONE          (0x10)
#define MCF_UART_UMR_PM_FORCE_HI      (0x0C)
#define MCF_UART_UMR_PM_FORCE_LO      (0x08)
#define MCF_UART_UMR_PM_ODD           (0x04)
#define MCF_UART_UMR_PM_EVEN          (0x00)
#define MCF_UART_UMR_BC_5             (0x00)
#define MCF_UART_UMR_BC_6             (0x01)
#define MCF_UART_UMR_BC_7             (0x02)
#define MCF_UART_UMR_BC_8             (0x03)
#define MCF_UART_UMR_CM_NORMAL        (0x00)
#define MCF_UART_UMR_CM_ECHO          (0x40)
#define MCF_UART_UMR_CM_LOCAL_LOOP    (0x80)
#define MCF_UART_UMR_CM_REMOTE_LOOP   (0xC0)
#define MCF_UART_UMR_SB_STOP_BITS_1   (0x07)
#define MCF_UART_UMR_SB_STOP_BITS_15  (0x08)
#define MCF_UART_UMR_SB_STOP_BITS_2   (0x0F)

/* Bit definitions and macros for MCF_UART_USR */
#define MCF_UART_USR_RXRDY            (0x01)
#define MCF_UART_USR_FFULL            (0x02)
#define MCF_UART_USR_TXRDY            (0x04)
#define MCF_UART_USR_TXEMP            (0x08)
#define MCF_UART_USR_OE               (0x10)
#define MCF_UART_USR_PE               (0x20)
#define MCF_UART_USR_FE               (0x40)
#define MCF_UART_USR_RB               (0x80)

/* Bit definitions and macros for MCF_UART_UCSR */
#define MCF_UART_UCSR_TCS(x)          (((x)&0x0F)<<0)
#define MCF_UART_UCSR_RCS(x)          (((x)&0x0F)<<4)
#define MCF_UART_UCSR_RCS_SYS_CLK     (0xD0)
#define MCF_UART_UCSR_RCS_CTM16       (0xE0)
#define MCF_UART_UCSR_RCS_CTM         (0xF0)
#define MCF_UART_UCSR_TCS_SYS_CLK     (0x0D)
#define MCF_UART_UCSR_TCS_CTM16       (0x0E)
#define MCF_UART_UCSR_TCS_CTM         (0x0F)

/* Bit definitions and macros for MCF_UART_UCR */
#define MCF_UART_UCR_RXC(x)           (((x)&0x03)<<0)
#define MCF_UART_UCR_TXC(x)           (((x)&0x03)<<2)
#define MCF_UART_UCR_MISC(x)          (((x)&0x07)<<4)
#define MCF_UART_UCR_NONE             (0x00)
#define MCF_UART_UCR_STOP_BREAK       (0x70)
#define MCF_UART_UCR_START_BREAK      (0x60)
#define MCF_UART_UCR_BKCHGINT         (0x50)
#define MCF_UART_UCR_RESET_ERROR      (0x40)
#define MCF_UART_UCR_RESET_TX         (0x30)
#define MCF_UART_UCR_RESET_RX         (0x20)
#define MCF_UART_UCR_RESET_MR         (0x10)
#define MCF_UART_UCR_TX_DISABLED      (0x08)
#define MCF_UART_UCR_TX_ENABLED       (0x04)
#define MCF_UART_UCR_RX_DISABLED      (0x02)
#define MCF_UART_UCR_RX_ENABLED       (0x01)

/* Bit definitions and macros for MCF_UART_UIPCR */
#define MCF_UART_UIPCR_CTS            (0x01)
#define MCF_UART_UIPCR_COS            (0x10)

/* Bit definitions and macros for MCF_UART_UACR */
#define MCF_UART_UACR_IEC             (0x01)

/* Bit definitions and macros for MCF_UART_UISR */
#define MCF_UART_UISR_TXRDY           (0x01)
#define MCF_UART_UISR_RXRDY_FU        (0x02)
#define MCF_UART_UISR_DB              (0x04)
#define MCF_UART_UISR_RXFTO           (0x08)
#define MCF_UART_UISR_TXFIFO          (0x10)
#define MCF_UART_UISR_RXFIFO          (0x20)
#define MCF_UART_UISR_COS             (0x80)

/* Bit definitions and macros for MCF_UART_UIMR */
#define MCF_UART_UIMR_TXRDY           (0x01)
#define MCF_UART_UIMR_RXRDY_FU        (0x02)
#define MCF_UART_UIMR_DB              (0x04)
#define MCF_UART_UIMR_COS             (0x80)

/* Bit definitions and macros for MCF_UART_UIP */
#define MCF_UART_UIP_CTS              (0x01)

/* Bit definitions and macros for MCF_UART_UOP1 */
#define MCF_UART_UOP1_RTS             (0x01)

/* Bit definitions and macros for MCF_UART_UOP0 */
#define MCF_UART_UOP0_RTS             (0x01)

/********************************************************************/

#endif /* __MCF5213_UART_H__ */
