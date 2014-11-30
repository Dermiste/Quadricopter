/*
 * File:    mcf5213_scm.h
 * Purpose: Register and bit definitions
 */

#ifndef __MCF5213_SCM_H__
#define __MCF5213_SCM_H__

/*********************************************************************
*
* System Control Module (SCM)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_SCM_IPSBAR                (*(vuint32*)(&__IPSBAR[0x000000]))
#define MCF_SCM_RAMBAR                (*(vuint32*)(&__IPSBAR[0x000008]))
#define MCF_SCM_CRSR                  (*(vuint8 *)(&__IPSBAR[0x000010]))
#define MCF_SCM_CWCR                  (*(vuint8 *)(&__IPSBAR[0x000011]))
#define MCF_SCM_LPICR                 (*(vuint8 *)(&__IPSBAR[0x000012]))
#define MCF_SCM_CWSR                  (*(vuint8 *)(&__IPSBAR[0x000013]))
#define MCF_SCM_PPMRH                 (*(vuint32*)(&__IPSBAR[0x00000C]))
#define MCF_SCM_PPMRL                 (*(vuint32*)(&__IPSBAR[0x000018]))
#define MCF_SCM_MPARK                 (*(vuint32*)(&__IPSBAR[0x00001C]))
#define MCF_SCM_PPMRS                 (*(vuint8 *)(&__IPSBAR[0x000021]))
#define MCF_SCM_PPMRC                 (*(vuint8 *)(&__IPSBAR[0x000022]))

/* Bit definitions and macros for MCF_SCM_IPSBAR */
#define MCF_SCM_IPSBAR_V              (0x00000001)
#define MCF_SCM_IPSBAR_BA(x)          ((x)&0xC0000000)

/* Bit definitions and macros for MCF_SCM_RAMBAR */
#define MCF_SCM_RAMBAR_BDE            (0x00000200)
#define MCF_SCM_RAMBAR_BA(x)          ((x)&0xFFFF0000)

/* Bit definitions and macros for MCF_SCM_CRSR */
#define MCF_SCM_CRSR_CWDR             (0x20)
#define MCF_SCM_CRSR_EXT              (0x80)

/* Bit definitions and macros for MCF_SCM_CWCR */
#define MCF_SCM_CWCR_CWTIC            (0x01)
#define MCF_SCM_CWCR_CWTAVAL          (0x02)
#define MCF_SCM_CWCR_CWTA             (0x04)
#define MCF_SCM_CWCR_CWT(x)           (((x)&0x07)<<3)
#define MCF_SCM_CWCR_CWRI             (0x40)
#define MCF_SCM_CWCR_CWE              (0x80)

/* Bit definitions and macros for MCF_SCM_LPICR */
#define MCF_SCM_LPICR_XIPL(x)         (((x)&0x07)<<4)
#define MCF_SCM_LPICR_ENBSTOP         (0x80)

/* Bit definitions and macros for MCF_SCM_CWSR */
#define MCF_SCM_CWSR_CWSR(x)          (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_SCM_PPMRH */
#define MCF_SCM_PPMRH_CDPORTS         (0x00000001)
#define MCF_SCM_PPMRH_CDEPORT         (0x00000002)
#define MCF_SCM_PPMRH_CDPIT0          (0x00000008)
#define MCF_SCM_PPMRH_CDPIT1          (0x00000010)
#define MCF_SCM_PPMRH_CDADC           (0x00000080)
#define MCF_SCM_PPMRH_CDGPT           (0x00000100)
#define MCF_SCM_PPMRH_CDPWM           (0x00000200)
#define MCF_SCM_PPMRH_CDFCAN          (0x00000400)
#define MCF_SCM_PPMRH_CDCFM           (0x00000800)

/* Bit definitions and macros for MCF_SCM_PPMRL */
#define MCF_SCM_PPMRL_CDG             (0x00000002)
#define MCF_SCM_PPMRL_CDEIM           (0x00000008)
#define MCF_SCM_PPMRL_CDDMA           (0x00000010)
#define MCF_SCM_PPMRL_CDUART0         (0x00000020)
#define MCF_SCM_PPMRL_CDUART1         (0x00000040)
#define MCF_SCM_PPMRL_CDUART2         (0x00000080)
#define MCF_SCM_PPMRL_CDI2C           (0x00000200)
#define MCF_SCM_PPMRL_CDQSPI          (0x00000400)
#define MCF_SCM_PPMRL_CDDTIM0         (0x00002000)
#define MCF_SCM_PPMRL_CDDTIM1         (0x00004000)
#define MCF_SCM_PPMRL_CDDTIM2         (0x00008000)
#define MCF_SCM_PPMRL_CDDTIM3         (0x00010000)
#define MCF_SCM_PPMRL_CDINTC0         (0x00020000)

