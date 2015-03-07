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
Sheet 8 9
Title ""
Date "24 may 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R35
U 1 1 51781CE6
P 5950 1450
F 0 "R35" V 6000 1250 50  0000 C CNN
F 1 "1K" V 5950 1450 50  0000 C CNN
	1    5950 1450
	0    -1   -1   0   
$EndComp
$Comp
L R R36
U 1 1 51781CE5
P 5950 1550
F 0 "R36" V 6000 1350 50  0000 C CNN
F 1 "1K" V 5950 1550 50  0000 C CNN
	1    5950 1550
	0    -1   -1   0   
$EndComp
$Comp
L R R37
U 1 1 51781CE4
P 5950 1650
F 0 "R37" V 6000 1450 50  0000 C CNN
F 1 "1K" V 5950 1650 50  0000 C CNN
	1    5950 1650
	0    -1   -1   0   
$EndComp
$Comp
L R R33
U 1 1 51781CE3
P 5950 1250
F 0 "R33" V 6000 1050 50  0000 C CNN
F 1 "1K" V 5950 1250 50  0000 C CNN
	1    5950 1250
	0    -1   -1   0   
$EndComp
$Comp
L R R34
U 1 1 51781CE2
P 5950 1350
F 0 "R34" V 6000 1150 50  0000 C CNN
F 1 "1K" V 5950 1350 50  0000 C CNN
	1    5950 1350
	0    -1   -1   0   
$EndComp
$Comp
L R R32
U 1 1 51781CE1
P 5950 1150
F 0 "R32" V 6000 950 50  0000 C CNN
F 1 "1K" V 5950 1150 50  0000 C CNN
	1    5950 1150
	0    -1   -1   0   
$EndComp
$Comp
L C C17
U 1 1 51781CE0
P 6650 1850
F 0 "C17" V 6700 1950 50  0000 L CNN
F 1 "100nF" V 6800 1750 50  0000 L CNN
	1    6650 1850
	0    1    1    0   
$EndComp
$Comp
L R R31
U 1 1 51781CDF
P 5950 1050
F 0 "R31" V 6000 850 50  0000 C CNN
F 1 "1K" V 5950 1050 50  0000 C CNN
	1    5950 1050
	0    -1   -1   0   
$EndComp
Text HLabel 8800 1650 2    60   Output ~ 0
MBAT1
Text HLabel 8800 1550 2    60   Output ~ 0
MBAT2
Text HLabel 8800 1450 2    60   Output ~ 0
MBAT3
Text HLabel 8800 1350 2    60   Output ~ 0
MBAT4
Text HLabel 8800 1250 2    60   Output ~ 0
MBAT5
Text HLabel 8800 1150 2    60   Output ~ 0
MBAT6
Text HLabel 8800 1050 2    60   Output ~ 0
MBAT7
$Comp
L R R24
U 1 1 51781CDE
P 1550 2800
F 0 "R24" V 1630 2800 50  0000 C CNN
F 1 "500" V 1550 2800 50  0000 C CNN
	1    1550 2800
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q10
U 1 1 51781CDD
P 4300 3450
F 0 "Q10" H 4550 3450 60  0000 R CNN
F 1 "MOSFET_N/NDS7002A" H 4200 3700 60  0000 R CNN
	1    4300 3450
	-1   0    0    -1  
$EndComp
$Comp
L MOSFET_N Q11
U 1 1 51781CDC
P 4300 4650
F 0 "Q11" H 4550 4650 60  0000 R CNN
F 1 "MOSFET_N/NDS7002A" H 4200 4900 60  0000 R CNN
	1    4300 4650
	-1   0    0    -1  
$EndComp
$Comp
L MOSFET_N Q12
U 1 1 51781CDB
P 4300 5850
F 0 "Q12" H 4550 5850 60  0000 R CNN
F 1 "MOSFET_N/NDS7002A" H 4200 6100 60  0000 R CNN
	1    4300 5850
	-1   0    0    -1  
