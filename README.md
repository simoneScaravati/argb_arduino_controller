<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">project_title</h3>

  <p align="center">
    project_description
    <br />
    <a href="https://github.com/github_username/repo_name"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/github_username/repo_name">View Demo</a>
    ·
    <a href="https://github.com/github_username/repo_name/issues">Report Bug</a>
    ·
    <a href="https://github.com/github_username/repo_name/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>





_Transform a cheap USB soldering iron in a powerfull Active tip Soldering Station._


**With almost no thermal capacity this station regulates the tip's temperature instantaneously. Solder larger thermal mass with ease, it's magic.**

_fiy: Active Soldering irons cost a lot of money_



*The cheapest Micro soldering Station ever:*


![BOX](https://github.com/peekpt/MicroSolderingStation/raw/master/media/DSCF9575.JPG)

![BOX](https://github.com/peekpt/MicroSolderingStation/raw/master/media/box.png)

## Youtube

[![YOUTUBE overview](https://img.youtube.com/vi/iJwf-qWp4lI/0.jpg)](https://www.youtube.com/watch?v=iJwf-qWp4lI)


[![YOUTUBE performance](https://img.youtube.com/vi/kRIv3psVogc/0.jpg)](https://www.youtube.com/watch?v=kRIv3psVogc)





## Features

- Cheap & easy build under 10$
- Temperature controled (PID)
- Memories
- Micro soldering tip
- Serial command interface
- Ploter (outputs usefull data) 
- Great User Interface with output power Bargraph
- UI Sounds, with temperature reached warning.
- Open Source Arduino based
- Firmware Updates
- 3D Printed Case
- Wake up from standby iron pickup detection (by temperature sensing)

## Materials

- 1x Arduino Uno
- 1x Nokia LCD Module
- 1x USB Soldering Iron
- 1x Thermistor 100k 3950
- 1x 4 wire wire cable(usb cable works)
- 1x 5mm Led
- 2x 1k resistor
- 1x 4,7k resitor
- 1x 10n Capacitor
- Kapton tape 10-20mm
- 1x N MosFet (or use the Iron's pcb one)
- 1x rocker switch
- 10 x small screws 2.5x5mm large head

## Schematic

![Schematic](https://raw.githubusercontent.com/peekpt/MicroSolderingStation/master/media/schematic.png)



## Soldering Tip Diagram
![Diagram](https://github.com/peekpt/MicroSolderingStation/raw/master/media/soldering%20tip.png)

## UNO R3 CH340 Power Hack
![BOX](https://github.com/peekpt/MicroSolderingStation/raw/master/media/UNO%20CH340%20hack.jpg)

_Cut Power the trace underneath the PCB and connect a rocker switch in series._

## Fritzing
![Fritzing](https://github.com/peekpt/MicroSolderingStation/raw/master/media/fritzing_bb.png)

Remove the pcb from the soldering iron and grab a cable with 4 wires (2 for thermistor, 2 for the heater).
Poke an hole in the side of the iron's case, near the yellow nut, to pass the 2 wires and solder them to the thermistor.
Use kapton tape to isolate the thermistor pins and to fix the thermistor's glass tip to the iron end with some kapton turns.
The other 2 wires connect to the heater and the led with a resistor in series. (watch the polarity of the led)
Remove the ball bearing and connect the led in the hole, break the spring post from the other side of the case.


## User Interface Screenshots
![UNO](https://github.com/peekpt/MicroSolderingStation/raw/master/media/interface_small.png)


## Operation

**main view**

- \< >                   temp up down
- [click]                cycle memories
- [click & hold]         store mem mode
- [double click]         settings mode

**stand by mode**
- [click]                  leave standby mode

**store mem**
- \< >                   select memory to store
- [click]                store

**settings mode submenus**
 - \< >                   navigate submenus
 - [click]                edit submenu

**edit submenu**
- \< >                   change value up down
- [click]                exit submenu

## ChangeLog

2018-4-11

- interfance feedback sounds, you can disable on settings
- temperature reached beep 

2018-4-9

- improved automatic pickup detection (must be more improved in the future)
- you can now choose the type of wake up from standby between manual (by clicking) or automatic (by temperature) 



## Parts & Modules ##

100k thermistor (3950):


![](https://github.com/peekpt/MicroSolderingStation/raw/master/media/thermistor_100k_3950.jpg)


Arduino Uno R3 ch340:


![](https://github.com/peekpt/MicroSolderingStation/raw/master/media/uno_r3_ch340.jpg)


Rotary Encoder:


![](https://github.com/peekpt/MicroSolderingStation/raw/master/media/rotary_encoder.jpg)

USB Soldering Iron:


![](https://github.com/peekpt/MicroSolderingStation/raw/master/media/soldering_iron.jpg)

LCD:


![](https://github.com/peekpt/MicroSolderingStation/raw/master/media/lcd.jpg)

Switch:


![](https://github.com/peekpt/MicroSolderingStation/raw/master/media/rocker_switch.jpg)


















