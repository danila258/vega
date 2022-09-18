# Vega
A cross-platform scheduling application for MIREA students which works on desktop and in the future mobile devices.


<p align="center">
  <img src = "https://drive.google.com/uc?export=view&id=1MFjsYxMI363i4cZwvsMLhhjbxnVtxekB" width=350>
  <img src = "https://drive.google.com/uc?export=view&id=1ae52CZgoTDfw9CzMq-MFeAtHAjqUskTM" width=350>
</p>


## Table of Contents
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Build](#build)
* [License](#license)


## Technologies Used
- Qt 6.2.4 LTS
- C++17
- CMake 3.5


## Features
List the ready features here:
- Cross platform
- Automatic schedule update
- Offline work
- Dark theme
- Horizontal and vertical orientation


## Build
Fork the repository and open it in Qt Creator.
If you use Linux, in order to install the application icon, you need:
1. Build the application and move the resulting binary file to the `/usr/bin/`.
2. From `Vega/Resources/VegaIcon/Linux/` move `Vega.svg` to `/usr/share/icons/hicolor/scalable/apps/` 
   and `vega.desktop` to `/usr/share/applications/` this requires superuser rights.
3. Run Vega from `/usr/bin/`.


## License
LGPL
