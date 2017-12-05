all: project

project: project.cpp
	g++   project.cpp perlin.cpp simran.cpp -Wall -oproject -lX11 -lm \
	    -D USE_OPENAL_SOUND \
	    /usr/lib/x86_64-linux-gnu/libopenal.so \
	    /usr/lib/x86_64-linux-gnu/libalut.so

clean:
	rm -f project
