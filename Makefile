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
	@if [ ! -d $(DISTDIR) ]; then mkdir -p $(DISTDIR); fi
	install -m755 $(APPNAME)-debug $(DISTDIR)/gmenu2x
	install -m644 $(BUILDDIR)/input.conf.$(TARGET) $(DISTDIR)/input.conf
	cp -R $(BUILDDIR)/skins $(BUILDDIR)/translations $(DISTDIR)
	mkdir -p $(DISTDIR)/sections/applications $(DISTDIR)/sections/emulators $(DISTDIR)/sections/games $(DISTDIR)/sections/settings

depend:
	makedepend -fMakefile.$(TARGET) -p$(OBJDIR)/ -- $(CFLAGS) -- src/*.cpp
# DO NOT DELETE