$EndComp
Text HLabel 4900 5850 2    60   Output ~ 0
DISCH1
Text HLabel 4950 4650 2    60   Output ~ 0
DISCH2
Text HLabel 4900 3450 2    60   Output ~ 0
DISCH3
Text HLabel 2300 6150 2    60   Output ~ 0
DISCH4
Text HLabel 2300 4800 2    60   Output ~ 0
DISCH5
Text HLabel 2300 3450 2    60   Output ~ 0
DISCH6
Text Notes 550  950  0    100  ~ 0
Battery Connection
Text Notes 1850 2600 0    100  ~ 0
Cell Balance FETs
Text HLabel 8800 800  2    60   Output ~ 0
VDDHV
$Comp
L R R30
U 1 1 51781CDA
P 5950 800
F 0 "R30" V 6030 800 50  0000 C CNN
F 1 "10" V 5950 800 50  0000 C CNN
	1    5950 800 
	0    -1   -1   0   
$EndComp
$Comp
L R R25
U 1 1 51781CD9
P 1550 4250
F 0 "R25" V 1630 4250 50  0000 C CNN
F 1 "500" V 1550 4250 50  0000 C CNN
	1    1550 4250
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q7
U 1 1 51781CD8
P 1650 3450
F 0 "Q7" H 1900 3450 60  0000 R CNN
F 1 "MOSFET_N/NDS7002A" H 1550 3700 60  0000 R CNN
	1    1650 3450
	-1   0    0    -1  
$EndComp
$Comp
L MOSFET_N Q8
U 1 1 51781CD7
P 1650 4800
F 0 "Q8" H 1900 4800 60  0000 R CNN
F 1 "MOSFET_N/NDS7002A" H 1550 5050 60  0000 R CNN
	1    1650 4800
	-1   0    0    -1  
$EndComp
$Comp
L R R26
U 1 1 51781CD6
P 1550 5400
F 0 "R26" V 1630 5400 50  0000 C CNN
F 1 "500" V 1550 5400 50  0000 C CNN
	1    1550 5400
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q9
U 1 1 51781CD5
P 1650 6150
F 0 "Q9" H 1900 6150 60  0000 R CNN
F 1 "MOSFET_N/NDS7002A" H 1550 6400 60  0000 R CNN
	1    1650 6150
	-1   0    0    -1  
$EndComp
$Comp
L R R27
U 1 1 51781CD4
P 4200 3000
F 0 "R27" V 4280 3000 50  0000 C CNN
F 1 "500" V 4200 3000 50  0000 C CNN
	1    4200 3000
	1    0    0    -1  
$EndComp
$Comp
L R R28
U 1 1 51781CD3
P 4200 4200
F 0 "R28" V 4280 4200 50  0000 C CNN
F 1 "500" V 4200 4200 50  0000 C CNN
	1    4200 4200
	1    0    0    -1  
$EndComp
$Comp
L R R29
U 1 1 51781CD2
P 4200 5400
F 0 "R29" V 4280 5400 50  0000 C CNN
F 1 "500" V 4200 5400 50  0000 C CNN
	1    4200 5400
	1    0    0    -1  
$EndComp
$Comp
L CONN_7 P4
U 1 1 51781CD1
P 950 1350
F 0 "P4" V 920 1350 60  0000 C CNN
F 1 "CONN_7" V 1020 1350 60  0000 C CNN
	1    950  1350
	-1   0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 51781CD0
P 7200 1850
F 0 "C18" V 7250 1950 50  0000 L CNN
F 1 "100nF" V 7350 1750 50  0000 L CNN
	1    7200 1850
	0    1    1    0   
$EndComp
$Comp
L C C22
U 1 1 51781CCF
P 8250 1850
F 0 "C22" V 8300 1950 50  0000 L CNN
F 1 "100nF" V 8400 1750 50  0000 L CNN
	1    8250 1850
	0    1    1    0   
$EndComp
$Comp
L C C20
U 1 1 51781CCE
P 7700 1850
F 0 "C20" V 7750 1950 50  0000 L CNN
F 1 "100nF" V 7850 1750 50  0000 L CNN
	1    7700 1850
	0    1    1    0   
$EndComp
$Comp
L C C19
U 1 1 51781CCD
P 7600 650
F 0 "C19" V 7650 750 50  0000 L CNN
F 1 "100nF" V 7700 350 50  0000 L CNN
	1    7600 650 
	0    1    -1   0   
$EndComp
$Comp
L C C21
U 1 1 51781CCC
P 8150 650
F 0 "C21" V 8200 750 50  0000 L CNN
F 1 "100nF" V 8200 350 50  0000 L CNN
	1    8150 650 
	0    1    -1   0   
$EndComp
Wire Wire Line
	3700 1650 3700 7300
