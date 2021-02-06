EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title "Separate board with camera, leds and LDR"
Date "2021-02-05"
Rev "1.1"
Comp "Cyclope robot by Adrien RICCIARDI"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:LED D1
U 1 1 5F289A86
P 3000 2800
F 0 "D1" H 2993 3016 50  0000 C CNN
F 1 "158301250" H 2993 2925 50  0000 C CNN
F 2 "158301250:158301250" H 3000 2800 50  0001 C CNN
F 3 "~" H 3000 2800 50  0001 C CNN
	1    3000 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5F28F949
P 3000 3350
F 0 "D2" H 2993 3566 50  0000 C CNN
F 1 "158301250" H 2993 3475 50  0000 C CNN
F 2 "158301250:158301250" H 3000 3350 50  0001 C CNN
F 3 "~" H 3000 3350 50  0001 C CNN
	1    3000 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5F2984F8
P 7350 3850
F 0 "J5" H 7429 3705 50  0000 L CNN
F 1 "Front" H 7429 3796 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7350 3850 50  0001 C CNN
F 3 "~" H 7350 3850 50  0001 C CNN
F 4 "DNP" H 7429 3887 50  0000 L CNN "Populate"
	1    7350 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F29B440
P 7650 4050
F 0 "#PWR0101" H 7650 3800 50  0001 C CNN
F 1 "GND" H 7655 3877 50  0000 C CNN
F 2 "" H 7650 4050 50  0001 C CNN
F 3 "" H 7650 4050 50  0001 C CNN
	1    7650 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0102
U 1 1 5F29F0FF
P 5050 4050
F 0 "#PWR0102" H 5050 3800 50  0001 C CNN
F 1 "GNDD" H 5054 3895 50  0000 C CNN
F 2 "" H 5050 4050 50  0001 C CNN
F 3 "" H 5050 4050 50  0001 C CNN
	1    5050 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5F2A1CD1
P 7650 2750
F 0 "#PWR0103" H 7650 2600 50  0001 C CNN
F 1 "+5V" H 7665 2923 50  0000 C CNN
F 2 "" H 7650 2750 50  0001 C CNN
F 3 "" H 7650 2750 50  0001 C CNN
	1    7650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3650 7650 3650
$Comp
L Device:C C?
U 1 1 5F2A61A6
P 7950 3100
AR Path="/5F1F2F9E/5F2A61A6" Ref="C?"  Part="1" 
AR Path="/5F22814A/5F2A61A6" Ref="C?"  Part="1" 
AR Path="/5F288D93/5F2A61A6" Ref="C18"  Part="1" 
F 0 "C18" H 7835 2963 50  0000 R CNN
F 1 "100n" H 7835 3054 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7988 2950 50  0001 C CNN
F 3 "~" H 7950 3100 50  0001 C CNN
F 4 "25V" H 7835 3145 50  0000 R CNN "Value2"
F 5 "X7R" H 7835 3236 50  0000 R CNN "Value3"
	1    7950 3100
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5F2A61AE
P 8450 3100
AR Path="/5F1F2F9E/5F2A61AE" Ref="C?"  Part="1" 
AR Path="/5F22814A/5F2A61AE" Ref="C?"  Part="1" 
AR Path="/5F288D93/5F2A61AE" Ref="C19"  Part="1" 
F 0 "C19" H 8335 2963 50  0000 R CNN
F 1 "2.2u" H 8335 3054 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8488 2950 50  0001 C CNN
F 3 "~" H 8450 3100 50  0001 C CNN
F 4 "25V" H 8335 3145 50  0000 R CNN "Value2"
F 5 "X7R" H 8335 3236 50  0000 R CNN "Value3"
	1    8450 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	7650 2850 7950 2850
Wire Wire Line
	7950 2850 7950 2950
Wire Wire Line
	7950 2850 8450 2850
Wire Wire Line
	8450 2850 8450 2950
Connection ~ 7950 2850
Wire Wire Line
	7950 3250 7950 3300
Wire Wire Line
	8450 3300 8450 3250
Wire Wire Line
	7950 3300 8200 3300
$Comp
L power:GND #PWR0104
U 1 1 5F2AC559
P 8200 3350
F 0 "#PWR0104" H 8200 3100 50  0001 C CNN
F 1 "GND" H 8205 3177 50  0000 C CNN
F 2 "" H 8200 3350 50  0001 C CNN
F 3 "" H 8200 3350 50  0001 C CNN
	1    8200 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3350 8200 3300
