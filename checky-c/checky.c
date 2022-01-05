/* """Lists how many images are in each brand's image processing folder""" */
/* __author__ = "Jason Rebuck" */
/* __copyright__ = "2020" */
/* __version__ = "0.16" */
/* NEW CP VERSION */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

//STRING LENS 
#define PATH_LENGTH 150
#define BRAND_LENGTH 10
#define FOLDER_LENGTH 25

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

//Quick and dirty uppercase function
void upper_string(char s[]) {
   int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}

//Find proofs folder
void get_base_path(char *base){
    DIR * dirp;
    const char *folders[2] = { ROOT_DIR, ROOT_DIR_FALLBACK };
    for(int i=0; i<2; i++){
	dirp = opendir(folders[i]);
	if (dirp){
	    strcpy(base, folders[i]);
	    closedir(dirp);
	    return;
	}
    }
    printf("%s%sMissing Proofs Path!%s\n", RED_COLOR, BOLD_STYLE, CLEAR_STYLE);
    exit(0);
}

//Count files in Directory
int count(char path[PATH_LENGTH]) {
    int num = 0;
    DIR * dirp;
    struct dirent * entry;
    dirp = opendir(path);
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
void print_title(char name[BRAND_LENGTH]){
    char name_upper[BRAND_LENGTH];
    strcpy(name_upper, name);
    upper_string(name_upper);
    printf("\n%s%11s%-9s%s\n", REVERSE_STYLE, name_upper, "", CLEAR_STYLE);
}

//Print folder name and number of files
void print_count(char *name, int num) {
    if (num == 0) {
	printf(" %s%-13s%-2s%s\n", BOLD_STYLE, name, BLOCK_EMOJI, CLEAR_STYLE );
    } else if (num == -1) {
	printf(" %s%s%-13s-ERR-%s\n", BOLD_STYLE, DIM_STYLE, name, CLEAR_STYLE);
    } else if (num >= 50) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, BLINK_STYLE, name, num, CLEAR_STYLE, SKULL_EMOJI);
    } else if (num >= 40) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, MAGENTA_COLOR, name, num, CLEAR_STYLE, UNICORN_EMOJI);
    } else if (num >= 30) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, GREEN_COLOR, name, num, CLEAR_STYLE, DRAGON_EMOJI);
    } else if (num >= 20) {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, YELLOW_COLOR, name, num, CLEAR_STYLE, FIRE_EMOJI);
    } else {
	printf(" %s%s%-13s%2i%s %s\n", BOLD_STYLE, RED_COLOR, name, num, CLEAR_STYLE, PIN_EMOJI);
    }
}

//Make path for new cms type folders
void print_status(char *brand, char *base, int start, int stop) {
    print_title(brand);
    char *folders[7] = { "overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe" };
    for(int i=start; i<stop; i++){
	char full_path[PATH_LENGTH];
	char folder_upper[FOLDER_LENGTH];
	strcpy(folder_upper, folders[i]);
	upper_string(folder_upper);
	strcpy(full_path, base);
	strcat(full_path, IMAGE_DIR);
	strcat(full_path, brand);
	strcat(full_path, PROCESS_DIR);
	strcat(full_path, folders[i]);
	print_count(folder_upper, count(full_path));
    }
}

//Main function
int main() {

    char base[PATH_LENGTH];
    char brand[BRAND_LENGTH];

    //make sure you get the proofs folder or exit
    get_base_path(base); 

    //hbd section
    strcpy(brand, "hbd");
    print_status(brand, base, 0, 7);

    //yhl section
    strcpy(brand, "yhl");
    print_status(brand, base, 0, 7);

    //rlp section
    strcpy(brand, "rlp");
    print_status(brand, base, 0, 5);

    //don't forget extra line space
    printf("\n");
    return 0;
}
