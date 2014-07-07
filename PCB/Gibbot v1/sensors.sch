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
LIBS:MyLib
LIBS:Test-cache
EELAYER 27 0
EELAYER END
$Descr A2 23386 16535
encoding utf-8
Sheet 4 4
Title ""
Date "15 jul 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C C47
U 1 1 51A3D246
P 14650 5450
F 0 "C47" H 14700 5550 50  0000 L CNN
F 1 "0.1uF" H 14700 5350 50  0000 L CNN
F 2 "" H 14650 5450 60  0001 C CNN
F 3 "" H 14650 5450 60  0001 C CNN
	1    14650 5450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0108
U 1 1 51A3D245
P 14650 5250
F 0 "#PWR0108" H 14650 5350 30  0001 C CNN
F 1 "VCC" H 14650 5350 30  0000 C CNN
F 2 "" H 14650 5250 60  0001 C CNN
F 3 "" H 14650 5250 60  0001 C CNN
	1    14650 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0109
U 1 1 51A3D244
P 14650 5650
F 0 "#PWR0109" H 14650 5650 30  0001 C CNN
F 1 "GND" H 14650 5580 30  0001 C CNN
F 2 "" H 14650 5650 60  0001 C CNN
F 3 "" H 14650 5650 60  0001 C CNN
	1    14650 5650
	1    0    0    -1  
$EndComp
$Comp
L C C45
U 1 1 51A3D243
P 14000 5450
F 0 "C45" H 14050 5550 50  0000 L CNN
F 1 "0.1uF" H 14050 5350 50  0000 L CNN
F 2 "" H 14000 5450 60  0001 C CNN
F 3 "" H 14000 5450 60  0001 C CNN
	1    14000 5450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0110
U 1 1 51A3D242
P 14000 5250
F 0 "#PWR0110" H 14000 5350 30  0001 C CNN
F 1 "VCC" H 14000 5350 30  0000 C CNN
F 2 "" H 14000 5250 60  0001 C CNN
F 3 "" H 14000 5250 60  0001 C CNN
	1    14000 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0111
U 1 1 51A3D241
P 14000 5650
F 0 "#PWR0111" H 14000 5650 30  0001 C CNN
F 1 "GND" H 14000 5580 30  0001 C CNN
F 2 "" H 14000 5650 60  0001 C CNN
F 3 "" H 14000 5650 60  0001 C CNN
	1    14000 5650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0112
U 1 1 51A3D240
P 14350 5650
F 0 "#PWR0112" H 14350 5650 30  0001 C CNN
F 1 "GND" H 14350 5580 30  0001 C CNN
F 2 "" H 14350 5650 60  0001 C CNN
F 3 "" H 14350 5650 60  0001 C CNN
	1    14350 5650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0113
U 1 1 51A3D23F
P 14350 5250
F 0 "#PWR0113" H 14350 5350 30  0001 C CNN
F 1 "VCC" H 14350 5350 30  0000 C CNN
F 2 "" H 14350 5250 60  0001 C CNN
F 3 "" H 14350 5250 60  0001 C CNN
	1    14350 5250
	1    0    0    -1  
$EndComp
$Comp
L C C46
U 1 1 51A3D23E
P 14350 5450
F 0 "C46" H 14400 5550 50  0000 L CNN
F 1 "0.1uF" H 14400 5350 50  0000 L CNN
F 2 "" H 14350 5450 60  0001 C CNN
F 3 "" H 14350 5450 60  0001 C CNN
	1    14350 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4300 6200 4300
Wire Wire Line
	6000 4200 6200 4200
Wire Wire Line
	6200 4100 6000 4100
Wire Wire Line
	5450 4000 6200 4000
Wire Wire Line
	7100 4300 7200 4300
Wire Wire Line
	7100 4200 7300 4200
Wire Wire Line
	7100 4100 7350 4100
Wire Wire Line
	7350 4100 7350 4300
Wire Wire Line
	7350 4300 7850 4300
Wire Wire Line
	7100 4000 7400 4000
Wire Wire Line
	7400 4000 7400 4200
Wire Wire Line
	7400 4200 7850 4200
Wire Wire Line
	7100 3900 7450 3900
Wire Wire Line
	7450 3900 7450 4100
Wire Wire Line
	7450 4100 7850 4100
Wire Wire Line
	7800 3700 7800 3900
Wire Wire Line
	7800 3900 7850 3900
Wire Wire Line
	7650 4000 7850 4000
Wire Wire Line
	6200 3700 5350 3700
Wire Wire Line
	5350 3700 5350 3550
Wire Wire Line
	5350 3550 4200 3550
Connection ~ 5000 3550
Wire Wire Line
	4700 4150 5350 4150
Wire Wire Line
	4700 4150 4700 4050
Wire Wire Line
	4700 4050 4200 4050
Connection ~ 4400 3550
Connection ~ 4400 4050
Wire Wire Line
	3800 3550 3800 4250
Connection ~ 3800 4050
Wire Wire Line
	6200 3800 5350 3800
Wire Wire Line
	5350 3800 5350 4150
Connection ~ 5000 4150
Wire Wire Line
	6000 3900 6200 3900
Wire Wire Line
	7100 3700 7500 3700
Wire Wire Line
	7100 3800 7350 3800
Wire Wire Line
	7350 3800 7350 3700
Connection ~ 7350 3700
Wire Wire Line
	14650 6850 18000 6850
Wire Bus Line
	6900 7350 6900 8000
Wire Wire Line
	5000 7250 4800 7250
Wire Wire Line
	5000 7350 4800 7350
Wire Wire Line
	3550 7250 3300 7250
Wire Wire Line
	14650 6950 15500 6950
Wire Wire Line
	15500 6950 15500 7050
Wire Wire Line
	15800 7450 15800 7750
Connection ~ 15800 6750
Wire Wire Line
	15800 7050 15800 6750
Wire Wire Line
	16350 6750 16500 6750
Wire Wire Line
	14650 6750 15850 6750
