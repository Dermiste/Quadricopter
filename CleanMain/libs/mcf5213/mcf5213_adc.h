/*
 * File:    mcf5213_adc.h
 * Purpose: Register and bit definitions
 */

#ifndef __MCF5213_ADC_H__
#define __MCF5213_ADC_H__

/*********************************************************************
*
* Analog-to-Digital Converter (ADC)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_ADC_CTRL1              (*(vuint16*)(&__IPSBAR[0x190000]))
#define MCF_ADC_CTRL2              (*(vuint16*)(&__IPSBAR[0x190002]))
#define MCF_ADC_ADZCC              (*(vuint16*)(&__IPSBAR[0x190004]))
#define MCF_ADC_ADLST1             (*(vuint16*)(&__IPSBAR[0x190006]))
#define MCF_ADC_ADLST2             (*(vuint16*)(&__IPSBAR[0x190008]))
#define MCF_ADC_ADSDIS             (*(vuint16*)(&__IPSBAR[0x19000A]))
#define MCF_ADC_ADSTAT             (*(vuint16*)(&__IPSBAR[0x19000C]))
#define MCF_ADC_ADLSTAT            (*(vuint16*)(&__IPSBAR[0x19000E]))
#define MCF_ADC_ADZCSTAT           (*(vuint16*)(&__IPSBAR[0x190010]))
#define MCF_ADC_ADRSLT0            (*(vuint16*)(&__IPSBAR[0x190012]))
#define MCF_ADC_ADRSLT1            (*(vuint16*)(&__IPSBAR[0x190014]))
#define MCF_ADC_ADRSLT2            (*(vuint16*)(&__IPSBAR[0x190016]))
#define MCF_ADC_ADRSLT3            (*(vuint16*)(&__IPSBAR[0x190018]))
#define MCF_ADC_ADRSLT4            (*(vuint16*)(&__IPSBAR[0x19001A]))
#define MCF_ADC_ADRSLT5            (*(vuint16*)(&__IPSBAR[0x19001C]))
#define MCF_ADC_ADRSLT6            (*(vuint16*)(&__IPSBAR[0x19001E]))
#define MCF_ADC_ADRSLT7            (*(vuint16*)(&__IPSBAR[0x190020]))
#define MCF_ADC_ADRSLT(x)          (*(vuint16*)(&__IPSBAR[0x190012+((x)*0x002)]))
#define MCF_ADC_ADLLMT0            (*(vuint16*)(&__IPSBAR[0x190022]))
#define MCF_ADC_ADLLMT1            (*(vuint16*)(&__IPSBAR[0x190024]))
#define MCF_ADC_ADLLMT2            (*(vuint16*)(&__IPSBAR[0x190026]))
#define MCF_ADC_ADLLMT3            (*(vuint16*)(&__IPSBAR[0x190028]))
#define MCF_ADC_ADLLMT4            (*(vuint16*)(&__IPSBAR[0x19002A]))
#define MCF_ADC_ADLLMT5            (*(vuint16*)(&__IPSBAR[0x19002C]))
#define MCF_ADC_ADLLMT6            (*(vuint16*)(&__IPSBAR[0x19002E]))
#define MCF_ADC_ADLLMT7            (*(vuint16*)(&__IPSBAR[0x190030]))
#define MCF_ADC_ADLLMT(x)          (*(vuint16*)(&__IPSBAR[0x190022+((x)*0x002)]))
#define MCF_ADC_ADHLMT0            (*(vuint16*)(&__IPSBAR[0x190032]))
#define MCF_ADC_ADHLMT1            (*(vuint16*)(&__IPSBAR[0x190034]))
#define MCF_ADC_ADHLMT2            (*(vuint16*)(&__IPSBAR[0x190036]))
#define MCF_ADC_ADHLMT3            (*(vuint16*)(&__IPSBAR[0x190038]))
#define MCF_ADC_ADHLMT4            (*(vuint16*)(&__IPSBAR[0x19003A]))
#define MCF_ADC_ADHLMT5            (*(vuint16*)(&__IPSBAR[0x19003C]))
#define MCF_ADC_ADHLMT6            (*(vuint16*)(&__IPSBAR[0x19003E]))
#define MCF_ADC_ADHLMT7            (*(vuint16*)(&__IPSBAR[0x190040]))
#define MCF_ADC_ADHLMT(x)          (*(vuint16*)(&__IPSBAR[0x190032+((x)*0x002)]))
#define MCF_ADC_ADOFS0             (*(vuint16*)(&__IPSBAR[0x190042]))
#define MCF_ADC_ADOFS1             (*(vuint16*)(&__IPSBAR[0x190044]))
#define MCF_ADC_ADOFS2             (*(vuint16*)(&__IPSBAR[0x190046]))
#define MCF_ADC_ADOFS3             (*(vuint16*)(&__IPSBAR[0x190048]))
#define MCF_ADC_ADOFS4             (*(vuint16*)(&__IPSBAR[0x19004A]))
#define MCF_ADC_ADOFS5             (*(vuint16*)(&__IPSBAR[0x19004C]))
#define MCF_ADC_ADOFS6             (*(vuint16*)(&__IPSBAR[0x19004E]))
#define MCF_ADC_ADOFS7             (*(vuint16*)(&__IPSBAR[0x190050]))
#define MCF_ADC_ADOFS(x)           (*(vuint16*)(&__IPSBAR[0x190042+((x)*0x002)]))
#define MCF_ADC_POWER              (*(vuint16*)(&__IPSBAR[0x190052]))
#define MCF_ADC_CAL                (*(vuint16*)(&__IPSBAR[0x190054]))

/* Bit definitions and macros for MCF_ADC_CTRL1 */
#define MCF_ADC_CTRL1_SMODE(x)     ((x)&0x0007)
#define MCF_ADC_CTRL1_CHNCFG(x)    (((x)&0x000F)<<4)
#define MCF_ADC_CTRL1_HLMTIE       (0x0100)
#define MCF_ADC_CTRL1_LLMTIE       (0x0200)
#define MCF_ADC_CTRL1_ZCIE         (0x0400)
#define MCF_ADC_CTRL1_EOSIE0       (0x0800)
#define MCF_ADC_CTRL1_SYNC0        (0x1000)
#define MCF_ADC_CTRL1_START0       (0x2000)
#define MCF_ADC_CTRL1_STOP0        (0x4000)

