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
pio run build
```

## compile_commands.json
```
pio run -t compiledb
```


## Resources
- [SimpleFOCMini - example](https://docs.simplefoc.com/mini_example)
- [Arduino-FOC github](https://github.com/simplefoc/Arduino-FOC/tree/master)