Connection ~ 3700 6350
Connection ~ 3500 1550
Wire Wire Line
	4200 5000 3500 5000
Wire Wire Line
	3500 5000 3500 1550
Connection ~ 3100 2250
Wire Wire Line
	3100 2250 4200 2250
Wire Wire Line
	4200 2250 4200 2750
Connection ~ 7800 1150
Connection ~ 8350 1250
Connection ~ 8050 1350
Wire Wire Line
	8050 1350 8050 1850
Connection ~ 7500 1450
Wire Wire Line
	7500 1450 7500 1850
Connection ~ 7000 1550
Wire Wire Line
	7000 1550 7000 1850
Connection ~ 6450 1650
Wire Wire Line
	6450 1650 6450 1850
Connection ~ 3100 1350
Wire Wire Line
	3100 1350 3100 7000
Wire Wire Line
	3100 7000 1550 7000
Wire Wire Line
	4500 5850 4900 5850
Connection ~ 4200 5000
Connection ~ 4200 3800
Wire Wire Line
	4500 3450 4900 3450
Wire Wire Line
	1850 6150 2300 6150
Wire Wire Line
	1850 4800 2300 4800
Wire Wire Line
	1850 3450 2300 3450
Wire Wire Line
	1350 1250 1350 5150
Connection ~ 1550 3800
Wire Wire Line
	1550 3800 1450 3800
Wire Wire Line
	1450 3800 1450 1150
Wire Wire Line
	1550 2550 1550 1050
Wire Wire Line
	6200 800  8800 800 
Connection ~ 5300 1050
Wire Wire Line
	5300 1050 5300 800 
Wire Notes Line
	1100 2650 1100 7200
Wire Wire Line
	4200 3650 4200 3950
Connection ~ 1350 1250
Wire Wire Line
	1550 5000 1550 5150
Wire Wire Line
	5700 1050 1300 1050
Wire Wire Line
	6200 1050 8800 1050
Wire Wire Line
	6200 1150 8800 1150
Wire Wire Line
	6200 1250 8800 1250
Wire Wire Line
	6200 1350 8800 1350
Wire Wire Line
	6200 1450 8800 1450
Wire Wire Line
	6200 1550 8800 1550
Wire Wire Line
	6200 1650 8800 1650
Wire Wire Line
	1300 1150 5700 1150
Wire Wire Line
	1300 1250 5700 1250
Wire Wire Line
	1300 1350 5700 1350
Wire Wire Line
	1300 1450 5700 1450
Wire Wire Line
	1300 1550 5700 1550
Wire Wire Line
	1300 1650 5700 1650
Wire Wire Line
	1550 5650 1550 5950
Connection ~ 1550 1050
Connection ~ 1450 1150
Wire Wire Line
	4200 5150 4200 4850
Wire Wire Line
	4200 6050 4200 6350
Wire Wire Line
	5300 800  5700 800 
Wire Wire Line
	1550 3050 1550 3250
Wire Wire Line
	1550 4000 1550 3650
Wire Wire Line
	1550 4500 1550 4600
Wire Wire Line
	1550 5150 1350 5150
Wire Wire Line
	1550 7000 1550 6350
Wire Wire Line
	4500 4650 4950 4650
Wire Wire Line
	6850 1850 6850 1550
Connection ~ 6850 1550
Wire Wire Line
	7400 1450 7400 1850
Connection ~ 7400 1450
Wire Wire Line
	7900 1350 7900 1850
Connection ~ 7900 1350
Wire Wire Line
	8450 1250 8450 1850
Connection ~ 8450 1250
Wire Wire Line
	8350 1250 8350 650 
Wire Wire Line
	7800 1150 7800 650 
Wire Wire Line
	7400 1050 7400 650 
Wire Wire Line
	7950 1150 7950 650 
Connection ~ 7950 1150
Connection ~ 7400 1050
Wire Wire Line
	3300 1450 3300 3800
Wire Wire Line
	3300 3800 4200 3800
Connection ~ 3300 1450
Wire Wire Line
	4200 6350 3700 6350
Connection ~ 3700 1650
Wire Notes Line
	1100 2650 5800 2650
Wire Notes Line
	5800 2650 5800 7200
Wire Notes Line
	5800 7200 1100 7200
Wire Wire Line
	3700 7300 4050 7300
Text HLabel 4050 7300 2    60   Output ~ 0
BAT_BOT
$EndSCHEMATC