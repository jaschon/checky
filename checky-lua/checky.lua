#!/usr/local/bin/lua
-- /* """Lists how many images are in each brand's image processing folder""" */
-- /* __author__ = "Jason Rebuck" */
-- /* __copyright__ = "2021" */
-- /* __version__ = "0.10" */

require 'lfs'

-- find proofs folder
function get_base_path()
    for index,path in ipairs({'/Volumes/proofs', '/mnt/proofs'})
	do
	    if lfs.attributes(path:gsub("\\$",""),"mode") == "directory" 
	    then
		return path
	    end
	end
     kill_if_no_path()
end


-- exit if not proofs folder found
function kill_if_no_path()
    print("\027[1m\027[31mMissing Proofs Path!\027[0m\n")
    os.exit()
end

-- count the number of files in a folder
function count(path)
    if lfs.attributes(path:gsub("\\$",""),"mode") == "directory"
    then
	cnt = 0
	for file in lfs.dir(path)
	do
	    if string.match(file, "^[A-Za-z]")
	    then
		cnt = cnt + 1
	    end
	end
	return cnt
    else
	return -1
    end
end

-- print brand title
function print_title(brand)
    print(string.format("\n%s%11s%-9s%s", "\027[7m", brand:upper(), "", "\027[0m"))
end

-- print folder name, count and icon
function print_count(name, num)
    color = "\027[30m"
    icon = " "
    if num == 0
    then
        num = "▪"
    elseif num == -1
    then
        num = "-ERR-"
        color = "\027[2m"
    elseif num >= 50
    then
        color = "\027[5m\027[35m"
        icon = "☠️"
    elseif num >= 40
    then
        color = "\027[32m"
        icon = "🐲"
    elseif num >= 30
    then
        color = "\027[35m"
        icon = "🦄"
    elseif num >= 20
    then
        color = "\027[33m"
        icon = "🔥"
    else
        color = "\027[31m"
    end
    print(string.format(" \027[1m%s%-13s%s%s %s ", color, name:upper(), tostring(num), "\027[0m", icon))
end

-- loop through folders and print folder name and count
function print_status(brand, base, folders)
    print_title(brand)
    for index, folder in ipairs(folders)
    do
        print_count(folder, count(string.format("%s/images/bdp/%s/image_processing/%s", base, brand:lower(), folder)))
    end
end

-- main loop
function main()
    base_path = get_base_path()

    --HBD
    print_status("hbd", base_path, {"overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"})

    --YHL
    print_status("yhl", base_path, {"overlay", "portrait", "logo", "house", "pdf", "recipe", "postcard"})

    --RLP
    print_status("rlp", base_path, {"overlay", "portrait", "logo", "house", "pdf"})

    print("")
end

-- run main
main()

