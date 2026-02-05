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





# Building
This project in built using [PlatformIO](https://platformio.org/) so install it.

## compiling the firmware
```
pio run -e uno
```


## uploading
```
pio run -e uno -t upload
```


## compile_commands.json
```
pio run -t compiledb -e uno
```


# Hardware
## Schematic
[Schematic](https://simple-circuit.com/wp-content/uploads/2018/01/arduino-sensorless-brushless-dc-motor-control-diy-esc.png)

## Resources
- [Code stolen from](https://simple-circuit.com/arduino-sensorless-bldc-motor-controller-esc/)
- [SimpleFOCMini - example](https://docs.simplefoc.com/mini_example)
- [Arduino-FOC github](https://github.com/simplefoc/Arduino-FOC/tree/master)
