# Nexgen Motor Shield Library #

The Nexgen Rover is an Arduino based robot designed wholly by Nexgen Codecamp Pty Ltd. It is used in technology related STEM courses aimed at high schools. The robot is based on Arduino technology and runs an Arduino UNO with a motor controller shield

This library makes using the Nexgen Motor Shield simple.

### Motor Shield Capabilities ###

The Nexgen Motor Shield utilises the L293B H-bridge and has been designed with the following capability:
* Ability to control two bidirectional DC motors for direction and rotation speed.
* A 2 pin JST-RCY connection for a LiPo battery to power the shield and attached Arduino UNO.
* LED power indication for VCC and the 5V regulated supply. The 5VDC regulator on the UNO is used.
* Voltage monitoring to prevent excessive discharge of the LiPo (needs to be programmed).
* The UNO reset switch reproduced on the shield.
* Bulk decoupling to reduce low frequency ripple and bypass capacitors to reduce high frequency noise.
* Additional pin headers for GND and 5VDC.
* Two additional, Signal, 5V and GND headers for use with servo motors or similar.

The L293B chip allows us to control two bidirectional motors with a stall current of up to 2A. It expects an RMS current of 1A. In the L293, motor direction is controlled by the state of two input pins and speed is controlled by applying a PWM signal to the enable pin. This library abstracts that detail away.

To monitor the battery we use a simple voltage divider and the ADC (Analog to Digital Converter) on the UNO. We need the resistive divider because you can't apply more than 5V to an Analog Input on the UNO. You can read more about the details of battery monitoring in our article [Designing your own Arduino Motor Shield](https://medium.com/r/?url=https%3A%2F%2Freefwing.medium.com%2Fdesigning-your-own-arduino-uno-motor-shield-ca507ab61f4b).

### Motor Shield Pin Connections ###

The control pins for Motor 1 (M1) and the pin connections for the UNO (in bold) on our shield are:

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

In total the Nexgen Motor Shield uses **8** Digital Inputs and **1** Analogue Input. The remaining pins are free and available via the stackable header. 

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

These are defined terms in the library. You will generally set the configuration before you set the speed. The speed can be set between 0 (stopped) and 255 (fastest). As soon as you set the speed the motor will start running, unless the configuration state is BRAKE or COAST.

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