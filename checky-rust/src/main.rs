//"""Lists how many images are in each brand's image processing folder"""
//__author__ = "Jason Rebuck"
//__copyright__ = "2019-2021"
//__version__ = "0.14"

extern crate colored;
use colored::*;
use glob::glob;
use std::fs;
use std::process;

//check if proofs folder was mounted and return the path. panic if it wasn't found.
fn get_base_path() -> String {
    for p in ["/Volumes/proofs", "/mnt/proofs"].iter() {
        if fs::metadata(p).is_ok() {
            return p.to_string();
        }
    }
    println!("{}\n", "Missing Proofs Path!".to_string().bold().red());
    process::exit(1);
}

//glob match path and count the number of files, return count
fn count(path: String) -> i32 {
    // println!("{}, {}", &path, fs::metadata(&path).is_ok()); //debug test
    if fs::metadata(&path).is_ok(){
        let mut count = 0;
        for _e in glob(&format!("{}/[a-zA-Z]*", &path)).expect("Failed to glob!") {
            count += 1; 
        }
        count
    } else {
        return -1;
    }
}

//print title of section underlined and capitalized
fn print_title(name: &str) {
    println!("\n{:^20}", name.to_uppercase().reversed());    
}

//print out count results. print a dash instead of a zero
fn print_count(name: &str, count: i32){
    match count {
        0 => println!(" {:<14}{:<2}  ", name.to_uppercase().bold(), "▪"),
        -1 => println!(" {:<14}{:<2}  ", name.to_uppercase().bold().dimmed(), "-ERR-".to_string().bold().dimmed()),
        d if d >= 50 => println!(" {:<14}{:<2} ☠️", name.to_uppercase().magenta().blink().bold(), count.to_string().magenta().blink().bold()),
        d if d >= 40 => println!(" {:<14}{:<2} 🐲", name.to_uppercase().green().bold(), count.to_string().green().bold()),
        d if d >= 30 => println!(" {:<14}{:<2} 🦄", name.to_uppercase().magenta().bold(), count.to_string().magenta().bold()),
        d if d >= 20 => println!(" {:<14}{:<2} 🔥", name.to_uppercase().yellow().bold(), count.to_string().yellow().bold()),
        _ => println!(" {:<14}{:<2} 📌", name.to_uppercase().red().bold(), count.to_string().red().bold()),
    }
}

//loop through folders, create path and grab counted
//params = brand (hbd, yhl), base proofs path (proofs folder), folders list (overlays, pdfs, photos),  which path format to use (use "" for default)
fn print_status(brand: &str, base: &String, folders: &[&str]){
    print_title(brand);
    for f in folders.iter(){
        print_count(f, count(format!("{}/images/bdp/{}/image_processing/{}", base, brand , f)));
    }
}

fn main() {

    //Check if proofs folder was mounted and return it
    let base_path = get_base_path();

    // HBD
    print_status("hbd", &base_path, &["overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe"]);

    // YHL
    print_status("yhl", &base_path, &["overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe"]);

    // RLP
    print_status("rlp", &base_path, &["overlay", "portrait", "logo", "house", "pdf"]);

    println!("");

}
