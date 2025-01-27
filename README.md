# AUTOSAR MCAL Embedded Upskilling Training

This repository contains the projects, codes, examples, exercises, and results for the **AUTOSAR MCAL Embedded Upskilling Training** by [Modular MX](https://www.linkedin.com/company/modular-mx/). 

![AUTOSAR Training Banner](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/AUTOSAR_MCAL_Upskilling.png)

Date: *January 2025*

- The [**Certificate and Badge**](https://www.acreditta.com/credential/aee05611-e576-451e-a2fd-d97ee1cde115) are available.

![Autosar_MCAL_Certificate_Badge.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Badge_AUTOSAR_MCAL_training.png)
## Table of Contents

1. [**Overview**](#1-overview)  
2. [**Hardware Requirements**](#2-hardware-requirements)  
3. [**Software Requirements**](#3-software-requirements)  
4. [**Setup Notes**](#4-setup-notes)  
5. [**Documentation**](#5-documentation)  
6. [**Examples and Exercises**](#6-examples-and-exercises)  
7. [**Sample Evidences**](#7-sample-evidences)  



## 1. Overview

_<-- Back to [Table of Contents](#table-of-contents)_  

The AUTOSAR Upskilling Training focuses on developing and integrating low-level drivers (MCAL layer) using tools and methodologies from the automotive industry. This training spans **6 weeks** with **90% hands-on experience** and **10% theory**, utilizing platforms like the NXP S32K144 microcontroller and tools like Elektrobit Tresos and SEGGER Ozone Debugger.

Topics covered include:  
- MCAL fundamentals and toolchain configuration.  
- Configuring various peripheral drivers (PORT, DIO, MCU, GPT, Platform, ADC, SPI, CAN, CANIF).  
- Practical examples, exercises, and real-world implementation.

  What it's covered from the Classic AUTOSAR layers perspective:
  ![AUTOSAR_layered_view.jpeg](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/AUTOSAR_layered_view.jpeg)
  



## 2. Hardware Requirements

_<-- Back to [Table of Contents](#table-of-contents)_  

- **[NXP S32K144-Q100 Evaluation Board](https://www.nxp.com/products/S32K144)**:
 ![NXP S32K144-Q100 Evaluation Board](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/NXP%20S32K144-Q100.png)  
  Based on the Arm Cortex-M4F architecture, this serves as the primary microcontroller platform for this training.  
  

- **Modular-S1 Board**:  
  A companion board with additional peripherals, tailored for hands-on exercises.  
  ![MODULAR_S1_V2](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/MODULAR_S1_V2.jpg)



## 3. Software Requirements

_<-- Back to [Table of Contents](#table-of-contents)_  

- **[EB Tresos Studio](https://www.elektrobit.com/products/ecu/eb-tresos/studio/)**: Configure, validate, and generate AUTOSAR basic software (BSW).  
- **[SEGGER Ozone Debugger](https://www.segger.com/ozone/)**: Debug embedded applications at both source and assembly levels.  
- **[SavvyCAN](https://www.savvycan.com/)**: Analyze and interact with CAN bus traffic.  



## 4. Setup Notes

_<-- Back to [Table of Contents](#table-of-contents)_  

- [**NXP / EB Tresos tools installation.**](#nxp--eb-tresos-tools-installation)
- [**SEGGER tools installation.**](#segger-tools-installation)
- [**Importing the EB Tresos template project file.**](#importing-the-eb-tresos-template-project-file)

#### <ins>NXP / EB Tresos tools installation:<ins>

_Back to [Setup Notes](#4-setup-notes)_

1. Create your own NXP account.
2. Go to [Real-Time Drivers RTD](https://www.nxp.com/design/design-center/software/automotive-software-and-tools/real-time-drivers-rtd:AUTOMOTIVE-RTD). You should scroll until you reach the Download section for the Real-Time Drivers for S32K1. Click on Download and will open a new website that asks to log-in using your account.

![Setup_image_1.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup1.png)

3. You should have reached this area called _Product Information: Automotive SW - S32K1 - Real-Time Drivers_ where we will download the Real-Time Drivers for S32K1 as well as EB Tresos Studio

![Setup_image_2.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup2.png)

4. First let's download _EB tresos Studio / AUTOSAR Configuration Tool_. Click on the second option and then click on _EB tresos Studio 29.0.0_ which as of now is the latest version.

![Setup_image_3.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup3.png)

5. You will see Software Terms and Conditions, click '_I Agree_' and then we will see the main Product Download section. Download **EBTresosStudio_EBTresosStudio.uip**, **EB_Client_License_Administrator_1_5_1_Setup.exe** and **setup.exe**. Place all the files in a folder, the **EBTresosStudio_EBTresosStudio.uip** might be downloaded automatically as a .zip file. In case it is not, change the file extension from .uip to .zip, then extract. Execute **setup.exe** and click **Install**.

![Setup_image_4.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup4.png)


6. Once the EB Tresos tool is installed, notice that in the website there was a text highlighted in yellow that contains the chain of characters for the license code. Input that in the EB Client License Administrator.

![Setup_image_5.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup5.png)

7. Now let's download _S32K1_S32M24x - Real-Time Drivers for Cortex-M_. Go back and click on the first option and then download latest version which at the moment of writing this is _S32K1-S32M24X Real Time Drivers AUTOSAR R21-11 Version 2.0.0 P04_.

![Setup_image_6.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup6.png)

![Setup_image_7.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup7.png)

![Setup_image_8.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup8.png)

![Setup_image_9.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup9.png)

![Setup_image_10.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup10.png)

8. <ins>VERY IMPORTANT: At the moment of installing it do not forget to point it out to the EB Tresos install path!<ins>

![Setup_image_11.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup11.png)

9. Now we need a compiler, let's download the [GCC NXP](https://www.nxp.com/design/design-center/software/development-software/s32-design-studio-ide/s32-design-studio-for-s32-platform:S32DS-S32PLATFORM). Scroll down until you reach the Downloads section and there look up for this item as in the image: _NXP Embedded GCC 10.2 Compiler Tools for ARM v7 Embedded, build 1728 - Windows_. Proceed to install. (Only the compiler is needed, not the S32 Design Studio.)

![Setup_image_12.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup12.png)

![Setup_image_13.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup13.png)

#### <ins>SEGGER tools installation:<ins>

_Back to [Setup Notes](#4-setup-notes)_

1. For the Debugger, the hardware board provided by [Modular MX](https://www.linkedin.com/company/modular-mx/) is programmed with SEGGER J-Link to flash and debug the microcontroller. In case you acquire separately the NXP S32K144, you need to switch from OpenSDA for J-

2. After that, drivers are needed so go to [SEGGER J-Link official page](https://www.segger.com/downloads/jlink) and download and install the latest version of J-Link Software and Documentation Pack.

![Setup_image_14.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup14.png)

3. For [SEGGER Ozone Debugger](https://www.segger.com/products/development-tools/ozone-j-link-debugger/) download and install the latest version.

![Setup_image_15.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup15.png)

#### <ins>Importing the EB Tresos template project file:<ins>

_Back to [Setup Notes](#4-setup-notes)_

1. Git clone the project (that also comes with a makefile to compile the basic example in there and run it into the hardware board).

2. Open EB Tresos, go to **File → Import…**, then select **General → Existing Projects into Workspace**, then **Next** and **Browse…** the project folder (the cloned repository), click check on the **'template-s144'** project and **Finish**. 

![Setup_image_16.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup16.png)

![Setup_image_17.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup17.png)

3. Select the project and double click in **template-s144 → template-s144 (CORTEXM, S32K14X)** to display all the modules in use, then just click the hammer icon _'Generate code for the currently selected project'_.

![Setup_image_18.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup18.png)
![Setup_image_19.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup19.png)

4. Might see a warning dialog box regarding Module Configurations. Just ignore, those are not required due to the license type.

![Setup_image_20.png](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/Images/Setup20.png)



## 5. Documentation

_<-- Back to [Table of Contents](#table-of-contents)_  

The following documentation is available:  

You can find here the [**Documentation**](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/Documentation/) reference regarding:
* [AUTOSAR Driver Specification.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/Documentation/AUTOSAR%20Driver%20Specification)
* [Board.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/Documentation/Board)
* [Manuals](https://github.com/renatosoriano/AUTOSAR-MCAL-Embedded-Upskilling-Bootcamp/tree/main/Documentation/NXP%20EB%20Tresos%20MCAL%20drivers%20Integration-User%20Manuals)
* [NXP EB Tresos MCAL drivers Integration-User Manuals](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/Documentation/NXP%20EB%20Tresos%20MCAL%20drivers%20Integration-User%20Manuals)
* [SEGGER](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/Documentation/SEGGER)



## 6. Examples and Exercises

_<-- Back to [Table of Contents](#table-of-contents)_  

Each week's training includes examples and exercises. Key topics include:  

1. [Template](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/template-s144)
2. [DIO and PORT driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio)
3. [MCU driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/Mcu_Driver)
4. [GPT driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver)
5. [Platform driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PlatformDriver)
6. [ADC driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/AdcDriver)
8. [SPI driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/Spi_Driver)
10. [CAN driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/CanDriver)
11. [CANIF driver.](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/CanIfDriver)




## 7. Sample Evidences

_<-- Back to [Table of Contents](#table-of-contents)_  

In this section we have evidence like photos and video of some results with visible output in communication (software) or physical world (board).

### <ins>DIO-PORT Driver Evidences<ins>

_Back to [Sample Evidences](#7-sample-evidences)_

* #### [Port Dio Blink LEDs connected to port C](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDioExercise_Blink_LEDs_connected_to_port_C)

Blink the LEDs connected to port C alternately.

![PortDioExercise_Blink_LEDs_connected_to_port_C](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDioExercise_Blink_LEDs_connected_to_port_C/PortDioExercise_Blink_LEDs_connected_to_port_C.gif)

* #### [Port Dio 1 button 4 speeds](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_1_button_4_speeds)

Write a program that rotates an LED on port C, with 1 button and 4 different speeds. Each time the button is pressed, the speed will increase, and when it reaches the last speed, it will start over.

![PortDio_1_button_4_speeds](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_1_button_4_speeds/PortDio_1_button_4_speeds.gif)

* #### [Port Dio Control RGB leds with three buttons](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Control_RGB_leds_with_three_buttons)

Write a program that turn on RGB leds, each button will control each color in RGB.

![PortDio_Control_RGB_leds_with_three_buttons](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Control_RGB_leds_with_three_buttons/PortDio_Control_RGB_leds_with_three_buttons.gif)

* ### [Port Dio flip two channels](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Flip_two_channels)

  Toggle two leds.

  ![PortDio_Flip_two_channels](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Flip_two_channels/PortDio_Flip_two_channels.gif)

  * ### [Port Dio rotate LEDs](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Rotate_LEDS)
 
  Rotate LEDs in port C

  ![PortDio_Rotate_LEDS](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Rotate_LEDS/PortDio_Rotate_LEDS.gif)

 * ### [PortDio_Rotate_LEDS](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Rotate_group_of_channels)
 
  Rotate LEDs from C8 to C11

  ![PortDio_Rotate_LEDS](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Rotate_group_of_channels/PortDio_Rotate_group_of_channels.gif)

 * ### [Port Dio rotate a turned off LED in port C](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Rotates_a_turned-off_LED_on_port_C)
 
  Rotate a turned off LED in port C

  ![PortDio_Rotates_a_turned-off_LED_on_port_C](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Rotates_a_turned-off_LED_on_port_C/PortDio_Rotates_a_turned-off_LED_on_port_C.gif)

* ### [Port Dio Toggle LED](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Toggle_Led)
 
  Toggle an LED

  ![PortDio_Toggle_Led](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Toggle_Led/PortDio_Toggle_Led.gif)

  * ### [Port Dio turn on LED with button](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Turns_on_LED_with_button)
 
  Turns on LED when button is pressed

  ![PortDio_Toggle_Led](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Turns_on_LED_with_button/PortDio_Turns_on_LED_with_button.gif)

  * ### [Port Dio write a group of channels](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/PortDio/PortDio_Write_group_of_channels)
 
  Write a value of four bits on a group of Dio channels

  ![PortDio_Write_group_of_channels](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/PortDio/PortDio_Write_group_of_channels/PortDio_Write_group_of_channels.gif)


### <ins>GPT Driver Evidences<ins>

_Back to [Sample Evidences](#7-sample-evidences)_

* #### [Gpt driver 2 timers 2 speeds](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_2Timers_2Speeds)

Configure two different timers ( FTM1 and FTM2 ) to toggle two leds at different speeds ( 100ms and 300ms ), both timers shall use notifications in one shot mode, plus been feed by FIRC clock at 12MHz

![GptDriver_2Timers_2Speeds](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_2Timers_2Speeds/GptDriver_2Timers_2Speeds.gif)

* #### [Gpt driver 3 timers RGB LED](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_3Timers_RGB_LED)

Configure three timers FTM with one channel each of them to toggle the three RGB leds at different frequencies, the most important is that each FTM timer shall be feed by a different clock reference.

![GptDriver_3Timers_RGB_LED](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_3Timers_RGB_LED/GptDriver_3Timers_RGB_LED.gif)

* #### [Gpt driver 7 channels continous mode with notifications](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_7channels_continuous_with_notifications)

Configure all seven channels of timer FTM1 as Gpt timers in continuous mode with notifications, all of them some how shall be make a period of 1.4 second to toggle a led, use the notifications for that purpose

![GptDriver_7channels_continuous_with_notifications](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_7channels_continuous_with_notifications/GptDriver_7channels_continuous_with_notifications.gif)

* #### [Gpt driver continous mode](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_Continuous_mode)

Toggle one led every 100ms using continuous mode and notifications.

![GptDriver_Continuous_mode](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_Continuous_mode/GptDriver_Continuous_mode.gif)

* #### [Gpt driver LPIT timer](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_Lpit_timer)

Toggle one led every 300ms, but this time using the Lpit timer, continuous mode with notifications

![GptDriver_Lpit_timer](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_Lpit_timer/GptDriver_Lpit_timer.gif)

* #### [GptDriver oneshot mode](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_Oneshot_timer)

Toggle one led each 100ms using oneshot mode

![GptDriver_Oneshot_timer](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_Oneshot_timer/GptDriver_Oneshot_timer.gif)

* #### [GptDriver poll button](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_Poll_1_button)

Using one timer poll one button every 50ms and then read the button state to toggle one led every time the button has been pressed

![GptDriver_Poll_1_button](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_Poll_1_button/GptDriver_Poll_1_button.gif)

* #### [GptDriver timer with external clock](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/GptDriver/GptDriver_Timer_w_external_clock)

Toggle two leds each of them in alternate way every 200ms using two GPT timer in continuous mode and Notifications one for each of them. Both timer uses FTM0 as reference but with different FTM channels The frequency feeding the FTM0 timer is the FIRCDIV1 with a preescaler of 2.

![GptDriver_Timer_w_external_clock](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/GptDriver/GptDriver_Timer_w_external_clock/GptDriver_Timer_w_external_clock.gif)


### <ins>ADC Driver Evidences<ins>

_Back to [Sample Evidences](#7-sample-evidences)_

* #### [Adc driver single channel single conversion](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/AdcDriver/AdcDriver_1_channel_single_conversion)

One single conversion from one single channel. the on board Pot1 is connected to channel 5 from the ADC0

![AdcDriver_1_channel_single_conversion](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/AdcDriver/AdcDriver_1_channel_single_conversion/AdcDriver_1_channel_single_conversion.png)

* #### [Adc driver 2 channels single conversion](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/AdcDriver/AdcDriver_2_channels_single_conversion)

Similar to previous one, but this time using two channels (5 and 8) using the same ADC0

![AdcDriver_2_channels_single_conversion](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/AdcDriver/AdcDriver_2_channels_single_conversion/AdcDriver_2_channels_single_conversion.png)

* #### [Adc driver notifications with single channel, single conversion](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/tree/main/AdcDriver/AdcDriver_Notifications_1_channel_single_conversion)

Similar to the first one but using notifications, notifications are functions called by the adc ISR when a group conversion is finished, this allow us to inform the upper layer when a conversion is ready.

![AdcDriver_Notifications_1_channel_single_conversion](https://github.com/yesustrasvina/AUTOSAR_MCAL_Embedded_Upskilling_Training/blob/main/AdcDriver/AdcDriver_Notifications_1_channel_single_conversion/AdcDriver_Notifications_1_channel_single_conversion.png)