/* Bit definitions and macros for MCF_ADC_CTRL2 */
#define MCF_ADC_CTRL2_DIV(x)       ((x)&0x001F)
#define MCF_ADC_CTRL2_SIMULT       (0x0020)
#define MCF_ADC_CTRL2_EOSIE1       (0x0800)
#define MCF_ADC_CTRL2_SYNC1        (0x1000)
#define MCF_ADC_CTRL2_START1       (0x2000)
#define MCF_ADC_CTRL2_STOP1        (0x4000)

/* Bit definitions and macros for MCF_ADC_ADZCC */
#define MCF_ADC_ADZCC_ZCE0(x)      (((x)&0x0003)<<0)
#define MCF_ADC_ADZCC_ZCE1(x)      (((x)&0x0003)<<2)
#define MCF_ADC_ADZCC_ZCE2(x)      (((x)&0x0003)<<4)
#define MCF_ADC_ADZCC_ZCE3(x)      (((x)&0x0003)<<6)
#define MCF_ADC_ADZCC_ZCE4(x)      (((x)&0x0003)<<8)
#define MCF_ADC_ADZCC_ZCE5(x)      (((x)&0x0003)<<10)
#define MCF_ADC_ADZCC_ZCE6(x)      (((x)&0x0003)<<12)
#define MCF_ADC_ADZCC_ZCE7(x)      (((x)&0x0003)<<14)

/* Bit definitions and macros for MCF_ADC_ADLST1 */
#define MCF_ADC_ADLST1_SAMPLE0(x)  (((x)&0x0007)<<0)
#define MCF_ADC_ADLST1_SAMPLE1(x)  (((x)&0x0007)<<4)
#define MCF_ADC_ADLST1_SAMPLE2(x)  (((x)&0x0007)<<8)
#define MCF_ADC_ADLST1_SAMPLE3(x)  (((x)&0x0007)<<12)

/* Bit definitions and macros for MCF_ADC_ADLST2 */
#define MCF_ADC_ADLST2_SAMPLE4(x)  (((x)&0x0007)<<0)
#define MCF_ADC_ADLST2_SAMPLE5(x)  (((x)&0x0007)<<4)
#define MCF_ADC_ADLST2_SAMPLE6(x)  (((x)&0x0007)<<8)
#define MCF_ADC_ADLST2_SAMPLE7(x)  (((x)&0x0007)<<12)

/* Bit definitions and macros for MCF_ADC_ADSDIS */
#define MCF_ADC_ADSDIS_DS0         (0x0001)
#define MCF_ADC_ADSDIS_DS1         (0x0002)
#define MCF_ADC_ADSDIS_DS2         (0x0004)
#define MCF_ADC_ADSDIS_DS3         (0x0008)
#define MCF_ADC_ADSDIS_DS4         (0x0010)
#define MCF_ADC_ADSDIS_DS5         (0x0020)
#define MCF_ADC_ADSDIS_DS6         (0x0040)
#define MCF_ADC_ADSDIS_DS7         (0x0080)

