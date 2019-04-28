@echo off
cd ../
mbed compile --target NUCLEO_L476RG --toolchain GCC_ARM
cd .tools
pause
