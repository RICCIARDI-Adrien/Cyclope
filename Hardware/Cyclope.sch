EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title "Main page"
Date "2020-07-27"
Rev "1.0"
Comp "Cyclope robot by Adrien RICCIARDI"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 2500 2000 1500 1500
U 5F1F2F9E
F0 "Power_Supply" 50
F1 "Power_Supply.sch" 50
$EndSheet
$Sheet
S 5000 2000 1500 1500
U 5F22814A
F0 "Raspberry_Pi" 50
F1 "Raspberry_Pi.sch" 50
$EndSheet
$Sheet
S 7500 2000 1500 1500
U 5F1FECAE
F0 "ADC" 50
F1 "ADC.sch" 50
$EndSheet
$Sheet
S 2500 4000 1500 1450
U 5F288D93
F0 "Front_Board" 50
F1 "Front_Board.sch" 50
$EndSheet
$Comp
L Mechanical:MountingHole_Pad H7
U 1 1 5F3532F6
P 6150 5050
F 0 "H7" H 6250 5099 50  0000 L CNN
F 1 "Motherboard" H 6250 5008 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 6150 5050 50  0001 C CNN
F 3 "~" H 6150 5050 50  0001 C CNN
	1    6150 5050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H8
U 1 1 5F353CDE
P 6850 5050
F 0 "H8" H 6950 5099 50  0000 L CNN
F 1 "Motherboard" H 6950 5008 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 6850 5050 50  0001 C CNN
F 3 "~" H 6850 5050 50  0001 C CNN
	1    6850 5050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H9
U 1 1 5F35418A
P 7550 5050
F 0 "H9" H 7650 5099 50  0000 L CNN
F 1 "Motherboard" H 7650 5008 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 7550 5050 50  0001 C CNN
F 3 "~" H 7550 5050 50  0001 C CNN
	1    7550 5050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H10
U 1 1 5F3543C8
P 8250 5050
F 0 "H10" H 8350 5099 50  0000 L CNN
F 1 "Motherboard" H 8350 5008 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 8250 5050 50  0001 C CNN
F 3 "~" H 8250 5050 50  0001 C CNN
	1    8250 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5F3568FB
P 7200 5250
F 0 "#PWR018" H 7200 5000 50  0001 C CNN
F 1 "GND" H 7205 5077 50  0000 C CNN
F 2 "" H 7200 5250 50  0001 C CNN
F 3 "" H 7200 5250 50  0001 C CNN
	1    7200 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5150 6150 5200
Wire Wire Line
	6150 5200 6850 5200
Wire Wire Line
	6850 5200 6850 5150
Wire Wire Line
	6850 5200 7200 5200
Wire Wire Line
	7200 5200 7200 5250
Connection ~ 6850 5200
Wire Wire Line
	7200 5200 7550 5200
Connection ~ 7200 5200
Wire Wire Line
	7550 5200 7550 5150
Connection ~ 7550 5200
Wire Wire Line
	8250 5200 8250 5150
Wire Wire Line
	7550 5200 8250 5200
$EndSCHEMATC
