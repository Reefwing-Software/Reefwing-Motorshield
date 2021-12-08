# Nexgen Motor Shield Library #

The Nexgen Rover is an Arduino based robot designed wholly by Nexgen Codecamp Pty Ltd. It is used in technology related STEM courses aimed at high schools. The robot is based on Arduino technology and runs an Arduino UNO or Arduino Nano 33 IoT with a motor controller shield/carrier board.

The shield for the UNO and the carrier board for the Nano 33 IoT have a similar design but different headers to match the boards.

This library makes using the Nexgen Motor Shield simple.

### 1.0 Motor Shield Capabilities ###

Both the Nexgen Motor Shield and Carrier Boards utilise the L293B H-bridge and have been designed with the following capabilities:
* Ability to control two bidirectional DC motors for direction and rotation speed.
* An XT-60 connection for the LiPo battery to power the shield and attached Arduino board.
* Reverse polarity protection for the battery connection.
* LED power indication for VCC (i.e., LiPo voltage) and the 5V regulated supply. A separate 5VDC regulator is provided on the shield/carrier board. The 5VDC regulator on the UNO and Nano is not used. Note that the 5VDC regulator output on the Nano 33 IoT is normally not connected to the header pin (unless you bridge the pads on the board). The Nano carrier board also provides power indication for the 3V3 bus. This comes from the 3V3DC regulator on the Nano 33 IoT.
* Voltage monitoring to prevent excessive discharge of the LiPo (needs to be programmed).
* The UNO/Nano reset switch reproduced on the shield.
* Bulk decoupling to reduce low frequency ripple and bypass capacitors to reduce high frequency noise.
* Additional pin headers for GND, 5VDC and 3V3DC (on the Nano Carrier Board).
* Two additional, Signal, 5V and GND headers for use with servo motors or similar.

The L293B chip allows us to control two bidirectional motors with a stall current of up to 2A. It expects an RMS current of 1A. In the L293, motor direction is controlled by the state of two input pins and speed is controlled by applying a PWM signal to the enable pin. This library abstracts that detail away.

To monitor the battery we use a simple voltage divider and the ADC (Analog to Digital Converter) on the Arduino boards. We need a resistive divider because you can't apply more than 5V to an Analog Input on the UNO or 3V3 to the Nano 33 IoT. You can read more about the details of battery monitoring in our article [Designing your own Arduino Motor Shield](https://medium.com/r/?url=https%3A%2F%2Freefwing.medium.com%2Fdesigning-your-own-arduino-uno-motor-shield-ca507ab61f4b).

The Nano 33 IoT carrier board also comes with an on/off switch, which disconnects power from the LiPo battery and a passive piezo electric buzzer. 

### 2.0 Motor Shield Pin Connections ###

**2.1 Arduino UNO R3**

The control pins for Motor 1 (M1) and the pin connections for the UNO (in **bold**) on our shield are:

* **D3**  -  Chip Enable M1
* **D2**  -  M1 Input 1 
* **D4**  -  M1 Input 2 
* M1 Output 1 (to one terminal of M1)
* M1 Output 2 (to the other terminal of M1)

Similarly for Motor 2 (M2):

* **D11**  -  Chip Enable M2
* **D7**   -  M2 Input 3
* **D8**   -  M2 Input 4
* M2 Output 3 (to M2 terminals)
* M2 Output 4 (to M2 terminals)

In addition, we have the following pins connected:

* **D9**   -  Servo 1 (optional Servo Controls or general purpose digital output)
* **D10**  -  Servo 2 (optional Servo Controls or general purpose digital output)
* **A0** -  Voltage Divider output from battery

In total the Nexgen UNO Motor Shield uses **8** Digital Inputs and **1** Analogue Input. The remaining pins are free and available via the stackable header. 

Additional 5V DC and GND header pins are also provided for use with sensors, etc.

**2.2 Arduino Nano 33 IoT**

The control pins for Motor 1 (M1) and the pin connections for the Nano 33 IoT (in **bold**) on our carrier board are:

* **D2**  -  Chip Enable M1
* **D3**  -  M1 Input 1 
* **D4**  -  M1 Input 2 
* M1 Output 1 (to one terminal of M1)
* M1 Output 2 (to the other terminal of M1)

Similarly for Motor 2 (M2):

* **D5**  -  Chip Enable M2
* **D6**   -  M2 Input 3
* **D7**   -  M2 Input 4
* M2 Output 3 (to M2 terminals)
* M2 Output 4 (to M2 terminals)

In addition, we have the following pins connected to headers:

* **D9**   -  Servo 1 (optional Servo Controls or general purpose digital output)
* **D10**  -  Servo 2 (optional Servo Controls or general purpose digital output)
* **D11** - SPI MOSI (not used by carrier board)
* **D12** - SPI MISO (not used by carrier board)
* **D13** - SPI SCK (not used by carrier board)
* **A0** -  Voltage Divider output from battery
* **A2** - Connected to the passive piezo buzzer circuit
* **A4** - I2C SDA (not used by carrier board)
* **A5** - I2C SCL (not used by carrier board)

In total the Nexgen Nano 33 IoT carrier board uses **8** Digital Inputs and **2** Analogue Inputs. The remaining pins are free and available via the stackable header or additional board headers (e.g., the I2C and SPI bus pins). 

Additional 5V DC, 3V3 DC and GND header pins are also provided for use with sensors, etc.

### How to Use the Library ###

The quickest way to learn how to use this library is to look at the examples. Assuming you have the Nexgen Motor Shield library in your Arduino libraries directory, you can access the library functionality by including the header file:

```
#include <NexgenMotorShield.h>
```

A motor shield object can be instantiated using the provided constructor:

```
NexgenMotorShield motorShield;
```

You can then control the two motors using the **setConfiguration()** and **setSpeed** methods. For example, for motor 1:

```
motorShield.motor1.setConfiguration(FORWARD);
motorShield.motor1.setSpeed(255);
```

You can do similar for motor 2.

The **setConfiguration()** method has four available options:
1. FORWARD
2. REVERSE
3. BRAKE
4. COAST
5. DISCONNECT

When a new motor shield object is instantiated, the two motors are set to the DISCONNECT state. This disables the motor and sets both input pins low.

The 5 configuration options are defined terms in the library. You will generally set the configuration before you set the speed. The speed can be set between 0 (stopped) and 255 (fastest). As soon as you set the speed the motor will start running, unless the configuration state is BRAKE or COAST.

The alternative to setting the speed is to use **enable()** and **disable()**. For example for motor 2:

```
motorShield.motor2.setConfiguration(FORWARD);
motorShield.motor2.enable();
delay(1000);
motorShield.motor2.disable();
```

Enabling the motor is equivalent to **setSpeed(255)** and disabling the motor is equivalent to **setSpeed(0)**.

You can actively brake a motor using:

```
motorShield.motor1.setConfiguration(BRAKE);
```

Be aware that active braking can generate significant back EMF in the motor shield and it is better to use **COAST**. Setting the configuration to COAST and using motor disable() is equivalent.

### Help and Questions ###

* Contact [Nexgen Codecamp](https://nexgencodecamp.com.au/)
* Other community or team contact