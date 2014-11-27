/*
 * File:    mcf5213_cfm.h
 * Purpose: Register and bit definitions
 */

#ifndef __MCF5213_CFM_H__
#define __MCF5213_CFM_H__

/*********************************************************************
*
* ColdFire Flash Module (CFM)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_CFM_CFMMCR           (*(vuint16*)(&__IPSBAR[0x1D0000]))
#define MCF_CFM_CFMCLKD          (*(vuint8 *)(&__IPSBAR[0x1D0002]))
#define MCF_CFM_CFMSEC           (*(vuint32*)(&__IPSBAR[0x1D0008]))
#define MCF_CFM_CFMPROT          (*(vuint32*)(&__IPSBAR[0x1D0010]))
#define MCF_CFM_CFMSACC          (*(vuint32*)(&__IPSBAR[0x1D0014]))
#define MCF_CFM_CFMDACC          (*(vuint32*)(&__IPSBAR[0x1D0018]))
#define MCF_CFM_CFMUSTAT         (*(vuint8 *)(&__IPSBAR[0x1D0020]))
#define MCF_CFM_CFMCMD           (*(vuint8 *)(&__IPSBAR[0x1D0024]))

/* Bit definitions and macros for MCF_CFM_CFMMCR */
#define MCF_CFM_CFMMCR_KEYACC    (0x0020)
#define MCF_CFM_CFMMCR_CCIE      (0x0040)
#define MCF_CFM_CFMMCR_CBEIE     (0x0080)
#define MCF_CFM_CFMMCR_AEIE      (0x0100)
#define MCF_CFM_CFMMCR_PVIE      (0x0200)
#define MCF_CFM_CFMMCR_LOCK      (0x0400)

/* Bit definitions and macros for MCF_CFM_CFMCLKD */
#define MCF_CFM_CFMCLKD_DIV(x)   (((x)&0x3F)<<0)
#define MCF_CFM_CFMCLKD_PRDIV8   (0x40)
#define MCF_CFM_CFMCLKD_DIVLD    (0x80)

/* Bit definitions and macros for MCF_CFM_CFMSEC */
#define MCF_CFM_CFMSEC_SEC(x)    (((x)&0x0000FFFF)<<0)
#define MCF_CFM_CFMSEC_SECSTAT   (0x40000000)
#define MCF_CFM_CFMSEC_KEYEN     (0x80000000)

/* Bit definitions and macros for MCF_CFM_CFMUSTAT */
#define MCF_CFM_CFMUSTAT_BLANK   (0x04)
#define MCF_CFM_CFMUSTAT_ACCERR  (0x10)
#define MCF_CFM_CFMUSTAT_PVIOL   (0x20)
#define MCF_CFM_CFMUSTAT_CCIF    (0x40)
#define MCF_CFM_CFMUSTAT_CBEIF   (0x80)

/* Bit definitions and macros for MCF_CFM_CFMCMD */
#define MCF_CFM_CFMCMD_CMD(x)    (((x)&0x7F)<<0)
#define MCF_CFM_CFMCMD_RDARY1    (0x05)
#define MCF_CFM_CFMCMD_PGM       (0x20)
#define MCF_CFM_CFMCMD_PGERS     (0x40)
#define MCF_CFM_CFMCMD_MASERS    (0x41)
#define MCF_CFM_CFMCMD_PGERSVER  (0x06)

/********************************************************************/

#endif /* __MCF5213_CFM_H__ */
