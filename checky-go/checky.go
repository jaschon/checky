// """Lists how many images are in each brand's image processing folder"""
// __author__ = "Jason Rebuck"
// __copyright__ = "2022"
// __version__ = "0.05"

package main

import (
  "fmt"
  "os"
  "strings"
  . "github.com/logrusorgru/aurora"
)

func get_base_path() string {
  for _, dir := range [2]string{"/Volumes/proofs", "/mnt/proofs"} {
    if _, err := os.Stat(dir); !os.IsNotExist(err) {
      return dir
    }
  }
  kill_if_no_path()
  return ""
}

func kill_if_no_path(){
  fmt.Println(Red("Missing Proofs Path!"))
  fmt.Println("")
  os.Exit(0)
}

func count(path string) int {
  files, err := os.ReadDir(path)     
  if err != nil {
    panic(err)
  }
  return len(files)
}

func print_title(brand string) {
  fmt.Println(Inverse(fmt.Sprintf("%11s%-9s", strings.ToUpper(brand), "")))
}

func print_count(name string, num int) {
  color := Bold(strings.ToUpper(name))
  switch {
  case num == 0:
    fmt.Printf(" %-13s ▪ \n", color)
  case num == -1:
    fmt.Printf(" %-14s%-2d -ERR-\n", Faint(color), num)
  case num >=50:
    fmt.Printf(" %-14s%-2d ☠️ \n", Blink(Magenta(color)))
  case num >=40:
    fmt.Printf(" %-14s%-2d 🐲 \n", Green(color))
  case num >=30:
    fmt.Printf(" %-14s%-2d 🦄 \n", Magenta(color))
  case num >=20:
    fmt.Printf(" %-14s%-2d 🔥 \n", Yellow(color))
  default:
    fmt.Printf(" %-14s%-2d 📌 \n", Red(color))
  }
}

func print_status(brand string, base string, folders []string) {
  fmt.Println("")
  print_title(brand)
  for _, f := range folders {
    print_count(f, count(fmt.Sprintf("%s/images/bdp/%s/image_processing/%s", base, brand, f)))
  }
}

func main() {
  base_path := get_base_path()
  print_status("hbd", base_path, []string{"overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"})
  print_status("yhl", base_path, []string{"overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"})
  print_status("rlp", base_path, []string{"overlay", "portrait", "logo", "house", "pdf"})
  fmt.Println("")
}
