/*
 * File:    mcf5213_clock.h
 * Purpose: Register and bit definitions
 */

#ifndef __MCF5213_CLOCK_H__
#define __MCF5213_CLOCK_H__

/*********************************************************************
*
* Clock Module (CLOCK)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_CLOCK_SYNCR          (*(vuint16*)(&__IPSBAR[0x120000]))
#define MCF_CLOCK_SYNSR          (*(vuint8 *)(&__IPSBAR[0x120002]))
#define MCF_CLOCK_LPCR           (*(vuint8 *)(&__IPSBAR[0x120007]))

/* Bit definitions and macros for MCF_CLOCK_SYNCR */
#define MCF_CLOCK_SYNCR_PLLEN    (0x0001)
#define MCF_CLOCK_SYNCR_PLLMODE  (0x0002)
#define MCF_CLOCK_SYNCR_CLKSRC   (0x0004)
#define MCF_CLOCK_SYNCR_FWKUP    (0x0020)
#define MCF_CLOCK_SYNCR_DISCLK   (0x0040)
#define MCF_CLOCK_SYNCR_LOCEN    (0x0080)
#define MCF_CLOCK_SYNCR_RFD(x)   (((x)&0x0007)<<8)
#define MCF_CLOCK_SYNCR_LOCRE    (0x0800)
#define MCF_CLOCK_SYNCR_MFD(x)   (((x)&0x0007)<<12)
#define MCF_CLOCK_SYNCR_LOLRE    (0x8000)

/* Bit definitions and macros for MCF_CLOCK_SYNSR */
#define MCF_CLOCK_SYNSR_LOCS     (0x04)
#define MCF_CLOCK_SYNSR_LOCK     (0x08)
#define MCF_CLOCK_SYNSR_LOCKS    (0x10)
#define MCF_CLOCK_SYNSR_CRYOSC   (0x20)
#define MCF_CLOCK_SYNSR_OCOSC    (0x40)
#define MCF_CLOCK_SYNSR_EXTOSC   (0x80)

/* Bit definitions and macros for MCF_CLOCK_LPCR */
#define MCF_CLOCK_LPCR_LPD(x)    (((x)&0x0F)<<0)

/********************************************************************/

#endif /* __MCF5213_CLOCK_H__ */
