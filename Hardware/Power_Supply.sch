EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
Title "DC/DC power supply"
Date "2020-07-27"
Rev "1.0"
Comp "Cyclope robot by Adrien RICCIARDI"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Switching:TPS565208 U1
U 1 1 5F1F3596
P 6000 3600
F 0 "U1" H 6000 3967 50  0000 C CNN
F 1 "TPS565208DDC" H 6000 3876 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 6050 3350 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps565208.pdf" H 6000 3600 50  0001 C CNN
	1    6000 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5F1F38BC
P 7600 3500
F 0 "L1" V 7790 3500 50  0000 C CNN
F 1 "IHLP3232DZER3R3M01" V 7699 3500 50  0000 C CNN
F 2 "IHLP3232DZER3R3M01:IHLP3232DZER3R3M01" H 7600 3500 50  0001 C CNN
F 3 "~" H 7600 3500 50  0001 C CNN
F 4 "Vishay-Dale" H 7600 3500 50  0001 C CNN "Manufacturer"
	1    7600 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5F1F6510
P 8050 3750
F 0 "R1" H 8120 3841 50  0000 L CNN
F 1 "54.9K" H 8120 3750 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7980 3750 50  0001 C CNN
F 3 "~" H 8050 3750 50  0001 C CNN
F 4 "1%" H 8120 3659 50  0000 L CNN "Value2"
	1    8050 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F1F6CFB
P 8050 4150
F 0 "R2" H 8120 4241 50  0000 L CNN
F 1 "10K" H 8120 4150 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7980 4150 50  0001 C CNN
F 3 "~" H 8050 4150 50  0001 C CNN
F 4 "1%" H 8120 4059 50  0000 L CNN "Value2"
	1    8050 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5F1F72DC
P 5000 3750
F 0 "C4" H 4885 3613 50  0000 R CNN
F 1 "100n" H 4885 3704 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5038 3600 50  0001 C CNN
F 3 "~" H 5000 3750 50  0001 C CNN
F 4 "50V" H 4885 3795 50  0000 R CNN "Value2"
F 5 "X7R" H 4885 3886 50  0000 R CNN "Value3"
	1    5000 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 5F1F85F3
P 4550 3750
F 0 "C3" H 4435 3613 50  0000 R CNN
F 1 "10u" H 4435 3704 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4588 3600 50  0001 C CNN
F 3 "~" H 4550 3750 50  0001 C CNN
F 4 "50V" H 4435 3795 50  0000 R CNN "Value2"
F 5 "X7R" H 4435 3886 50  0000 R CNN "Value3"
	1    4550 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 5F1F89CE
P 4100 3750
F 0 "C2" H 3985 3613 50  0000 R CNN
F 1 "10u" H 3985 3704 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4138 3600 50  0001 C CNN
F 3 "~" H 4100 3750 50  0001 C CNN
F 4 "50V" H 3985 3795 50  0000 R CNN "Value2"
F 5 "X7R" H 3985 3886 50  0000 R CNN "Value3"
	1    4100 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C5
U 1 1 5F1F9FA0
P 8700 3750
F 0 "C5" H 8585 3613 50  0000 R CNN
F 1 "10u" H 8585 3704 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8738 3600 50  0001 C CNN
F 3 "~" H 8700 3750 50  0001 C CNN
F 4 "25V" H 8585 3795 50  0000 R CNN "Value2"
F 5 "X7R" H 8585 3886 50  0000 R CNN "Value3"
F 6 "CC1206KRX7R9BB104" V 8700 3750 50  0001 C CNN "ManufacturerReference"
	1    8700 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C6
U 1 1 5F1FBC43
P 9150 3750
F 0 "C6" H 9035 3613 50  0000 R CNN
F 1 "22u" H 9035 3704 50  0000 R CNN
F 2 "Capacitor_SMD:C_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 9188 3600 50  0001 C CNN
F 3 "~" H 9150 3750 50  0001 C CNN
F 4 "25V" H 9035 3795 50  0000 R CNN "Value2"
F 5 "X7R" H 9035 3886 50  0000 R CNN "Value3"
F 6 "CC1206KRX7R9BB104" V 9150 3750 50  0001 C CNN "ManufacturerReference"
	1    9150 3750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C7