Connection ~ 8200 3300
Wire Wire Line
	8200 3300 8450 3300
Text GLabel 7800 3750 2    50   UnSpc ~ 0
FRONT_BOARD_LDR
Wire Wire Line
	7800 3750 7550 3750
Wire Notes Line
	6500 5250 10300 5250
Wire Notes Line
	10300 5250 10300 2450
Wire Notes Line
	10300 2450 6500 2450
Wire Notes Line
	6500 2450 6500 5250
Text Notes 6600 5150 0    50   ~ 0
Part of motherboard.
$Comp
L power:+5VD #PWR0105
U 1 1 5F2BDBFA
P 5050 3550
F 0 "#PWR0105" H 5050 3400 50  0001 C CNN
F 1 "+5VD" H 5065 3723 50  0000 C CNN
F 2 "" H 5050 3550 50  0001 C CNN
F 3 "" H 5050 3550 50  0001 C CNN
	1    5050 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3550 5050 3650
Wire Wire Line
	5050 3650 5150 3650
Wire Wire Line
	2850 3350 2750 3350
Wire Wire Line
	2750 3350 2750 2800
Wire Wire Line
	2750 2800 2850 2800
Text Notes 2750 2350 0    50   ~ 0
Led forward voltage : 3V.\nLed forward current : 20mA.
$Comp
L Device:R R7
U 1 1 5F2D70A9
P 3550 2800
F 0 "R7" V 3253 2800 50  0000 C CNN
F 1 "100" V 3344 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3480 2800 50  0001 C CNN
F 3 "~" H 3550 2800 50  0001 C CNN
F 4 "5%" V 3435 2800 50  0000 C CNN "Value2"
	1    3550 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 5F2DA263
P 3550 3350
F 0 "R8" V 3253 3350 50  0000 C CNN
F 1 "100" V 3344 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3480 3350 50  0001 C CNN
F 3 "~" H 3550 3350 50  0001 C CNN
F 4 "5%" V 3435 3350 50  0000 C CNN "Value2"
	1    3550 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 2800 3400 2800
Wire Wire Line
	3150 3350 3400 3350
Wire Wire Line
	3700 2800 3800 2800
Wire Wire Line
	3800 3350 3700 3350
$Comp
L Mechanical:MountingHole H3
U 1 1 5F2EC62F
P 4500 2350
F 0 "H3" H 4600 2396 50  0000 L CNN
F 1 "Camera" H 4600 2305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 4500 2350 50  0001 C CNN
F 3 "~" H 4500 2350 50  0001 C CNN
	1    4500 2350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5F2F030A
P 5250 2350
F 0 "H4" H 5350 2396 50  0000 L CNN
F 1 "Camera" H 5350 2305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 5250 2350 50  0001 C CNN
F 3 "~" H 5250 2350 50  0001 C CNN
	1    5250 2350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 5F2F0621
P 4500 2650
F 0 "H5" H 4600 2696 50  0000 L CNN
F 1 "Camera" H 4600 2605 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 4500 2650 50  0001 C CNN
F 3 "~" H 4500 2650 50  0001 C CNN
	1    4500 2650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H6
U 1 1 5F2F098F
P 5250 2650
F 0 "H6" H 5350 2696 50  0000 L CNN
F 1 "Camera" H 5350 2605 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 5250 2650 50  0001 C CNN
F 3 "~" H 5250 2650 50  0001 C CNN
	1    5250 2650
	1    0    0    -1  
$EndComp
Wire Notes Line
	2500 5250 6250 5250
Wire Notes Line
	6250 5250 6250 2050
Wire Notes Line
	6250 2050 2500 2050
Wire Notes Line
	2500 2050 2500 5250
Text Notes 5350 5150 0    50   ~ 0
Separate front board.
Connection ~ 2750 3350
$Comp
L Transistor_FET:DMG3414U Q1
U 1 1 5F310BD3
P 8550 4100
F 0 "Q1" H 8754 4146 50  0000 L CNN
F 1 "DMG3414U" H 8754 4055 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8750 4025 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/ds31739.pdf" H 8550 4100 50  0001 L CNN
	1    8550 4100
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5F3169A9
P 8650 4550
F 0 "#PWR013" H 8650 4300 50  0001 C CNN
F 1 "GND" H 8655 4377 50  0000 C CNN
F 2 "" H 8650 4550 50  0001 C CNN
F 3 "" H 8650 4550 50  0001 C CNN
	1    8650 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 3850 8450 3900
