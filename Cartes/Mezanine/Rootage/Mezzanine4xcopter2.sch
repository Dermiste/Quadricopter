EESchema Schematic File Version 2
LIBS:74xgxx
LIBS:74xx
LIBS:ac-dc
LIBS:actel
LIBS:adc-dac
LIBS:analog_switches
LIBS:atmel
LIBS:audio
LIBS:brooktre
LIBS:cmos_ieee
LIBS:cmos4000
LIBS:conn
LIBS:contrib
LIBS:cypress
LIBS:dc-dc
LIBS:device
LIBS:digital-audio
LIBS:display
LIBS:dsp
LIBS:elec-unifil
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:intel
LIBS:interface
LIBS:ir
LIBS:linear
LIBS:logo
LIBS:memory
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:microchip
LIBS:microcontrollers
LIBS:motor_drivers
LIBS:motorola
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:opto
LIBS:philips
LIBS:power
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:regul
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:silabs
LIBS:siliconi
LIBS:special
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:texas
LIBS:transf
LIBS:transistors
LIBS:ttl_ieee
LIBS:valves
LIBS:video
LIBS:xilinx
LIBS:4xcopter
LIBS:adaptateur_accéléromètre
LIBS:L3G4-adapt
LIBS:lm1117
LIBS:LTC4150
LIBS:mcf5212-lqfp64
LIBS:quadri_ulti-cache
LIBS:Mezzanine4xcopter2-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "3 dec 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 1850 750  0    60   ~ 0
GND_batt
Text Label 1850 850  0    60   ~ 0
Vbatt
Text Label 1850 950  0    60   ~ 0
PWM1
Wire Wire Line
	1850 950  1250 950 
Wire Wire Line
	1250 850  1850 850 
Wire Wire Line
	1250 750  1850 750 
$Comp
L CONN_3 K2
U 1 1 50BCC83E
P 900 850
F 0 "K2" V 850 850 50  0000 C CNN
F 1 "CONN_3" V 950 850 40  0000 C CNN
F 2 "" H 900 850 60  0001 C CNN
F 3 "" H 900 850 60  0001 C CNN
	1    900  850 
	-1   0    0    -1  
$EndComp
Text Label 1850 1750 0    60   ~ 0
GND_batt
Text Label 1850 1850 0    60   ~ 0
Vbatt
Text Label 1850 1950 0    60   ~ 0
PWM5
Wire Wire Line
	1250 1950 1850 1950
Wire Wire Line
	1850 1850 1250 1850
Wire Wire Line
	1850 1750 1250 1750
$Comp
L CONN_3 K3
U 1 1 50BCC7FF
P 900 1850
F 0 "K3" V 850 1850 50  0000 C CNN
F 1 "CONN_3" V 950 1850 40  0000 C CNN
F 2 "" H 900 1850 60  0001 C CNN
F 3 "" H 900 1850 60  0001 C CNN
	1    900  1850
	-1   0    0    -1  
$EndComp
$Comp
L CONN_3 K4
U 1 1 50BCC7C8
P 900 1300
F 0 "K4" V 850 1300 50  0000 C CNN
F 1 "CONN_3" V 950 1300 40  0000 C CNN
F 2 "" H 900 1300 60  0001 C CNN
F 3 "" H 900 1300 60  0001 C CNN
	1    900  1300
	-1   0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 50BCC7BC
P 900 2400
F 0 "K1" V 850 2400 50  0000 C CNN
F 1 "CONN_3" V 950 2400 40  0000 C CNN
F 2 "" H 900 2400 60  0001 C CNN
F 3 "" H 900 2400 60  0001 C CNN
	1    900  2400
	-1   0    0    -1  
$EndComp
Text Label 2750 5600 0    60   ~ 0
DTIN0_trig
Wire Wire Line
	2650 5600 2750 5600
