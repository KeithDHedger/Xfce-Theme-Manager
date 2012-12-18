PROGRAM=translate
SOURCES=translate.cpp ../src/globals.cpp
VERSION=0.2.1

CXXFLAGS=-O3 -Wall -Wunused-result -Wunused-function -lXcursor -lgthread-2.0 `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gdk-2.0` `pkg-config --cflags --libs gtk+-2.0` -DGTK_DISABLE_DEPRECATED -DGTK_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGSEAL_ENABLE $(LIBXFCEUI) $(USELIBXFCEUI)

$(PROGRAM):$(SOURCES)
	g++ $(SOURCES) $(CXXFLAGS) -o $(PROGRAM)
