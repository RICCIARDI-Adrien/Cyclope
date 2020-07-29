EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title "Analog-to-digital converter"
Date "2020-07-27"
Rev "1.0"
Comp "Cyclope robot by Adrien RICCIARDI"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:C C?
U 1 1 5E943D14
P 5350 2350
AR Path="/5E943D14" Ref="C?"  Part="1" 
AR Path="/5E8C5A93/5E943D14" Ref="C7"  Part="1" 
AR Path="/5F1FECAE/5E943D14" Ref="C13"  Part="1" 
F 0 "C13" H 5465 2487 50  0000 L CNN
F 1 "2.2u" H 5465 2396 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 5388 2200 50  0001 C CNN
F 3 "~" H 5350 2350 50  0001 C CNN
F 4 "16V" H 5465 2305 50  0000 L CNN "Value2"
F 5 "X7R" H 5465 2214 50  0000 L CNN "Value3"
	1    5350 2350
	1    0    0    -1  
$EndComp
$Comp
L Analog_ADC:MCP3002 U3
U 1 1 5F215D4B
P 6000 3600
F 0 "U3" H 6250 4200 50  0000 C CNN
F 1 "MCP3002" H 6350 4100 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6000 3500 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21294E.pdf" H 6000 3800 50  0001 C CNN
	1    6000 3600
	1    0    0    -1  
$EndComp
$Comp
L NCP51460SN33T1G:NCP51460SN33T1G U2
U 1 1 5EEA1D3C
P 3950 2150
F 0 "U2" H 3950 2515 50  0000 C CNN
F 1 "NCP51460SN33T1G" H 3950 2424 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4150 1850 50  0001 C CNN
F 3 "" H 4150 1850 50  0001 C CNN
	1    3950 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0126
U 1 1 5EEA2B6D
P 3200 2050
F 0 "#PWR0126" H 3200 1900 50  0001 C CNN
F 1 "+5V" H 3215 2223 50  0000 C CNN
F 2 "" H 3200 2050 50  0001 C CNN
F 3 "" H 3200 2050 50  0001 C CNN
	1    3200 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EEA3388
P 3200 2350
AR Path="/5EEA3388" Ref="C?"  Part="1" 
AR Path="/5E8C5A93/5EEA3388" Ref="C?"  Part="1" 
AR Path="/5EBFD376/5EEA3388" Ref="C68"  Part="1" 
AR Path="/5F1FECAE/5EEA3388" Ref="C11"  Part="1" 
F 0 "C11" H 3315 2487 50  0000 L CNN
F 1 "100n" H 3315 2396 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3238 2200 50  0001 C CNN
F 3 "~" H 3200 2350 50  0001 C CNN
F 4 "25V" H 3315 2305 50  0000 L CNN "Value2"
F 5 "X7R" H 3315 2214 50  0000 L CNN "Value3"
	1    3200 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5EEA3712
P 4700 2350
AR Path="/5EEA3712" Ref="C?"  Part="1" 
AR Path="/5E8C5A93/5EEA3712" Ref="C?"  Part="1" 
AR Path="/5EBFD376/5EEA3712" Ref="C69"  Part="1" 
AR Path="/5F1FECAE/5EEA3712" Ref="C12"  Part="1" 
F 0 "C12" H 4850 2500 50  0000 L CNN
F 1 "100n" H 4850 2400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4738 2200 50  0001 C CNN
F 3 "~" H 4700 2350 50  0001 C CNN
F 4 "16V" H 4850 2300 50  0000 L CNN "Value2"
F 5 "X7R" H 4850 2200 50  0000 L CNN "Value3"
	1    4700 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0142
U 1 1 5EEA6E32
P 3950 2600
F 0 "#PWR0142" H 3950 2350 50  0001 C CNN
F 1 "GND" H 3955 2427 50  0000 C CNN
F 2 "" H 3950 2600 50  0001 C CNN
F 3 "" H 3950 2600 50  0001 C CNN
	1    3950 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2050 3200 2150
Wire Wire Line
	3200 2150 3550 2150
Wire Wire Line
	3200 2150 3200 2200
Connection ~ 3200 2150
Wire Wire Line
	3200 2500 3200 2550
Wire Wire Line
	3200 2550 3950 2550
Wire Wire Line
	3950 2550 3950 2600
Wire Wire Line
	3950 2550 3950 2450
Connection ~ 3950 2550
Wire Wire Line
	4700 2550 4700 2500
Wire Wire Line
	4350 2150 4700 2150
Wire Wire Line
	4700 2150 4700 2200
Connection ~ 4700 2150
Wire Wire Line
	3950 2550 4700 2550
Wire Wire Line
	6000 3100 6000 2150
Wire Wire Line
	4700 2150 5350 2150
Wire Wire Line
	5350 2150 5350 2200
Wire Wire Line
	4700 2550 5350 2550
Wire Wire Line
	5350 2550 5350 2500
Connection ~ 4700 2550
Wire Wire Line
	5350 2150 6000 2150
Connection ~ 5350 2150
$Comp
L power:GND #PWR010
U 1 1 5F24968B
P 6000 4200
F 0 "#PWR010" H 6000 3950 50  0001 C CNN
F 1 "GND" H 6005 4027 50  0000 C CNN
F 2 "" H 6000 4200 50  0001 C CNN
F 3 "" H 6000 4200 50  0001 C CNN
	1    6000 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4200 6000 4100
