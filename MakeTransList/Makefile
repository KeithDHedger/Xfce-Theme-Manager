PROGRAM1=translategui
SOURCES1=translate.cpp ../Xfce-Theme-Manager/src/globals.cpp
PROGRAM2=translatehelp
SOURCES2=translatehelp.cpp ../Xfce-Theme-Manager/src/globals.cpp
VERSION=0.3.3


CXXFLAGS=-O3 -Wall -Wunused-result -Wunused-function -lXcursor -lgthread-2.0 `pkg-config --cflags --libs libxfconf-0` `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gdk-2.0` `pkg-config --cflags --libs gtk+-2.0` -DVERSION -DGTK_DISABLE_DEPRECATED -DGTK_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGSEAL_ENABLE $(LIBXFCEUI) $(USELIBXFCEUI)

all:
	g++ $(SOURCES1) $(CXXFLAGS) -o $(PROGRAM1)
	g++ $(SOURCES2) $(CXXFLAGS) -o $(PROGRAM2)
	./$(PROGRAM1)
	./$(PROGRAM2)

clean:
	rm $(PROGRAM1) $(PROGRAM2)

