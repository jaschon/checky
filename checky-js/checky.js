#!/usr/bin/node
const fs = require("fs")

// """Lists how many images are in each brand's image processing folder"""
// __author__ = "Jason Rebuck"
// __copyright__ = "2022"
// __version__ = "0.05"

//get base path
const get_base_path = () => {
    directory = "/Volumes/proofs"
    if (fs.existsSync(directory)) {
	return directory;
    } else {
	console.log("\033[1m\033[31mMissing Proofs Path!\033[0m\n");
	process.exit(1);
    }
}

//count files
const count = (path) => { 
    try {
	return fs.readdirSync(path).length;
    } catch(e) {
	return -1;
    }
};

//print section title
const print_title = (brand) => { console.log("\n\033[7m%s%s\33[0m", "".padStart(8), brand.toUpperCase().padEnd(10)) };

//print folder count
const print_count = (name, num) => { 
    icon = "";
    color = "\033[30m"
    if (num == 0) {  
	num = "▪"; 
    } else if (num == -1) {
	num = "-ERR-";
	color = "\033[30m\033[2m";
    } else if (num >= 50) {
	color = "\033[5m\033[35m";
	icon = "☠️";
    } else if (num >= 40) {
	color = "\033[32m";
	icon = "🐲";
    } else if (num >= 30) {
	color = "\033[35m";
	icon = "🦄";
    } else if (num >= 20) {
	color = "\033[33m";
	icon = "🔥";
    } else {
	color = "\033[31m";
	icon = "📌";
    }
    console.log(" \033[1m%s%s%s\033[0m %s", color, name.toUpperCase().padEnd(13), num.toString().padEnd(2), icon); 
};


//loop though folders
const print_status = (brand, base, folders) => {
    print_title(brand);
    folders.forEach(folder => { 
	print_count(folder, count(`${base}/images/bdp/${brand.toLowerCase()}/image_processing/${folder}`))
    });
}

// main
const main = () => {
    // find base path or exit
    let base = get_base_path();
    // hbd
    print_status("hbd", base, ["overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe"]);
    // yhl
    print_status("yhl", base, ["overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe"]);
    //rlp
    print_status("rlp", base, ["overlay", "portrait", "logo", "house", "pdf"]);
    console.log("");
}


//start
main();

