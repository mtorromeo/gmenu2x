TARGET=pc

CC = gcc
CXX = g++
STRIP = strip

CFLAGS = -I"/usr/include" `sdl-config --cflags` -DTARGET_PC -DTARGET=$(TARGET) -DLOG_LEVEL=4 -Wall -Wundef -Wno-deprecated -Wno-unknown-pragmas -Wno-format -fno-exceptions -pg -O3 -g
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L"/usr/lib" `sdl-config --libs` -lfreetype -lSDL_image -lSDL_ttf -lSDL_gfx -ljpeg -lpng12 -lz #-lSDL_gfx

BUILDDIR = build
OBJDIR = objs/$(TARGET)
DISTDIR = dist/$(TARGET)
APPNAME = $(BUILDDIR)/gmenu2x.$(TARGET)

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
	install -m755 -D $(APPNAME) $(DISTDIR)/gmenu2x
	install -m644 assets/$(TARGET)/input.conf $(DISTDIR)
	install -m755 -d $(DISTDIR)/sections/applications $(DISTDIR)/sections/emulators $(DISTDIR)/sections/games $(DISTDIR)/sections/settings
	cp -R assets/skins assets/translations $(DISTDIR)

depend:
	makedepend -fMakefile.$(TARGET) -p$(OBJDIR)/ -- $(CFLAGS) -- src/*.cpp
# DO NOT DELETE
