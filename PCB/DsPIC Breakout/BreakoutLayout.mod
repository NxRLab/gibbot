PCBNEW-LibModule-V1  7/9/2013 11:27:05 AM
# encoding utf-8
Units mm
$INDEX
8MHZ_CER_RES
JST-1mm-2pin
MY_TQFP_64
PIN_ARRAY_16x1
SM0603
TQFP_64
$EndINDEX
$MODULE 8MHZ_CER_RES
Po 0 0 0 15 51AE5051 00000000 ~~
Li 8MHZ_CER_RES
Sc 0
AR /51AD2563
Op 0 0 0
T0 -2.54 -2.54 1.524 1.524 0 0.3048 N V 21 N "CR1"
T1 0 -2.60096 1.524 1.524 0 0.3048 N I 21 N "CERAMIC_RES"
DS 0 0.65024 -1.6002 0.65024 0.381 21
DS -1.6002 0.65024 -1.6002 -0.65024 0.381 21
DS -1.6002 -0.65024 1.6002 -0.65024 0.381 21
DS 1.6002 -0.65024 1.6002 0.65024 0.381 21
DS 1.6002 0.65024 0 0.65024 0.381 21
$PAD
Sh "1" R 0.39878 1.99898 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 3 "N-0000018"
Po -1.00076 0
$EndPAD
$PAD
Sh "2" R 0.39878 1.99898 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 1 "GND"
Po 0 0
$EndPAD
$PAD
Sh "3" R 0.39878 1.99898 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 2 "N-0000013"
Po 1.00076 0
$EndPAD
$EndMODULE 8MHZ_CER_RES
$MODULE JST-1mm-2pin
Po 0 0 0 15 51AE18FE 00000000 ~~
Li JST-1mm-2pin
Sc 0
AR /51AC32A2
Op 0 0 0
.LocalClearance 0.1
T0 0 -1.25 1 1 0 0.15 N V 21 N "P10"
T1 0 -4 1 1 0 0.15 N I 21 N "CONN_2"
DC -1.2 -1.9 -1.2 -2 0.15 21
DS 0.9 -1.4 1.9 -1.4 0.15 21
DS 1.9 -1.4 1.9 2.9 0.15 21
DS 1.9 2.9 -1.4 2.9 0.15 21
DS -1.4 2.9 -1.9 2.9 0.15 21
DS -1.9 2.9 -1.9 -1.4 0.15 21
DS -1.9 -1.4 -0.9 -1.4 0.15 21
$PAD
Sh "1" R 0.6 1.35 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 1 "GND"
Po -0.5 -1.9
$EndPAD
$PAD
Sh "2" R 0.6 1.35 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 2 "N-000005"
Po 0.5 -1.9
$EndPAD
$PAD
Sh "" R 1.2 2 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 1.2 1.8
$EndPAD
$PAD
Sh "" R 1.2 2 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -1.2 1.8
$EndPAD
$EndMODULE JST-1mm-2pin
$MODULE MY_TQFP_64
Po 0 0 0 15 51AE9163 00000000 ~~
Li MY_TQFP_64
Kw TQFP64 TQFP SMD IC
Sc 0
AR /51A29A62
Op 0 0 0
.LocalClearance 0.1
T0 6.731 7.62 1.09982 1.09982 0 0.127 N V 21 N "U1"
T1 9.779 -9.017 1.00076 1.00076 0 0.1524 N V 21 N "DSPIC33EP512MC806"
DC -5.1 6.5 -5 6.5 0.15 21
DS -5.7 4.2 -5.7 4 0.15 21
DS -4.2 5.7 -4 5.7 0.15 21
DS 4.1 5.7 4 5.7 0.15 21
DS 5.7 4.1 5.7 4 0.15 21
DS 5.7 -4.2 5.7 -4 0.15 21
DS 4.2 -5.7 4 -5.7 0.15 21
DS -4.2 -5.7 -4 -5.7 0.15 21
DS -5.7 -4.2 -5.7 -4 0.15 21
DS -5.7 4.2 -5.7 5.7 0.15 21
DS -5.7 5.7 -4.2 5.7 0.15 21
DS -4.2 -5.7 -5.7 -5.7 0.15 21
DS -5.7 -5.7 -5.7 -4.2 0.15 21
DS 5.7 -4.2 5.7 -5.7 0.15 21
DS 5.7 -5.7 4.2 -5.7 0.15 21
DS 4.1 5.7 5.7 5.7 0.15 21
DS 5.7 5.7 5.7 4.1 0.15 21
$PAD
Sh "1" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 32 "/MotorControl5"
Po -3.75 5.7
$EndPAD
$PAD
Sh "2" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 25 "/MagnetControl0"
Po -3.25 5.7
$EndPAD
$PAD
Sh "3" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 26 "/MagnetControl1"
Po -2.75 5.7
$EndPAD
$PAD
Sh "4" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 35 "/SPI_BUS0"
Po -2.25 5.7
$EndPAD
$PAD
Sh "5" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 36 "/SPI_BUS1"
Po -1.75 5.7
$EndPAD
$PAD
Sh "6" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 37 "/SPI_BUS2"
Po -1.25 5.7
$EndPAD
$PAD
Sh "7" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 48 "N-0000081"
Po -0.75 5.7
$EndPAD
$PAD
Sh "8" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 20 "/LED1"
Po -0.25 5.7
$EndPAD
$PAD
Sh "9" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 39 "GND"
Po 0.25 5.7
$EndPAD
$PAD
Sh "10" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 51 "VCC"
Po 0.75 5.7
$EndPAD
$PAD
Sh "11" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 4 "/ANC0"
Po 1.25 5.7
$EndPAD
$PAD
Sh "12" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 5 "/ANC1"
Po 1.75 5.7
$EndPAD
$PAD
Sh "13" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 6 "/ANC2"
Po 2.25 5.7
$EndPAD
$PAD
Sh "14" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 0 ""
Po 2.75 5.7
$EndPAD
$PAD
Sh "15" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 0 ""
Po 3.25 5.7
$EndPAD
$PAD
Sh "16" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 0 ""
Po 3.75 5.7
$EndPAD
$PAD
Sh "17" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 45 "N-0000037"
Po 5.7 3.75
$EndPAD
$PAD
Sh "18" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 46 "N-0000060"
Po 5.7 3.25
$EndPAD
$PAD
Sh "19" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 49 "N-0000096"
Po 5.7 2.75
$EndPAD
$PAD
Sh "20" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 39 "GND"
Po 5.7 2.25
$EndPAD
$PAD
Sh "21" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 0 ""
Po 5.7 1.75
$EndPAD
$PAD
Sh "22" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 0 ""
Po 5.7 1.25
$EndPAD
$PAD
Sh "23" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 0 ""
Po 5.7 0.75
$EndPAD
$PAD
Sh "24" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 43 "N-0000014"
Po 5.7 0.25
$EndPAD
$PAD
Sh "25" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 39 "GND"
Po 5.7 -0.25
$EndPAD
$PAD
Sh "26" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 51 "VCC"
Po 5.7 -0.75
$EndPAD
$PAD
Sh "27" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 21 "/LED2"
Po 5.7 -1.25
$EndPAD
$PAD
Sh "28" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 22 "/LED3"
Po 5.7 -1.75
$EndPAD
$PAD
Sh "29" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 23 "/LED4"
Po 5.7 -2.25
$EndPAD
$PAD
Sh "30" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 24 "/LED5"
Po 5.7 -2.75
$EndPAD
$PAD
Sh "31" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 47 "N-000007"
Po 5.7 -3.25
$EndPAD
$PAD
Sh "32" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 41 "N-0000012"
Po 5.7 -3.75
$EndPAD
$PAD
Sh "33" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 40 "N-0000010"
Po 3.75 -5.7
$EndPAD
$PAD
Sh "34" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 8 "/ENC0"
Po 3.25 -5.7
$EndPAD
$PAD
Sh "35" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 33 "/RTS"
Po 2.75 -5.7
$EndPAD
$PAD
Sh "36" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 9 "/ENC1"
Po 2.25 -5.7
$EndPAD
$PAD
Sh "37" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 10 "/ENC2"
Po 1.75 -5.7
$EndPAD
$PAD
Sh "38" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 51 "VCC"
Po 1.25 -5.7
$EndPAD
$PAD
Sh "39" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 44 "N-0000018"
Po 0.75 -5.7
$EndPAD
$PAD
Sh "40" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 42 "N-0000013"
Po 0.25 -5.7
$EndPAD
$PAD
Sh "41" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 39 "GND"
Po -0.25 -5.7
$EndPAD
$PAD
Sh "42" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 17 "/GYRO0"
Po -0.75 -5.7
$EndPAD
$PAD
Sh "43" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 18 "/GYRO1"
Po -1.25 -5.7
$EndPAD
$PAD
Sh "44" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 19 "/GYRO2"
Po -1.75 -5.7
$EndPAD
$PAD
Sh "45" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 1 "/ACCEL0"
Po -2.25 -5.7
$EndPAD
$PAD
Sh "46" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 7 "/CTS"
Po -2.75 -5.7
$EndPAD
$PAD
Sh "47" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 2 "/ACCEL1"
Po -3.25 -5.7
$EndPAD
$PAD
Sh "48" R 0.3 1.5 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 3 "/ACCEL2"
Po -3.75 -5.7
$EndPAD
$PAD
Sh "49" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 0 ""
Po -5.7 -3.75
$EndPAD
$PAD
Sh "50" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 11 "/ENCODER1"
Po -5.7 -3.25
$EndPAD
$PAD
Sh "51" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 12 "/ENCODER2"
Po -5.7 -2.75
$EndPAD
$PAD
Sh "52" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 13 "/ENCODER3"
Po -5.7 -2.25
$EndPAD
$PAD
Sh "53" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 14 "/ENCODER4"
Po -5.7 -1.75
$EndPAD
$PAD
Sh "54" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 38 "/TX"
Po -5.7 -1.25
$EndPAD
$PAD
Sh "55" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 34 "/RX"
Po -5.7 -0.75
$EndPAD
$PAD
Sh "56" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 50 "N-0000097"
Po -5.7 -0.25
$EndPAD
$PAD
Sh "57" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 51 "VCC"
Po -5.7 0.25
$EndPAD
$PAD
Sh "58" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 15 "/ENCODER5"
Po -5.7 0.75
$EndPAD
$PAD
Sh "59" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 16 "/ENCODER6"
Po -5.7 1.25
$EndPAD
$PAD
Sh "60" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 27 "/MotorControl0"
Po -5.7 1.75
$EndPAD
$PAD
Sh "61" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 28 "/MotorControl1"
Po -5.7 2.25
$EndPAD
$PAD
Sh "62" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 29 "/MotorControl2"
Po -5.7 2.75
$EndPAD
$PAD
Sh "63" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 30 "/MotorControl3"
Po -5.7 3.25
$EndPAD
$PAD
Sh "64" R 0.3 1.5 0 0 900
Dr 0 0 0
At SMD N 00808000
Ne 31 "/MotorControl4"
Po -5.7 3.75
$EndPAD
$SHAPE3D
Na "smd/TQFP_64.wrl"
Sc 0.3937 0.3937 0.3937
Of 0 0 0.001
Ro 0 0 0
$EndSHAPE3D
$EndMODULE MY_TQFP_64
$MODULE PIN_ARRAY_16x1
Po 0 0 0 15 51DC39C2 00000000 ~~
Li PIN_ARRAY_16x1
Cd Double rangee de contacts 2 x 12 pins
Kw CONN
Sc 0
AR /51DB88AB
Op 0 0 0
T0 0 -1.27 1.016 1.016 0 0.27432 N V 21 N "J1"
T1 0 3.81 1.016 1.016 0 0.2032 N V 21 N "BREADBOARD_HEADER_L"
DS 15.24 0 -25.4 0 0.15 21
DS -25.4 0 -25.4 2.54 0.15 21
DS -25.4 2.54 15.24 2.54 0.15 21
DS 15.24 2.54 15.24 0 0.15 21
$PAD
Sh "1" R 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 15 "N-000009"
Po -24.13 1.27
$EndPAD
$PAD
Sh "2" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 3 "N-0000010"
Po -21.59 1.27
$EndPAD
$PAD
Sh "11" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 2 "N-000001"
Po 1.27 1.27
$EndPAD
$PAD
Sh "4" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 8 "N-000002"
Po -16.51 1.27
$EndPAD
$PAD
Sh "13" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 14 "N-000008"
Po 6.35 1.27
$EndPAD
$PAD
Sh "6" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 10 "N-000004"
Po -11.43 1.27
$EndPAD
$PAD
Sh "15" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 5 "N-0000012"
Po 11.43 1.27
$EndPAD
$PAD
Sh "8" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 11 "N-000005"
Po -6.35 1.27
$EndPAD
$PAD
Sh "10" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 16 "VCC"
Po -1.27 1.27
$EndPAD
$PAD
Sh "12" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 13 "N-000007"
Po 3.81 1.27
$EndPAD
$PAD
Sh "14" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 4 "N-0000011"
Po 8.89 1.27
$EndPAD
$PAD
Sh "16" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 6 "N-0000013"
Po 13.97 1.27
$EndPAD
$PAD
Sh "3" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 12 "N-000006"
Po -19.05 1.27
$EndPAD
$PAD
Sh "5" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 9 "N-000003"
Po -13.97 1.27
$EndPAD
$PAD
Sh "7" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 7 "N-0000015"
Po -8.89 1.27
$EndPAD
$PAD
Sh "9" C 1.524 1.524 0 0 0
Dr 1.016 0 0
At STD N 00E0FFFF
Ne 1 "GND"
Po -3.81 1.27
$EndPAD
$SHAPE3D
Na "pin_array/pins_array_20x2.wrl"
Sc 1 1 1
Of 0 0 0
Ro 0 0 0
$EndSHAPE3D
$EndMODULE PIN_ARRAY_16x1
$MODULE SM0603
Po 0 0 0 15 51AE4FF9 00000000 ~~
Li SM0603
Sc 0
AR /51A91DB6
Op 0 0 0
At SMD
T0 0 1.27 0.508 0.4572 0 0.1143 N V 21 N "R32"
T1 0 0 0.508 0.4572 0 0.1143 N I 21 N "1M"
DS -1.143 -0.635 1.143 -0.635 0.127 21
DS 1.143 -0.635 1.143 0.635 0.127 21
DS 1.143 0.635 -1.143 0.635 0.127 21
DS -1.143 0.635 -1.143 -0.635 0.127 21
$PAD
Sh "1" R 0.635 1.143 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 2 "N-0000018"
Po -0.762 0
$EndPAD
$PAD
Sh "2" R 0.635 1.143 0 0 0
Dr 0 0 0
At SMD N 00808000
Ne 1 "N-0000013"
Po 0.762 0
$EndPAD
$SHAPE3D
Na "smd\\resistors\\R0603.wrl"
Sc 0.5 0.5 0.5
Of 0 0 0.001
Ro 0 0 0
$EndSHAPE3D
$EndMODULE SM0603
$MODULE TQFP_64
Po 0 0 0 15 48A969ED 00000000 ~~
Li TQFP_64
Kw TQFP64 TQFP SMD IC
Sc 0
AR 
Op 0 0 0
T0 0.127 -1.524 1.09982 1.09982 0 0.127 N V 21 N "TQFP_64"
T1 0 1.651 1.00076 1.00076 0 0.1524 N V 21 N "VAL**"
DC -3.98272 3.98272 -3.98272 3.60172 0.2032 21
DS 5.16128 -5.16128 -4.99872 -5.16128 0.2032 21
DS -4.99872 -5.16128 -4.99872 4.36372 0.2032 21
DS -4.99872 4.36372 -4.36372 4.99872 0.2032 21
DS -4.36372 4.99872 5.16128 4.99872 0.2032 21
DS 5.16128 4.99872 5.16128 -5.16128 0.2032 21
$PAD
Sh "1" R 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -3.74904 5.86994
$EndPAD
$PAD
Sh "2" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -3.24866 5.86994
$EndPAD
$PAD
Sh "3" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -2.74828 5.86994
$EndPAD
$PAD
Sh "4" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -2.2479 5.86994
$EndPAD
$PAD
Sh "5" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -1.74752 5.86994
$EndPAD
$PAD
Sh "6" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -1.24968 5.86994
$EndPAD
$PAD
Sh "7" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -0.7493 5.86994
$EndPAD
$PAD
Sh "8" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -0.24892 5.86994
$EndPAD
$PAD
Sh "9" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 0.25146 5.86994
$EndPAD
$PAD
Sh "10" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 0.75184 5.86994
$EndPAD
$PAD
Sh "11" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 1.25222 5.86994
$EndPAD
$PAD
Sh "12" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 1.75006 5.86994
$EndPAD
$PAD
Sh "13" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 2.25044 5.86994
$EndPAD
$PAD
Sh "14" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 2.75082 5.86994
$EndPAD
$PAD
Sh "15" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 3.2512 5.86994
$EndPAD
$PAD
Sh "16" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 3.75158 5.86994
$EndPAD
$PAD
Sh "17" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 3.74904
$EndPAD
$PAD
Sh "18" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 3.24866
$EndPAD
$PAD
Sh "19" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 2.74828
$EndPAD
$PAD
Sh "20" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 2.2479
$EndPAD
$PAD
Sh "21" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 1.74752
$EndPAD
$PAD
Sh "22" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 1.24968
$EndPAD
$PAD
Sh "23" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 0.7493
$EndPAD
$PAD
Sh "24" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 0.24892
$EndPAD
$PAD
Sh "25" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -0.25146
$EndPAD
$PAD
Sh "26" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -0.75184
$EndPAD
$PAD
Sh "27" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -1.25222
$EndPAD
$PAD
Sh "28" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -1.75006
$EndPAD
$PAD
Sh "29" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -2.25044
$EndPAD
$PAD
Sh "30" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -2.75082
$EndPAD
$PAD
Sh "31" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -3.2512
$EndPAD
$PAD
Sh "32" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 6.0325 -3.75158
$EndPAD
$PAD
Sh "33" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 3.75158 -6.0325
$EndPAD
$PAD
Sh "34" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 3.2512 -6.0325
$EndPAD
$PAD
Sh "35" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 2.75082 -6.0325
$EndPAD
$PAD
Sh "36" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 2.25044 -6.0325
$EndPAD
$PAD
Sh "37" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 1.75006 -6.0325
$EndPAD
$PAD
Sh "38" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 1.25222 -6.0325
$EndPAD
$PAD
Sh "39" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 0.75184 -6.0325
$EndPAD
$PAD
Sh "40" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po 0.25146 -6.0325
$EndPAD
$PAD
Sh "41" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -0.24892 -6.0325
$EndPAD
$PAD
Sh "42" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -0.7493 -6.0325
$EndPAD
$PAD
Sh "43" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -1.24968 -6.0325
$EndPAD
$PAD
Sh "44" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -1.74752 -6.0325
$EndPAD
$PAD
Sh "45" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -2.2479 -6.0325
$EndPAD
$PAD
Sh "46" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -2.74828 -6.0325
$EndPAD
$PAD
Sh "47" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -3.24866 -6.0325
$EndPAD
$PAD
Sh "48" O 0.24892 1.524 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -3.74904 -6.0325
$EndPAD
$PAD
Sh "49" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 -3.75158
$EndPAD
$PAD
Sh "50" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 -3.2512
$EndPAD
$PAD
Sh "52" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 -2.25044
$EndPAD
$PAD
Sh "51" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.88772 -2.75082
$EndPAD
$PAD
Sh "53" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 -1.75006
$EndPAD
$PAD
Sh "54" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 -1.25222
$EndPAD
$PAD
Sh "55" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 -0.75184
$EndPAD
$PAD
Sh "56" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 -0.25146
$EndPAD
$PAD
Sh "57" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 0.24892
$EndPAD
$PAD
Sh "58" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 0.7493
$EndPAD
$PAD
Sh "59" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 1.24206
$EndPAD
$PAD
Sh "60" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 1.74244
$EndPAD
$PAD
Sh "61" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 2.24282
$EndPAD
$PAD
Sh "62" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 2.7432
$EndPAD
$PAD
Sh "63" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 3.24104
$EndPAD
$PAD
Sh "64" O 1.524 0.24892 0 0 0
Dr 0 0 0
At SMD N 00888000
Ne 0 ""
Po -5.86994 3.74142
$EndPAD
$SHAPE3D
Na "smd/TQFP_64.wrl"
Sc 0.3937 0.3937 0.3937
Of 0 0 0.001
Ro 0 0 0
$EndSHAPE3D
$EndMODULE TQFP_64
$EndLIBRARY