Connection ~ 4800 3900
Connection ~ 4800 4400
Connection ~ 4800 4900
Connection ~ 9950 2750
Connection ~ 9950 2100
Connection ~ 9950 2550
Connection ~ 7550 6150
Connection ~ 7550 6250
Connection ~ 8950 6250
Connection ~ 8950 5950
Connection ~ 7550 6050
Connection ~ 7550 5950
Connection ~ 7700 5000
Connection ~ 7700 4700
Connection ~ 7700 4600
Connection ~ 7700 4500
Connection ~ 7700 4400
Connection ~ 7700 4300
Connection ~ 4950 5600
Connection ~ 4600 5700
Connection ~ 4950 6400
Connection ~ 4600 6500
Connection ~ 3900 5000
Connection ~ 3900 4700
Connection ~ 3400 4700
Connection ~ 3400 5000
Connection ~ 3000 5000
Connection ~ 3000 4700
Connection ~ 2650 4400
Connection ~ 2650 4500
Connection ~ 2650 4600
Connection ~ 2650 4700
Connection ~ 2650 4800
Connection ~ 1850 4600
Connection ~ 1850 4700
Connection ~ 1850 4800
Connection ~ 1850 4900
Connection ~ 1850 5000
Connection ~ 2650 5400
Connection ~ 2650 5500
Connection ~ 2650 5700
Connection ~ 2650 6600
Connection ~ 4850 1900
Connection ~ 6100 1900
Connection ~ 6100 1500
Connection ~ 5900 1500
Connection ~ 4850 1500
Connection ~ 5100 1500
Connection ~ 4750 2450
Connection ~ 4750 2250
Connection ~ 3550 2450
Connection ~ 4250 2250
Connection ~ 3750 2250
Connection ~ 3550 2250
Connection ~ 1850 6900
Connection ~ 1350 6900
Connection ~ 5700 6000
Connection ~ 5700 5200
Connection ~ 5100 5200
Connection ~ 4950 5200
Connection ~ 4600 5200
Connection ~ 5100 6000
Connection ~ 4950 6000
Connection ~ 4600 6000
Connection ~ 5500 1900
Wire Wire Line
	5500 1800 5500 1900
Wire Wire Line
	5100 5200 4450 5200
Connection ~ 5500 1800
Wire Wire Line
	6100 1900 4650 1900
Wire Wire Line
	5900 1500 6450 1500
Wire Wire Line
	4350 2250 4350 1950
Wire Wire Line
	4350 1950 4300 1950
Wire Wire Line
	9950 2750 9600 2750
Wire Wire Line
	3000 5000 3000 4800
Wire Wire Line
	3000 4800 2650 4800
Wire Wire Line
	2650 4600 4400 4600
Wire Wire Line
	4400 4600 4400 6000
Wire Wire Line
	2650 4400 4800 4400
Wire Wire Line
	4800 3900 5050 3900
Wire Wire Line
	7400 6250 7550 6250
Wire Wire Line
	7400 5950 7550 5950
Connection ~ 4350 2250
Wire Wire Line
	4250 2250 4750 2250
Wire Wire Line
	3550 2250 3750 2250
Wire Wire Line
	2650 5500 2750 5500
Wire Wire Line
	2650 5700 2750 5700
Wire Wire Line
	2650 6600 2750 6600
Wire Wire Line
	1750 4900 1850 4900
Wire Wire Line
	1750 4700 1850 4700
Wire Wire Line
	1250 2300 1850 2300
Wire Wire Line
	1250 2400 1850 2400
Wire Wire Line
	1850 2500 1250 2500
Wire Wire Line
	1850 1200 1250 1200
Wire Wire Line
	1850 1300 1250 1300
Wire Wire Line
	1250 1400 1850 1400
Wire Wire Line
	9950 2100 9600 2100
Wire Wire Line
	1750 4600 1850 4600
Wire Wire Line
	1750 4800 1850 4800
Wire Wire Line
	1750 5000 1850 5000
Wire Wire Line
	1250 6900 1350 6900
Wire Wire Line
	2650 5400 2750 5400
Wire Wire Line
	4750 2450 3550 2450
