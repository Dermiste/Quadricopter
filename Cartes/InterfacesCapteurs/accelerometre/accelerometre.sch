EESchema Schematic File Version 2  date 24/02/2011 10:03:27
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
LIBS:lis331dlh
LIBS:accelerometre-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "27 jan 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LIS331DLH U1
U 1 1 4D417997
P 7600 2800
F 0 "U1" H 7650 2850 60  0001 C CNN
F 1 "LIS331DLH" H 7600 2800 60  0001 C CNN
F 4 "U" H 7600 2950 60  0000 C CNN "R�f�rence"
F 5 "LIS331DLH" H 7600 2850 60  0000 C CNN "Valeur"
F 6 "" H 7600 2800 60  0000 C CNN "Module"
F 7 "" H 7600 2800 60  0000 C CNN "Documentation"
	1    7600 2800
	1    0    0    -1  
$EndComp
Connection ~ 8400 3600
Connection ~ 7450 1350
Connection ~ 7450 1050
Connection ~ 7850 1050
Connection ~ 7850 1350
Connection ~ 8000 2150
Connection ~ 8000 2050
Connection ~ 8000 1950
Connection ~ 7300 2150
Connection ~ 7300 2050
Connection ~ 7300 1950
Connection ~ 7300 1850
Connection ~ 8650 3850
Connection ~ 8300 1850
Connection ~ 8000 1850
Wire Wire Line
	7850 1050 7850 1350
Wire Wire Line
	7300 1350 7300 1850
Wire Wire Line
	7300 1350 7450 1350
Wire Wire Line
	7850 1350 8000 1350
Connection ~ 6800 3000
Connection ~ 6800 3150
Connection ~ 6800 3300
Connection ~ 6800 3450
Connection ~ 6800 3600
Connection ~ 6800 3750
Connection ~ 6800 3900
Connection ~ 8400 3900
Connection ~ 7050 1850
Connection ~ 8300 1850
Connection ~ 8400 3000
Connection ~ 8400 3150
Connection ~ 8400 3450
Connection ~ 8500 3300
Connection ~ 8400 3300
Wire Wire Line
	7300 1950 6550 1950
Wire Wire Line
	6550 1950 6550 3150
Wire Wire Line
	6550 3150 6800 3150
Wire Wire Line
	7300 2150 6250 2150
Wire Wire Line
	6250 2150 6250 3450
Wire Wire Line
	6250 3450 6800 3450
Wire Wire Line
	8000 2050 8950 2050
Wire Wire Line
	8950 2050 8950 4100
Wire Wire Line
	8950 4100 6700 4100
Wire Wire Line
	6700 4100 6700 3750
Wire Wire Line
	6700 3750 6800 3750
Connection ~ 8500 1850
Wire Wire Line
	8500 1850 8000 1850
Connection ~ 6800 1850
Wire Wire Line
	8500 3300 8400 3300
Wire Wire Line
	8650 3750 8400 3750
Wire Wire Line
	8400 3150 8650 3150
Connection ~ 8400 3750
Wire Wire Line
	8400 3900 8400 3600
Wire Wire Line
	8400 3150 8400 3000
Wire Wire Line
	8400 3300 8400 3450
Wire Wire Line
	7300 1850 6800 1850
Wire Wire Line
	6800 1850 6800 3000
Wire Wire Line
	8650 3150 8650 3850
Connection ~ 8650 3750
Wire Wire Line
	6800 3900 6800 4050
Wire Wire Line
	6800 4050 8850 4050
Wire Wire Line
	8850 4050 8850 1950
Wire Wire Line
	8850 1950 8000 1950
Wire Wire Line
	6800 3600 6650 3600
Wire Wire Line
	6650 3600 6650 4150
Wire Wire Line
	6650 4150 9050 4150
Wire Wire Line
	9050 4150 9050 2150
Wire Wire Line
	9050 2150 8000 2150
Wire Wire Line
	6800 3300 6400 3300
Wire Wire Line
	6400 3300 6400 2050
Wire Wire Line
	6400 2050 7300 2050
Wire Wire Line
	8000 1850 8000 1350
Wire Wire Line
	7450 1350 7450 1050
$Comp
L C C2
U 1 1 4D416AFA
P 7650 1350
F 0 "C2" H 7700 1450 50  0000 L CNN
F 1 "100nF" H 7700 1250 50  0000 L CNN
	1    7650 1350
	0    1    1    0   
$EndComp
$Comp
L C C1
U 1 1 4D416AF3
P 7650 1050
F 0 "C1" H 7700 1150 50  0000 L CNN
F 1 "10uF" H 7700 950 50  0000 L CNN
	1    7650 1050
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG01
U 1 1 4D4169DF
P 7050 1850
F 0 "#FLG01" H 7050 2120 30  0001 C CNN
F 1 "PWR_FLAG" H 7050 2080 30  0000 C CNN
	1    7050 1850
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 4D4169DB
P 8300 1850
F 0 "#FLG02" H 8300 2120 30  0001 C CNN
F 1 "PWR_FLAG" H 8300 2080 30  0000 C CNN
	1    8300 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 4D4168FA
P 8500 1850
F 0 "#PWR03" H 8500 1850 30  0001 C CNN
F 1 "GND" H 8500 1780 30  0001 C CNN
	1    8500 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 4D4168F2
P 8650 3850
F 0 "#PWR04" H 8650 3850 30  0001 C CNN
F 1 "GND" H 8650 3780 30  0001 C CNN
	1    8650 3850
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR05
U 1 1 4D4168E0
P 6800 1850
F 0 "#PWR05" H 6800 1950 30  0001 C CNN
F 1 "VDD" H 6800 1960 30  0000 C CNN
	1    6800 1850
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR06
U 1 1 4D4168D6
P 8500 3300
F 0 "#PWR06" H 8500 3400 30  0001 C CNN
F 1 "VDD" H 8500 3410 30  0000 C CNN
	1    8500 3300
	1    0    0    -1  
$EndComp
$Comp
L DIL8 P1
U 1 1 4D416855
P 7650 2000
F 0 "P1" H 7650 2250 60  0000 C CNN
F 1 "DIL8" V 7650 2000 50  0000 C CNN
	1    7650 2000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