Connection ~ 16500 6650
Wire Wire Line
	14650 6650 16500 6650
Connection ~ 15500 7750
Wire Wire Line
	15500 7450 15500 7750
Connection ~ 15250 7750
Wire Wire Line
	15250 7450 15250 7750
Connection ~ 15050 7750
Wire Wire Line
	14650 7050 15250 7050
Wire Wire Line
	15050 7800 15050 7150
Wire Wire Line
	15050 7150 14650 7150
Connection ~ 16500 6250
Wire Wire Line
	16150 6250 16500 6250
Wire Wire Line
	16150 6550 16300 6550
Connection ~ 15600 6550
Wire Wire Line
	15600 6550 15600 6250
Wire Wire Line
	15600 6250 15650 6250
Wire Wire Line
	14650 6550 15650 6550
Connection ~ 13650 7000
Wire Wire Line
	10850 7000 13650 7000
Connection ~ 13650 6600
Wire Wire Line
	13250 6600 13650 6600
Connection ~ 13650 7050
Wire Wire Line
	13750 7050 13650 7050
Connection ~ 13650 6950
Wire Wire Line
	13750 6950 13650 6950
Connection ~ 13650 6650
Wire Wire Line
	13750 6650 13650 6650
Connection ~ 13650 6550
Wire Wire Line
	13750 6550 13650 6550
Wire Wire Line
	13750 6850 13650 6850
Wire Wire Line
	13650 6850 13650 7150
Wire Wire Line
	13650 7150 13750 7150
Wire Wire Line
	13750 6750 13650 6750
Wire Wire Line
	13650 6750 13650 6450
Wire Wire Line
	13650 6450 13750 6450
Wire Wire Line
	4800 7450 5000 7450
Wire Wire Line
	4800 7800 5250 7800
Wire Wire Line
	4800 7700 5250 7700
Wire Wire Line
	4800 7600 5250 7600
Wire Wire Line
	7000 7800 7200 7800
Wire Wire Line
	7000 7700 7200 7700
Wire Wire Line
	7000 7900 7200 7900
Connection ~ 8700 7950
Wire Wire Line
	8700 7950 8450 7950
Connection ~ 8700 7800
Wire Wire Line
	8700 7800 8450 7800
Connection ~ 8700 7700
Wire Wire Line
	8700 7700 8450 7700
Connection ~ 8700 7600
Wire Wire Line
	8450 7600 8700 7600
Wire Wire Line
	8700 8500 8700 7500
Wire Wire Line
	8700 7500 8450 7500
Connection ~ 9050 7350
Wire Wire Line
	9050 7350 8450 7350
Connection ~ 9050 7250
Wire Wire Line
	9050 7250 8450 7250
Wire Wire Line
	9050 7000 9050 8050
Wire Wire Line
	9050 8050 8450 8050
Wire Wire Line
	8700 8150 8450 8150
Connection ~ 8700 8150
Wire Wire Line
	3300 6900 3300 8150
Wire Wire Line
	3300 8150 3550 8150
Connection ~ 3300 7250
Wire Wire Line
	3300 7350 3550 7350
Connection ~ 3300 7350
Wire Wire Line
	3550 7550 3450 7550
Wire Wire Line
	3450 7550 3450 8400
Wire Wire Line
	3550 7650 3450 7650
Connection ~ 3450 7650
Wire Wire Line
	3450 7750 3550 7750
Connection ~ 3450 7750
Wire Wire Line
	3450 7850 3550 7850
Connection ~ 3450 7850
Wire Wire Line
	3450 7950 3550 7950
Connection ~ 3450 7950
Wire Wire Line
	3450 8050 3550 8050
Connection ~ 3450 8050
Connection ~ 3450 8250
Wire Wire Line
	4800 8000 4950 8000
Wire Wire Line
	4950 8250 4850 8250
Wire Wire Line
	4850 8250 4850 8000
Connection ~ 4850 8000
Wire Wire Line
	5350 8000 6250 8000
Wire Wire Line
	6250 8000 6250 8450
Wire Wire Line
	5350 8250 5500 8250
Wire Wire Line
	6000 8250 6250 8250
Connection ~ 6250 8250
Wire Wire Line
	14650 6450 15200 6450
Wire Wire Line
	15200 6450 15200 6000
Wire Wire Line
	14600 9050 18000 9050
Wire Wire Line
	14600 9150 15450 9150
Wire Wire Line
	15450 9150 15450 9250
Wire Wire Line
	15750 9650 15750 9950
Connection ~ 15750 8950
Wire Wire Line
	15750 9250 15750 8950
Wire Wire Line
	16300 8950 16450 8950
Wire Wire Line
	14600 8950 15800 8950
Connection ~ 16450 8850
Wire Wire Line
	14600 8850 16450 8850
Connection ~ 15450 9950
Wire Wire Line
	15450 9650 15450 9950
Connection ~ 15200 9950
Wire Wire Line
	15200 9650 15200 9950
Connection ~ 15000 9950
Wire Wire Line
	14600 9250 15200 9250
Wire Wire Line
	15000 10000 15000 9350
Wire Wire Line
	15000 9350 14600 9350
Connection ~ 16450 8450
Wire Wire Line
	16100 8450 16450 8450
Wire Wire Line
	16100 8750 16250 8750
Connection ~ 15550 8750
Wire Wire Line
	15550 8750 15550 8450
Wire Wire Line
	15550 8450 15600 8450
Wire Wire Line
	14600 8750 15600 8750
Connection ~ 13600 9200
Wire Wire Line
	10950 9200 13600 9200
Connection ~ 13600 8800
Wire Wire Line
	13250 8800 13600 8800
Connection ~ 13600 9250
Wire Wire Line
	13700 9250 13600 9250
Connection ~ 13600 9150
Wire Wire Line
	13700 9150 13600 9150
Connection ~ 13600 8850
Wire Wire Line
	13700 8850 13600 8850
Connection ~ 13600 8750
Wire Wire Line
	13700 8750 13600 8750