U 1 1 5F1FC068
P 9600 3750
F 0 "C7" H 9485 3613 50  0000 R CNN
F 1 "22u" H 9485 3704 50  0000 R CNN
F 2 "Capacitor_SMD:C_1210_3225Metric_Pad1.42x2.65mm_HandSolder" H 9638 3600 50  0001 C CNN
F 3 "~" H 9600 3750 50  0001 C CNN
F 4 "25V" H 9485 3795 50  0000 R CNN "Value2"
F 5 "X7R" H 9485 3886 50  0000 R CNN "Value3"
F 6 "CC1206KRX7R9BB104" V 9600 3750 50  0001 C CNN "ManufacturerReference"
	1    9600 3750
	-1   0    0    1   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5F1FE00E
P 2250 4000
F 0 "H2" V 2487 4003 50  0000 C CNN
F 1 "BATTERY-" V 2396 4003 50  0000 C CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 2250 4000 50  0001 C CNN
F 3 "~" H 2250 4000 50  0001 C CNN
	1    2250 4000
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5F1FF3A5
P 2250 3400
F 0 "H1" V 2487 3403 50  0000 C CNN
F 1 "BATTERY+" V 2396 3403 50  0000 C CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad" H 2250 3400 50  0001 C CNN
F 3 "~" H 2250 3400 50  0001 C CNN
	1    2250 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 3500 4100 3600
Wire Wire Line
	4100 3500 4550 3500
Wire Wire Line
	4550 3500 4550 3600
Connection ~ 4100 3500
Wire Wire Line
	4550 3500 5000 3500
Wire Wire Line
	5000 3500 5000 3600
Connection ~ 4550 3500
Wire Wire Line
	5000 3500 5500 3500
Connection ~ 5000 3500
Wire Wire Line
	5500 3500 5500 3700
Wire Wire Line
	5500 3700 5600 3700
Connection ~ 5500 3500
Wire Wire Line
	5500 3500 5600 3500
Wire Wire Line
	4100 3900 4100 4000
Wire Wire Line
	4550 4000 4550 3900
Wire Wire Line
	4550 4000 5000 4000
Wire Wire Line
	5000 4000 5000 3900
Connection ~ 4550 4000
Wire Wire Line
	5000 4000 6000 4000
Wire Wire Line
	6000 4000 6000 3900
Connection ~ 5000 4000
Wire Wire Line
	2350 4000 3550 4000
Wire Wire Line
	4100 4000 4550 4000
$Comp
L power:GND #PWR02
U 1 1 5F204807
P 6000 4100
F 0 "#PWR02" H 6000 3850 50  0001 C CNN
F 1 "GND" H 6005 3927 50  0000 C CNN
F 2 "" H 6000 4100 50  0001 C CNN
F 3 "" H 6000 4100 50  0001 C CNN
	1    6000 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4100 6000 4000
Connection ~ 6000 4000
Wire Wire Line
	6400 3700 6550 3700
Wire Wire Line
	6400 3600 6650 3600
Wire Wire Line
	6650 3600 6650 3700
Wire Wire Line
	7050 3700 7150 3700
$Comp
L Device:C C1
U 1 1 5F1F48E7
P 6900 3700
F 0 "C1" V 6350 3700 50  0000 C CNN
F 1 "100n" V 6450 3700 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6938 3550 50  0001 C CNN
F 3 "~" H 6900 3700 50  0001 C CNN
F 4 "25V" V 6550 3700 50  0000 C CNN "Value2"
F 5 "X7R" V 6650 3700 50  0000 C CNN "Value3"
F 6 "CC1206KRX7R9BB104" V 6900 3700 50  0001 C CNN "ManufacturerReference"
	1    6900 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	8050 3500 8700 3500
Wire Wire Line
	8700 3500 8700 3600
Connection ~ 8050 3500
Wire Wire Line
	8700 3500 9150 3500
Wire Wire Line
	9150 3500 9150 3600
Connection ~ 8700 3500
Wire Wire Line
	9150 3500 9600 3500
Wire Wire Line
	9600 3500 9600 3600
Connection ~ 9150 3500
$Comp
L power:+5V #PWR01
U 1 1 5F20FD84
P 9600 3400
F 0 "#PWR01" H 9600 3250 50  0001 C CNN
F 1 "+5V" H 9615 3573 50  0000 C CNN
F 2 "" H 9600 3400 50  0001 C CNN
F 3 "" H 9600 3400 50  0001 C CNN
	1    9600 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 3500 9600 3400
Connection ~ 9600 3500
Wire Wire Line
	8700 3900 8700 4000