Wire Wire Line
	3950 2450 3950 2650
Wire Wire Line
	3950 2650 4100 2650
Connection ~ 3950 2450
Wire Wire Line
	7400 6050 7550 6050
Wire Wire Line
	7400 6150 7550 6150
Wire Wire Line
	5700 5200 5850 5200
Wire Wire Line
	5700 6000 5850 6000
Wire Wire Line
	4800 4900 5100 4900
Wire Wire Line
	4450 5200 4450 4500
Wire Wire Line
	4450 4500 2650 4500
Wire Wire Line
	2650 4700 3000 4700
Wire Wire Line
	9950 2550 9600 2550
Wire Wire Line
	3450 4400 3450 4100
Connection ~ 3450 4400
Wire Wire Line
	3450 4100 3750 4100
Wire Wire Line
	4550 2250 4550 1500
Connection ~ 4550 2250
Wire Wire Line
	4550 1500 5100 1500
Connection ~ 4650 2450
Wire Wire Line
	4650 1900 4650 2450
Wire Wire Line
	4400 6000 5100 6000
Wire Wire Line
	4950 5600 5100 5600
Wire Wire Line
	4950 6400 5100 6400
Wire Wire Line
	9550 2300 9950 2300
Text Label 5100 6400 0    60   ~ 0
GND_3.3
Text Label 5100 5600 0    60   ~ 0
GND_3.3
$Comp
L C C4
U 1 1 50AA3A34
P 4950 6200
F 0 "C4" H 5000 6300 50  0000 L CNN
F 1 "100nF" H 5000 6100 50  0000 L CNN
F 2 "" H 4950 6200 60  0001 C CNN
F 3 "" H 4950 6200 60  0001 C CNN
	1    4950 6200
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 50AA3A2B
P 4950 5400
F 0 "C3" H 5000 5500 50  0000 L CNN
F 1 "100nF" H 5000 5300 50  0000 L CNN
F 2 "" H 4950 5400 60  0001 C CNN
F 3 "" H 4950 5400 60  0001 C CNN
	1    4950 5400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 50AA393B
P 4850 1700
F 0 "C1" H 4900 1800 50  0000 L CNN
F 1 "22µF" H 4900 1600 50  0000 L CNN
F 2 "" H 4850 1700 60  0001 C CNN
F 3 "" H 4850 1700 60  0001 C CNN
	1    4850 1700
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 50AA390B
P 6100 1700
F 0 "C2" H 6150 1800 50  0000 L CNN
F 1 "100nF" H 6150 1600 50  0000 L CNN
F 2 "" H 6100 1700 60  0001 C CNN
F 3 "" H 6100 1700 60  0001 C CNN
	1    6100 1700
	1    0    0    -1  
$EndComp
Text Label 6450 1500 0    60   ~ 0
Vcc_5V
$Comp
L LM7805 U5
U 1 1 50AA38BC
P 5500 1550
F 0 "U5" H 5650 1354 60  0000 C CNN
F 1 "LM7805" H 5500 1750 60  0000 C CNN
F 2 "" H 5500 1550 60  0001 C CNN
F 3 "" H 5500 1550 60  0001 C CNN
	1    5500 1550
	1    0    0    -1  
$EndComp
Text Label 3750 4100 0    60   ~ 0
image_tension
Text Label 9600 2550 2    60   ~ 0
Vcc_5V
$Comp
L CONN_2 P9
U 1 1 50AA377B
P 10300 2650
F 0 "P9" V 10250 2650 40  0000 C CNN
F 1 "CONN_2" V 10350 2650 40  0000 C CNN
F 2 "" H 10300 2650 60  0001 C CNN
F 3 "" H 10300 2650 60  0001 C CNN
	1    10300 2650
	1    0    0    -1  
