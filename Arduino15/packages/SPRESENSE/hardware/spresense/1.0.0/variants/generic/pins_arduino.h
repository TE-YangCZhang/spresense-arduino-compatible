/*
  pins_arduino.h - Pin definition functions for Arduino
  Copyright (C) 2018 Sony Semiconductor Solutions Corp.
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis
  Modified for ESP8266 platform by Ivan Grokhotkov, 2014-2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <cxd56_pinconfig.h>

#define NUM_DIGITAL_PINS    (22)
#define NUM_ANALOG_INPUTS   (6)
#define PIN_NOT_ASSIGNED    (0xFF)

// Variant definition
#define TARGET_USES_PROTO3_BOARD

// Pin type
#define PINTYPE_MASK    0xc0
#define PINTYPE_DIGITAL 0x00
#define PINTYPE_LED     0x40
#define PINTYPE_ANALOG  0x80
#define _DIGITAL_PIN(N) (uint8_t)(PINTYPE_DIGITAL|(N))
#define _LED_PIN(N)     (uint8_t)(PINTYPE_LED    |(N))
#define _ANALOG_PIN(N)  (uint8_t)(PINTYPE_ANALOG |(N))
#define _PIN_OFFSET(P)  ((P)&~PINTYPE_MASK)

// Digital pins - 0x0N
#define PIN_D00     _DIGITAL_PIN(0)
#define PIN_D01     _DIGITAL_PIN(1)
#define PIN_D02     _DIGITAL_PIN(2)
#define PIN_D03     _DIGITAL_PIN(3)
#define PIN_D04     _DIGITAL_PIN(4)
#define PIN_D05     _DIGITAL_PIN(5)
#define PIN_D06     _DIGITAL_PIN(6)
#define PIN_D07     _DIGITAL_PIN(7)
#define PIN_D08     _DIGITAL_PIN(8)
#define PIN_D09     _DIGITAL_PIN(9)
#define PIN_D10     _DIGITAL_PIN(10)
#define PIN_D11     _DIGITAL_PIN(11)
#define PIN_D12     _DIGITAL_PIN(12)
#define PIN_D13     _DIGITAL_PIN(13)
#define PIN_D14     _DIGITAL_PIN(14)
#define PIN_D15     _DIGITAL_PIN(15)
#define PIN_D16     _DIGITAL_PIN(16)
#define PIN_D17     _DIGITAL_PIN(17)
#define PIN_D18     _DIGITAL_PIN(18)
#define PIN_D19     _DIGITAL_PIN(19)
#define PIN_D20     _DIGITAL_PIN(20)
#define PIN_D21     _DIGITAL_PIN(21)
#define PIN_D22     _DIGITAL_PIN(22)
#define PIN_D23     _DIGITAL_PIN(23)
#define PIN_D24     _DIGITAL_PIN(24)
#define PIN_D25     _DIGITAL_PIN(25)
#define PIN_D26     _DIGITAL_PIN(26)
#define PIN_D27     _DIGITAL_PIN(27)
#define PIN_D28     _DIGITAL_PIN(28)

// LED - 0x4N
#define PIN_LED0    _LED_PIN(0)
#define PIN_LED1    _LED_PIN(1)
#define PIN_LED2    _LED_PIN(2)
#define PIN_LED3    _LED_PIN(3)

static const uint8_t LED0 = PIN_LED0;
static const uint8_t LED1 = PIN_LED1;
static const uint8_t LED2 = PIN_LED2;
static const uint8_t LED3 = PIN_LED3;

#define PIN_DA0     PIN_D14
#define PIN_DA1     PIN_D15
#define PIN_DA2     PIN_D16
#define PIN_DA3     PIN_D17
#define PIN_DA4     PIN_D18
#define PIN_DA5     PIN_D19

#define PIN_PWM_0   PIN_D06
#define PIN_PWM_1   PIN_D05
#define PIN_PWM_2   PIN_D09
#define PIN_PWM_3   PIN_D03

static const uint8_t DA0 = PIN_DA0;
static const uint8_t DA1 = PIN_DA1;
static const uint8_t DA2 = PIN_DA2;
static const uint8_t DA3 = PIN_DA3;
static const uint8_t DA4 = PIN_DA4;
static const uint8_t DA5 = PIN_DA5;

// Analog pins - 0x8N
#define PIN_A0      _ANALOG_PIN(0)
#define PIN_A1      _ANALOG_PIN(1)
#define PIN_A2      _ANALOG_PIN(2)
#define PIN_A3      _ANALOG_PIN(3)
#define PIN_A4      _ANALOG_PIN(4)
#define PIN_A5      _ANALOG_PIN(5)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;

// SPI pins
#define PIN_SPI_SS    PIN_D10
#define PIN_SPI_MOSI  PIN_D11
#define PIN_SPI_MISO  PIN_D12
#define PIN_SPI_SCK   PIN_D13
static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// TWI pins
#define PIN_WIRE_SCL  PIN_D21
#define PIN_WIRE_SDA  PIN_D20
static const uint8_t SCL = PIN_WIRE_SCL;
static const uint8_t SDA = PIN_WIRE_SDA;

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial

// WiFi Pins
#define WIFI_READY      7  // handshake pin
//#define WIFI_LED     9   // led on wifi shield

#endif /* Pins_Arduino_h */
