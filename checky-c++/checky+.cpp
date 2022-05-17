/* """Lists how many images are in each brand's image processing folder""" */
/* __author__ = "Jason Rebuck" */
/* __copyright__ = "2022" */
/* __version__ = "0.10" */

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

//ROOT FOLDERS
#define ROOT_DIR "/Volumes/proofs"
#define ROOT_DIR_FALLBACK "/mnt/proofs"

//FOLDER NAMES
#define IMAGE_DIR "/images/bdp/"
#define PROCESS_DIR "/image_processing/"

//STYLES
#define CLEAR_STYLE "\033[0m"
#define BOLD_STYLE "\033[1m"
#define DIM_STYLE "\033[2m"
#define BLINK_STYLE "\033[5m"
#define REVERSE_STYLE "\033[7m"

//COLORS
#define BLACK_COLOR "\033[30m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define MAGENTA_COLOR "\033[35m"

//EMOJIS
#define BLOCK_EMOJI " ▪"
#define SKULL_EMOJI "☠️"
#define PIN_EMOJI "📌"
#define DRAGON_EMOJI "🐲"
#define UNICORN_EMOJI "🦄"
#define FIRE_EMOJI "🔥"


//Uppercase function
string upper_string(string str) {
    transform(str.begin(), str.end(),str.begin(), ::toupper);
    return str;
}

//Find proof folder
string get_base_path(){
    string folders[2] = { ROOT_DIR, ROOT_DIR_FALLBACK };
    for(int i=0; i<2; i++){
	struct stat buffer;
	if (stat(folders[i].c_str(), &buffer) == 0) {
	    return folders[i];
	}
    }
    printf("%s%sMissing Proofs Path!%s\n", RED_COLOR, BOLD_STYLE, CLEAR_STYLE);
    exit(0);
    return "";
}

//Count files in directory
int count(string path) {
    int num = 0;
    DIR * dirp;
    struct dirent * entry;
    dirp = opendir(path.c_str());
    if (dirp) {
	while((entry = readdir(dirp)) != NULL){
	    if ((entry->d_name[0] != '.' )) {
		num++;
	    }
	}
	closedir(dirp);
	return num;
    } else {
	return -1;
    }
}

//Print brand title
void print_title(string name){
    printf("\n%s%11s%-9s%s\n", REVERSE_STYLE, upper_string(name).c_str(), "", CLEAR_STYLE);
}

//Print folder name and number of files
void print_count(string name, int num) {
    if (num == 0) {
	printf(" %s%-13s%-2s%s\n", BOLD_STYLE, name.c_str(), BLOCK_EMOJI, CLEAR_STYLE );
    } else if (num == -1) {
	printf(" %s%s%-13s-ERR-%s\n", BOLD_STYLE, DIM_STYLE, name.c_str(), CLEAR_STYLE);
    } else if (num >= 50) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, BLINK_STYLE, name.c_str(), num, CLEAR_STYLE, SKULL_EMOJI);
    } else if (num >= 40) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, MAGENTA_COLOR, name.c_str(), num, CLEAR_STYLE, UNICORN_EMOJI);
    } else if (num >= 30) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, GREEN_COLOR, name.c_str(), num, CLEAR_STYLE, DRAGON_EMOJI);
    } else if (num >= 20) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, YELLOW_COLOR, name.c_str(), num, CLEAR_STYLE, FIRE_EMOJI);
    } else {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, RED_COLOR, name.c_str(), num, CLEAR_STYLE, PIN_EMOJI);
    }
}

//Make path for new cms type folders
void print_status(string brand, string base, int start, int stop) {
    print_title(brand);
    string folders[7] = { "overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe" };
    for(int i=start; i<stop; i++){
	string full_path = base + IMAGE_DIR + brand + PROCESS_DIR + folders[i];
	print_count(upper_string(folders[i]), count(full_path));
    }
}

int main() {
  string base = get_base_path();
  //hbd section
  print_status("hbd", base, 0, 7);
  //yhl section
  print_status("yhl", base, 0, 7);
  //rlp section
  print_status("rlp", base, 0, 5);
  //don't forget to add extra line space
  cout << endl;
  return 0;
}
