prefix?=/usr/local
debug_flags?=

maintainer_name ?= Noah Paladino
maintainer_email ?= sgt@noahpaladino.com

build: ButtonBox.o Prompt.o main.o 
	mkdir -p bin
	g++ $(debug_flags) main.o ButtonBox.o Prompt.o -std=c++11 -o bin/sgt `pkg-config gtkmm-3.0 --cflags --libs`
main.o: ButtonBox.o Prompt.o src/main.cpp 
	g++ $(debug_flags) -c src/main.cpp -std=c++11 `pkg-config gtkmm-3.0 --cflags --libs`
ButtonBox.o: src/ButtonBox.cpp
	g++ $(debug_flags) -c src/ButtonBox.cpp -std=c++11 `pkg-config gtkmm-3.0 --cflags --libs`
Prompt.o: src/Prompt.cpp
	g++ $(debug_flags) -c src/Prompt.cpp -std=c++11 `pkg-config gtkmm-3.0 --cflags --libs`
install: build clean
	cp bin/sgt $(prefix)/bin
clean:
	rm -rf *.o
uninstall:
	rm $(prefix)/bin/sgt

deb: build
	mkdir -p pkg/DEBIAN pkg/usr/bin
	cp bin/sgt pkg/usr/bin/sgt
	echo "Package: simple-gtk-tools\nVersion: 1.0\nSection: utils\nPriority: optional\nArchitecture: amd64\nMaintainer: $(maintainer_name) <$(maintainer_email)>\nDescription: Simple GTK tools" > pkg/DEBIAN/control
	dpkg-deb --build pkg simple-gtk-tools_1.0_amd64.deb
	rm -rf pkg

rpm: build
	mkdir -p pkg/usr/bin
	cp bin/sgt pkg/usr/bin/sgt
	fpm -s dir -t rpm -n simple-gtk-tools -v 1.0 --maintainer "$(maintainer_name) <$(maintainer_email)>" --prefix=/usr pkg/usr/bin/sgt
	rm -rf pkg
