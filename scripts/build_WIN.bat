@echo off
setlocal ENABLEDELAYEDEXPANSION

for /F %%a in ('echo prompt $E ^| cmd') do (
  set "ESC=%%a"
)

cls

echo %ESC%[33mChecking System for Git...%ESC%[0m
echo:

where /q git
IF ERRORLEVEL 1 (
    echo %ESC%[31mError: Git not found in system!%ESC%[0m
    EXIT /B
) ELSE (
    echo %ESC%[32mGit Found!%ESC%[0m
    echo:
)

echo %ESC%[33mChecking System for CMake...%ESC%[0m
echo:

where /q cmake
IF ERRORLEVEL 1 (
    echo %ESC%[31mError: CMake not found in system!%ESC%[0m
    EXIT /B
) ELSE (
    echo %ESC%[32mCMake Found!%ESC%[0m
    echo:
)

cls
:pselect 
echo ++++++++++++++++++ && echo Plugins Available: && echo ++++++++++++++++++ && echo:
echo 1. Digital Delay && echo 2. Reverb && echo 3. IIR Filter && echo 4. Vibrado && echo 5. Chorus && echo 6. Flanger && echo 7. Distortion && echo 8. Compressor && echo 9. Limiter && echo 0. Exit && echo:

set /p "id=Select a plug-in to build [0-9]: "
set "selection=null"
set "parallel_build=0"

IF %id% == 0 (
	EXIT /B
) ELSE IF %id% == 1 (
	set "selection=Delay"
) ELSE IF %id% == 2 (
	set "selection=Reverb"
) ELSE IF %id% == 3 (
	set "selection=IIRFilter"
) ELSE IF %id% == 4 (
	set "selection=Vibrado"
) ELSE IF %id% == 5 (
	set "selection=Chorus"
) ELSE IF %id% == 6 (
	set "selection=Flanger"
) ELSE IF %id% == 7 (
	set "selection=Distortion"
) ELSE IF %id% == 8 (
	set "selection=Compressor"
) ELSE IF %id% == 9 (
	set "selection=Limiter"
) ELSE (
	cls
	echo:
	echo %ESC%[31mError: Wrong input. Please try again...%ESC%[0m
	echo:
	goto pselect
)

cls

:jselect
set /p "jselect=Enable parallel build? [y/n]: "
IF %jselect% == y (
	set "parallel_build=1"
) ELSE IF %jselect% == n (
	set "parallel_build=0"
) ELSE (
	cls
	echo:
	echo %ESC%[31mError: Wrong input. Please try again...%ESC%[0m
	echo:
	goto jselect
)

set p_path=..\plugins\%selection%
set "build_command=%p_path% -B %p_path%\build && cmake --build %p_path%\build\ --config Release"

IF %parallel_build% == 1 (
	set "build_command=%p_path% -B %p_path%\build && cmake --build %p_path%\build\ -j 8 --config Release"
)

cls

echo %ESC%[33mInitializing git submodules...%ESC%[0m

git submodule update --init --recursive

echo:
echo %ESC%[36mBuilding %selection% plugin...%ESC%[0m
echo:


cmake %build_command%

echo:
echo %ESC%[32mDone. Press and key to exit...!%ESC%[0m
pause>nul