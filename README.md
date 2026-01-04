<div align=center>

# Drive Controller

Drop in PCB to control the BLDC motor of a Seagate HDD.
<br />
</div>



# Motivation
I want to make a grid of spinning harddrives, so this board will be housing a DRV8313 with some microcontroller. The board will be addressable allowing you to "stack" the harddrives and control them individually.

This repo currently contains some experimentation code trying out the
[SimpleFOCMini](https://docs.simplefoc.com/mini_v1_connect_hardware).
I'm currently trying to understand the driver code and design my own board around it.



# Toolchain setup
## PlatformIO
This project is build using PlatformIO, download it from here [platformio.org](https://platformio.org/)

## pre-commit
```sh
pip install pre-commit
```
## Clang-format
You will probably already have this install if have clang installed.
I downloaded `v19.1.7` from [github](https://github.com/tqfx/clang-format/releases/tag/microsoft%2Fv19.1.7) and installed it in `~/.local/bin`.

# Building

## compiling the firmware
```
pio run build
```

## compile_commands.json
```
pio run -t compiledb
```


## Resources
- [SimpleFOCMini - example](https://docs.simplefoc.com/mini_example)
- [Arduino-FOC github](https://github.com/simplefoc/Arduino-FOC/tree/master)