Wire Wire Line
	8700 4000 9150 4000
Wire Wire Line
	9150 4000 9150 3900
Wire Wire Line
	9150 4000 9600 4000
Wire Wire Line
	9600 4000 9600 3900
Connection ~ 9150 4000
$Comp
L power:GND #PWR03
U 1 1 5F2113CA
P 9150 4100
F 0 "#PWR03" H 9150 3850 50  0001 C CNN
F 1 "GND" H 9155 3927 50  0000 C CNN
F 2 "" H 9150 4100 50  0001 C CNN
F 3 "" H 9150 4100 50  0001 C CNN
	1    9150 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 4100 9150 4000
Wire Wire Line
	6550 3950 8050 3950
Wire Wire Line
	8050 3950 8050 3900
Wire Wire Line
	6550 3700 6550 3950
Wire Wire Line
	8050 3950 8050 4000
Connection ~ 8050 3950
$Comp
L power:GND #PWR04
U 1 1 5F213955
P 8050 4400
F 0 "#PWR04" H 8050 4150 50  0001 C CNN
F 1 "GND" H 8055 4227 50  0000 C CNN
F 2 "" H 8050 4400 50  0001 C CNN
F 3 "" H 8050 4400 50  0001 C CNN
	1    8050 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4400 8050 4300
Wire Wire Line
	8050 3500 8050 3600
Wire Wire Line
	6650 3700 6750 3700
Wire Wire Line
	7150 3700 7150 3500
Wire Wire Line
	6400 3500 7150 3500
Connection ~ 7150 3500
Wire Wire Line
	7150 3500 7450 3500
Wire Wire Line
	7750 3500 8050 3500
$Comp
L Switch:SW_SPDT SW1
U 1 1 5F22069E
P 2800 3400
F 0 "SW1" H 2800 3685 50  0000 C CNN
F 1 "1101M2S3AQE2" H 2800 3594 50  0000 C CNN
F 2 "1101M2S3AQE2:1101M2S3AQE2" H 2800 3400 50  0001 C CNN
F 3 "~" H 2800 3400 50  0001 C CNN
	1    2800 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3400 2600 3400
Text GLabel 3600 3250 2    50   UnSpc ~ 0
BATTERY+
Wire Wire Line
	3600 3250 3550 3250
Wire Wire Line
	3550 3250 3550 3500
Wire Wire Line
	3000 3300 3200 3300
Wire Wire Line
	3200 3300 3200 3500
NoConn ~ 3000 3500
$Comp
L Supply_Part:Supply_Part BAT?
U 1 1 5F37F87A
P 1200 3650
AR Path="/5F22814A/5F37F87A" Ref="BAT?"  Part="1" 
AR Path="/5F37F87A" Ref="BAT?"  Part="1" 
AR Path="/5F1F2F9E/5F37F87A" Ref="BAT1"  Part="1" 
F 0 "BAT1" H 1428 3696 50  0000 L CNN
F 1 "MP000303" H 1428 3605 50  0000 L CNN
F 2 "Supply_Part:Supply_Part" H 1200 3650 50  0001 C CNN
F 3 "" H 1200 3650 50  0001 C CNN
F 4 "MULTICOMP_PRO" H 1200 3650 50  0001 C CNN "Manufacturer"
F 5 "Battery_Holder" H 1200 3650 50  0001 C CNN "Value2"
	1    1200 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C20
U 1 1 5F467D3F
P 3550 3750
F 0 "C20" H 3668 3841 50  0000 L CNN
F 1 "4700u" H 3668 3750 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L9.0mm_W2.5mm_P7.50mm_MKT" H 3588 3600 50  0001 C CNN
F 3 "~" H 3550 3750 50  0001 C CNN
F 4 "35V" H 3668 3659 50  0000 L CNN "Value2"
F 5 "MCKSK035M472J32S" H 3550 3750 50  0001 C CNN "Value3"
	1    3550 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3500 3550 3500
Wire Wire Line
	3550 3500 4100 3500
Connection ~ 3550 3500
Wire Wire Line
	3550 3500 3550 3600
Wire Wire Line
	3550 3900 3550 4000
Connection ~ 3550 4000
Connection ~ 4100 4000
Wire Wire Line
	3550 4000 4100 4000
Text Notes 3050 4350 0    50   ~ 0
C20 capacitor must be bent\nover SMD parts and glued.
$EndSCHEMATC
