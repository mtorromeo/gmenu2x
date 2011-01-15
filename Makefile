TARGET=pc

CC = gcc
CXX = g++
STRIP = strip

CFLAGS = -I"/usr/include" `sdl-config --cflags` -DTARGET_PC -DTARGET=$(TARGET) -DLOG_LEVEL=4 -Wall -Wundef -Wno-deprecated -Wno-unknown-pragmas -Wno-format -pg -O0 -g3
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L"/usr/lib" `sdl-config --libs` -lfreetype -lSDL_image -lSDL_ttf -lSDL_gfx -ljpeg -lpng12 -lz #-lSDL_gfx

OBJDIR = objs/$(TARGET)
DISTDIR = dist/$(TARGET)/gmenu2x
APPNAME = $(OBJDIR)/gmenu2x

SOURCES := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, $(OBJDIR)/src/%.o, $(SOURCES))

# File types rules
$(OBJDIR)/src/%.o: src/%.cpp src/%.h
	$(CXX) $(CFLAGS) -o $@ -c $<

all: dir shared

dir:
	@if [ ! -d $(OBJDIR)/src ]; then mkdir -p $(OBJDIR)/src; fi

debug: $(OBJS)
	@echo "Linking gmenu2x-debug..."
	$(CXX) -o $(APPNAME)-debug $(LDFLAGS) $(OBJS)

shared: debug
	$(STRIP) $(APPNAME)-debug -o $(APPNAME)

clean:
	rm -rf $(OBJDIR) $(DISTDIR) *.gcda *.gcno $(APPNAME)

dist: dir shared
	install -m755 -D $(APPNAME)-debug $(DISTDIR)/gmenu2x
	install -m644 assets/$(TARGET)/input.conf $(DISTDIR)
	install -m755 -d $(DISTDIR)/sections/applications $(DISTDIR)/sections/emulators $(DISTDIR)/sections/games $(DISTDIR)/sections/settings
	install -m644 -D README.rst $(DISTDIR)/README.txt
	install -m644 -D COPYING $(DISTDIR)/COPYING
	install -m644 -D ChangeLog $(DISTDIR)/ChangeLog
	cp -RH assets/skins assets/translations $(DISTDIR)

-include $(patsubst src/%.cpp, $(OBJDIR)/src/%.d, $(SOURCES))

$(OBJDIR)/src/%.d: src/%.cpp
	@if [ ! -d $(OBJDIR)/src ]; then mkdir -p $(OBJDIR)/src; fi
	$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