$EndComp
Text Notes 750  6750 0    60   ~ 0
Valeur fusible à verrif
$Comp
L LED D2
U 1 1 50A1185F
P 3200 5000
F 0 "D2" H 3200 5100 50  0000 C CNN
F 1 "LED" H 3200 4900 50  0000 C CNN
F 2 "" H 3200 5000 60  0001 C CNN
F 3 "" H 3200 5000 60  0001 C CNN
	1    3200 5000
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 50A1185E
P 3650 5000
F 0 "R2" V 3730 5000 50  0000 C CNN
F 1 "130" V 3650 5000 50  0000 C CNN
F 2 "" H 3650 5000 60  0001 C CNN
F 3 "" H 3650 5000 60  0001 C CNN
	1    3650 5000
	0    -1   -1   0   
$EndComp
Text Label 3900 5000 0    60   ~ 0
GND_3.3
Text Label 3900 4700 0    60   ~ 0
GND_3.3
$Comp
L R R1
U 1 1 50A11804
P 3650 4700
F 0 "R1" V 3730 4700 50  0000 C CNN
F 1 "130" V 3650 4700 50  0000 C CNN
F 2 "" H 3650 4700 60  0001 C CNN
F 3 "" H 3650 4700 60  0001 C CNN
	1    3650 4700
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 50A117D9
P 3200 4700
F 0 "D1" H 3200 4800 50  0000 C CNN
F 1 "LED" H 3200 4600 50  0000 C CNN
F 2 "" H 3200 4700 60  0001 C CNN
F 3 "" H 3200 4700 60  0001 C CNN
	1    3200 4700
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 50A11590
P 5400 6000
F 0 "SW2" H 5550 6110 50  0000 C CNN
F 1 "SW_PUSH" H 5400 5920 50  0000 C CNN
F 2 "" H 5400 6000 60  0001 C CNN
F 3 "" H 5400 6000 60  0001 C CNN
	1    5400 6000
	1    0    0    -1  
$EndComp
Text Label 5850 6000 0    60   ~ 0
GND_3.3
$Comp
L R R4
U 1 1 50A1158F
P 4600 6250
F 0 "R4" V 4680 6250 50  0000 C CNN
F 1 "330" V 4600 6250 50  0000 C CNN
F 2 "" H 4600 6250 60  0001 C CNN
F 3 "" H 4600 6250 60  0001 C CNN
	1    4600 6250
	1    0    0    -1  
$EndComp
Text Label 4600 6500 0    60   ~ 0
Vcc_3.3V
Text Label 4600 5700 0    60   ~ 0
Vcc_3.3V
$Comp
L R R3
U 1 1 50A1155E
P 4600 5450
F 0 "R3" V 4680 5450 50  0000 C CNN
F 1 "330" V 4600 5450 50  0000 C CNN
F 2 "" H 4600 5450 60  0001 C CNN
F 3 "" H 4600 5450 60  0001 C CNN
	1    4600 5450
	1    0    0    -1  
$EndComp
Text Label 5850 5200 0    60   ~ 0
GND_3.3
$Comp
L SW_PUSH SW1
U 1 1 50A1152A
P 5400 5200
F 0 "SW1" H 5550 5310 50  0000 C CNN
F 1 "SW_PUSH" H 5400 5120 50  0000 C CNN
F 2 "" H 5400 5200 60  0001 C CNN
F 3 "" H 5400 5200 60  0001 C CNN
	1    5400 5200
	1    0    0    -1  
$EndComp
Text Label 5100 4900 0    60   ~ 0
GND_batt
Text Label 5050 3900 0    60   ~ 0
Vbatt
$Comp
L R R5
U 1 1 50A113F6
P 4800 4150
F 0 "R5" V 4880 4150 50  0000 C CNN
F 1 "20k" V 4800 4150 50  0000 C CNN
F 2 "" H 4800 4150 60  0001 C CNN
F 3 "" H 4800 4150 60  0001 C CNN
	1    4800 4150
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 50A113F0
P 4800 4650
F 0 "R6" V 4880 4650 50  0000 C CNN
F 1 "10k" V 4800 4650 50  0000 C CNN
F 2 "" H 4800 4650 60  0001 C CNN
F 3 "" H 4800 4650 60  0001 C CNN
	1    4800 4650
	1    0    0    -1  
