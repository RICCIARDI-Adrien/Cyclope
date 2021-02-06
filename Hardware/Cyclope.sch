EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 6
Title "Main page"
Date "2021-02-05"
Rev "1.1"
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
S 2500 4000 1500 1500
U 5F288D93
F0 "Front_Board" 50
F1 "Front_Board.sch" 50
$EndSheet
$Comp
L Mechanical:MountingHole_Pad H7
U 1 1 5F3532F6
P 2050 6800
F 0 "H7" H 2150 6849 50  0000 L CNN
F 1 "Motherboard" H 2150 6758 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 2050 6800 50  0001 C CNN
F 3 "~" H 2050 6800 50  0001 C CNN
	1    2050 6800
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H8
U 1 1 5F353CDE
P 2750 6800
F 0 "H8" H 2850 6849 50  0000 L CNN
F 1 "Motherboard" H 2850 6758 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 2750 6800 50  0001 C CNN
F 3 "~" H 2750 6800 50  0001 C CNN
	1    2750 6800
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H9
U 1 1 5F35418A
P 3450 6800
F 0 "H9" H 3550 6849 50  0000 L CNN
F 1 "Motherboard" H 3550 6758 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 3450 6800 50  0001 C CNN
F 3 "~" H 3450 6800 50  0001 C CNN
	1    3450 6800
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H10
U 1 1 5F3543C8
P 4150 6800
F 0 "H10" H 4250 6849 50  0000 L CNN
F 1 "Motherboard" H 4250 6758 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 4150 6800 50  0001 C CNN
F 3 "~" H 4150 6800 50  0001 C CNN
	1    4150 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5F3568FB
P 3100 7000
F 0 "#PWR018" H 3100 6750 50  0001 C CNN
F 1 "GND" H 3105 6827 50  0000 C CNN
F 2 "" H 3100 7000 50  0001 C CNN
F 3 "" H 3100 7000 50  0001 C CNN
	1    3100 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 6900 2050 6950
Wire Wire Line
	2050 6950 2750 6950
Wire Wire Line
	2750 6950 2750 6900
Wire Wire Line
	2750 6950 3100 6950
Wire Wire Line
	3100 6950 3100 7000
Connection ~ 2750 6950
Wire Wire Line
	3100 6950 3450 6950
Connection ~ 3100 6950
Wire Wire Line
	3450 6950 3450 6900
Connection ~ 3450 6950
Wire Wire Line
	4150 6950 4150 6900
Wire Wire Line
	3450 6950 4150 6950
$Sheet
S 5000 4000 1500 1500
U 601E5913
F0 "Lidar" 50
F1 "Lidar.sch" 50
$EndSheet
$EndSCHEMATC