Wire Wire Line
	13700 9050 13600 9050
Wire Wire Line
	13600 9050 13600 9350
Wire Wire Line
	13600 9350 13700 9350
Wire Wire Line
	13700 8950 13600 8950
Wire Wire Line
	13600 8950 13600 8650
Wire Wire Line
	13600 8650 13700 8650
Wire Wire Line
	14600 8650 15150 8650
Wire Wire Line
	15150 8650 15150 8200
Wire Wire Line
	14550 11050 18000 11050
Wire Wire Line
	14550 11150 15400 11150
Wire Wire Line
	15400 11150 15400 11250
Wire Wire Line
	15700 11650 15700 11950
Connection ~ 15700 10950
Wire Wire Line
	15700 11250 15700 10950
Wire Wire Line
	16250 10950 16400 10950
Wire Wire Line
	14550 10950 15750 10950
Connection ~ 16400 10850
Wire Wire Line
	14550 10850 16400 10850
Connection ~ 15400 11950
Wire Wire Line
	15400 11650 15400 11950
Connection ~ 15150 11950
Wire Wire Line
	15150 11650 15150 11950
Connection ~ 14950 11950
Wire Wire Line
	14550 11250 15150 11250
Wire Wire Line
	14950 12000 14950 11350
Wire Wire Line
	14950 11350 14550 11350
Connection ~ 16400 10450
Wire Wire Line
	16050 10450 16400 10450
Wire Wire Line
	16050 10750 16200 10750
Connection ~ 15500 10750
Wire Wire Line
	15500 10750 15500 10450
Wire Wire Line
	15500 10450 15550 10450
Wire Wire Line
	14550 10750 15550 10750
Connection ~ 13550 11200
Wire Wire Line
	11050 11200 13550 11200
Connection ~ 13550 10800
Wire Wire Line
	13250 10800 13550 10800
Connection ~ 13550 11250
Wire Wire Line
	13650 11250 13550 11250
Connection ~ 13550 11150
Wire Wire Line
	13650 11150 13550 11150
Connection ~ 13550 10850
Wire Wire Line
	13650 10850 13550 10850
Connection ~ 13550 10750
Wire Wire Line
	13650 10750 13550 10750
Wire Wire Line
	13650 11050 13550 11050
Wire Wire Line
	13550 11050 13550 11350
Wire Wire Line
	13550 11350 13650 11350
Wire Wire Line
	13650 10950 13550 10950
Wire Wire Line
	13550 10950 13550 10650
Wire Wire Line
	13550 10650 13650 10650
Wire Wire Line
	14550 10650 15100 10650
Wire Wire Line
	15100 10650 15100 10200
Wire Bus Line
	5100 4400 5100 7350
$Comp
L GND #PWR0114
U 1 1 51A3D0B8
P 8000 9050
F 0 "#PWR0114" H 8000 9050 30  0001 C CNN
F 1 "GND" H 8000 8980 30  0001 C CNN
F 2 "" H 8000 9050 60  0001 C CNN
F 3 "" H 8000 9050 60  0001 C CNN
	1    8000 9050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0115
U 1 1 51A3D0B7
P 8000 8650
F 0 "#PWR0115" H 8000 8750 30  0001 C CNN
F 1 "VCC" H 8000 8750 30  0000 C CNN
F 2 "" H 8000 8650 60  0001 C CNN
F 3 "" H 8000 8650 60  0001 C CNN
	1    8000 8650
	1    0    0    -1  
$EndComp
$Comp
L C C44
U 1 1 51A3D0B6
P 8000 8850
F 0 "C44" H 8050 8950 50  0000 L CNN
F 1 "0.1uF" H 8050 8750 50  0000 L CNN
F 2 "" H 8000 8850 60  0001 C CNN
F 3 "" H 8000 8850 60  0001 C CNN
	1    8000 8850
	1    0    0    -1  
$EndComp
$Comp
L C C43
U 1 1 51A3D0B5
P 7600 8850
F 0 "C43" H 7650 8950 50  0000 L CNN
F 1 "0.1uF" H 7650 8750 50  0000 L CNN
F 2 "" H 7600 8850 60  0001 C CNN
F 3 "" H 7600 8850 60  0001 C CNN
	1    7600 8850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0116
U 1 1 51A3D0B4
P 7600 8650
F 0 "#PWR0116" H 7600 8750 30  0001 C CNN
F 1 "VCC" H 7600 8750 30  0000 C CNN
F 2 "" H 7600 8650 60  0001 C CNN
F 3 "" H 7600 8650 60  0001 C CNN
	1    7600 8650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0117
U 1 1 51A3D0B3
P 7600 9050
F 0 "#PWR0117" H 7600 9050 30  0001 C CNN
F 1 "GND" H 7600 8980 30  0001 C CNN
F 2 "" H 7600 9050 60  0001 C CNN
F 3 "" H 7600 9050 60  0001 C CNN
	1    7600 9050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0118
U 1 1 51A3D0B1
P 4050 8950
F 0 "#PWR0118" H 4050 8950 30  0001 C CNN
F 1 "GND" H 4050 8880 30  0001 C CNN
F 2 "" H 4050 8950 60  0001 C CNN
F 3 "" H 4050 8950 60  0001 C CNN
	1    4050 8950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0119
U 1 1 51A3D0B0
P 4050 8550
F 0 "#PWR0119" H 4050 8650 30  0001 C CNN
F 1 "VCC" H 4050 8650 30  0000 C CNN
F 2 "" H 4050 8550 60  0001 C CNN
F 3 "" H 4050 8550 60  0001 C CNN
	1    4050 8550
	1    0    0    -1  
$EndComp
$Comp
L C C41
U 1 1 51A3D0AF
P 4050 8750
F 0 "C41" H 4100 8850 50  0000 L CNN
F 1 "0.1uF" H 4100 8650 50  0000 L CNN
F 2 "" H 4050 8750 60  0001 C CNN
F 3 "" H 4050 8750 60  0001 C CNN
	1    4050 8750
	1    0    0    -1  