Wire Wire Line
	7550 3850 8450 3850
$Comp
L Device:R R9
U 1 1 5F31C7BD
P 8850 4300
F 0 "R9" H 8780 4209 50  0000 R CNN
F 1 "10K" H 8780 4300 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8780 4300 50  0001 C CNN
F 3 "~" H 8850 4300 50  0001 C CNN
F 4 "5%" H 8780 4391 50  0000 R CNN "Value2"
	1    8850 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	8450 4500 8650 4500
Wire Wire Line
	8650 4500 8650 4550
Wire Wire Line
	8450 4300 8450 4500
Wire Wire Line
	8650 4500 8850 4500
Wire Wire Line
	8850 4500 8850 4450
Connection ~ 8650 4500
Wire Wire Line
	8750 4100 8850 4100
Wire Wire Line
	8850 4100 8850 4150
Text GLabel 9100 4100 2    50   Input ~ 0
FRONT_BOARD_LEDS
Wire Wire Line
	8850 4100 9100 4100
Connection ~ 8850 4100
Wire Wire Line
	4250 4200 4250 4150
$Comp
L power:GNDD #PWR0106
U 1 1 5F2C3356
P 4250 4200
F 0 "#PWR0106" H 4250 3950 50  0001 C CNN
F 1 "GNDD" H 4254 4045 50  0000 C CNN
F 2 "" H 4250 4200 50  0001 C CNN
F 3 "" H 4250 4200 50  0001 C CNN
	1    4250 4200
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Optical:LDR07 R?
U 1 1 5F29225B
P 4250 4000
AR Path="/5F1FECAE/5F29225B" Ref="R?"  Part="1" 
AR Path="/5F288D93/5F29225B" Ref="R6"  Part="1" 
F 0 "R6" H 4320 4046 50  0000 L CNN
F 1 "LDR07" H 4320 3955 50  0000 L CNN
F 2 "OptoDevice:R_LDR_5.1x4.3mm_P3.4mm_Vertical" V 4425 4000 50  0001 C CNN
F 3 "http://www.tme.eu/de/Document/f2e3ad76a925811312d226c31da4cd7e/LDR07.pdf" H 4250 3950 50  0001 C CNN
	1    4250 4000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5F294EF0
P 5350 3750
F 0 "J4" H 5430 3787 50  0000 L CNN
F 1 "Front" H 5430 3696 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5350 3750 50  0001 C CNN
F 3 "~" H 5350 3750 50  0001 C CNN
F 4 "DNP" H 5430 3605 50  0000 L CNN "Populate"
	1    5350 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3950 5050 3950
Wire Wire Line
	5050 3950 5050 4050
Wire Wire Line
	4250 3750 5150 3750
Wire Wire Line
	4250 3750 4250 3850
Wire Wire Line
	4700 3850 5150 3850
Wire Wire Line
	7650 2750 7650 2850
Connection ~ 7650 2850
Wire Wire Line
	7650 2850 7650 3650
Wire Wire Line
	7550 3950 7650 3950
Wire Wire Line
	7650 3950 7650 4050
$Comp
L Device:LED D3
U 1 1 5F22A727
P 3000 3900
F 0 "D3" H 2993 4116 50  0000 C CNN
F 1 "158301250" H 2993 4025 50  0000 C CNN
F 2 "158301250:158301250" H 3000 3900 50  0001 C CNN
F 3 "~" H 3000 3900 50  0001 C CNN
	1    3000 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 5F22A72D
P 3000 4450
F 0 "D4" H 2993 4666 50  0000 C CNN
F 1 "158301250" H 2993 4575 50  0000 C CNN
F 2 "158301250:158301250" H 3000 4450 50  0001 C CNN
F 3 "~" H 3000 4450 50  0001 C CNN
	1    3000 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4450 2750 4450
$Comp
L Device:R R16
U 1 1 5F22A736
P 3550 3900
F 0 "R16" V 3253 3900 50  0000 C CNN
F 1 "100" V 3344 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3480 3900 50  0001 C CNN
F 3 "~" H 3550 3900 50  0001 C CNN
F 4 "5%" V 3435 3900 50  0000 C CNN "Value2"
	1    3550 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R R17
