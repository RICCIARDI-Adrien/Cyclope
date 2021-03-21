EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
Title "RPLIDAR A1M8 Dev Kit Lidar"
Date "2021-02-05"
Rev "1.1"
Comp "Cyclope robot by Adrien RICCIARDI"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	2950 4250 2950 4300
Wire Wire Line
	3050 4250 2950 4250
Connection ~ 3150 4650
Wire Wire Line
	3350 4450 3350 4650
Wire Wire Line
	3150 4650 3350 4650
Wire Wire Line
	3150 4650 3150 4700
Wire Wire Line
	2950 4650 3150 4650
Wire Wire Line
	2950 4600 2950 4650
$Comp
L Device:R R?
U 1 1 603424E6
P 2950 4450
AR Path="/5F1F2F9E/603424E6" Ref="R?"  Part="1" 
AR Path="/5F22814A/603424E6" Ref="R?"  Part="1" 
AR Path="/601E5913/603424E6" Ref="R23"  Part="1" 
F 0 "R23" H 3020 4541 50  0000 L CNN
F 1 "10K" H 3020 4450 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 2880 4450 50  0001 C CNN
F 3 "~" H 2950 4450 50  0001 C CNN
F 4 "5%" H 3020 4359 50  0000 L CNN "Value2"
	1    2950 4450
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 603424EC
P 3150 4700
AR Path="/5F22814A/603424EC" Ref="#PWR?"  Part="1" 
AR Path="/601E5913/603424EC" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 3150 4450 50  0001 C CNN
F 1 "GND" H 3155 4527 50  0000 C CNN
F 2 "" H 3150 4700 50  0001 C CNN
F 3 "" H 3150 4700 50  0001 C CNN
	1    3150 4700
	1    0    0    -1  
$EndComp
Connection ~ 3350 3750
Wire Wire Line
	3350 3750 3350 4050
Wire Wire Line
	3450 3750 3350 3750
Wire Wire Line
	3350 3750 3350 3700
Connection ~ 3550 3350
Wire Wire Line
	3750 3350 3750 3550
Wire Wire Line
	3550 3350 3750 3350
Wire Wire Line
	3350 3350 3350 3400
Wire Wire Line
	3550 3350 3350 3350
Wire Wire Line
	3550 3300 3550 3350
$Comp
L power:+5V #PWR?
U 1 1 603424FC
P 3550 3300
AR Path="/5F22814A/603424FC" Ref="#PWR?"  Part="1" 
AR Path="/601E5913/603424FC" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 3550 3150 50  0001 C CNN
F 1 "+5V" H 3565 3473 50  0000 C CNN
F 2 "" H 3550 3300 50  0001 C CNN
F 3 "" H 3550 3300 50  0001 C CNN
	1    3550 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3950 3750 4000
$Comp
L Transistor_FET:DMG2301L Q?
U 1 1 60342504
P 3650 3750
AR Path="/5F22814A/60342504" Ref="Q?"  Part="1" 
AR Path="/601E5913/60342504" Ref="Q6"  Part="1" 
F 0 "Q6" H 3855 3704 50  0000 L CNN
F 1 "DMG2301L" H 3855 3795 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3850 3675 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2301L.pdf" H 3650 3750 50  0001 L CNN
	1    3650 3750
	1    0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6034250B
P 3350 3550
AR Path="/5F1F2F9E/6034250B" Ref="R?"  Part="1" 
AR Path="/5F22814A/6034250B" Ref="R?"  Part="1" 
AR Path="/601E5913/6034250B" Ref="R22"  Part="1" 
F 0 "R22" H 3420 3641 50  0000 L CNN
F 1 "10K" H 3420 3550 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3280 3550 50  0001 C CNN
F 3 "~" H 3350 3550 50  0001 C CNN
F 4 "5%" H 3420 3459 50  0000 L CNN "Value2"
	1    3350 3550
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:DMG3414U Q?
U 1 1 60342511
P 3250 4250
AR Path="/5F22814A/60342511" Ref="Q?"  Part="1" 
AR Path="/601E5913/60342511" Ref="Q7"  Part="1" 
F 0 "Q7" H 3454 4296 50  0000 L CNN
F 1 "DMG3414U" H 3454 4205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3450 4175 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/ds31739.pdf" H 3250 4250 50  0001 L CNN
	1    3250 4250
	1    0    0    -1  
