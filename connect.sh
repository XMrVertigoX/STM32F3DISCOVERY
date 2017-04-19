#! /bin/bash

JLinkGDBServer -device STM32F303VC -if swd -speed auto -nogui -xc connect.gdb
