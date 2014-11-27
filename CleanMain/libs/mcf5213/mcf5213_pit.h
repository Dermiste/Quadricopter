/*
 * File:    mcf5213_pit.h
 * Purpose: Register and bit definitions
 */

#ifndef __MCF5213_PIT_H__
#define __MCF5213_PIT_H__

/*********************************************************************
*
* Programmable Interrupt Timer Modules (PIT)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_PIT0_PCSR        (*(vuint16*)(&__IPSBAR[0x150000]))
#define MCF_PIT0_PMR         (*(vuint16*)(&__IPSBAR[0x150002]))
#define MCF_PIT0_PCNTR       (*(vuint16*)(&__IPSBAR[0x150004]))
#define MCF_PIT1_PCSR        (*(vuint16*)(&__IPSBAR[0x160000]))
#define MCF_PIT1_PMR         (*(vuint16*)(&__IPSBAR[0x160002]))
#define MCF_PIT1_PCNTR       (*(vuint16*)(&__IPSBAR[0x160004]))
#define MCF_PIT_PCSR(x)      (*(vuint16*)(&__IPSBAR[0x150000+((x)*0x10000)]))
#define MCF_PIT_PMR(x)       (*(vuint16*)(&__IPSBAR[0x150002+((x)*0x10000)]))
#define MCF_PIT_PCNTR(x)     (*(vuint16*)(&__IPSBAR[0x150004+((x)*0x10000)]))

/* Bit definitions and macros for MCF_PIT_PCSR */
#define MCF_PIT_PCSR_EN      (0x0001)
#define MCF_PIT_PCSR_RLD     (0x0002)
#define MCF_PIT_PCSR_PIF     (0x0004)
#define MCF_PIT_PCSR_PIE     (0x0008)
#define MCF_PIT_PCSR_OVW     (0x0010)
#define MCF_PIT_PCSR_HALTED  (0x0020)
#define MCF_PIT_PCSR_DOZE    (0x0040)
#define MCF_PIT_PCSR_PRE(x)  (((x)&0x000F)<<8)

/* Bit definitions and macros for MCF_PIT_PMR */
#define MCF_PIT_PMR_PM(x)    (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_PIT_PCNTR */
#define MCF_PIT_PCNTR_PC(x)  (((x)&0xFFFF)<<0)

/********************************************************************/

#endif /* __MCF5213_PIT_H__ */