$EndComp
Text Notes 5800 1950 0    50   ~ 0
Lidar\nRPLIDAR A1M8
Wire Wire Line
	5800 2550 5800 2350
$Comp
L power:GND #PWR?
U 1 1 603CF144
P 6000 2550
AR Path="/5F22814A/603CF144" Ref="#PWR?"  Part="1" 
AR Path="/601E5913/603CF144" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 6000 2300 50  0001 C CNN
F 1 "GND" H 6005 2377 50  0000 C CNN
F 2 "" H 6000 2550 50  0001 C CNN
F 3 "" H 6000 2550 50  0001 C CNN
	1    6000 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2550 6000 2350
$Comp
L power:GND #PWR?
U 1 1 603D1535
P 6400 2550
AR Path="/5F22814A/603D1535" Ref="#PWR?"  Part="1" 
AR Path="/601E5913/603D1535" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 6400 2300 50  0001 C CNN
F 1 "GND" H 6405 2377 50  0000 C CNN
F 2 "" H 6400 2550 50  0001 C CNN
F 3 "" H 6400 2550 50  0001 C CNN
	1    6400 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2550 6400 2350
Wire Wire Line
	6300 2350 6300 3050
Wire Wire Line
	6200 2350 6200 3150
Wire Wire Line
	2500 4250 2950 4250
Connection ~ 2950 4250
Text GLabel 2500 4250 0    50   Input ~ 0
LIDAR_ENABLE
Wire Wire Line
	5800 2550 5900 2550
Wire Wire Line
	5900 2550 5900 2350
Connection ~ 5800 2550
Text Notes 4900 2400 0    50   ~ 0
Always set 100%\nduty cycle PWM.
$Comp
L Device:CP C?
U 1 1 6036D681
P 4800 2850
AR Path="/5F22814A/6036D681" Ref="C?"  Part="1" 
AR Path="/601E5913/6036D681" Ref="C21"  Part="1" 
F 0 "C21" H 4918 2941 50  0000 L CNN
F 1 "47u" H 4918 2850 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.4" H 4838 2700 50  0001 C CNN
F 3 "~" H 4800 2850 50  0001 C CNN
F 4 "25V" H 4918 2759 50  0000 L CNN "Value2"
F 5 "MCVVT016M470DA1L" H 4800 2850 50  0001 C CNN "Value3"
	1    4800 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2550 4800 2700
Wire Wire Line
	4800 3000 4800 3100
$Comp
L power:GND #PWR?
U 1 1 603A976D
P 4800 3100
AR Path="/5F22814A/603A976D" Ref="#PWR?"  Part="1" 
AR Path="/601E5913/603A976D" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 4800 2850 50  0001 C CNN
F 1 "GND" H 4805 2927 50  0000 C CNN
F 2 "" H 4800 3100 50  0001 C CNN
F 3 "" H 4800 3100 50  0001 C CNN
	1    4800 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3150 7400 3150
Text GLabel 7400 3150 2    50   Output ~ 0
LIDAR_UART_TX
Text GLabel 7400 3050 2    50   Input ~ 0
LIDAR_UART_RX
Wire Wire Line
	6300 3050 7400 3050
Text Notes 8150 3150 0    50   ~ 0
Lidar UART voltages\nare +3.3V.\n
Wire Wire Line
	4800 2550 5800 2550
Text Notes 5000 3350 0    50   ~ 0
Lidar already provides\nmotor decoupling\ncapacitors, but add\nsome more.
$Comp
L Device:C C?
U 1 1 602007C7
P 5700 4250
AR Path="/602007C7" Ref="C?"  Part="1" 
AR Path="/5E8C5A93/602007C7" Ref="C?"  Part="1" 
AR Path="/5EBFD376/602007C7" Ref="C?"  Part="1" 
AR Path="/5F1FECAE/602007C7" Ref="C?"  Part="1" 
AR Path="/601E5913/602007C7" Ref="C23"  Part="1" 
F 0 "C23" H 5850 4400 50  0000 L CNN
F 1 "100n" H 5850 4300 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5738 4100 50  0001 C CNN
F 3 "~" H 5700 4250 50  0001 C CNN
F 4 "16V" H 5850 4200 50  0000 L CNN "Value2"
F 5 "X7R" H 5850 4100 50  0000 L CNN "Value3"
	1    5700 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6020D2C5
