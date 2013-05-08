EESchema Schematic File Version 2  date 5/7/2013 3:13:48 PM
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
Sheet 1 9
Title ""
Date "7 may 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 1800 850  0    60   ~ 0
lower battery manager
Wire Wire Line
	4950 2550 7550 2550
Wire Wire Line
	4950 2450 7550 2450
Wire Wire Line
	7550 1250 6200 1250
Wire Wire Line
	6000 1150 6000 1250
Wire Wire Line
	6000 1250 4950 1250
Wire Wire Line
	6200 1250 6200 1150
Wire Wire Line
	7550 1700 4950 1700
Wire Wire Line
	7550 1800 4950 1800
Wire Wire Line
	7550 1900 4950 1900
Wire Wire Line
	7550 2000 4950 2000
Wire Wire Line
	7550 2100 4950 2100
Wire Wire Line
	7550 2200 4950 2200
$Sheet
S 2550 1100 2400 2750
U 51709CAD
F0 "battery_manager" 60
F1 "battery_manager.sch" 60
F2 "BAT_TOP" O R 4950 1250 60 
F3 "IRQ_IN" I R 4950 1700 60 
F4 "CLK_OUT" O R 4950 1800 60 
F5 "CS_N_OUT" O R 4950 1900 60 
F6 "SCK_OUT" O R 4950 2000 60 
F7 "MOSI_OUT" O R 4950 2100 60 
F8 "MISO_IN" I R 4950 2200 60 
F9 "PD_N" I R 4950 2450 60 
F10 "VDDHVP" I R 4950 2550 60 
$EndSheet
$Sheet
S 7550 1150 2150 2500
U 51781C83
F0 "batt_man_2" 60
F1 "batt_man_2.sch" 60
F2 "IRQ" O L 7550 1700 60 
F3 "CLK" I L 7550 1800 60 
F4 "CS_N" I L 7550 1900 60 
F5 "SCK" I L 7550 2000 60 
F6 "MOSI" I L 7550 2100 60 
F7 "MISO" O L 7550 2200 60 
F8 "BAT_BOT" O L 7550 1250 60 
F9 "PD_N_OUT" O L 7550 2450 60 
F10 "VDDHVM" O L 7550 2550 60 
$EndSheet
Text Notes 5350 650  0    60   ~ 0
Jumper for serializing the battery packs
$Comp
L CONN_2 P1
U 1 1 51781833
P 6100 800
F 0 "P1" V 6050 800 40  0000 C CNN
F 1 "CONN_2" V 6150 800 40  0000 C CNN
	1    6100 800 
	0    -1   -1   0   
$EndComp
$Sheet
S 4500 4700 2900 1900
U 5169884D
F0 "battery_charger" 60
F1 "battery_charger.sch" 60
$EndSheet
$EndSCHEMATC
