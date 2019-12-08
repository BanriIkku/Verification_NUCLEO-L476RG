@echo off
rem ========================================================
cd ../../
python -m pip install --upgrade pip
python -m pip install mbed-cli
git clone https://github.com/ARMmbed/mbed-os
cd .tools\CMD
rem ========================================================
Mbed_upgrad.cmd
rem ========================================================
Export.cmd
rem ========================================================
pause
cd .tools\CMD
