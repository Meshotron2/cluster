# Meshotron Raspberry Pi Research
### Raspberry Pi Models Relevant specs
- [Raspberry Pi 4 Model B](https://datasheets.raspberrypi.com/rpi4/raspberry-pi-4-datasheet.pdf)
    - Quad core Cortex-A72 (ARM v8) 64-bit SoC @ 1.5GHz
    - 2/4/8 GB LPDDR4-3200 SDRAM (depending on model)
    - 2 USB 3.0 ports
    - 2 USB 2.0 ports
    - 2.4 GHz and 5.0 GHz IEEE 802.11ac wireless
    - Gigabit Ethernet
    - 40 pin GPIO header
    - Up to 6x UART
    - Up to 6x I2C
    - Up to 5x SPI
- Raspberry Pi 3 Model B+
    - Cortex-A53 (ARMv8) 64-bit SoC @ 1.4GHz
    - 1GB LPDDR2 SDRAM
    - 4 USB 2.0 ports
    - 2.4GHz and 5GHz IEEE 802.11.b/g/n/ac wireless LAN
    - Gigabit Ethernet over USB 2.0 (maximum throughput 300 Mbps)
    - 40-pin GPIO header
    - Up to 2x Uart
- Raspberry Pi 1 Model B+
    - 700 MHz ARM11 processor
    - 512 MB of RAM
    - 4 USB 2.0 ports
    - 40-pin GPIO header
    - 100 Base Ethernet 
    - Up to 2x Uart
- Raspberry Pi Pico
    - Dual-core Arm Cortex-M0+ processor, flexible clock running up to 133 MHz
    - 264KB on-chip SRAM
    - 26 multifunction GPIO pins, including 3 analogue inputs
    - 2 × UART, 2 × SPI controllers, 2 × I2C controllers, 16 × PWM channels
    - 1 × USB 1.1 controller and PHY, with host and device support
    - 8 × Programmable I/O (PIO) state machines for custom peripheral 
- Raspberry Pi Zero 2 W
    - 1GHz quad-core 64-bit Arm Cortex-A53 CPU
    - 512MB SDRAM
    - 2.4GHz 802.11 b/g/n wireless LAN
    - HAT-compatible 40-pin header footprint (unpopulated)
    - Can't find UART/I2C info on this model. Only stuff from the RPi Zero W appears

## Cluster Nodes Communication Methods
#### SPIO
- Needs [2 pins](https://forums.raspberrypi.com/viewtopic.php?t=255907) for each connected RPi. Make our own protocol? More signals?
#### UART (Serial)
- Viable on the 4 b since it has up to 6 UARTS
- Helpfull info [here](https://forums.raspberrypi.com/viewtopic.php?t=244827) and [here](https://forums.raspberrypi.com/viewtopic.php?t=105995)
#### SPI
- Needs more research
#### I2C
- Apparently the RPi 4 can act as an I2C [slave](https://forums.raspberrypi.com/viewtopic.php?t=265832) so seems also possible. Although not sure how many slave pins there are...
#### USB
- [Sigh](https://stackoverflow.com/questions/53876665/connect-two-raspberry-pis-using-usb-cable-or-usb-serial)
- To my limited understanding not easy and since the RPi shares 1 interface with it's USB ports and Ethernet so might as well just use that instead
#### Wi-Fi
- Allows for communication between all RPi although each RPi would only communicate with its "neighbours"
- Too much latency? Probably not
- Easy connection
- No cable mess
- Used [here](https://projects.raspberrypi.org/en/projects/build-an-octapi/8)
#### Ethernet
- All in one network but each one only communicates with its "neighbours"
- Not very messy (8 ethernet cables (9 to connect to master) + 1 switch) 
- Wi-Fi but faster and with less latency
- Used [here](https://www.youtube.com/watch?v=H2rTecSO0gk)

Rasbpberry Pi specs from [here](https://www.raspberrypi.org/)
Usefull [link](https://pinout.xyz/#)