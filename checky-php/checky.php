<?php

/* """Lists how many images are in each brand's image processing folder""" */
/* __author__ = "Jason Rebuck" */
/* __copyright__ = "2022" */
/* __version__ = "0.05" */

//get and check for root path
function get_base_path() {
    foreach(["/mnt/nfs/fs1/data/smb/proofs", "/Volumes/proofs", "/mnt/proofs"] as $folder) {
	if(is_dir($folder)){
	    return $folder;
	}
    }
    printf("%s%sMissing Proofs Path!%s\n", "\033[31m", "\033[1m", "\033[0m");
    exit(0);
}

//count files in folder
function count_path($path) {
    try {
	if (is_dir($path)) {
	    return count(glob($path . "*.{jpg,jpeg,gif,png,eps,pdf,psd,webp,bmp,tif,tiff}"));
	} else {
	    return -1;
	}
    } catch(Exception $e) {
	return -1;
    }
}

//print section title
function print_title($brand) {
    printf("\n%s%11s%-9s%s\n", "\033[7m", strtoupper($brand), "", "\033[0m");
}

//print count
function print_count($name, $num) {
    $color = "\033[30m";
    $icon = "";
    if ($num == 0) {
	$num = "▪";
    } elseif ($num == -1) {
	$num = "-ERR-";
	$color = "\033[30m\033[2m";
    } elseif ($num >= 50) {
	$color = "\033[5m\033[35m"; #blinky magenta
	$icon = "☠️";
    } elseif ($num >= 40) {
	$color = "\033[32m"; #green
	$icon = "🐲";
    } elseif ($num >= 30) {
	$color = "\033[35m"; #magenta
	$icon = "🦄";
    } elseif ($num >= 20) {
	$color = "\033[33m"; #yellow
	$icon = "🔥";
    } else {
	$color = "\033[31m";
	$icon = "📌";
    }
    printf(" \033[1m%s%-13s%-2s\033[0m %s\n", $color, strtoupper($name), $num, $icon);
}

//loop and print status
function print_status($brand, $base, $folders) {
    print_title($brand);
    foreach ($folders as $folder) {
	print_count($folder, count_path($base."/images/bdp/".strtolower($brand)."/image_processing/".$folder));
    }
}

//main
function main_start() {
    $base_path = get_base_path();
    #HBD
    print_status("hbd", $base_path, ["overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"]);
    #YHL
    print_status("yhl", $base_path, ["overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"]);
    #RLP
    print_status("rlp", $base_path, ["overlay", "portrait", "logo", "house", "pdf"]);
    print("\n");
}

//start
main_start();

?>
