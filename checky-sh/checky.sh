#!/bin/bash
#"""Lists how many images are in each brand's image processing folder"""
# Jason Rebuck
# v.10 2021

ROOT_DIR="/Volumes/proofs"
ROOT_DIR_FALLBACK="/mnt/proofs"

IMAGE_DIR="/images/bdp"
PROCESS_DIR="image_processing"
BASE_PATH=""

get_base_path() {
    #Try to find proof path
    for DIRECTORY in $ROOT_DIR $ROOT_DIR_FALLBACK;
    do
	if [ -d $DIRECTORY ]; then
	    BASE_PATH=$DIRECTORY;
	fi
    done
    if [ -z $BASE_PATH ]; then
	printf "\033[1m\033[31mMissing Proofs Path!\033[0m\n"
	exit
    fi
}

print_count() {
    #Print folder and num count
    PATH_UPPER=`echo "${1}" | awk '{print toupper($1)}'`
    COUNT=0
    if [ -d $FULL_PATH/$1 ]; then
	COUNT=`ls $FULL_PATH/$1 | wc -l | cut -c 8-10`
    fi
    if [ $COUNT -eq 0 ]; then
	COLOR="\033[30m"
	COUNT="▪"
	ICON=""
    elif [ $COUNT -eq -1 ]; then
	COUNT="-ERR-"
	COLOR="\033[30m\033[2m"
    elif [ $COUNT -ge 50 ]; then
	COLOR="\033[5m\033[35m"
	ICON="☠️"
    elif [ $COUNT -ge 40 ]; then
	COLOR="\033[32m"
	ICON="🐲"
    elif [ $COUNT -ge 30 ]; then
	COLOR="\033[35m"
	ICON="🦄"
    elif [ $COUNT -ge 20 ]; then
	COLOR="\033[33m"
	ICON="🔥"
    else
	COLOR="\033[31m" #red
	ICON="📌"
    fi
    printf "  \033[1m${COLOR}%-14s${COUNT}\033[0m ${ICON}\n" ${PATH_UPPER}
}

print_status() {
    #Loop through folders and run print count
    BRAND=${1}
    BRAND_LOWER=`echo "${BRAND}" | awk '{print tolower($1)}'`
    FULL_PATH="${BASE_PATH}/${IMAGE_DIR}/${BRAND_LOWER}/${PROCESS_DIR}"
    printf "\n\033[7m        %s         \33[0m\n" $BRAND
    for DIR in 'overlay' 'portrait' 'logo' 'pdf' 'postcard' 'recipe'; do
	print_count $DIR
    done;
}

#Main
get_base_path
print_status "HBD"
print_status "YHL"
print_status "RLP"
echo ""

