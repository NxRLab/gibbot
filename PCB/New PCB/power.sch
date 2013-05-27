EESchema Schematic File Version 2  date 5/26/2013 8:12:24 PM
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
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
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
L CONN_2 P?
U 1 1 51A2B2CF
P 1150 1600
F 0 "P?" V 1100 1600 40  0000 C CNN
F 1 "BATT_CONN" V 1200 1600 40  0000 C CNN
	1    1150 1600
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR?
U 1 1 51A2B2CE
P 4800 1350
F 0 "#PWR?" H 4800 1450 30  0001 C CNN
F 1 "VCC" H 4800 1450 30  0000 C CNN
	1    4800 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 51A2B2CD
P 4100 2350
F 0 "#PWR?" H 4100 2350 30  0001 C CNN
F 1 "GND" H 4100 2280 30  0001 C CNN
	1    4100 2350
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 51A2B2CC
P 4650 1850
F 0 "C?" H 4650 1950 40  0000 L CNN
F 1 "C" H 4656 1765 40  0000 L CNN
F 2 "~" H 4688 1700 30  0000 C CNN
F 3 "~" H 4650 1850 60  0000 C CNN
	1    4650 1850
	1    0    0    -1  
$EndComp
$Comp
L REG1117 IC?
U 1 1 51A2B2CB
P 4100 1650
F 0 "IC?" H 4000 1900 60  0000 C CNN
F 1 "REG1117" H 4150 1750 60  0000 C CNN
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
	1600 1700 1600 2100
Connection ~ 4100 2150
Wire Wire Line
	1600 1500 1500 1500
Wire Wire Line
	1500 1700 1600 1700
$EndSCHEMATC