$EndComp
$Comp
L C C42
U 1 1 51A3D0AE
P 4450 8750
F 0 "C42" H 4500 8850 50  0000 L CNN
F 1 "0.1uF" H 4500 8650 50  0000 L CNN
F 2 "" H 4450 8750 60  0001 C CNN
F 3 "" H 4450 8750 60  0001 C CNN
	1    4450 8750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0120
U 1 1 51A3D0AD
P 4450 8550
F 0 "#PWR0120" H 4450 8650 30  0001 C CNN
F 1 "VCC" H 4450 8650 30  0000 C CNN
F 2 "" H 4450 8550 60  0001 C CNN
F 3 "" H 4450 8550 60  0001 C CNN
	1    4450 8550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0121
U 1 1 51A3D0AC
P 4450 8950
F 0 "#PWR0121" H 4450 8950 30  0001 C CNN
F 1 "GND" H 4450 8880 30  0001 C CNN
F 2 "" H 4450 8950 60  0001 C CNN
F 3 "" H 4450 8950 60  0001 C CNN
	1    4450 8950
	1    0    0    -1  
$EndComp
Entry Wire Line
	5000 7450 5100 7350
Entry Wire Line
	5000 7350 5100 7250
Entry Wire Line
	5000 7250 5100 7150
Entry Wire Line
	7000 7700 6900 7800
Entry Wire Line
	7000 7800 6900 7900
Entry Wire Line
	7000 7900 6900 8000
Text Label 5000 7450 0    60   ~ 0
SPI_BUS1
Text Label 5000 7350 0    60   ~ 0
SPI_BUS2
Text Label 5000 7250 0    60   ~ 0
SPI_BUS0
Text Label 7000 7900 2    60   ~ 0
SPI_BUS2
Text Label 7000 7700 2    60   ~ 0
SPI_BUS0
Text Label 7000 7800 2    60   ~ 0
SPI_BUS1
$Comp
L GND #PWR0122
U 1 1 51A2B272
P 15050 7800
F 0 "#PWR0122" H 15050 7800 30  0001 C CNN
F 1 "GND" H 15050 7730 30  0001 C CNN
F 2 "" H 15050 7800 60  0001 C CNN
F 3 "" H 15050 7800 60  0001 C CNN
	1    15050 7800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0123
U 1 1 51A2B271
P 16500 6200
F 0 "#PWR0123" H 16500 6300 30  0001 C CNN
F 1 "VCC" H 16500 6300 30  0000 C CNN
F 2 "" H 16500 6200 60  0001 C CNN
F 3 "" H 16500 6200 60  0001 C CNN
	1    16500 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #GND0124
U 1 1 51A2B270
P 16300 6550
F 0 "#GND0124" H 16300 6550 30  0001 C CNN
F 1 "GND" H 16300 6480 30  0001 C CNN
F 2 "" H 16300 6550 60  0001 C CNN
F 3 "" H 16300 6550 60  0001 C CNN
	1    16300 6550
	0    -1   -1   0   
$EndComp
$Comp
L C C23
U 1 1 51A2B26D
P 15800 7250
F 0 "C23" H 15800 7350 40  0000 L CNN
F 1 "DNI" H 15806 7165 40  0000 L CNN
F 2 "~" H 15838 7100 30  0000 C CNN
F 3 "~" H 15800 7250 60  0000 C CNN
	1    15800 7250
	1    0    0    -1  
$EndComp
$Comp
L C C20
U 1 1 51A2B26C
P 15500 7250
F 0 "C20" H 15500 7350 40  0000 L CNN
F 1 "DNI" H 15506 7165 40  0000 L CNN
F 2 "~" H 15538 7100 30  0000 C CNN
F 3 "~" H 15500 7250 60  0000 C CNN
	1    15500 7250
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 51A2B26B
P 15250 7250
F 0 "C17" H 15250 7350 40  0000 L CNN
F 1 "1nF" H 15256 7165 40  0000 L CNN
F 2 "~" H 15288 7100 30  0000 C CNN
F 3 "~" H 15250 7250 60  0000 C CNN
	1    15250 7250
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 51A2B26A
P 16100 6750
F 0 "R13" V 16180 6750 40  0000 C CNN
F 1 "330" V 16107 6751 40  0000 C CNN
F 2 "~" V 16030 6750 30  0000 C CNN
F 3 "~" H 16100 6750 30  0000 C CNN
	1    16100 6750
	0    -1   -1   0   
$EndComp
$Comp
L R R10
U 1 1 51A2B269
P 15900 6550
F 0 "R10" V 15980 6550 40  0000 C CNN
F 1 "DNI" V 15907 6551 40  0000 C CNN
F 2 "~" V 15830 6550 30  0000 C CNN
F 3 "~" H 15900 6550 30  0000 C CNN
	1    15900 6550
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 51A2B268
P 15900 6250
F 0 "R9" V 15980 6250 40  0000 C CNN
F 1 "DNI" V 15907 6251 40  0000 C CNN
F 2 "~" V 15830 6250 30  0000 C CNN
F 3 "~" H 15900 6250 30  0000 C CNN
	1    15900 6250
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 51A2B265
P 5750 8250
F 0 "R1" V 5830 8250 40  0000 C CNN
F 1 "10K" V 5757 8251 40  0000 C CNN
F 2 "~" V 5680 8250 30  0000 C CNN
F 3 "~" H 5750 8250 30  0000 C CNN
	1    5750 8250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR0125
U 1 1 51A2B264
P 6250 8450
F 0 "#PWR0125" H 6250 8450 30  0001 C CNN
F 1 "GND" H 6250 8380 30  0001 C CNN
F 2 "" H 6250 8450 60  0001 C CNN
F 3 "" H 6250 8450 60  0001 C CNN
	1    6250 8450
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 51A2B263
P 5150 8250
F 0 "C5" H 5150 8350 40  0000 L CNN
F 1 "470 nF" H 5156 8165 40  0000 L CNN
F 2 "~" H 5188 8100 30  0000 C CNN
F 3 "~" H 5150 8250 60  0000 C CNN
	1    5150 8250
	0    1    1    0   