U 1 1 5F22A73D
P 3550 4450
F 0 "R17" V 3253 4450 50  0000 C CNN
F 1 "100" V 3344 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3480 4450 50  0001 C CNN
F 3 "~" H 3550 4450 50  0001 C CNN
F 4 "5%" V 3435 4450 50  0000 C CNN "Value2"
	1    3550 4450
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 3900 3400 3900
Wire Wire Line
	3150 4450 3400 4450
Wire Wire Line
	3700 3900 3800 3900
Wire Wire Line
	3800 4450 3700 4450
Wire Wire Line
	2850 3900 2750 3900
Connection ~ 2750 3900
Wire Wire Line
	2750 3900 2750 3350
Wire Wire Line
	3800 3350 3800 3650
Connection ~ 3800 3350
Wire Wire Line
	3800 3900 3800 4450
Connection ~ 3800 3900
Wire Wire Line
	2750 3900 2750 4450
Wire Wire Line
	3800 2800 3800 3350
Connection ~ 5050 3650
Wire Wire Line
	3800 3650 5050 3650
Connection ~ 3800 3650
Wire Wire Line
	3800 3650 3800 3900
Wire Wire Line
	2750 4450 2750 4850
Wire Wire Line
	2750 4850 4700 4850
Wire Wire Line
	4700 3850 4700 4850
Connection ~ 2750 4450
$Comp
L Mechanical:MountingHole H11
U 1 1 5F25DF87
P 4500 2950
F 0 "H11" H 4600 2996 50  0000 L CNN
F 1 "Front_Board" H 4600 2905 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 4500 2950 50  0001 C CNN
F 3 "~" H 4500 2950 50  0001 C CNN
	1    4500 2950
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H12
U 1 1 5F25EF87
P 5250 2950
F 0 "H12" H 5350 2996 50  0000 L CNN
F 1 "Front_Board" H 5350 2905 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5250 2950 50  0001 C CNN
F 3 "~" H 5250 2950 50  0001 C CNN
	1    5250 2950
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole BT1
U 1 1 5F3734C7
P 5550 4300
F 0 "BT1" H 5650 4346 50  0000 L CNN
F 1 "BreakTab" H 5650 4255 50  0000 L CNN
F 2 "Break_Tab:Break_Tab" H 5550 4300 50  0001 C CNN
F 3 "~" H 5550 4300 50  0001 C CNN
	1    5550 4300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole BT2
U 1 1 5F3A13DD
P 5550 4550
F 0 "BT2" H 5650 4596 50  0000 L CNN
F 1 "BreakTab" H 5650 4505 50  0000 L CNN
F 2 "Break_Tab:Break_Tab" H 5550 4550 50  0001 C CNN
F 3 "~" H 5550 4550 50  0001 C CNN
	1    5550 4550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole BT3
U 1 1 5F3A17F1
P 5550 4800
F 0 "BT3" H 5650 4846 50  0000 L CNN
F 1 "BreakTab" H 5650 4755 50  0000 L CNN
F 2 "Break_Tab:Break_Tab" H 5550 4800 50  0001 C CNN
F 3 "~" H 5550 4800 50  0001 C CNN
	1    5550 4800
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole BT4
U 1 1 5F3ABA27
P 6800 4300
F 0 "BT4" H 6900 4346 50  0000 L CNN
F 1 "BreakTab" H 6900 4255 50  0000 L CNN
F 2 "Break_Tab:Break_Tab" H 6800 4300 50  0001 C CNN
F 3 "~" H 6800 4300 50  0001 C CNN
	1    6800 4300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole BT5
U 1 1 5F3ABA2D
P 6800 4550
F 0 "BT5" H 6900 4596 50  0000 L CNN
F 1 "BreakTab" H 6900 4505 50  0000 L CNN
F 2 "Break_Tab:Break_Tab" H 6800 4550 50  0001 C CNN
F 3 "~" H 6800 4550 50  0001 C CNN
	1    6800 4550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole BT6
U 1 1 5F3ABA33
P 6800 4800
F 0 "BT6" H 6900 4846 50  0000 L CNN
F 1 "BreakTab" H 6900 4755 50  0000 L CNN
F 2 "Break_Tab:Break_Tab" H 6800 4800 50  0001 C CNN
F 3 "~" H 6800 4800 50  0001 C CNN
	1    6800 4800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
