#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""Lists how many images are in each brand's image processing folder"""
__author__ = "Jason Rebuck"
__copyright__ = "2020-2021"
__version__ = "0.16"

import os

def get_base_path():
    """Try to find proof's path"""
    for directory in ("/Volumes/proofs", "/mnt/proofs"):
        if os.path.isdir(directory):
            return directory
    kill_if_no_path() #pylint workaround
    return ""

def kill_if_no_path():
    """Warn and exit if no proofs path found."""
    print("\033[1m\033[31mMissing Proofs Path!\033[0m\n")
    exit()

def count(path):
    """Count how many files are in folder"""
    try:
        if os.path.isdir(path):
            return len([j for j in os.listdir(path) if j[0] != '.'])
        else:
            return -1
    except OSError:
        return 0

def print_title(brand):
    """Print brand title"""
    print(f"\n\033[7m{brand.upper():^20}\33[0m")

def print_count(name, num):
    """Print folder and num"""
    color = "\033[30m"
    icon = " "
    if num == 0:
        num = "▪"
    elif num == -1:
        num = "-ERR-"
        color = "\033[30m\033[2m"
    elif num >= 50:
        color = "\033[5m\033[35m" #blinky magenta
        icon = "☠️"
    elif num >= 40:
        color = "\033[32m" #green
        icon = "🐲"
    elif num >= 30:
        color = "\033[35m" #magenta
        icon = "🦄"
    elif num >= 20:
        color = "\033[33m" #yellow
        icon = "🔥"
    else:
        color = "\033[31m" #red
        icon = "📌"
    print(f" \033[1m{color}{name.upper():<14}{num:<2}\033[0m {icon}")

def print_status(brand, base, folders):
    """Loop through folders and run print count"""
    print_title(brand)
    for folder in folders:
        print_count(folder, count(f"{base}/images/bdp/{brand.lower()}/image_processing/{folder}"))

def main():
    """Print title and count of each brand and brand folder"""

    # Check if folder was mounted
    base_path = get_base_path()

    # HBD
    print_status("hbd", base_path, (
        "overlay", "portrait", "logo", "house",
        "pdf", "recipe", "postcard"))

    # YHL
    print_status("yhl", base_path, (
        "overlay", "portrait", "logo", "house",
        "pdf", "recipe", "postcard"))

    #RLP
    print_status("rlp", base_path, ("overlay", "portrait", "logo", "house", "pdf"))

    print("")

if __name__ == "__main__":
    main()
