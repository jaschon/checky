#!/usr/bin/env ruby
#"""Lists how many images are in each brand's image processing folder"""
#__author__ = "Jason Rebuck"
#__copyright__ = "2021"
#__version__ = "0.11"

def get_base_path
  #Try to find proof's path
  ["/Volumes/proofs", "/mnt/proofs"].each do |dir|
    if Dir.exists?(dir)
      return dir
    end
  end
  kill_if_no_path
  return ""
end

def kill_if_no_path
  #Warn and exit if no proofs path found
  abort("\033[1m\033[31mMissing Proofs Path!\033[0m\n")
end

def count(path)
  #Count how many files are in folder
  if Dir.exists?(path)
    return Dir.entries(path).size - 2
  else
    return -1
  end
end

def print_title(brand)
  #Print brand title
  puts "\n\033[7m#{brand.upcase.center(20)}\33[0m"
end

def print_count(name, num)
  #Print folder and number count
  color = "\033[30m"
  icon = " "
  if num == 0
    num = "▪"
  elsif num == -1
    num = "-ERR-"
    color = "\033[30m\033[2m"
  elsif num >= 50
    color = "\033[5m\033[35m" #blinky magenta
    icon = "☠️"
  elsif num >= 40
    color = "\033[32m" #green
    icon = "🐲"
  elsif num >= 30
    color = "\033[35m" #magenta
    icon = "🦄"
  elsif num >= 20
    color = "\033[33m" #yellow
    icon = "🔥"
  else
    color = "\033[31m" #red
    icon = "📌"
  end
  puts "  \033[1m#{color}#{name.upcase.ljust(13)}#{num.to_s.rjust(2)}\033[0m #{icon}"
end

def print_status(brand, base, folders)
  #Loop through folders and run print count
  print_title(brand)
  folders.each { |folder| print_count(folder, count("#{base}/images/bdp/#{brand.downcase}/image_processing/#{folder}")) }
end


def main
  #Print title and count for each brand and brand folder

  #Check if folder was mounted
  base_path = get_base_path

  #HBD
  print_status("hbd", base_path, ["overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe"])

  #YHL
  print_status("yhl", base_path, ["overlay", "portrait", "logo", "house", "pdf", "postcard", "recipe"])

  #RLP
  print_status("rlp", base_path, ["overlay", "portrait", "logo", "house", "pdf"])

  puts ""

end



if __FILE__ == $0
  main
end
