EESchema Schematic File Version 2  date 5/7/2013 3:13:49 PM
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
LIBS:schematic_lib
LIBS:Misc
LIBS:Connectors
LIBS:batt_test_parts-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 7 9
Title ""
Date "7 may 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATA6870 U2
U 2 1 51781D02
P 6050 2450
F 0 "U2" H 6050 2450 60  0000 C CNN
F 1 "ATA6870" H 6050 2550 60  0000 C CNN
	2    6050 2450
	1    0    0    -1  
$EndComp
$Comp
L R R23
U 1 1 51781D01
P 6700 4350
F 0 "R23" V 6780 4350 50  0000 C CNN
F 1 "10" V 6700 4350 50  0000 C CNN
	1    6700 4350
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 51781D00
P 4800 3850
F 0 "C16" H 4850 3950 50  0000 L CNN
F 1 "10nF" H 4850 3750 50  0000 L CNN
	1    4800 3850
	1    0    0    -1  
$EndComp
Text HLabel 7650 4050 2    60   Output ~ 0
VSS
Text HLabel 4100 2700 0    60   Output ~ 0
VDD
$Comp
L C C15
U 1 1 51781CFF
P 4450 3850
F 0 "C15" H 4500 3950 50  0000 L CNN
F 1 "100nF" H 4500 3750 50  0000 L CNN
	1    4450 3850
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 51781CFE
P 4200 3850
F 0 "C14" H 4250 3950 50  0000 L CNN
F 1 "10uF" H 4250 3750 50  0000 L CNN
	1    4200 3850
	1    0    0    -1  
$EndComp
NoConn ~ 6800 2700
NoConn ~ 6800 2800
NoConn ~ 6800 2900
Text Notes 6750 2550 0    60   ~ 0
Must be left floating
Text HLabel 3250 3500 0    60   Input ~ 0
POW_EN
$Comp
L CONN_3 K2
U 1 1 51781CFD
P 3650 4900
F 0 "K2" V 3600 4900 50  0000 C CNN
F 1 "CONN_3" V 3700 4900 40  0000 C CNN
	1    3650 4900
	0    1    1    0   
$EndComp
Text Notes 2700 5200 0    60   ~ 0
Jumper to select pow_en high or low
Text HLabel 6700 4900 3    60   Input ~ 0
BAT_BOT
Wire Wire Line
	6700 4600 6700 4900
Connection ~ 4800 2850
Wire Wire Line
	3550 4550 3550 2850
Wire Wire Line
	3550 2850 5300 2850
Connection ~ 6900 3200
Wire Wire Line
	6800 3200 6900 3200
Connection ~ 5150 3450
Connection ~ 5150 3350
Wire Wire Line
	5300 3350 5150 3350
Connection ~ 4450 2700
Wire Wire Line
	4450 2700 4450 3650
Connection ~ 4450 4050
Connection ~ 4800 4050
Wire Wire Line
	5300 2700 4100 2700
Wire Wire Line
	4800 2950 5300 2950
Connection ~ 4800 2950
Wire Wire Line
	6700 4050 6700 4100
Connection ~ 6700 4050
Wire Wire Line
	4800 2850 4800 3650
Connection ~ 5150 4050
Wire Wire Line
	4200 3650 4200 2700
Connection ~ 4200 2700
Wire Wire Line
	5150 3250 5300 3250
Wire Wire Line
	5300 3450 5150 3450
Wire Wire Line
	6800 3100 6900 3100
Wire Wire Line
	6900 3100 6900 4050
Connection ~ 6900 4050
Wire Wire Line
	6900 3300 6800 3300
Connection ~ 6900 3300
Wire Wire Line
	3250 3500 3650 3500
Wire Wire Line
	3650 3500 3650 4550
Wire Wire Line
	7650 4050 3750 4050
Wire Wire Line
	3750 4050 3750 4550
Connection ~ 4200 4050
Wire Wire Line
	5150 4050 5150 3100
Wire Wire Line
	5150 3100 5300 3100
Connection ~ 5150 3250
Text Notes 4750 1950 0    60   ~ 0
This will be the top level monitor pack
$EndSCHEMATC