$EndComp
Text Notes 7350 7550 0    60   ~ 0
Carte Mezzanine           Debeuret Rochefeuille
NoConn ~ 7700 4900
NoConn ~ 7700 4800
Text Label 7700 4700 2    60   ~ 0
GND_3.3
Text Label 7700 4600 2    60   ~ 0
QSPI_MISO
Text Label 7700 4500 2    60   ~ 0
QSPI_MOSI
Text Label 7700 4300 2    60   ~ 0
Vcc_3.3V
Text Label 8950 6250 0    60   ~ 0
GND_3.3
NoConn ~ 8950 6150
NoConn ~ 8950 6050
Text Label 7400 6050 2    60   ~ 0
QSPI_CLK
Text Label 4300 1950 2    60   ~ 0
Vbatt
Text Label 4100 2650 0    60   ~ 0
GND_batt
$Comp
L FUSE F2
U 1 1 50A0FC75
P 1600 6900
F 0 "F2" H 1700 6950 40  0000 C CNN
F 1 "300mA" H 1500 6850 40  0000 C CNN
F 2 "" H 1600 6900 60  0001 C CNN
F 3 "" H 1600 6900 60  0001 C CNN
	1    1600 6900
	1    0    0    -1  
$EndComp
$Comp
L FUSE F1
U 1 1 50A0FC59
P 4000 2250
F 0 "F1" H 4100 2300 40  0000 C CNN
F 1 "25A" H 3900 2200 40  0000 C CNN
F 2 "" H 4000 2250 60  0001 C CNN
F 3 "" H 4000 2250 60  0001 C CNN
	1    4000 2250
	1    0    0    -1  
$EndComp
Text Notes 5200 2300 0    60   ~ 0
Alim_carte_mere\n\nGND_carte_mere
$Comp
L CONN_2 P5
U 1 1 50A0FBD3
P 3200 2350
F 0 "P5" V 3150 2350 40  0000 C CNN
F 1 "CONN_2" V 3250 2350 40  0000 C CNN
F 2 "" H 3200 2350 60  0001 C CNN
F 3 "" H 3200 2350 60  0001 C CNN
	1    3200 2350
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P6
U 1 1 50A0FB82
P 5100 2350
F 0 "P6" V 5050 2350 40  0000 C CNN
F 1 "CONN_2" V 5150 2350 40  0000 C CNN
F 2 "" H 5100 2350 60  0001 C CNN
F 3 "" H 5100 2350 60  0001 C CNN
	1    5100 2350
	1    0    0    1   