P 4800 4250
AR Path="/5F1F2F9E/6020D2C5" Ref="C?"  Part="1" 
AR Path="/601E5913/6020D2C5" Ref="C22"  Part="1" 
F 0 "C22" H 4685 4113 50  0000 R CNN
F 1 "10u" H 4685 4204 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4838 4100 50  0001 C CNN
F 3 "~" H 4800 4250 50  0001 C CNN
F 4 "25V" H 4685 4295 50  0000 R CNN "Value2"
F 5 "X7R" H 4685 4386 50  0000 R CNN "Value3"
	1    4800 4250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 60216BA8
P 5250 4000
AR Path="/5F1F2F9E/60216BA8" Ref="R?"  Part="1" 
AR Path="/5F22814A/60216BA8" Ref="R?"  Part="1" 
AR Path="/601E5913/60216BA8" Ref="R24"  Part="1" 
F 0 "R24" V 5547 4000 50  0000 C CNN
F 1 "0" V 5456 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5180 4000 50  0001 C CNN
F 3 "~" H 5250 4000 50  0001 C CNN
F 4 "5%" V 5365 4000 50  0000 C CNN "Value2"
	1    5250 4000
	0    1    -1   0   
$EndComp
Wire Wire Line
	3750 4000 4400 4000
Wire Wire Line
	4800 4100 4800 4000
Connection ~ 4800 4000
Wire Wire Line
	4800 4000 5100 4000
Wire Wire Line
	5400 4000 5700 4000
Wire Wire Line
	5700 4000 5700 4100
Wire Wire Line
	5700 4000 6100 4000
Wire Wire Line
	6100 4000 6100 2350
Connection ~ 5700 4000
$Comp
L power:GND #PWR?
U 1 1 60223D37
P 5250 4550
AR Path="/5F22814A/60223D37" Ref="#PWR?"  Part="1" 
AR Path="/601E5913/60223D37" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 5250 4300 50  0001 C CNN
F 1 "GND" H 5255 4377 50  0000 C CNN
F 2 "" H 5250 4550 50  0001 C CNN
F 3 "" H 5250 4550 50  0001 C CNN
	1    5250 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4400 4800 4500
Wire Wire Line
	4800 4500 5250 4500
Wire Wire Line
	5250 4500 5250 4550
Wire Wire Line
	5250 4500 5700 4500
Wire Wire Line
	5700 4500 5700 4400
Connection ~ 5250 4500
Wire Wire Line
	4400 4000 4400 2550
Wire Wire Line
	4400 2550 4800 2550
Connection ~ 4400 4000
Wire Wire Line
	4400 4000 4800 4000
Connection ~ 4800 2550
Text Notes 4850 5200 0    50   ~ 0
Allow to create a pi\nfilter if needed to keep\nlidar core voltage below\n50mVpp ripple.
$Comp
L Connector_Generic:Conn_01x07 J?
U 1 1 60342521
P 6100 2150
AR Path="/5F22814A/60342521" Ref="J?"  Part="1" 
AR Path="/601E5913/60342521" Ref="J6"  Part="1" 
F 0 "J6" V 6064 2530 50  0000 L CNN
F 1 "22-03-5075" V 5973 2530 50  0000 L CNN
F 2 "Connector_Molex:Molex_SPOX_5267-07A_1x07_P2.50mm_Vertical" H 6100 2150 50  0001 C CNN
F 3 "https://www.molex.com/webdocs/datasheets/pdf/en-us/0022035075_PCB_HEADERS.pdf" H 6100 2150 50  0001 C CNN
F 4 "Molex" H 6100 2150 50  0001 C CNN "Manufacturer"
	1    6100 2150
	0    1    -1   0   
$EndComp
$EndSCHEMATC
