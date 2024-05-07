# Vimsetup

This is my personal script for installing vim on Unix/BSD compliant operating
systems. The main objective is to have a script that can install vim along
with my configuration on any linux and MacOS devices, with no preexisting 
setup and dependencies. 

## Installation

Compiling the make script is necessary. to do so simply run the command in
project root:

```bash
cc build.c -o make
make
```

If any changes is made to build.c recompilation is `not` necessary.

## Usage

Run the binary:
```bash
./vimsetup
```
To install and configure vim.

To simply configure a preexisting installation, run the command:
```bash
./vimsetup --config-only
```

Likewise to install vim without configuration, run the following command:
```bash
./vimsetup --install-only
```

## Notes
All vim configurations files are located at the conf/ directory.