/* Bit definitions and macros for MCF_SCM_MPARK */
#define MCF_SCM_MPARK_LCKOUT_TIME(x)  (((x)&0x0000000F)<<8)
#define MCF_SCM_MPARK_PRKLAST         (0x00001000)
#define MCF_SCM_MPARK_TIMEOUT         (0x00002000)
#define MCF_SCM_MPARK_FIXED           (0x00004000)
#define MCF_SCM_MPARK_M0PRTY(x)       (((x)&0x00000003)<<18)
#define MCF_SCM_MPARK_M2PRTY(x)       (((x)&0x00000003)<<20)
#define MCF_SCM_MPARK_BCR24BIT        (0x01000000)
#define MCF_SCM_MPARK_M2_P_EN         (0x02000000)

/* Bit definitions and macros for MCF_SCM_PPMRS */
#define MCF_SCM_PPMRS_DISABLE_ALL     (64)
#define MCF_SCM_PPMRS_DISABLE_CFM     (43)
#define MCF_SCM_PPMRS_DISABLE_CAN     (42)
#define MCF_SCM_PPMRS_DISABLE_PWM     (41)
#define MCF_SCM_PPMRS_DISABLE_GPT     (40)
#define MCF_SCM_PPMRS_DISABLE_ADC     (39)
#define MCF_SCM_PPMRS_DISABLE_PIT1    (36)
#define MCF_SCM_PPMRS_DISABLE_PIT0    (35)
#define MCF_SCM_PPMRS_DISABLE_EPORT   (33)
#define MCF_SCM_PPMRS_DISABLE_PORTS   (32)
#define MCF_SCM_PPMRS_DISABLE_INTC    (17)
#define MCF_SCM_PPMRS_DISABLE_DTIM3   (16)
#define MCF_SCM_PPMRS_DISABLE_DTIM2   (15)
#define MCF_SCM_PPMRS_DISABLE_DTIM1   (14)
#define MCF_SCM_PPMRS_DISABLE_DTIM0   (13)
#define MCF_SCM_PPMRS_DISABLE_QSPI    (10)
#define MCF_SCM_PPMRS_DISABLE_I2C     (9)
#define MCF_SCM_PPMRS_DISABLE_UART2   (7)
#define MCF_SCM_PPMRS_DISABLE_UART1   (6)
#define MCF_SCM_PPMRS_DISABLE_UART0   (5)
#define MCF_SCM_PPMRS_DISABLE_DMA     (4)
#define MCF_SCM_PPMRS_SET_CDG         (1)

/* Bit definitions and macros for MCF_SCM_PPMRC */
#define MCF_SCM_PPMRC_ENABLE_ALL      (64)
#define MCF_SCM_PPMRC_ENABLE_CFM      (43)
#define MCF_SCM_PPMRC_ENABLE_CAN      (42)
#define MCF_SCM_PPMRC_ENABLE_PWM      (41)
#define MCF_SCM_PPMRC_ENABLE_GPT      (40)
#define MCF_SCM_PPMRC_ENABLE_ADC      (39)
#define MCF_SCM_PPMRC_ENABLE_PIT1     (36)
#define MCF_SCM_PPMRC_ENABLE_PIT0     (35)
#define MCF_SCM_PPMRC_ENABLE_EPORT    (33)
#define MCF_SCM_PPMRC_ENABLE_PORTS    (32)
#define MCF_SCM_PPMRC_ENABLE_INTC     (17)
#define MCF_SCM_PPMRC_ENABLE_DTIM3    (16)
#define MCF_SCM_PPMRC_ENABLE_DTIM2    (15)
#define MCF_SCM_PPMRC_ENABLE_DTIM1    (14)
#define MCF_SCM_PPMRC_ENABLE_DTIM0    (13)
#define MCF_SCM_PPMRC_ENABLE_QSPI     (10)
#define MCF_SCM_PPMRC_ENABLE_I2C      (9)
#define MCF_SCM_PPMRC_ENABLE_UART2    (7)
#define MCF_SCM_PPMRC_ENABLE_UART1    (6)
#define MCF_SCM_PPMRC_ENABLE_UART0    (5)
#define MCF_SCM_PPMRC_ENABLE_DMA      (4)
#define MCF_SCM_PPMRC_CLEAR_CDG       (1)

/********************************************************************/

#endif /* __MCF5213_SCM_H__ */