$EndComp
$Comp
L C C4
U 1 1 51A2B262
P 5150 8000
F 0 "C4" H 5150 8100 40  0000 L CNN
F 1 "10 nF" H 5156 7915 40  0000 L CNN
F 2 "~" H 5188 7850 30  0000 C CNN
F 3 "~" H 5150 8000 60  0000 C CNN
	1    5150 8000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR0126
U 1 1 51A2B260
P 3450 8400
F 0 "#PWR0126" H 3450 8400 30  0001 C CNN
F 1 "GND" H 3450 8330 30  0001 C CNN
F 2 "" H 3450 8400 60  0001 C CNN
F 3 "" H 3450 8400 60  0001 C CNN
	1    3450 8400
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0127
U 1 1 51A2B25F
P 3300 6900
F 0 "#PWR0127" H 3300 7000 30  0001 C CNN
F 1 "VCC" H 3300 7000 30  0000 C CNN
F 2 "" H 3300 6900 60  0001 C CNN
F 3 "" H 3300 6900 60  0001 C CNN
	1    3300 6900
	1    0    0    -1  
$EndComp
$Comp
L A3G4250D GYROSCOPE1
U 1 1 51A2B25E
P 4150 7650
F 0 "GYROSCOPE1" H 3900 8200 50  0000 C CNN
F 1 "A3G4250D" H 3850 6950 50  0000 C CNN
F 2 "~" H -6200 8400 60  0000 C CNN
F 3 "~" H -6200 8400 60  0000 C CNN
	1    4150 7650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0128
U 1 1 51A2B25C
P 8700 8500
F 0 "#PWR0128" H 8700 8500 30  0001 C CNN
F 1 "GND" H 8700 8430 30  0001 C CNN
F 2 "" H 8700 8500 60  0001 C CNN
F 3 "" H 8700 8500 60  0001 C CNN
	1    8700 8500
	-1   0    0    -1  
$EndComp
$Comp
L VCC #PWR0129
U 1 1 51A2B25B
P 9050 7000
F 0 "#PWR0129" H 9050 7100 30  0001 C CNN
F 1 "VCC" H 9050 7100 30  0000 C CNN
F 2 "" H 9050 7000 60  0001 C CNN
F 3 "" H 9050 7000 60  0001 C CNN
	1    9050 7000
	-1   0    0    -1  
$EndComp
$Comp
L AIS328DQ ACCELEROMETER1
U 1 1 51A2B25A
P 7850 7650
F 0 "ACCELEROMETER1" H 7700 8250 50  0000 C CNN
F 1 "AIS328DQ" H 7550 6950 50  0000 C CNN
F 2 "~" H -2500 8400 60  0000 C CNN
F 3 "~" H -2500 8400 60  0000 C CNN
	1    7850 7650
	-1   0    0    -1  
$EndComp
Text Label 6000 4300 2    60   ~ 0
SPI_BUS2
Text Label 6000 4200 2    60   ~ 0
SPI_BUS1
Text Label 6000 4100 2    60   ~ 0
SPI_BUS0
$Comp
L GND #PWR0130
U 1 1 51A2D3BE
P 7650 4000
F 0 "#PWR0130" H 7650 4000 30  0001 C CNN
F 1 "GND" H 7650 3930 30  0001 C CNN
F 2 "" H 7650 4000 60  0001 C CNN
F 3 "" H 7650 4000 60  0001 C CNN
	1    7650 4000
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR0131
U 1 1 51A2D3C4
P 7800 3700
F 0 "#PWR0131" H 7800 3790 20  0001 C CNN
F 1 "+5V" H 7800 3790 30  0000 C CNN
F 2 "" H 7800 3700 60  0001 C CNN
F 3 "" H 7800 3700 60  0001 C CNN
	1    7800 3700
	1    0    0    -1  
$EndComp
$Comp
L MOT_ENC JP6
U 1 1 51A2D3CA
P 8250 4050
F 0 "JP6" H 8250 4350 60  0000 C CNN
F 1 "MOT_ENC" H 8350 3650 60  0000 C CNN
F 2 "" H 8250 4050 60  0001 C CNN
F 3 "" H 8250 4050 60  0001 C CNN
	1    8250 4050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0132
U 1 1 51A2D3D0
P 7500 3700
F 0 "#PWR0132" H 7500 3800 30  0001 C CNN
F 1 "VCC" H 7500 3800 30  0000 C CNN
F 2 "" H 7500 3700 60  0001 C CNN
F 3 "" H 7500 3700 60  0001 C CNN
	1    7500 3700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR0133
U 1 1 51A2D3D6
P 6000 3900
F 0 "#PWR0133" H 6000 3900 30  0001 C CNN
F 1 "GND" H 6000 3830 30  0001 C CNN
F 2 "" H 6000 3900 60  0001 C CNN
F 3 "" H 6000 3900 60  0001 C CNN
	1    6000 3900
	0    1    1    0   
$EndComp
$Comp
L GND #PWR0134
U 1 1 51A2D3DC
P 3800 4250
F 0 "#PWR0134" H 3800 4250 30  0001 C CNN
F 1 "GND" H 3800 4180 30  0001 C CNN
F 2 "" H 3800 4250 60  0001 C CNN
F 3 "" H 3800 4250 60  0001 C CNN
	1    3800 4250
	1    0    0    -1  
$EndComp
$Comp
L C C32
U 1 1 51A2D3E2
P 4000 4050
F 0 "C32" H 4000 4150 40  0000 L CNN
F 1 "0.1uF" H 4006 3965 40  0000 L CNN
F 2 "~" H 4038 3900 30  0000 C CNN
F 3 "~" H 4000 4050 60  0000 C CNN
	1    4000 4050
	0    -1   -1   0   
