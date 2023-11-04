#!/bin/bash

plugin_select() {
    echo ++++++++++++++++++ && echo Plugins Available: && echo ++++++++++++++++++ && printf "\n"
    printf "1. Digital Delay\n2. Reverb\n3. IIR Filter\n4. Vibrado\n5. Chorus\n6. Flanger\n7. Distortion\n8. Compressor\n9. Limiter\n0. Exit\n"

    printf "\nSelect a plug-in to build [0-9]:"

    read -r -s -n 1 id;
}

pBuild_select() {
    echo "Enable parallel build? [y/n]:"
    read -r -s -n 1 jselect;
}

clear
printf "\e[1;33mChecking System for Git...\n"
if type git > /dev/null 2>&1; then
    printf "\e[1;32mGit found!\n\033[0m"
else
    printf "\e[1;31mError: Git not found in system!\n\033[0m"
    exit
fi

printf "\e[1;33mChecking System for CMake...\n"
if type cmake > /dev/null 2>&1; then
    printf "\e[1;32mCMake found!\n\033[0m"
else
    printf "\e[1;31mError: CMake not found in system!\n\033[0m"
    exit
fi

pSelected=null
while [ $pSelected = null ]
do
    clear
    plugin_select
    if [[ $id -eq 1 ]]
    then
        pSelected=Delay
    elif [[ $id -eq 2 ]]
    then
        pSelected=Reverb
    elif [[ $id -eq 3 ]]
    then
        pSelected=IIRFilter
    elif [[ $id -eq 4 ]]
    then
        pSelected=Vibrado
    elif [[ $id -eq 5 ]]
    then
        pSelected=Chorus
    elif [[ $id -eq 6 ]]
    then
        pSelected=Flanger
    elif [[ $id -eq 7 ]]
    then
        pSelected=Distortion
    elif [[ $id -eq 8 ]]
    then
        pSelected=Compressor
    elif [[ $id -eq 9 ]]
    then
        pSelected=Limiter
    elif [[ $id -eq 0 ]]
    then
        exit
    fi
done

jSelected=null
while [ $jSelected = null ]
do
    clear
    pBuild_select
    if [ $jselect = Y ] || [ $jselect = y ]
    then
        jSelected=Y
    elif [ $jselect = N ] || [ $jselect = n ]
    then
        jSelected=N
    fi
done

p_path="../plugins/$pSelected"
config_command="$p_path -B $p_path/build -DCMAKE_BUILD_TYPE=Release"
build_command="--build $p_path/build"

if [ $jSelected = Y ]
then
    build_command="$build_command --parallel 8"
fi


clear
#echo cmake $build_command
printf "\e[1;33mInitializing git submodules...\n\n"
git submodule update --init --recursive

printf "\e[1;35m\n\nBuilding $pSelected plugin...\n"
printf "\e[1;33m\n"
cmake $config_command && cmake $build_command
printf "\e[1;32m\nDone. Press any key to exit\n\033[0m"
read -r -s -n 1 dumm;

