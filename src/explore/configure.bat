@ECHO OFF
REM **************************************************************************
REM *
REM * configure.bat for setting up compiling STLport under Windows
REM * to see available options, call with parameter --help
REM *
REM * Copyright (C) 2004 Michael Fink
REM *
REM **************************************************************************


REM initially create/overwrite config.mak
echo # config.mak generated with: > .\Makefiles\config.mak
echo # configure.bat %1 %2 %3 %4 %5 %6 %7 %8 %9 >> .\Makefiles\config.mak
echo # >> .\Makefiles\config.mak

set STLPORT_COMPILE_COMMAND=

echo. > .\Makefiles\config.mak

REM
REM option loop
REM
:opt_loop

REM help option
if "%1" == "-?" goto opt_help
if "%1" == "-h" goto opt_help
if "%1" == "/?" goto opt_help
if "%1" == "/h" goto opt_help
if "%1" == "--help" goto opt_help

REM compiler option
if "%1" == "-c" goto opt_compiler
if "%1" == "--compiler" goto opt_compiler

REM processor option
if "%1" == "-p" goto opt_processor
if "%1" == "--processor" goto opt_processor


echo Unknown parameter: %1

:reenter_loop

shift

REM no more options?
if "%1xyz123" == "xyz123" goto end_loop

goto opt_loop


REM **************************************************************************
REM *
REM * Help
REM *
REM **************************************************************************
:opt_help
echo.
echo configure.bat for setting up compiling STLport under Windows
echo.
echo The following parameters are available:
echo.
echo "-c <compiler>" or "--compiler <compiler>"
echo    Uses specified compiler to compile STLport. The following keywords
echo    are available:
echo    msvc6    Microsoft Visual C++ 6.0
echo    msvc7    Microsoft Visual C++ .NET 2002
echo    msvc71   Microsoft Visual C++ .NET 2003
echo    msvc8    Microsoft Visual C++ .NET 2005
echo    icl      Intel C++ Compiler
echo    evc3     Microsoft eMbedded Visual C++ 3
echo    evc4-arm Microsoft eMbedded Visual C++ .NET (ARM)
echo    evc4-x86 Microsoft eMbedded Visual C++ .NET (x86)
echo.
echo "-p <processor>" or "--processor <processor>"
echo    Sets target processor for given compiler; currently only used for
echo    evc3 compiler. The following keywords are available:
echo    ARM     ARM processor
echo    x86     x86 processor (Emulator)
echo.
goto end_loop

REM **************************************************************************
REM *
REM * Compiler configuration
REM *
REM **************************************************************************
:opt_compiler

if "%2" == "msvc6" goto opt_comp_msvc6
if "%2" == "msvc7" goto opt_comp_msvc7
if "%2" == "msvc71" goto opt_comp_msvc71
if "%2" == "msvc8" goto opt_comp_msvc8
if "%2" == "icl"   goto opt_comp_icl

if "%2" == "evc3" goto opt_comp_evc3
if "%2" == "evc4-arm" goto opt_comp_evc4_arm
if "%2" == "evc4-x86" goto opt_comp_evc4_x86

echo Unknown compiler: %2
goto opt_comp_end

:opt_comp_msvc6
echo Setting compiler: Microsoft Visual C++ 6.0
echo TARGET_OS=x86 >> .\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc6.mak
goto opt_comp_end

:opt_comp_msvc7
echo Compiler not supported in "explore" yet: Microsoft Visual C++ .NET 2002
REM echo Setting compiler: Microsoft Visual C++ .NET 2002
REM set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc7.mak
goto opt_comp_end

:opt_comp_msvc71
echo. > .\Makefiles\config.mak
REM echo Setting compiler: Microsoft Visual C++ .NET 2003
REM set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc71.mak
goto opt_comp_end

:opt_comp_msvc8
echo. > .\Makefiles\config.mak
REM echo Setting compiler: Microsoft Visual C++ .NET 2005
REM set STLPORT_COMPILE_COMMAND=nmake -f nmake-vc8.mak
goto opt_comp_end

:opt_comp_icl
echo Compiler not supported in "explore" yet: Intel C++ Compiler
REM echo Setting compiler: Intel C++ Compiler
REM set STLPORT_COMPILE_COMMAND=nmake -f nmake-icl.mak
goto opt_comp_end

:opt_comp_evc3
echo Setting compiler: Microsoft eMbedded Visual C++ 3
echo COMPILER_NAME=evc3 >> .\Makefiles\config.mak
echo CEVERSION=300 >> .\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-evc3.mak
goto opt_comp_end

:opt_comp_evc4_arm
echo Setting compiler: Microsoft eMbedded Visual C++ .NET (ARM)
echo COMPILER_NAME=evc4-arm >> .\Makefiles\config.mak
echo CEVERSION=420 >> .\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-evc4-arm.mak
goto opt_comp_end

:opt_comp_evc4_x86
echo Setting compiler: Microsoft eMbedded Visual C++ .NET (x86)
echo COMPILER_NAME=evc4-x86 >> .\Makefiles\config.mak
echo CEVERSION=420 >> .\Makefiles\config.mak
set STLPORT_COMPILE_COMMAND=nmake -f nmake-evc4-x86.mak
goto opt_comp_end

:opt_comp_end
shift

goto reenter_loop


REM **************************************************************************
REM *
REM * Target processor configuration
REM *
REM **************************************************************************
:opt_processor

if "%2" == "ARM" goto opt_proc_arm
if "%2" == "Arm" goto opt_proc_arm
if "%2" == "arm" goto opt_proc_arm

if "%2" == "X86" goto opt_proc_x86
if "%2" == "x86" goto opt_proc_x86

echo Unknown processor: %2
goto opt_proc_end

:opt_proc_arm
echo Setting processor: ARM
echo TARGET_PROC=arm >> .\Makefiles\config.mak
goto opt_proc_end

:opt_proc_x86
echo Setting processor: x86 (Emulator)
echo TARGET_PROC=x86 >> .\Makefiles\config.mak
goto opt_proc_end

:opt_proc_end
shift

goto reenter_loop


REM **************************************************************************
REM *
REM * End loop
REM *
REM **************************************************************************

:end_loop

echo Done configuring STLport.

if "%STLPORT_COMPILE_COMMAND%" == "" goto skip_compile_cmd
echo Please type "%STLPORT_COMPILE_COMMAND%" to build STLport.
:skip_compile_cmd
echo.

set STLPORT_COMPILE_COMMAND=