$EndComp
$Comp
L C C31
U 1 1 51A2D3E8
P 4000 3550
F 0 "C31" H 4000 3650 40  0000 L CNN
F 1 "0.1uF" H 4006 3465 40  0000 L CNN
F 2 "~" H 4038 3400 30  0000 C CNN
F 3 "~" H 4000 3550 60  0000 C CNN
	1    4000 3550
	0    -1   -1   0   
$EndComp
$Comp
L R R14
U 1 1 51A2D3EE
P 4400 3800
F 0 "R14" V 4480 3800 40  0000 C CNN
F 1 "1M" V 4407 3801 40  0000 C CNN
F 2 "~" V 4330 3800 30  0000 C CNN
F 3 "~" H 4400 3800 30  0000 C CNN
	1    4400 3800
	1    0    0    -1  
$EndComp
$Comp
L QUARTZCMS4 X3
U 1 1 51A2D3F4
P 5000 3850
F 0 "X3" H 5000 4000 60  0000 C CNN
F 1 "20 MHz" H 5000 3700 60  0000 C CNN
F 2 "~" H 5000 3850 60  0000 C CNN
F 3 "~" H 5000 3850 60  0000 C CNN
	1    5000 3850
	0    -1   -1   0   
$EndComp
$Comp
L C C33
U 1 1 51A2D3FA
P 6600 3150
F 0 "C33" H 6600 3250 40  0000 L CNN
F 1 "0.1uF" H 6606 3065 40  0000 L CNN
F 2 "~" H 6638 3000 30  0000 C CNN
F 3 "~" H 6600 3150 60  0000 C CNN
	1    6600 3150
	-1   0    0    1   
$EndComp
$Comp
L LS7366RDIP MOTOR1
U 1 1 51A2D400
P 6550 4050
F 0 "MOTOR1" H 6700 4550 50  0000 C CNN
F 1 "LS7366RDIP" H 6550 3650 50  0000 C CNN
F 2 "" H 6550 4050 60  0001 C CNN
F 3 "" H 6550 4050 60  0001 C CNN
	1    6550 4050
	1    0    0    -1  
$EndComp
Entry Wire Line
	5900 4400 6000 4300
Entry Wire Line
	5900 4300 6000 4200
Entry Wire Line
	5900 4200 6000 4100
$Comp
L GND #PWR0135
U 1 1 51A2ED72
P 15000 10000
F 0 "#PWR0135" H 15000 10000 30  0001 C CNN
F 1 "GND" H 15000 9930 30  0001 C CNN
F 2 "" H 15000 10000 60  0001 C CNN
F 3 "" H 15000 10000 60  0001 C CNN
	1    15000 10000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0136
U 1 1 51A2ED78
P 16450 8400
F 0 "#PWR0136" H 16450 8500 30  0001 C CNN
F 1 "VCC" H 16450 8500 30  0000 C CNN
F 2 "" H 16450 8400 60  0001 C CNN
F 3 "" H 16450 8400 60  0001 C CNN
	1    16450 8400
	1    0    0    -1  
$EndComp
$Comp
L GND #GND0137
U 1 1 51A2ED7E
P 16250 8750
F 0 "#GND0137" H 16250 8750 30  0001 C CNN
F 1 "GND" H 16250 8680 30  0001 C CNN
F 2 "" H 16250 8750 60  0001 C CNN
F 3 "" H 16250 8750 60  0001 C CNN
	1    16250 8750
	0    -1   -1   0   
$EndComp
$Comp
L C C22
U 1 1 51A2ED90
P 15750 9450
F 0 "C22" H 15750 9550 40  0000 L CNN
F 1 "DNI" H 15756 9365 40  0000 L CNN
F 2 "~" H 15788 9300 30  0000 C CNN
F 3 "~" H 15750 9450 60  0000 C CNN
	1    15750 9450
	1    0    0    -1  
$EndComp
$Comp
L C C19
U 1 1 51A2ED96
P 15450 9450
F 0 "C19" H 15450 9550 40  0000 L CNN
F 1 "DNI" H 15456 9365 40  0000 L CNN
F 2 "~" H 15488 9300 30  0000 C CNN
F 3 "~" H 15450 9450 60  0000 C CNN
	1    15450 9450
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 51A2ED9C
P 15200 9450
F 0 "C16" H 15200 9550 40  0000 L CNN
F 1 "1nF" H 15206 9365 40  0000 L CNN
F 2 "~" H 15238 9300 30  0000 C CNN
F 3 "~" H 15200 9450 60  0000 C CNN
	1    15200 9450
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 51A2EDA2
P 16050 8950
F 0 "R12" V 16130 8950 40  0000 C CNN
F 1 "330" V 16057 8951 40  0000 C CNN
F 2 "~" V 15980 8950 30  0000 C CNN
F 3 "~" H 16050 8950 30  0000 C CNN
	1    16050 8950
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 51A2EDA8
P 15850 8750
F 0 "R8" V 15930 8750 40  0000 C CNN
F 1 "DNI" V 15857 8751 40  0000 C CNN
F 2 "~" V 15780 8750 30  0000 C CNN
F 3 "~" H 15850 8750 30  0000 C CNN
	1    15850 8750
	0    -1   -1   0   
$EndComp
$Comp
L R R7
U 1 1 51A2EDAE
P 15850 8450
F 0 "R7" V 15930 8450 40  0000 C CNN
F 1 "DNI" V 15857 8451 40  0000 C CNN
F 2 "~" V 15780 8450 30  0000 C CNN
F 3 "~" H 15850 8450 30  0000 C CNN
	1    15850 8450
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR0138
U 1 1 51A2EDFD
P 14950 12000
F 0 "#PWR0138" H 14950 12000 30  0001 C CNN
F 1 "GND" H 14950 11930 30  0001 C CNN
F 2 "" H 14950 12000 60  0001 C CNN
F 3 "" H 14950 12000 60  0001 C CNN
	1    14950 12000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0139
