![](https://github.com/RICCIARDI-Adrien/Cyclope/workflows/Buildroot%20build/badge.svg)
![](https://github.com/RICCIARDI-Adrien/Cyclope/workflows/PC%20application%20build/badge.svg)

# Cyclope

A little robot powered by a Raspberry Pi 3 A+ and featuring a 8MPixel Raspberry Pi Camera V2.  
A fast WiFi connection allows to remote control the robot while displaying camera real-time full HD video stream.

## Hardware

PCB has been designed using KiCad 5.1.5. All manufacturing files are available from [Release](https://github.com/RICCIARDI-Adrien/Cyclope/releases) page.  
A PDF version of the schematic is also provided.

## Software

Robot's Raspberry Pi is powered by a tailored [Buildroot](https://buildroot.org) Linux distribution.

### Getting sources

Clone the repository and the submodules all in the row :
```
git clone --recurse-submodules https://github.com/RICCIARDI-Adrien/Cyclope
```

### Building

Enter repository directory, clean previous build (if needed) and generate image :
```
cd Cyclope/Software/Raspberry_Pi/buildroot
make distclean
make BR2_EXTERNAL=$(realpath ..)/cyclope cyclope_defconfig
make
```

Generated image to burn to a SD card is `Cyclope/Software/Raspberry_Pi/buildroot/output/images/sdcard.img`.

## Mechanical

Chassis is made of two overlaid 3mm-thick steel plates.  
See [Mechanical_Dimensions.odg](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Chassis/Mechanical_Dimensions.odg) file for additional design information.  
Provide the `Chassis.dxf` file from [Release](https://github.com/RICCIARDI-Adrien/Cyclope/releases) page to a metal laser cutting service.

## Supply parts

See `Bill_Of_Material.csv` file from [Release](https://github.com/RICCIARDI-Adrien/Cyclope/releases) page for PCB parts. All other needed mechanical and electrical parts are listed below.

### Electrical

* 2x servomotor : [Feetech FS5113R](https://www.gotronic.fr/art-servomoteur-fs5113r-25841.htm)
* 40-pin flat cable : [Amphenol FC40150-0](https://fr.farnell.com/amphenol/fc40150-0/cordon-2-54mm-f-f-150mm-40voies/dp/2217617)
* Battery holder : [EM8](https://www.gotronic.fr/art-coupleur-8-piles-lr6-em8-5718.htm), isolate apparent contacts but battery holder ones with adhesive tape to prevent them from touching chassis spacers

### Mechanical

* Front castor wheel : [Guitel 55031100](https://fr.rs-online.com/web/p/roulettes-industrielles/3064300)
* 2x servomotor support : [ASB01](https://www.gotronic.fr/art-support-de-servos-asb01-11637.htm)
* 2x servomotor wheel : [FS5103R-W](https://www.gotronic.fr/art-roue-pour-servomoteur-fs5103r-25857.htm)
* 2x front board flat angle bracket : NFLE2012-20
* 21x chassis plates spacer : [Ettinger 05.04.401](https://fr.farnell.com/ettinger/05-04-401/entretoise-m4x40-vzk/dp/1466794)
* TODO

## Photo gallery

### Castor wheel

![Castor wheel](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Castor_Wheel.jpg)

### Servomotor, wheel and support

![Servomotor, wheel and support](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Servomotor_And_Parts.jpg)

### Chassis

![Chassis plates](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Chassis_Plates.jpg)
![Assembled wheels 1](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Wheels_1.jpg)
![Assembled wheels 2](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Wheels_2.jpg)
![Assembled chassis bottom 1](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Chassis_Bottom_1.jpg)
![Assembled chassis bottom 2](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Chassis_Bottom_2.jpg)

### PCB

![Naked PCB top](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Naked_PCB_Top.jpg)
![Naked PCB bottom](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Naked_PCB_Bottom.jpg)

### Motherboard

PCB has been soldered by hands (resistors array part was missing, I used normal 0805 resistors) :
![Assembled motherboard PCB top](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Motherboard_PCB_Top.jpg)
![Assembled motherboard PCB bottom](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Motherboard_PCB_Bottom.jpg)

A big capacitor has been added to keep battery voltage stable when a lot of current is required :
![Motherboard PCB with big capacitor](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Motherboard_PCB_With_Big_Capacitor.jpg)

### Front board

![Assembled front board PCB top](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Front_Board_PCB_Top.jpg)
![Assembled front board PCB bottom](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Assembled_Front_Board_PCB_Bottom.jpg)

With Raspberry Pi Camera V2 mounted :
![Front board with camera](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Front_Board_With_Camera.jpg)

### Assembled electronic boards

![Electronic boards 1](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Electronic_Boards_1.jpg)
![Electronic boards 2](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Electronic_Boards_2.jpg)
![Electronic boards 3](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Electronic_Boards_3.jpg)
![Electronic boards 4](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Electronic_Boards_4.jpg)
![Electronic boards 5](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Electronic_Boards_5.jpg)

### Assembled robot

![Robot front rotated](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Robot_Front_Rotated.jpg)
![Robot bottom rotated](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Robot_Bottom_Rotated.jpg)
![Robot front](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Robot_Front.jpg)
![Robot bottom](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Robot_Bottom.jpg)
![Robot left side](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Robot_Left_Side.jpg)
![Robot right side](https://github.com/RICCIARDI-Adrien/Cyclope/blob/master/Resources/Pictures/Robot_Right_Side.jpg)
