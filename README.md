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
cd Cyclope
make -C buildroot distclean
make BR2_EXTERNAL=$(realpath ..)/cyclope cyclope_defconfig
make -C buildroot
```

Generated image to burn to a SD card is `Cyclope/Software/buildroot/output/images/sdcard.img`.

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