U 1 1 51A2EE03
P 16400 10400
F 0 "#PWR0139" H 16400 10500 30  0001 C CNN
F 1 "VCC" H 16400 10500 30  0000 C CNN
F 2 "" H 16400 10400 60  0001 C CNN
F 3 "" H 16400 10400 60  0001 C CNN
	1    16400 10400
	1    0    0    -1  
$EndComp
$Comp
L GND #GND0140
U 1 1 51A2EE09
P 16200 10750
F 0 "#GND0140" H 16200 10750 30  0001 C CNN
F 1 "GND" H 16200 10680 30  0001 C CNN
F 2 "" H 16200 10750 60  0001 C CNN
F 3 "" H 16200 10750 60  0001 C CNN
	1    16200 10750
	0    -1   -1   0   
$EndComp
$Comp
L C C21
U 1 1 51A2EE1B
P 15700 11450
F 0 "C21" H 15700 11550 40  0000 L CNN
F 1 "DNI" H 15706 11365 40  0000 L CNN
F 2 "~" H 15738 11300 30  0000 C CNN
F 3 "~" H 15700 11450 60  0000 C CNN
	1    15700 11450
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 51A2EE21
P 15400 11450
F 0 "C18" H 15400 11550 40  0000 L CNN
F 1 "DNI" H 15406 11365 40  0000 L CNN
F 2 "~" H 15438 11300 30  0000 C CNN
F 3 "~" H 15400 11450 60  0000 C CNN
	1    15400 11450
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 51A2EE27
P 15150 11450
F 0 "C15" H 15150 11550 40  0000 L CNN
F 1 "1nF" H 15156 11365 40  0000 L CNN
F 2 "~" H 15188 11300 30  0000 C CNN
F 3 "~" H 15150 11450 60  0000 C CNN
	1    15150 11450
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 51A2EE2D
P 16000 10950
F 0 "R11" V 16080 10950 40  0000 C CNN
F 1 "330" V 16007 10951 40  0000 C CNN
F 2 "~" V 15930 10950 30  0000 C CNN
F 3 "~" H 16000 10950 30  0000 C CNN
	1    16000 10950
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 51A2EE33
P 15800 10750
F 0 "R6" V 15880 10750 40  0000 C CNN
F 1 "DNI" V 15807 10751 40  0000 C CNN
F 2 "~" V 15730 10750 30  0000 C CNN
F 3 "~" H 15800 10750 30  0000 C CNN
	1    15800 10750
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 51A2EE39
P 15800 10450
F 0 "R5" V 15880 10450 40  0000 C CNN
F 1 "DNI" V 15807 10451 40  0000 C CNN
F 2 "~" V 15730 10450 30  0000 C CNN
F 3 "~" H 15800 10450 30  0000 C CNN
	1    15800 10450
	0    -1   -1   0   
$EndComp
Wire Bus Line
	18100 6950 18100 11250
Wire Bus Line
	18100 11250 20100 11250
Entry Wire Line
	18000 6850 18100 6950
Entry Wire Line
	18000 9050 18100 9150
Entry Wire Line
	18000 11050 18100 11150
Text Label 17650 6850 0    60   ~ 0
ANC2
Text Label 17600 9050 0    60   ~ 0
ANC1
Text Label 17600 11050 0    60   ~ 0
ANC0
Entry Wire Line
	13150 6500 13250 6600
Entry Wire Line
	13150 8700 13250 8800
Entry Wire Line
	13150 10700 13250 10800
Wire Bus Line
	13150 6500 13150 10700
Text Label 13550 10800 2    60   ~ 0
MotorOut0
Text Label 13550 8800 2    60   ~ 0
MotorOut1
Text Label 13600 6600 2    60   ~ 0
MotorOut2
Wire Bus Line
	13150 10700 12250 10700
$Comp
L CONN_3 K1
U 1 1 51A913C9
P 10950 12750
F 0 "K1" V 10900 12750 50  0000 C CNN
F 1 "CONN_3" V 11000 12750 40  0000 C CNN
F 2 "" H 10950 12750 60  0000 C CNN
F 3 "" H 10950 12750 60  0000 C CNN
	1    10950 12750
	0    1    1    0   
$EndComp
Wire Wire Line
	11050 11200 11050 12400
Wire Wire Line
	10950 9200 10950 12400
Wire Wire Line
	10850 7000 10850 12400
Text Notes 10300 13000 0    60   ~ 0
3 Phase Motor Connector
Wire Wire Line
	15150 8200 18450 8200
$Comp
L CONN_3 K2
U 1 1 51A91CC8
P 18800 8200
F 0 "K2" V 18750 8200 50  0000 C CNN
F 1 "CONN_3" V 18850 8200 40  0000 C CNN
F 2 "" H 18800 8200 60  0000 C CNN
F 3 "" H 18800 8200 60  0000 C CNN
	1    18800 8200
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR0141
U 1 1 51A91CD7
P 18450 8100
F 0 "#PWR0141" H 18450 8200 30  0001 C CNN
F 1 "VCC" H 18450 8200 30  0000 C CNN
F 2 "" H 18450 8100 60  0000 C CNN
F 3 "" H 18450 8100 60  0000 C CNN
	1    18450 8100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0142
U 1 1 51A91CE6
P 18450 8300
F 0 "#PWR0142" H 18450 8300 30  0001 C CNN
F 1 "GND" H 18450 8230 30  0001 C CNN
F 2 "" H 18450 8300 60  0000 C CNN
F 3 "" H 18450 8300 60  0000 C CNN
	1    18450 8300
	1    0    0    -1  
$EndComp
Wire Wire Line
	15100 10200 18250 10200
Wire Wire Line
	18250 10200 18250 6000
Connection ~ 18250 8200
Wire Wire Line
	18250 6000 15200 6000
Text Notes 19050 8200 0    59   ~ 0
Jumper to set all chips to have FAULT_EN protection
$Comp
L VCC #PWR0143
U 1 1 51A91F5E
P 6600 2950
F 0 "#PWR0143" H 6600 3050 30  0001 C CNN
F 1 "VCC" H 6600 3050 30  0000 C CNN
F 2 "" H 6600 2950 60  0000 C CNN
F 3 "" H 6600 2950 60  0000 C CNN
	1    6600 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR0144
