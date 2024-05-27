# A10C UFC Arduino

This directory contains the code for the A10C UFC (Up Front Controller) project. The project is designed to interface with DCS:Worlds A-10C II using an Arduino Nano and the DCS-BIOS over COM. The UFC includes functionality for various buttons and LEDs found on the ingame A10C UFC, such as Master Caution lights that are flashing, or dimming the backlight.

## Table of Contents
- [Project Overview](#project-overview)
- [Demo Video](#demo-video)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Configuration](#configuration)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Project Overview

The A10C UFC project aims to replicate the functionality of the A-10C II UFC using a custom PCB and an Arduino Nano. This project utilizes the DCS-BIOS library to communicate with DCS: World, allowing for realistic control and feedback from the simulation.

## Demo Video

Check out the demo video on YouTube to see the A10C UFC in action:

[![A10C UFC Demo](https://img.youtube.com/vi/IKTZMvRl_7A/0.jpg)](https://www.youtube.com/watch?v=IKTZMvRl_7A)

## Hardware Requirements

- Arduino Micro
- Custom PCB (see [A10C UFC PCB](../pcb))
- LEDs, buttons, and other components as specified in the PCB design

## Software Requirements

- [PlatformIO](https://platformio.org/)
- [DCS-BIOS - Skunkworks Fork](https://github.com/DCS-Skunkworks/dcs-bios)

## Usage
Use Platform.io with an IDE of your choice (e.g. VSCode) and change the COM upload / monitoring ports in the `platformio.ini` file to fit your needs. You can find your COM port in the Windows device manager.
Then press Upload in Platform.IO and you're ready to go.

## Configuration

### Pin Configuration

The pin configuration for the matrix switch and LEDs is defined in the `main.cpp` file. Here is a summary:

- **Row Pins**: 2, 3, 4
- **Column Pins**: 7, 8, 9, 10, 16, 14, 15, 18, 19, 20, 21, 1, 0
- **LED Pins**: 
  - Backlight LED: 5
  - Master Caution LED: 6

### DCS-BIOS Configuration

Ensure you have DCS-BIOS configured to communicate over COM. Adjust the settings in DCS-BIOS as needed to match your setup.

## Usage

### Debug Mode

To enter debug mode, hold down the buttons corresponding to `UFC_1`, `UFC_2`, and `UFC_3` for 3 seconds. In debug mode, you can:

- Toggle the Master Caution LED
- Cycle the backlight intensity
- Print the state of all buttons via Serial monitor

### Main Functionality

The code handles the button presses and LED states based on the matrix configuration. It interfaces with DCS-BIOS to send and receive data, allowing for seamless integration with DCS: World.

## Contributing

Contributions are welcome! If you have improvements or fixes, please fork the repository, make your changes, and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the GNU General Public License v3.0 License. See the [LICENSE](LICENSE) file for details.

---