$EndComp
NoConn ~ 2650 4000
NoConn ~ 2650 4100
NoConn ~ 2650 4200
NoConn ~ 2650 4300
NoConn ~ 2650 4900
NoConn ~ 2650 5000
NoConn ~ 2650 5100
NoConn ~ 2650 5200
NoConn ~ 2650 5300
NoConn ~ 2650 5800
NoConn ~ 2650 5900
NoConn ~ 2650 6000
NoConn ~ 2650 6200
NoConn ~ 2650 6300
NoConn ~ 2650 6400
NoConn ~ 2650 6500
NoConn ~ 2650 6700
NoConn ~ 2650 6800
NoConn ~ 2650 6900
NoConn ~ 1850 6800
NoConn ~ 1850 6700
NoConn ~ 1850 6600
NoConn ~ 1850 6500
NoConn ~ 1850 6400
NoConn ~ 1850 6300
NoConn ~ 1850 6200
NoConn ~ 1850 5800
NoConn ~ 1850 5700
NoConn ~ 1850 5600
NoConn ~ 1850 5500
NoConn ~ 1850 4500
NoConn ~ 1850 4400
NoConn ~ 1850 4300
NoConn ~ 1850 4200
NoConn ~ 1850 4100
NoConn ~ 1850 4000
Text Label 1850 2500 0    60   ~ 0
PWM7
Text Label 1850 2400 0    60   ~ 0
Vbatt
Text Label 1850 2300 0    60   ~ 0
GND_batt
Text Label 1850 1400 0    60   ~ 0
PWM3
Text Label 1850 1300 0    60   ~ 0
Vbatt
Text Label 1850 1200 0    60   ~ 0
GND_batt
Text Label 9550 2300 2    60   ~ 0
DTIN0_trig
Text Label 9600 2100 2    60   ~ 0
PTC1_echo
Text Label 7400 5950 2    60   ~ 0
Vcc_3.3V
Text Label 7700 5000 2    60   ~ 0
CS_ACC
Text Label 8950 5950 0    60   ~ 0
CS_GYRO
Text Label 7400 6150 2    60   ~ 0
QSPI_MOSI
Text Label 7400 6250 2    60   ~ 0
QSPI_MISO
Text Label 7700 4400 2    60   ~ 0
QSPI_CLK
Text Label 2750 5700 0    60   ~ 0
PTC1_echo
Text Label 1250 6900 2    60   ~ 0
Vcc_3.3V
Text Label 2750 6600 0    60   ~ 0
GND_3.3
Text Label 1700 5100 2    60   ~ 0
CS_GYRO
Text Label 1750 5000 2    60   ~ 0
QSPI_CLK
Text Label 1700 5200 2    60   ~ 0
CS_ACC
Text Label 2750 5500 0    60   ~ 0
PWM7
Text Label 2750 5400 0    60   ~ 0
PWM5
Text Label 1750 4700 2    60   ~ 0
PWM3
Text Label 1750 4600 2    60   ~ 0
PWM1
Text Label 1750 4900 2    60   ~ 0
QSPI_MISO
Text Label 1750 4800 2    60   ~ 0
QSPI_MOSI
$Comp
L L3G4-ADAPT U3
U 1 1 5097E136
P 8250 5700
F 0 "U3" H 8250 5700 60  0000 C CNN
F 1 "L3G4200D_Gyroscope" H 8250 5600 60  0000 C CNN
F 2 "" H 8250 5700 60  0001 C CNN
F 3 "" H 8250 5700 60  0001 C CNN
	1    8250 5700
	1    0    0    -1  
$EndComp
$Comp
L CONN_30X2 P7
U 1 1 5097DAF1
P 2250 5450
F 0 "P7" H 2250 7000 60  0000 C CNN
F 1 "CONN_30X2" V 2250 5450 50  0000 C CNN
F 2 "" H 2250 5450 60  0001 C CNN
F 3 "" H 2250 5450 60  0001 C CNN
	1    2250 5450
	1    0    0    -1  
$EndComp
Text Notes 10400 2150 0    60   ~ 0
Retour\nUltrasson\nEntrée 
$Comp
L CONN_2 P8
U 1 1 508559B6
P 10300 2200
F 0 "P8" V 10250 2200 40  0000 C CNN
F 1 "CONN_2" V 10350 2200 40  0000 C CNN
F 2 "" H 10300 2200 60  0001 C CNN
F 3 "" H 10300 2200 60  0001 C CNN
	1    10300 2200
	1    0    0    -1  
$EndComp
$Comp
L Accelero U2
U 1 1 54FD7B73
P 8100 4150
F 0 "U2" H 8350 3150 60  0000 C CNN
F 1 "LIS331DLH_Accelero" H 8350 4200 60  0000 C CNN
F 2 "" H 8100 4150 60  0000 C CNN
F 3 "" H 8100 4150 60  0000 C CNN
	1    8100 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 5100 1700 5100
Connection ~ 1850 5100
Connection ~ 1850 5300
Connection ~ 1850 5400
Wire Wire Line
	1850 5300 1700 5300
Wire Wire Line
	1850 5400 1700 5400
Wire Wire Line
	1700 5200 1850 5200
