# Personal QMK Keymap Management

Managing a large repository with numerous keymaps can be quite a hassle, especially when dealing with daily updates and changes that come with synchronizing thousands of keymaps. To keep my keymaps separate and easily manageable, I've developed a simple Makefile script that streamlines the process. This approach is inspired by the ease of use I find in ZMK, which I personally prefer for this purpose.

## Getting Started

### Prerequisites

- [QMK Firmware](https://github.com/qmk/qmk_firmware): Make sure you have the QMK binary on your system.  

### Usage

1. Clone this repository and navigate to its directory.
2. Modify the `USER` variable in the Makefile with your name.
3. Adjust the keyboard name and paths according to your needs:

   - Set `KEYBOARDS` to the names of your keyboards.
   - Update `PATH_KEYBOARD_`*keyboard-name* to the actual path of your keyboard in the QMK Firmware repository.
   - Update `PATH_KEYMAPS_`*keyboard-name* to the keymap path in the QMK Firmware repository.

4. Open your terminal and run the following commands:

   ```bash
   make update      # Initialize submodules
   make keyboard-name # Build and flash keymaps
   make clean       # Clean build artifacts
   ```

## Makefile Description

Here's a breakdown of the Makefile's main targets and their functionalities:

- `all`: This target builds all specified keyboards.
- `keyboard-name`: This target builds for the specified keyboard 
- `clean`: Removes build artifacts and intermediate files.
- `update`: Initializes submodules (useful for fetching external resources).

For each keyboard specified in the `KEYBOARDS` variable:

1. Old symlinks are removed from the QMK Firmware repository.
2. New symlinks are added for the user's keymap.
3. Lint checks and builds are performed with the specified user keymap and keyboard.
4. Temporary symlinks are removed.

Remember to replace the placeholders with actual values according to your setup.

## Notes

This repository and tool are designed to simplify the management of personal keymaps. It's not an extensive program but a small utility to make handling multiple keymaps more convenient.

Feel free to customize and extend this tool according to your preferences and needs. If you have any questions or suggestions, please don't hesitate to reach out.