Text GLabel 7950 3450 2    50   Input ~ 0
ADC_SPI_CS
Text GLabel 7950 3550 2    50   Input ~ 0
ADC_SPI_SCK
Text GLabel 7950 3650 2    50   Output ~ 0
ADC_SPI_MISO
Text GLabel 7950 3750 2    50   Input ~ 0
ADC_SPI_MOSI
$Comp
L power:+3.3VA #PWR09
U 1 1 5F24C792
P 5350 2050
F 0 "#PWR09" H 5350 1900 50  0001 C CNN
F 1 "+3.3VA" H 5365 2223 50  0000 C CNN
F 2 "" H 5350 2050 50  0001 C CNN
F 3 "" H 5350 2050 50  0001 C CNN
	1    5350 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2050 5350 2150
Text Notes 3150 1500 0    50   ~ 0
Precision voltage regulator can provide up to 20mA.
Text GLabel 2750 3350 0    50   UnSpc ~ 0
BATTERY+
Text Notes 1550 3200 0    50   ~ 0
Battery maximum voltage is 8x2V (with margin) = 16V.\nThis voltage divider outputs 3.4V at Vcc = 16V.
$Comp
L Device:R R3
U 1 1 5F252511
P 2850 3600
F 0 "R3" H 2920 3691 50  0000 L CNN
F 1 "10K" H 2920 3600 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 2780 3600 50  0001 C CNN
F 3 "~" H 2850 3600 50  0001 C CNN
F 4 "1%" H 2920 3509 50  0000 L CNN "Value2"
	1    2850 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F25294F
P 2850 4000
F 0 "R4" H 2920 4091 50  0000 L CNN
F 1 "2.7K" H 2920 4000 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 2780 4000 50  0001 C CNN
F 3 "~" H 2850 4000 50  0001 C CNN
F 4 "1%" H 2920 3909 50  0000 L CNN "Value2"
	1    2850 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 3350 2850 3350
Wire Wire Line
	2850 3350 2850 3450
$Comp
L power:GND #PWR011
U 1 1 5F2551E4
P 2850 4250
F 0 "#PWR011" H 2850 4000 50  0001 C CNN
F 1 "GND" H 2855 4077 50  0000 C CNN
F 2 "" H 2850 4250 50  0001 C CNN
F 3 "" H 2850 4250 50  0001 C CNN
	1    2850 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4250 2850 4150
Wire Wire Line
	2850 3750 2850 3800
Wire Wire Line
	2850 3800 4500 3800
Wire Wire Line
	4500 3800 4500 3400
Wire Wire Line
	4500 3400 5500 3400
Connection ~ 2850 3800
Wire Wire Line
	2850 3800 2850 3850
$Comp
L Device:R R5
U 1 1 5F258418
P 3700 5050
F 0 "R5" H 3770 5141 50  0000 L CNN
F 1 "10K" H 3770 5050 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 3630 5050 50  0001 C CNN
F 3 "~" H 3700 5050 50  0001 C CNN
F 4 "1%" H 3770 4959 50  0000 L CNN "Value2"
	1    3700 5050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR012
U 1 1 5F259335
P 3700 4800
F 0 "#PWR012" H 3700 4650 50  0001 C CNN
F 1 "+3.3VA" H 3715 4973 50  0000 C CNN
F 2 "" H 3700 4800 50  0001 C CNN
F 3 "" H 3700 4800 50  0001 C CNN
	1    3700 4800
	1    0    0    -1  
$EndComp
Text Notes 2150 5250 0    50   ~ 0
Voltage divider maximum drawn\ncurrent is 3.3V/10000 = 330uA.
Wire Wire Line
	3700 4900 3700 4800
Wire Wire Line
	3700 5250 5050 5250
Wire Wire Line
	5050 5250 5050 3800
Wire Wire Line
	5050 3800 5500 3800
Connection ~ 3700 5250
Wire Wire Line
	3700 5250 3700 5200
$Comp
L Device:R_Pack04 RN1
U 1 1 5F207575
P 7450 3650
F 0 "RN1" V 7033 3650 50  0000 C CNN
F 1 "R_Pack04" V 7124 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_Array_Convex_4x1206" V 7725 3650 50  0001 C CNN
F 3 "~" H 7450 3650 50  0001 C CNN
F 4 "MP000987" V 7450 3650 50  0001 C CNN "Value2"
F 5 "Multicomp" V 7450 3650 50  0001 C CNN "Manufacturer"
	1    7450 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	6700 3700 6850 3700
Wire Wire Line
	6850 3700 6850 3650
Wire Wire Line
	6850 3650 7250 3650
Wire Wire Line
	6950 3800 6950 3750
Wire Wire Line
	6950 3750 7250 3750
Wire Wire Line
	6700 3800 6950 3800
Wire Wire Line
	6700 3500 6850 3500
Wire Wire Line
	6850 3500 6850 3550
Wire Wire Line
	6850 3550 7250 3550
Wire Wire Line
	6700 3400 6950 3400
Wire Wire Line
	6950 3400 6950 3450
Wire Wire Line
	6950 3450 7250 3450
Wire Wire Line
	7650 3750 7950 3750
Wire Wire Line
	7650 3650 7950 3650
Wire Wire Line
	7650 3550 7950 3550
Wire Wire Line
	7650 3450 7950 3450
Text GLabel 3650 5450 0    50   UnSpc ~ 0
FRONT_BOARD_LDR
Wire Wire Line
	3700 5450 3650 5450
Wire Wire Line
	3700 5250 3700 5450
$EndSCHEMATC
