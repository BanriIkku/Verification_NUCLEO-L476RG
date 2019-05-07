@echo off
echo ####################################################################
rem  -------------------------------------------------------------------
if ""=="%PROJECTNAME%" (
set /P PROJECTNAME="Please set projectname : "
)

rem ####################################################################
rem Name the application
rem  -------------------------------------------------------------------
set APP_NAME=%PROJECTNAME%

rem ####################################################################
rem set profile.
rem  -------------------------------------------------------------------

if ""=="%PROFILE%" (
set PROFILE=release
)

rem ####################################################################
rem get other argument
rem  -------------------------------------------------------------------

if ""=="%1" (
set EXTEND_COMPILE=
) else (
set EXTEND_COMPILE=%*
)


rem ####################################################################
rem Check if you want to rebuild.
rem  -------------------------------------------------------------------

set rebuildInput=-
set mbedclean=
if ""=="%RUN_Rebuild%" (
set /P rebuildInput="Do you want to rebuild?(y/n) : "
) else (
set rebuildInput=%RUN_Rebuild%
)

if ""=="%rebuildInput%" (
set mbedclean=
echo *NOT* rebuild
) else if y==%rebuildInput% (
set mbedclean=-c
echo Rebuild
) else if Y==%rebuildInput% (
set mbedclean=-c
echo Rebuild
) else (
set mbedclean=
echo *NOT* Rebuild
)

rem  ####################################################################
rem  Verbose diagnosis
rem  -------------------------------------------------------------------

if ""=="%Lv_Verbose%" (
set Lv_Verbose=-
set /P Lv_Verbose="Please set verbose diagnosis? (0-2) : "
)

if ""=="%Lv_Verbose%" (
set Verbose=
echo Verbose Lv.0 "NOT Verbose"
) else if 1==%Lv_Verbose% (
set Verbose=-v
echo Verbose Lv.1 "verbose diagnostic output"
) else if 2==%Lv_Verbose% (
set Verbose=-vv
echo Verbose Lv.2 "very verbose diagnostic output"
) else (
set Verbose=
echo Verbose Lv.0 "NOT Verbose"
)

echo ####################################################################
echo SET [target , toolchain] = (NUCLEO_L476RG , GCC_ARM)
rem  -------------------------------------------------------------------
mbed target NUCLEO_L476RG
mbed toolchain GCC_ARM


echo;
echo;
echo ####################################################################
echo ////////////////////////////////////////////////////////////////////
echo ////////////////////////////////////////////////////////////////////
echo compile profile = [[ %PROFILE% ]]
rem  -------------------------------------------------------------------
echo mbed compile --profile=%PROFILE% -N %APP_NAME% --source=. %mbedclean% %Verbose%
echo -------------------------------------------------------------------
     mbed compile --profile=%PROFILE% -N %APP_NAME% --source=. %mbedclean% %Verbose%
echo;

echo ////////////////////////////////////////////////////////////////////
echo ////////////////////////////////////////////////////////////////////
echo ####################################################################
echo;
rem  -------------------------------------------------------------------
mbed config --list
echo -------------------------------------------------------------------
mbed ls
echo ===================================================================
