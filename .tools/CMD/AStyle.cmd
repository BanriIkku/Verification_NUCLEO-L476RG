@echo off
echo /////////////////////////////////////
echo     AStyle.cmd Ver.0.0.1
echo /////////////////////////////////////
echo;
rem 検索する文字
set search=mbed-os

rem /////////////////////////////////////
set atylePath="%~dp0..\AStyle\astyle.exe"
set astylercPath="%~dp0..\..\.astylerc"
set pflder=%~dp0
cd ../../

rem /////////////////////////////////////
for %%i in (*.cpp) do (
echo "%%i" | find "%search%" >NUL
if not ERRORLEVEL 1 (
rem --------
) else (
%atylePath% -n --options=%astylercPath% "%%i"
)
) 
rem /////////////////////////////////////

for %%i in (*.h) do (
echo "%%i" | find "%search%" >NUL
if not ERRORLEVEL 1 (
rem --------
) else (
%atylePath% -n --options=%astylercPath% "%%i"
)
) 

rem /////////////////////////////////////
rem /////////////////////////////////////

for /d %%j in (*) do (
echo "%%j" | find "%search%" >NUL
if not ERRORLEVEL 1 (
rem ////////////
) else (
cd "%pflder%..\..\%%j"
rem "%pflder%..\..\%%j"

rem =====================================

for /r %%i in (*.cpp) do (
echo "%%i" | find "%search%" >NUL
if not ERRORLEVEL 1 (
rem ////////////
) else (
%atylePath% -n --options=%astylercPath% "%%i"
)
) 
rem =====================================

for /r %%i in (*.h) do (
echo "%%i" | find "%search%" >NUL
if not ERRORLEVEL 1 (
rem ////////////
) else (
%atylePath% -n --options=%astylercPath% "%%i"
)
) 
rem =====================================

cd ../

)
) 
rem /////////////////////////////////////
cd .tools\CMD
echo;
echo =====================================
