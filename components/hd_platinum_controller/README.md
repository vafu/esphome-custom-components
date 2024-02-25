# HD Platinum Controller

This is a custom component utilizing an ESP32 and an nrf24l01. The component exposes on/off switches for up to 8 shade groups as well as an "all" group. You can then use these switches with [Template Covers](https://esphome.io/components/cover/template.html) to set up shade automation.

Note that the HD Platinum protocol is unidirectional so position reporting isn't a thing. Your shades positions will need to be assumed and if they are manually controlled they will get out of sync.

## Hardware

You'll need an ESPHome support micro and an nrf24l01 2.4ghz module. Places like Sparkfun, Adafruit, ebay all sell these.

I used a Sparkfun ESP32 MicroMod, carrier board, and Mikrobus nrf24l1 module during prototyping.

## Remote ID
I have not yet implemented the ability to sniff the remote id

## Configuration

```yaml
# https://esphome.io/components/external_components.html?highlight=external_components
external_components:
  - source:
      type: git
      url: https://github.com/wingrunr21/esphome-custom-components
      ref: main
    components: [hd_platinum_controller]
 
spi:
  clk_pin: 18
  mosi_pin: 23
  miso_pin: 19

# Pin D1 on the ESP32 is connected to RST on the MikroBus
# See https://learn.sparkfun.com/tutorials/micromod-mikrobus-carrier-board-hookup-guide/hardware-overview
# and https://learn.sparkfun.com/tutorials/micromod-esp32-processor-board-hookup-guide/hardware-overview
# CE pin = 27; // This is D1 (ESP32 Pin 27) for Chip Enable
# CS pin = 5;  // This is GPIO5 (ESP32 Pin 5) for Chip Select
# IRQ pin = 4; // This is I2C_INT (ESP32 Pin 4) for I2C Interrupt
#
# Change these pins as needed for your setup!
hd_platinum_controller:
  id: hunter_douglas_platinum_controller
  remote_id: 0x14EC # you have to get this by sniffing an existing remote
  ce_pin: 27
  cs_pin: 5
  irq_pin: 4

switch:
  platform: hd_platinum_controller
  switches:
    - name: "Hunter Douglas Platinum - Group 1"
      group: 1
      id: hd_platinum_group_1
      internal: true
    - name: "Hunter Douglas Platinum - Group 2"
      group: 2
      id: hd_platinum_group_2
      internal: true
    - name: "Hunter Douglas Platinum - Group 3"
      group: 3
      id: hd_platinum_group_3
      internal: true
    - name: "Hunter Douglas Platinum - Group 4"
      group: 4
      id: hd_platinum_group_4
      internal: true
    - name: "Hunter Douglas Platinum - All"
      group: 0xff
      id: hd_platinum_group_all
      internal: true
cover:
  - platform: template
    name: "My Shades"
    open_action:
      - switch.turn_off: hd_platinum_group_1
    close_action:
      - switch.turn_on: hd_platinum_group_1
    stop_action:
      - switch.toggle: hd_platinum_group_1
    assumed_state: true # manual control is still possible
```

## Special Thanks
This work is based off the investigation done by folks over in the Arduino forums:

* [gpduino's protocol investigation](https://forum.arduino.cc/t/nrf24l01-hack-on-hunter-douglas-shades/676940/32)
* [zergraph's proof of concept sketch](https://forum.arduino.cc/t/esp8266-and-nrf24l01-hunter-douglas-platinum-remote/918887)