U 1 1 51A91F6D
P 6600 3350
F 0 "#PWR0144" H 6600 3350 30  0001 C CNN
F 1 "GND" H 6600 3280 30  0001 C CNN
F 2 "" H 6600 3350 60  0000 C CNN
F 3 "" H 6600 3350 60  0000 C CNN
	1    6600 3350
	1    0    0    -1  
$EndComp
Wire Bus Line
	5100 4400 5900 4400
Wire Bus Line
	5900 4400 5900 4200
Wire Bus Line
	3950 5450 5100 5450
Wire Bus Line
	5100 7350 6900 7350
Wire Wire Line
	7200 7350 7200 6950
Wire Wire Line
	7100 7450 7200 7450
Wire Wire Line
	7100 6950 7100 7450
Wire Wire Line
	7200 7600 7000 7600
Wire Wire Line
	7000 7600 7000 6950
Entry Wire Line
	5250 7600 5350 7700
Entry Wire Line
	5250 7700 5350 7800
Entry Wire Line
	5250 7800 5350 7900
Wire Bus Line
	5350 7900 5350 7550
Wire Bus Line
	5350 7550 5600 7550
Wire Bus Line
	5600 7550 5600 6300
Wire Bus Line
	5600 6300 8050 6300
Entry Wire Line
	6900 6850 7000 6950
Entry Wire Line
	7000 6850 7100 6950
Entry Wire Line
	7100 6850 7200 6950
Wire Bus Line
	6900 6850 8050 6850
Text Label 4900 7600 0    59   ~ 0
GYRO0
Text Label 4900 7700 0    59   ~ 0
GYRO1
Text Label 4900 7800 0    59   ~ 0
GYRO2
Text Label 7000 7150 1    59   ~ 0
ACCEL0
Text Label 7200 7150 1    59   ~ 0
ACCEL2
Text Label 7100 7150 1    59   ~ 0
ACCEL1
Wire Bus Line
	3950 4800 7400 4800
Entry Wire Line
	7300 4700 7400 4800
Entry Wire Line
	7200 4700 7300 4800
Entry Wire Line
	5450 4700 5550 4800
Wire Wire Line
	5450 4000 5450 4700
Text Label 5550 4000 0    59   ~ 0
ENC0
Wire Wire Line
	7200 4300 7200 4700
Wire Wire Line
	7300 4200 7300 4700
Text Label 7150 4300 0    59   ~ 0
ENC1
Text Label 7150 4200 0    59   ~ 0
ENC2
Wire Notes Line
	11350 4600 11350 12400
Wire Notes Line
	11350 4600 21600 4600
Wire Notes Line
	21600 4600 21600 12400
Wire Notes Line
	21600 12400 11350 12400
Text Notes 15750 4400 0    118  ~ 0
Motor Current Sensing
Wire Notes Line
	2450 9450 9700 9450
Wire Notes Line
	9700 9450 9700 2650
Wire Notes Line
	9700 2650 2450 2650
Text Notes 5050 2400 0    118  ~ 0
Accelerometer, Gyro, Opposite Link QEI
Text Label 6500 6300 0    60   ~ 0
GYRO[0..2]
Text Label 7400 6850 0    60   ~ 0
ACCEL[0..2]
Text Label 4450 5450 0    60   ~ 0
SPI_BUS[0..2]
Text Label 4550 4800 0    60   ~ 0
ENC[0..2]
Text Label 13150 10400 1    60   ~ 0
MotorOut[0:2]
Text HLabel 3950 4800 0    61   Input ~ 0
ENC[0..2]
Text HLabel 3950 5450 0    61   Input ~ 0
SPI_BUS[0..2]
Text HLabel 8050 6300 2    61   Input ~ 0
GYRO[0..2]
Text HLabel 8050 6850 2    61   Input ~ 0
ACCEL[0..2]
Text HLabel 12250 10700 0    61   Input ~ 0
MotorOut[0..2]
Text HLabel 20100 11250 2    61   Output ~ 0
ANC[0..2]
Text Label 18950 11250 0    61   ~ 0
ANC[0..2]
Text Notes 5700 7000 0    61   ~ 0
SPI_BUS0 - CLK\nSPI_BUS1 - DIN\nSPI_BUS2 - DOUT
$Comp
L ACS716 U9
U 1 1 51AE5442
P 14100 6800
F 0 "U9" H 14250 7300 50  0000 C CNN
F 1 "ACS716" H 14100 6300 50  0000 C CNN
F 2 "~" H 14100 6800 60  0000 C CNN
F 3 "~" H 14100 6800 60  0000 C CNN
	1    14100 6800
	1    0    0    -1  
$EndComp
$Comp
L ACS716 U8
U 1 1 51AE544F
P 14050 9000
F 0 "U8" H 14200 9500 50  0000 C CNN
F 1 "ACS716" H 14050 8500 50  0000 C CNN
F 2 "~" H 14050 9000 60  0000 C CNN
F 3 "~" H 14050 9000 60  0000 C CNN
	1    14050 9000
	1    0    0    -1  
$EndComp
$Comp
L ACS716 U7
U 1 1 51AE5455
P 14000 11000
F 0 "U7" H 14150 11500 50  0000 C CNN
F 1 "ACS716" H 14000 10500 50  0000 C CNN
F 2 "~" H 14000 11000 60  0000 C CNN
F 3 "~" H 14000 11000 60  0000 C CNN
	1    14000 11000
	1    0    0    -1  
$EndComp
Wire Wire Line
	15750 9950 15000 9950
Wire Wire Line
	16450 8950 16450 8400
Wire Wire Line
	15700 11950 14950 11950
Wire Wire Line
	16400 10950 16400 10400
Wire Wire Line
	15800 7750 15050 7750
Wire Wire Line
	16500 6750 16500 6200
Wire Notes Line
	2450 2650 2450 9450
$EndSCHEMATC
