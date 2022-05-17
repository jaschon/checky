name = checky+

check_folders: $(name).cpp
	gcc -o $(name) $(name).cpp -lstdc++
install: $(name)
	cp ./$(name) /usr/local/bin/
uninstall:
	rm -r /usr/local/bin/$(name)
