EESchema Schematic File Version 2  date 5/27/2013 10:54:42 AM
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
LIBS:MyLib
LIBS:Test-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date "27 may 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_2 P1
U 1 1 51A2B2CF
P 1950 1800
F 0 "P1" V 1900 1800 40  0000 C CNN
F 1 "BATT_CONN" V 2000 1800 40  0000 C CNN
F 2 "" H 1950 1800 60  0001 C CNN
F 3 "" H 1950 1800 60  0001 C CNN
	1    1950 1800
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR06
U 1 1 51A2B2CE
P 4800 1350
F 0 "#PWR06" H 4800 1450 30  0001 C CNN
F 1 "VCC" H 4800 1450 30  0000 C CNN
F 2 "" H 4800 1350 60  0001 C CNN
F 3 "" H 4800 1350 60  0001 C CNN
	1    4800 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 51A2B2CD
P 4100 2350
F 0 "#PWR07" H 4100 2350 30  0001 C CNN
F 1 "GND" H 4100 2280 30  0001 C CNN
F 2 "" H 4100 2350 60  0001 C CNN
F 3 "" H 4100 2350 60  0001 C CNN
	1    4100 2350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 51A2B2CC
P 4650 1850
F 0 "C1" H 4650 1950 40  0000 L CNN
F 1 "C" H 4656 1765 40  0000 L CNN
F 2 "~" H 4688 1700 30  0000 C CNN
F 3 "~" H 4650 1850 60  0000 C CNN
	1    4650 1850
	1    0    0    -1  
$EndComp
$Comp
L REG1117 3.3V1
U 1 1 51A2B2CB
P 4100 1650
F 0 "3.3V1" H 4000 1900 60  0000 C CNN
F 1 "REG1117" H 4150 1750 60  0000 C CNN
F 2 "" H 4100 1650 60  0001 C CNN
F 3 "" H 4100 1650 60  0001 C CNN
	1    4100 1650
	1    0    0    -1  
$EndComp
Connection ~ 4650 1650
Wire Wire Line
	4800 1650 4800 1350
Wire Wire Line
	4500 1650 4800 1650
Connection ~ 4100 2200
Wire Wire Line
	4650 2200 4100 2200
Wire Wire Line
	4650 2050 4650 2200
Connection ~ 4100 2000
Connection ~ 4100 2250
Wire Wire Line
	4050 2000 4200 2000
Wire Wire Line
	4100 2000 4100 2350
Wire Wire Line
	3850 1650 3650 1650
Wire Wire Line
	2400 1900 2400 2300
Connection ~ 4100 2150
Wire Wire Line
	2400 1700 2300 1700
Wire Wire Line
	2300 1900 2400 1900
$Comp
L SWITCH_INV SW1
U 1 1 51A3B93F
P 2900 1700
F 0 "SW1" H 2700 1850 50  0000 C CNN
F 1 "SWITCH_INV" H 2750 1550 50  0000 C CNN
F 2 "~" H 2900 1700 60  0000 C CNN
F 3 "~" H 2900 1700 60  0000 C CNN
	1    2900 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2300 4100 2300
Connection ~ 4100 2300
Wire Wire Line
	3400 1800 3400 2300
Connection ~ 3400 2300
Wire Wire Line
	3400 1600 3650 1600
Wire Wire Line
	3650 1600 3650 1650
Text HLabel 6900 3050 0    60   UnSpc ~ 0
DIO8
Text HLabel 6900 3150 0    60   UnSpc ~ 0
DIO9
Text HLabel 6900 3250 0    60   UnSpc ~ 0
DIO10
$EndSCHEMATC
