name = checky

check_folders: $(name).c
	gcc -o $(name) $(name).c
install: $(name)
	cp ./$(name) /usr/local/bin/
uninstall:
	rm -r /usr/local/bin/$(name)