Connection ~ 1850 5200
Text Label 1700 5300 2    60   ~ 0
CS_EXT1
Text Label 1700 5400 2    60   ~ 0
CS_EXT2
NoConn ~ 2650 6100
$Comp
L Accelero U4
U 1 1 54FDECD4
P 10350 4150
F 0 "U4" H 10600 3150 60  0000 C CNN
F 1 "AdditonalSPIModule_1" H 10600 4200 60  0000 C CNN
F 2 "" H 10350 4150 60  0000 C CNN
F 3 "" H 10350 4150 60  0000 C CNN
	1    10350 4150
	1    0    0    -1  
$EndComp
$Comp
L Accelero U1
U 1 1 54FE06DB
P 10350 5450
F 0 "U1" H 10600 4450 60  0000 C CNN
F 1 "AdditonalSPIModule_2" H 10600 5500 60  0000 C CNN
F 2 "" H 10350 5450 60  0000 C CNN
F 3 "" H 10350 5450 60  0000 C CNN
	1    10350 5450
	1    0    0    -1  
$EndComp
Text Label 9950 4300 2    60   ~ 0
Vcc_3.3V
Text Label 9950 4400 2    60   ~ 0
QSPI_CLK
Text Label 9950 4500 2    60   ~ 0
QSPI_MOSI
Text Label 9950 4600 2    60   ~ 0
QSPI_MISO
Text Label 9950 4700 2    60   ~ 0
GND_3.3
Text Label 9950 5600 2    60   ~ 0
Vcc_3.3V
Text Label 9950 5700 2    60   ~ 0
QSPI_CLK
Text Label 9950 5800 2    60   ~ 0
QSPI_MOSI
Text Label 9950 5900 2    60   ~ 0
QSPI_MISO
Text Label 9950 6000 2    60   ~ 0
GND_3.3
Text Label 9950 5000 2    60   ~ 0
CS_EXT1
Text Label 9950 6300 2    60   ~ 0
CS_EXT2
Text Label 7250 2750 2    60   ~ 0
GND_3.3
Text Label 1850 6100 2    60   ~ 0
CF_RX0
Text Label 1850 6000 2    60   ~ 0
CF_TX0
NoConn ~ 1850 5900
Text Label 7250 3050 2    60   ~ 0
CF_TX0
Text Label 7250 3150 2    60   ~ 0
CF_RX0
NoConn ~ 9950 6100
NoConn ~ 9950 6200
NoConn ~ 9950 4800
NoConn ~ 9950 4900
NoConn ~ 7250 2950
NoConn ~ 7250 3250
$Comp
L CONN_7 P1
U 1 1 54FF5D6F
P 7600 3050
F 0 "P1" V 7570 3050 60  0000 C CNN
F 1 "CONN_7" V 7670 3050 60  0000 C CNN
F 2 "" H 7600 3050 60  0000 C CNN
F 3 "" H 7600 3050 60  0000 C CNN
	1    7600 3050
	1    0    0    -1  
$EndComp
NoConn ~ 7250 3350
Text Label 9600 2750 2    60   ~ 0
GND_3.3
Text Label 7250 2850 2    60   ~ 0
Vcc_3.3V
$Comp
L LED D4
U 1 1 55016BAC
P 8400 1450
F 0 "D4" H 8400 1550 50  0000 C CNN
F 1 "LED" H 8400 1350 50  0000 C CNN
F 2 "" H 8400 1450 60  0000 C CNN
F 3 "" H 8400 1450 60  0000 C CNN
	1    8400 1450
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 55016BB2
P 9400 1450
F 0 "R8" V 9480 1450 50  0000 C CNN
F 1 "R" V 9407 1451 50  0000 C CNN
F 2 "" V 9330 1450 30  0000 C CNN
F 3 "" H 9400 1450 30  0000 C CNN
	1    9400 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 1450 9150 1450
Wire Wire Line
	9650 1450 9800 1450
Wire Wire Line
	7950 1450 8200 1450
Text Label 7950 1450 2    60   ~ 0
Vcc_3.3V
Text Label 9800 1450 0    60   ~ 0
GND_3.3
$EndSCHEMATC
