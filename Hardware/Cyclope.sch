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
$Comp
L Supply_Part:Supply_Part M?
U 1 1 5F27E4DF
P 1200 6400
AR Path="/5F22814A/5F27E4DF" Ref="M?"  Part="1" 
AR Path="/5F27E4DF" Ref="M2"  Part="1" 
F 0 "M2" H 1428 6446 50  0000 L CNN
F 1 "FS5113R" H 1428 6355 50  0000 L CNN
F 2 "Supply_Part:Supply_Part" H 1200 6400 50  0001 C CNN
F 3 "" H 1200 6400 50  0001 C CNN
F 4 "Manufacturer" H 1200 6400 50  0001 C CNN "Value2"
	1    1200 6400
	1    0    0    -1  
$EndComp
$Comp
L Supply_Part:Supply_Part M?
U 1 1 5F28128C
P 1200 6100
AR Path="/5F22814A/5F28128C" Ref="M?"  Part="1" 
AR Path="/5F28128C" Ref="M1"  Part="1" 
F 0 "M1" H 1428 6146 50  0000 L CNN
F 1 "FS5113R" H 1428 6055 50  0000 L CNN
F 2 "Supply_Part:Supply_Part" H 1200 6100 50  0001 C CNN
F 3 "" H 1200 6100 50  0001 C CNN
F 4 "Feetech" H 1200 6100 50  0001 C CNN "Manufacturer"
	1    1200 6100
	1    0    0    -1  
$EndComp
$Comp
L Supply_Part:Supply_Part M?
U 1 1 5F281D4B
P 2200 6100
AR Path="/5F22814A/5F281D4B" Ref="M?"  Part="1" 
AR Path="/5F281D4B" Ref="MP1"  Part="1" 
F 0 "MP1" H 2428 6146 50  0000 L CNN
F 1 "FS5103R-W" H 2428 6055 50  0000 L CNN
F 2 "Supply_Part:Supply_Part" H 2200 6100 50  0001 C CNN
F 3 "" H 2200 6100 50  0001 C CNN
F 4 "Feetech" H 2200 6100 50  0001 C CNN "Manufacturer"
F 5 "Wheel" H 2200 6100 50  0001 C CNN "Value2"
	1    2200 6100
	1    0    0    -1  
$EndComp
$Comp
L Supply_Part:Supply_Part M?
U 1 1 5F2828BE
P 2200 6400
AR Path="/5F22814A/5F2828BE" Ref="M?"  Part="1" 
AR Path="/5F2828BE" Ref="MP2"  Part="1" 
F 0 "MP2" H 2428 6446 50  0000 L CNN
F 1 "FS5103R-W" H 2428 6355 50  0000 L CNN
F 2 "Supply_Part:Supply_Part" H 2200 6400 50  0001 C CNN
F 3 "" H 2200 6400 50  0001 C CNN
F 4 "Feetech" H 2200 6400 50  0001 C CNN "Manufacturer"
F 5 "Wheel" H 2200 6400 50  0001 C CNN "Value2"
	1    2200 6400
	1    0    0    -1  
$EndComp
$Comp
L Supply_Part:Supply_Part MP?
U 1 1 5F283565
P 3200 6100
AR Path="/5F22814A/5F283565" Ref="MP?"  Part="1" 
AR Path="/5F283565" Ref="MP3"  Part="1" 
F 0 "MP3" H 3428 6146 50  0000 L CNN
F 1 "ASB01" H 3428 6055 50  0000 L CNN
F 2 "Supply_Part:Supply_Part" H 3200 6100 50  0001 C CNN
F 3 "" H 3200 6100 50  0001 C CNN
F 4 "Servomotor support" H 3200 6100 50  0001 C CNN "Value2"
F 5 "https://www.gotronic.fr/art-support-de-servos-asb01-11637.htm" H 3200 6100 50  0001 C CNN "PurchaseLink"
	1    3200 6100
	1    0    0    -1  
$EndComp
$Comp
L Supply_Part:Supply_Part MP?
U 1 1 5F283D48
P 3200 6400
AR Path="/5F22814A/5F283D48" Ref="MP?"  Part="1" 
AR Path="/5F283D48" Ref="MP4"  Part="1" 
F 0 "MP4" H 3428 6446 50  0000 L CNN
F 1 "ASB01" H 3428 6355 50  0000 L CNN
F 2 "Supply_Part:Supply_Part" H 3200 6400 50  0001 C CNN
F 3 "" H 3200 6400 50  0001 C CNN
F 4 "Servomotor support" H 3200 6400 50  0001 C CNN "Value2"
F 5 "https://www.gotronic.fr/art-support-de-servos-asb01-11637.htm" H 3200 6400 50  0001 C CNN "PurchaseLink"
	1    3200 6400
	1    0    0    -1  
$EndComp
$Sheet
S 2500 4000 1500 1450
U 5F288D93
F0 "Camera_Board" 50
F1 "Camera_Board.sch" 50
$EndSheet
$EndSCHEMATC