/* Bit definitions and macros for MCF_ADC_ADSTAT */
#define MCF_ADC_ADSTAT_RDY0        (0x0001)
#define MCF_ADC_ADSTAT_RDY1        (0x0002)
#define MCF_ADC_ADSTAT_RDY2        (0x0004)
#define MCF_ADC_ADSTAT_RDY3        (0x0008)
#define MCF_ADC_ADSTAT_RDY4        (0x0010)
#define MCF_ADC_ADSTAT_RDY5        (0x0020)
#define MCF_ADC_ADSTAT_RDY6        (0x0040)
#define MCF_ADC_ADSTAT_RDY7        (0x0080)
#define MCF_ADC_ADSTAT_HLMT        (0x0100)
#define MCF_ADC_ADSTAT_LLMTI       (0x0200)
#define MCF_ADC_ADSTAT_ZCI         (0x0400)
#define MCF_ADC_ADSTAT_EOSI        (0x0800)
#define MCF_ADC_ADSTAT_CIP         (0x8000)

/* Bit definitions and macros for MCF_ADC_ADLSTAT */
#define MCF_ADC_ADLSTAT_LLS0       (0x0001)
#define MCF_ADC_ADLSTAT_LLS1       (0x0002)
#define MCF_ADC_ADLSTAT_LLS2       (0x0004)
#define MCF_ADC_ADLSTAT_LLS3       (0x0008)
#define MCF_ADC_ADLSTAT_LLS4       (0x0010)
#define MCF_ADC_ADLSTAT_LLS5       (0x0020)
#define MCF_ADC_ADLSTAT_LLS6       (0x0040)
#define MCF_ADC_ADLSTAT_LLS7       (0x0080)
#define MCF_ADC_ADLSTAT_HLS0       (0x0100)
#define MCF_ADC_ADLSTAT_HLS1       (0x0200)
#define MCF_ADC_ADLSTAT_HLS2       (0x0400)
#define MCF_ADC_ADLSTAT_HLS3       (0x0800)
#define MCF_ADC_ADLSTAT_HLS4       (0x1000)
#define MCF_ADC_ADLSTAT_HLS5       (0x2000)
#define MCF_ADC_ADLSTAT_HLS6       (0x4000)
#define MCF_ADC_ADLSTAT_HLS7       (0x8000)

/* Bit definitions and macros for MCF_ADC_ADZCSTAT */
#define MCF_ADC_ADZCSTAT_ZCS0      (0x0001)
#define MCF_ADC_ADZCSTAT_ZCS1      (0x0002)
#define MCF_ADC_ADZCSTAT_ZCS2      (0x0004)
#define MCF_ADC_ADZCSTAT_ZCS3      (0x0008)
#define MCF_ADC_ADZCSTAT_ZCS4      (0x0010)
#define MCF_ADC_ADZCSTAT_ZCS5      (0x0020)
#define MCF_ADC_ADZCSTAT_ZCS6      (0x0040)
#define MCF_ADC_ADZCSTAT_ZCS7      (0x0080)

/* Bit definitions and macros for MCF_ADC_ADRSLT */
#define MCF_ADC_ADRSLT_RSLT(x)     (((x)&0x0FFF)<<3)
#define MCF_ADC_ADRSLT_SEXT        (0x8000)

/* Bit definitions and macros for MCF_ADC_ADLLMT */
#define MCF_ADC_ADLLMT_LLMT(x)     (((x)&0x0FFF)<<3)

/* Bit definitions and macros for MCF_ADC_ADHLMT */
#define MCF_ADC_ADHLMT_HLMT(x)     (((x)&0x0FFF)<<3)

/* Bit definitions and macros for MCF_ADC_ADOFS */
#define MCF_ADC_ADOFS_OFFSET(x)    (((x)&0x0FFF)<<3)

/* Bit definitions and macros for MCF_ADC_POWER */
#define MCF_ADC_POWER_PD0          (0x0001)
#define MCF_ADC_POWER_PD1          (0x0002)
#define MCF_ADC_POWER_PD2          (0x0004)
#define MCF_ADC_POWER_APD          (0x0008)
#define MCF_ADC_POWER_PUDELAY(x)   (((x)&0x003F)<<4)
#define MCF_ADC_POWER_PSTS0        (0x0400)
#define MCF_ADC_POWER_PSTS1        (0x0800)
#define MCF_ADC_POWER_PSTS2        (0x1000)
#define MCF_ADC_POWER_ASTBY        (0x8000)

/* Bit definitions and macros for MCF_ADC_CAL */
#define MCF_ADC_CAL_CAL0           (0x0001)
#define MCF_ADC_CAL_CRS0           (0x0002)
#define MCF_ADC_CAL_CAL1           (0x0004)
#define MCF_ADC_CAL_CRS1           (0x0008)

/********************************************************************/

#endif /* __MCF5213_ADC_H__ */
