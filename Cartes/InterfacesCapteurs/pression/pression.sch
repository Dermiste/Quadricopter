EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:adaptateur_accéléromètre
LIBS:pression-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DIL10 P1
U 1 1 550177FC
P 6200 2900
F 0 "P1" H 6200 3200 60  0000 C CNN
F 1 "DIL10" V 6200 2900 50  0000 C CNN
F 2 "" H 6200 2900 60  0000 C CNN
F 3 "" H 6200 2900 60  0000 C CNN
	1    6200 2900
	1    0    0    -1  
$EndComp
$Comp
L DIL8 P2
U 1 1 55017838
P 6200 3950
F 0 "P2" H 6200 4200 60  0000 C CNN
F 1 "DIL8" V 6200 3950 50  0000 C CNN
F 2 "" H 6200 3950 60  0000 C CNN
F 3 "" H 6200 3950 60  0000 C CNN
	1    6200 3950
	1    0    0    -1  
$EndComp
Text Label 5850 2700 2    60   ~ 0
Vcc
Text Label 5850 2800 2    60   ~ 0
CLK
Text Label 5850 3000 2    60   ~ 0
SDI
Text Label 5850 3100 2    60   ~ 0
SDO
Text Label 6550 3100 0    60   ~ 0
CS
$Comp
L GND #PWR01
U 1 1 550178C0
P 6950 2800
F 0 "#PWR01" H 6950 2550 60  0001 C CNN
F 1 "GND" H 6950 2650 60  0000 C CNN
F 2 "" H 6950 2800 60  0000 C CNN
F 3 "" H 6950 2800 60  0000 C CNN
	1    6950 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 550178D6
P 5050 2900
F 0 "#PWR02" H 5050 2650 60  0001 C CNN
F 1 "GND" H 5050 2750 60  0000 C CNN
F 2 "" H 5050 2900 60  0000 C CNN
F 3 "" H 5050 2900 60  0000 C CNN
	1    5050 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2800 6950 2800
Wire Wire Line
	6550 2900 6750 2900
Wire Wire Line
	6750 2900 6750 2800
Connection ~ 6750 2800
Wire Wire Line
	5850 2900 5050 2900
Text Label 6550 2700 0    60   ~ 0
Vcc
Text Label 6550 3000 0    60   ~ 0
INT1
Text Label 5850 3800 2    60   ~ 0
Vcc
Text Label 5850 3900 2    60   ~ 0
CLK
$Comp
L GND #PWR03
U 1 1 55018019
P 6950 3800
F 0 "#PWR03" H 6950 3550 60  0001 C CNN
F 1 "GND" H 6950 3650 60  0000 C CNN
F 2 "" H 6950 3800 60  0000 C CNN
F 3 "" H 6950 3800 60  0000 C CNN
	1    6950 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3800 6950 3800
Text Label 5850 4000 2    60   ~ 0
SDI
Text Label 5850 4100 2    60   ~ 0
SDO
Text Label 6550 4100 0    60   ~ 0
CS
NoConn ~ 6550 3900
NoConn ~ 6550 4000
NoConn ~ 7100 3000
Text Label 7350 2500 0    60   ~ 0
Vcc
Wire Wire Line
	7350 2500 7350 2650
$Comp
L C C1
U 1 1 550180DE
P 7350 2850
F 0 "C1" H 7400 2950 50  0000 L CNN
F 1 "4.7 uF" H 7400 2750 50  0000 L CNN
F 2 "" H 7388 2700 30  0000 C CNN
F 3 "" H 7350 2850 60  0000 C CNN
	1    7350 2850
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5501810D
P 7700 2850
F 0 "C2" H 7750 2950 50  0000 L CNN
F 1 "100 uF" H 7750 2750 50  0000 L CNN
F 2 "" H 7738 2700 30  0000 C CNN
F 3 "" H 7700 2850 60  0000 C CNN
	1    7700 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5501812A
P 7350 3250
F 0 "#PWR04" H 7350 3000 60  0001 C CNN
F 1 "GND" H 7350 3100 60  0000 C CNN
F 2 "" H 7350 3250 60  0000 C CNN
F 3 "" H 7350 3250 60  0000 C CNN
	1    7350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3050 7350 3250
Wire Wire Line
	7700 3050 7700 3200
Wire Wire Line
	7700 3200 7350 3200
Connection ~ 7350 3200
Wire Wire Line
	7350 2550 7700 2550
Wire Wire Line
	7700 2550 7700 2650
Connection ~ 7350 2550
$EndSCHEMATC
