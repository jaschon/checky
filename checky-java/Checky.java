/* """Lists how many images are in each brand's image processing folder""" */
/* __author__ = "Jason Rebuck" */
/* __copyright__ = "2022" */
/* __version__ = "0.05" */

import java.io.File;

public class Checky {

    public static void main(String[] args) {
        String base = get_base_path();
        //hbd section
        print_status("hbd", base, 0, 7);
        //yhl section
        print_status("yhl", base, 0, 7);
        //rlp section
        print_status("rlp", base, 0, 5);
        System.out.println("");
    }

    //Find proof folder
    static String get_base_path(){
        String[] folders = { "/Volumes/proofs", "/mnt/proofs" };
        for (int i=0; i<folders.length; ++i){
            File directory = new File(folders[i]);
            if (directory.exists()){
                return folders[i];
            }
        }
        System.out.printf("%s%sMissing Proofs Path!%s\n", "\033[31m", "\033[1m", "\033[0m");
        System.exit(0);
        return "";
    }

    //Count files in directory
    static int count(String path) {
        File directory = new File(path);
        if (directory.exists()) {
            return directory.list().length;
        }
        return -1;
    }

    //Print brand title
    static void print_title(String name) {
        System.out.printf("\n%s%11s%-9s%s\n", "\033[7m", name.toUpperCase(), "", "\033[0m");
    }

   //Print folder name and number of files 
    static void print_count(String name, int num){
        if(num == 0) {
            System.out.printf(" %s%-13s%-2s%s\n", "\033[1m", name, " ▪", "\033[0m");
        } else if(num == -1) {
            System.out.printf(" %s%s%-13s-ERR-%s\n", "\033[1m","\033[2m", name, "\033[0m");
        } else if(num >= 50) {
            System.out.printf(" %s%s%-13s%2s%s %s\n", "\033[1m", "\033[5m", name, num, "\033[0m", "☠️");
        } else if(num >= 40) {
            System.out.printf(" %s%s%-13s%2s%s %s\n", "\033[1m", "\033[35m", name, num, "\033[0m", "🦄");
        } else if(num >= 30) {
            System.out.printf(" %s%s%-13s%2s%s %s\n", "\033[1m",  "\033[32m", name, num, "\033[0m", "🐲");
        } else if(num >= 20) {
            System.out.printf(" %s%s%-13s%2s%s %s\n", "\033[1m",  "\033[33m", name, num, "\033[0m", "🔥");
        } else {
            System.out.printf(" %s%s%-13s%2s%s %s\n", "\033[1m",  "\033[31m", name, num, "\033[0m", "📌");
        }

    }

    //Make path for new cms type folders
    static void print_status(String brand, String base, int start, int stop) {
        print_title(brand);
        String[] folders = { "overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe" };
        for (int i = start; i < stop; ++i){
            String full_path = base + "/images/bdp/" + brand + "/image_processing/" + folders[i];
            print_count(folders[i].toUpperCase(), count(full_path));
        }
    }

}
