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
Sheet 3 9
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
L TEST_POINT TP5
U 1 1 5178A9A6
P 8800 5200
F 0 "TP5" H 8830 5200 40  0000 L CNN
F 1 "TEST_POINT" H 8900 5105 30  0001 C CNN
	1    8800 5200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR01
U 1 1 5178A9A5
P 8800 5450
F 0 "#PWR01" H 8800 5450 30  0001 C CNN
F 1 "GND" H 8800 5380 30  0001 C CNN
	1    8800 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 5350 8800 5450
Wire Wire Line
	9100 5350 9100 5450
$Comp
L GND #PWR02
U 1 1 5178A9A4
P 9100 5450
F 0 "#PWR02" H 9100 5450 30  0001 C CNN
F 1 "GND" H 9100 5380 30  0001 C CNN
	1    9100 5450
	1    0    0    -1  
$EndComp
$Comp
L TEST_POINT TP7
U 1 1 5178A9A3
P 9100 5200
F 0 "TP7" H 9130 5200 40  0000 L CNN
F 1 "TEST_POINT" H 9200 5105 30  0001 C CNN
	1    9100 5200
	0    -1   -1   0   
$EndComp
$Comp
L TEST_POINT TP6
U 1 1 5178A9A2
P 9100 4500
F 0 "TP6" H 9130 4500 40  0000 L CNN
F 1 "TEST_POINT" H 9200 4405 30  0001 C CNN
	1    9100 4500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR03
U 1 1 5178A9A1
P 9100 4750
F 0 "#PWR03" H 9100 4750 30  0001 C CNN
F 1 "GND" H 9100 4680 30  0001 C CNN
	1    9100 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 4650 9100 4750
Wire Wire Line
	8800 4650 8800 4750
$Comp
L GND #PWR04
U 1 1 5178A9A0
P 8800 4750
F 0 "#PWR04" H 8800 4750 30  0001 C CNN
F 1 "GND" H 8800 4680 30  0001 C CNN
	1    8800 4750
	1    0    0    -1  
$EndComp
$Comp
L TEST_POINT TP4
U 1 1 5178A99F
P 8800 4500
F 0 "TP4" H 8830 4500 40  0000 L CNN
F 1 "TEST_POINT" H 8900 4405 30  0001 C CNN
	1    8800 4500
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR05
U 1 1 5178A293
P 6550 4350
F 0 "#PWR05" H 6550 4350 30  0001 C CNN
F 1 "GND" H 6550 4280 30  0001 C CNN
	1    6550 4350
	1    0    0    -1  
$EndComp
Connection ~ 4650 2550
Wire Wire Line
	4650 2550 5150 2550
Connection ~ 4050 3500
Wire Wire Line
	3600 4000 3600 3500
Wire Wire Line
	3600 3500 7500 3500
Wire Wire Line
	3500 4000 3500 2950
Wire Wire Line
	3500 2950 3100 2950
Connection ~ 6750 2750
Wire Wire Line
	6750 2750 6650 2750
Connection ~ 6750 3500
Wire Wire Line
	6750 3500 6750 2550
Wire Wire Line
	6750 2550 6650 2550
Wire Wire Line
	5150 2900 5000 2900
Wire Wire Line
	5150 2700 5000 2700
Connection ~ 4050 2150
Wire Wire Line
	4050 3100 4050 2150
Connection ~ 5000 3500
Wire Wire Line
	4650 2300 4650 3100
Connection ~ 6550 3500
Wire Wire Line
	6550 3500 6550 3550
Connection ~ 4650 2400
Wire Wire Line
	4650 2400 5150 2400
Wire Wire Line
	5150 2150 3950 2150
Connection ~ 4650 3500
Connection ~ 4300 3500
Wire Wire Line
	4300 2150 4300 3100
Connection ~ 4300 2150
Wire Wire Line
	5150 2800 5000 2800
Connection ~ 5000 2800
Connection ~ 5000 2900
Wire Wire Line
	6650 2650 6750 2650
Connection ~ 6750 2650
Wire Wire Line
	5150 2300 3400 2300
Wire Wire Line
	3400 2300 3400 4000
Connection ~ 4650 2300
Wire Wire Line
	6550 4050 6550 4350
Wire Wire Line
	5000 2700 5000 3500
Text Notes 2550 4650 0    60   ~ 0
Jumper to select pow_en high or low
$Comp
L CONN_3 K1
U 1 1 51780C40
P 3500 4350
F 0 "K1" V 3450 4350 50  0000 C CNN
F 1 "CONN_3" V 3550 4350 40  0000 C CNN
	1    3500 4350
	0    1    1    0   
$EndComp
Text HLabel 3100 2950 0    60   Input ~ 0
POW_EN
Text Notes 6600 2000 0    60   ~ 0
Must be left floating
NoConn ~ 6650 2350
NoConn ~ 6650 2250
NoConn ~ 6650 2150
$Comp
L C C3
U 1 1 51780849
P 4050 3300
F 0 "C3" H 4100 3400 50  0000 L CNN
F 1 "10uF" H 4100 3200 50  0000 L CNN
	1    4050 3300
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 51780844
P 4300 3300
F 0 "C4" H 4350 3400 50  0000 L CNN
F 1 "100nF" H 4350 3200 50  0000 L CNN
	1    4300 3300
	1    0    0    -1  
$EndComp
Text HLabel 3950 2150 0    60   Output ~ 0
VDD
Text HLabel 7500 3500 2    60   Output ~ 0
VSS
$Comp
L C C5
U 1 1 5177035E
P 4650 3300
F 0 "C5" H 4700 3400 50  0000 L CNN
F 1 "10nF" H 4700 3200 50  0000 L CNN
	1    4650 3300
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 51770333
P 6550 3800
F 0 "R4" V 6630 3800 50  0000 C CNN
F 1 "10" V 6550 3800 50  0000 C CNN
	1    6550 3800
	1    0    0    -1  
$EndComp
$Comp
L ATA6870 U1
U 2 1 5172FD3F
P 5900 1900
F 0 "U1" H 5900 1900 60  0000 C CNN
F 1 "ATA6870" H 5900 2000 60  0000 C CNN
	2    5900 1900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
