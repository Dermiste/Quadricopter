/*
 * File:    mcf5213_dtim.h
 * Purpose: Register and bit definitions
 */

#ifndef __MCF5213_DTIM_H__
#define __MCF5213_DTIM_H__

/*********************************************************************
*
* DMA Timers (DTIM)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_DTIM0_DTMR           (*(vuint16*)(&__IPSBAR[0x000400]))
#define MCF_DTIM0_DTXMR          (*(vuint8 *)(&__IPSBAR[0x000402]))
#define MCF_DTIM0_DTER           (*(vuint8 *)(&__IPSBAR[0x000403]))
#define MCF_DTIM0_DTRR           (*(vuint32*)(&__IPSBAR[0x000404]))
#define MCF_DTIM0_DTCR           (*(vuint32*)(&__IPSBAR[0x000408]))
#define MCF_DTIM0_DTCN           (*(vuint32*)(&__IPSBAR[0x00040C]))
#define MCF_DTIM1_DTMR           (*(vuint16*)(&__IPSBAR[0x000440]))
#define MCF_DTIM1_DTXMR          (*(vuint8 *)(&__IPSBAR[0x000442]))
#define MCF_DTIM1_DTER           (*(vuint8 *)(&__IPSBAR[0x000443]))
#define MCF_DTIM1_DTRR           (*(vuint32*)(&__IPSBAR[0x000444]))
#define MCF_DTIM1_DTCR           (*(vuint32*)(&__IPSBAR[0x000448]))
#define MCF_DTIM1_DTCN           (*(vuint32*)(&__IPSBAR[0x00044C]))
#define MCF_DTIM2_DTMR           (*(vuint16*)(&__IPSBAR[0x000480]))
#define MCF_DTIM2_DTXMR          (*(vuint8 *)(&__IPSBAR[0x000482]))
#define MCF_DTIM2_DTER           (*(vuint8 *)(&__IPSBAR[0x000483]))
#define MCF_DTIM2_DTRR           (*(vuint32*)(&__IPSBAR[0x000484]))
#define MCF_DTIM2_DTCR           (*(vuint32*)(&__IPSBAR[0x000488]))
#define MCF_DTIM2_DTCN           (*(vuint32*)(&__IPSBAR[0x00048C]))
#define MCF_DTIM3_DTMR           (*(vuint16*)(&__IPSBAR[0x0004C0]))
#define MCF_DTIM3_DTXMR          (*(vuint8 *)(&__IPSBAR[0x0004C2]))
#define MCF_DTIM3_DTER           (*(vuint8 *)(&__IPSBAR[0x0004C3]))
#define MCF_DTIM3_DTRR           (*(vuint32*)(&__IPSBAR[0x0004C4]))
#define MCF_DTIM3_DTCR           (*(vuint32*)(&__IPSBAR[0x0004C8]))
#define MCF_DTIM3_DTCN           (*(vuint32*)(&__IPSBAR[0x0004CC]))
#define MCF_DTIM_DTMR(x)         (*(vuint16*)(&__IPSBAR[0x000400+((x)*0x040)]))
#define MCF_DTIM_DTXMR(x)        (*(vuint8 *)(&__IPSBAR[0x000402+((x)*0x040)]))
#define MCF_DTIM_DTER(x)         (*(vuint8 *)(&__IPSBAR[0x000403+((x)*0x040)]))
#define MCF_DTIM_DTRR(x)         (*(vuint32*)(&__IPSBAR[0x000404+((x)*0x040)]))
#define MCF_DTIM_DTCR(x)         (*(vuint32*)(&__IPSBAR[0x000408+((x)*0x040)]))
#define MCF_DTIM_DTCN(x)         (*(vuint32*)(&__IPSBAR[0x00040C+((x)*0x040)]))

/* Bit definitions and macros for MCF_DTIM_DTMR */
#define MCF_DTIM_DTMR_RST        (0x0001)
#define MCF_DTIM_DTMR_CLK(x)     (((x)&0x0003)<<1)
#define MCF_DTIM_DTMR_FRR        (0x0008)
#define MCF_DTIM_DTMR_ORRI       (0x0010)
#define MCF_DTIM_DTMR_OM         (0x0020)
#define MCF_DTIM_DTMR_CE(x)      (((x)&0x0003)<<6)
#define MCF_DTIM_DTMR_PS(x)      (((x)&0x00FF)<<8)
#define MCF_DTIM_DTMR_CE_ANY     (0x00C0)
#define MCF_DTIM_DTMR_CE_FALL    (0x0080)
#define MCF_DTIM_DTMR_CE_RISE    (0x0040)
#define MCF_DTIM_DTMR_CE_NONE    (0x0000)
#define MCF_DTIM_DTMR_CLK_DTIN   (0x0006)
#define MCF_DTIM_DTMR_CLK_DIV16  (0x0004)
#define MCF_DTIM_DTMR_CLK_DIV1   (0x0002)
#define MCF_DTIM_DTMR_CLK_STOP   (0x0000)

/* Bit definitions and macros for MCF_DTIM_DTXMR */
#define MCF_DTIM_DTXMR_MODE16    (0x01)
#define MCF_DTIM_DTXMR_DMAEN     (0x80)

/* Bit definitions and macros for MCF_DTIM_DTER */
#define MCF_DTIM_DTER_CAP        (0x01)
#define MCF_DTIM_DTER_REF        (0x02)

/* Bit definitions and macros for MCF_DTIM_DTRR */
#define MCF_DTIM_DTRR_REF(x)     (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_DTIM_DTCR */
#define MCF_DTIM_DTCR_CAP(x)     (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_DTIM_DTCN */
#define MCF_DTIM_DTCN_CNT(x)     (((x)&0xFFFFFFFF)<<0)

/********************************************************************/

#endif /* __MCF5213_DTIM_H__ */
