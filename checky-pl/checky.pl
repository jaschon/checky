#!/usr/bin/perl 

#"""Lists how many images are in each brand's image processing folder"""
#__author__ = "Jason Rebuck"
#__copyright__ = "2021"
#__version__ = "0.11"


sub get_base_path {
    #"""Try to find proof's path"""
    foreach ("/Volumes/proofs", "/mnt/proofs") {
	if(-d $_){
	    return $_;
	}
    }
    &kill_if_no_path();
}


sub kill_if_no_path {
    #"""Warn and exit if no proofs path found."""
    print "\033[1m\033[31mMissing Proofs Path!\033[0m\n";
    exit;
}

sub count {
    #"""Count how many files are in folder"""
    my $path = shift;
    if(-d $path){
	opendir my $dh, $path;
	my $num = () = readdir($dh);
	return $num - 2;
    }
    return -1;
}


sub print_title {
    #"""Print brand title"""
    printf("\n\033[7m       %s       \33[0m\n", uc($_[0]))
}

sub print_count {
    #"""Print folder and num"""
    
    my $name = shift;
    my $num = shift;

    my $color = "\033[30m";
    my $icon = " ";

    if($num == 0){
	$num = "▪";
    } elsif($num == -1){
	$num = "-ERR-";
	$color = "\033[30m\033[2m";
    } elsif($num >= 50){
	$color = "\033[5m\033[35m";
	$icon = "☠️"
    } elsif($num >= 40){
	$color = "\033[32m";
	$icon = "🐲";
    } elsif($num >= 30){
	$color = "\033[35m";
	$icon = "🦄";
    } elsif($num >= 20){
	$color = "\033[33m";
	$icon = "🔥";
    } else {
	$color = "\033[31m";
	$icon = "📌";
    }

    printf(" \033[1m%s%-14s%-2s\033[0m %s\n", $color, uc($name), $num, $icon);
}


sub print_status {
    #"""Loop through folders and run print count"""
    
    my $brand = shift;
    my $base = shift;
    my @folders = @_;

    &print_title($brand);

    $brand = lc($brand);

    foreach $folder (@folders) {
	&print_count($folder, &count("$base/images/bdp/$brand/image_processing/$folder"));
    }
}

sub main {
    #"""Print title and count of each brand and brand folder"""
    
    $base_path = &get_base_path();

    &print_status("hbd", $base_path, ("overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"));

    &print_status("yhl", $base_path, ("overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"));

    &print_status("rlp", $base_path, ("overlay", "portrait", "logo", "pdf"));

    print "\n";

}



# Main
&main;


