INCDIRS=-I$(HOME)/tools/opencv-2.4.13/include

LIBDIRS=-L$(HOME)/tools/opencv-2.4.13/lib

LIBS=-lopencv_core -lopencv_highgui

all: main

main: main.cpp
	g++ -std=c++11 $(INCDIRS) $(LIBDIRS) $< $(LIBS) -o $@

clean:
	rm main
