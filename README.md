# Cyclope

A little robot powered by a Raspberry Pi 3 A+ and featuring a 8MPixel Raspberry Pi Camera V2.  
A fast WiFi connection allows to remote control the robot while displaying camera real-time full HD video stream.

## Hardware

PCB has been designed using KiCad 5.1.5. All manufacturing files are available from GitHub Release page.

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

As much parts as possible were designed to be cut either from PCB or 3mm-thick steel plate used as chassis, decreasing custom crafted parts amount.  
Remaining electromechanical parts are listed above.

* Front castor wheel : [Guitel 55031100](https://fr.rs-online.com/web/p/roulettes-industrielles/3064300)
* 2x servomotor : [Feetech FS5113R](https://www.gotronic.fr/art-servomoteur-fs5113r-25841.htm)
* 2x servomotor support : [ASB01](https://www.gotronic.fr/art-support-de-servos-asb01-11637.htm)
* 2x servomotor wheel : [FS5103R-W](https://www.gotronic.fr/art-roue-pour-servomoteur-fs5103r-25857.htm)
* 2x front board flat angle bracket : NFLE2012-20
* 21x chassis plates spacer : [Ettinger 05.04.401](https://fr.farnell.com/ettinger/05-04-401/entretoise-m4x40-vzk/dp/1466794)
* TODO
