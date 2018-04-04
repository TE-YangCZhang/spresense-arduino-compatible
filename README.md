# Welcome to SPRESENSE libs for Arduino compatible project

Clone this repository and update submodules.

```
$ git clone --recursive git@github.com:sonydevworld/spresense-arduino-compatible.git
```

After repositories cloned, each submodules are in 'Detached HEAD'.
So you must checkout master before you getting started.
If you want to all of repository into master, just type like this.

```
$ git submodule foreach git checkout master
```

# Submodules

```
- spresense-core-lib     - SPRESENSE Arduino core library sources
- spresense-prebuilt-sdk - SPRESENSE SDK header and libraries
- spresense-tools        - SPRESENSE Arduino flash tools
- spresense-sketches     - SPRESENSE Arduino sample sketches
- gcc-arm-none-eabi      - Gcc compile tool
```

# Directory structure

```
spresense-arduino-compatible
|-- Arduino15
|   |-- packages/SPRESENSE           - SPRESENSE packages
|   |   |-- hardware
|   |   |   `--spresense             - SPRESENSE reference board codes
|   |   |      `-- 1.0.0
|   |   |          |-- cores
|   |   |          |-- libraries
|   |   |          `-- variants
|   |   `-- tools                    - Necessary tool chain and prebuilt binaries
|   |       |-- spresense-tools      - SPRESENSE tools
|   |       |   `-- 1.0.0
|   |       |-- spresense-sdk        - SPRESENSE SDK prebuilt binaries
|   |       |   `-- 2.2
|   |       `-- gcc-arm-none-eabi    - GCC compiler
|   |           `-- 5.4.1
|   `-- package_spresense_index.json - Arduino IDE configuration json file
|-- sketches                         - Sample Arduino sketches
|   `-- spresense
`-- tools                            - Import/Export tools
```

# How to use
## Import local SDK build

```
./tools/prepare_arduino.sh -H <Arduino IDE Host> -S <SDK build root> -p
```

### Options

| Option | Argument                   | Note                                |
|-------:|:---------------------------|:------------------------------------|
| -H     | Windows or Linux64 or Mac  | Arduino IDE Host OS                 |
| -S     | path/to/spresense-sdk-path | Local Spresense SDK build root path |
| -p     | -                          | Private access option               |

# Tools

Import/Export, download tools instructions are documented at [tools directory].

# Creating platform specific packages

To create a platform specific package for installation simply type:

```
make packages           - will create packages for all platforms
```

This command will generate the following files:

```
spresense-arduino-linux.zip
spresense-arduino-macosx.zip
spresense-arduino-windows.zip
```
