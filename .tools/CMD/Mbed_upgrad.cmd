@echo off
cd ../../mbed-os
python -m pip install --upgrade pip
mbed sync
mbed update latest --clean
mbed releases
echo *********************************************
mbed ls
echo *********************************************
pause
cd ../.tools\CMD
