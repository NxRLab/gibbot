EESchema Schematic File Version 2  date 5/24/2013 4:40:19 PM
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
Sheet 4 9
Title ""
Date "24 may 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 4050 2850
Wire Wire Line
	5550 3050 5100 3050
Wire Wire Line
	5550 2950 5100 2950
Wire Wire Line
	3850 2750 4300 2750
Wire Wire Line
	5550 2750 5100 2750
Wire Wire Line
	3850 2850 4300 2850
Wire Wire Line
	5550 2850 5100 2850
Connection ~ 5400 3050
$Comp
L R R58
U 1 1 5184844A
P 4050 2600
F 0 "R58" V 4130 2600 50  0000 C CNN
F 1 "1K" V 4050 2600 50  0000 C CNN
	1    4050 2600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR06
U 1 1 51848449
P 4050 2350
F 0 "#PWR06" H 4050 2310 30  0001 C CNN
F 1 "+3.3V" H 4050 2460 30  0000 C CNN
	1    4050 2350
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR07
U 1 1 51848433
P 5400 2550
F 0 "#PWR07" H 5400 2510 30  0001 C CNN
F 1 "+3.3V" H 5400 2660 30  0000 C CNN
	1    5400 2550
	1    0    0    -1  
$EndComp
NoConn ~ 5100 2650
$Comp
L +3.3V #PWR08
U 1 1 51848334
P 4300 2650
F 0 "#PWR08" H 4300 2610 30  0001 C CNN
F 1 "+3.3V" H 4300 2760 30  0000 C CNN
	1    4300 2650
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR09
U 1 1 5184832A
P 4300 3050
F 0 "#PWR09" H 4300 3050 40  0001 C CNN
F 1 "DGND" H 4300 2980 40  0000 C CNN
	1    4300 3050
	1    0    0    -1  
$EndComp
NoConn ~ 4300 2950
$Comp
L R R59
U 1 1 51848113
P 5400 2800
F 0 "R59" V 5480 2800 50  0000 C CNN
F 1 "1K" V 5400 2800 50  0000 C CNN
	1    5400 2800
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P2
U 1 1 51847E55
P 4700 2850
F 0 "P2" H 4700 3150 60  0000 C CNN
F 1 "CONN_5X2" V 4700 2850 50  0000 C CNN
	1    4700 2850
	1    0    0    -1  
$EndComp
Text HLabel 5550 2850 2    60   Input ~ 0
CS_N
Text HLabel 5550 2950 2    60   Input ~ 0
CLK
Text HLabel 3850 2750 0    60   Input ~ 0
SCK
Text HLabel 3850 2850 0    60   Input ~ 0
MISO
Text HLabel 5550 2750 2    60   Input ~ 0
MOSI
Text HLabel 5550 3050 2    60   Input ~ 0
IRQ
$EndSCHEMATC
