CHAINPREFIX=$(OPEN2X)
CROSS_COMPILE=$(CHAINPREFIX)/bin/arm-open2x-linux-

CC= $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

CFLAGS = -I"$(CHAINPREFIX)/include" `$(CHAINPREFIX)/bin/sdl-config --cflags` -DLOG_LEVEL=4 -DTARGET_GP2X -O3 -msoft-float -fomit-frame-pointer -ffast-math -funroll-loops -fno-exceptions -Wall -Wno-unknown-pragmas -Wno-format
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L$(CHAINPREFIX)/lib -lSDL_image -lSDL_ttf -lfreetype -lSDL_gfx -ljpeg -lpng12 -lSDL -lz -ldl

TARGET = ../build/gmenu2x
OBJDIR = ../objs/gp2x

SOURCES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(SOURCES))

#File types rules
$(OBJDIR)/%.o: %.cpp %.h
	$(CXX) $(CFLAGS) -o $@ -c $<

all: dir static

dir:
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi

static: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) -o $(TARGET) $(OBJS) -static `$(CHAINPREFIX)/bin/sdl-config --static-libs` $(LDFLAGS)
	$(STRIP) $(TARGET)

shared: $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) -o $(TARGET) `$(CHAINPREFIX)/bin/sdl-config --libs` $(LDFLAGS) $(OBJS)
	$(STRIP) $(TARGET)

clean:
	-rm -f $(OBJDIR)/*.o $(TARGET)

depend:
	makedepend -p$(OBJDIR)/ -- $(CFLAGS) -- *.cpp
# DO NOT DELETE

../objs/gp2x/browsedialog.o: browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/browsedialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/browsedialog.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/browsedialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/browsedialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/browsedialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/browsedialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/browsedialog.o: /usr/include/bits/types.h
../objs/gp2x/browsedialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/browsedialog.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/browsedialog.o: /usr/include/bits/endian.h
../objs/gp2x/browsedialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/browsedialog.o: /usr/include/sys/select.h
../objs/gp2x/browsedialog.o: /usr/include/bits/select.h
../objs/gp2x/browsedialog.o: /usr/include/bits/sigset.h
../objs/gp2x/browsedialog.o: /usr/include/bits/time.h
../objs/gp2x/browsedialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/browsedialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/browsedialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/browsedialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/browsedialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/browsedialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/browsedialog.o: /usr/include/stdlib.h
../objs/gp2x/browsedialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/browsedialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/browsedialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/browsedialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/browsedialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/browsedialog.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/browsedialog.o: /usr/include/iconv.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/browsedialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/browsedialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/browsedialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/browsedialog.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/browsedialog.o: surface.h sfontplus.h
../objs/gp2x/browsedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/browsedialog.o: buttonbox.h dialog.h
../objs/gp2x/buttonbox.o: button.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/buttonbox.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/buttonbox.o: /usr/include/sys/cdefs.h
../objs/gp2x/buttonbox.o: /usr/include/bits/wordsize.h
../objs/gp2x/buttonbox.o: /usr/include/gnu/stubs.h
../objs/gp2x/buttonbox.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/buttonbox.o: /usr/include/bits/types.h
../objs/gp2x/buttonbox.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/buttonbox.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/buttonbox.o: /usr/include/bits/byteswap.h
../objs/gp2x/buttonbox.o: /usr/include/sys/select.h
../objs/gp2x/buttonbox.o: /usr/include/bits/select.h
../objs/gp2x/buttonbox.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/buttonbox.o: /usr/include/sys/sysmacros.h
../objs/gp2x/buttonbox.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/buttonbox.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/buttonbox.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/buttonbox.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/buttonbox.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/buttonbox.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
../objs/gp2x/buttonbox.o: /usr/include/bits/waitstatus.h
../objs/gp2x/buttonbox.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/buttonbox.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/buttonbox.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/buttonbox.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/buttonbox.o: /usr/include/iconv.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/buttonbox.o: FastDelegate.h /usr/include/memory.h gmenu2x.h
../objs/gp2x/buttonbox.o: surfacecollection.h iconbutton.h translator.h
../objs/gp2x/buttonbox.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/buttonbox.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/buttonbox.o: inputmanager.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/buttonbox.o: surface.h sfontplus.h
../objs/gp2x/buttonbox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/buttonbox.o: buttonbox.h
../objs/gp2x/button.o: button.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/button.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/button.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
../objs/gp2x/button.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/button.o: /usr/include/bits/types.h
../objs/gp2x/button.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/button.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/button.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
../objs/gp2x/button.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
../objs/gp2x/button.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
../objs/gp2x/button.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
../objs/gp2x/button.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/button.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
../objs/gp2x/button.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
../objs/gp2x/button.o: /usr/include/bits/waitflags.h
../objs/gp2x/button.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/button.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/button.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/button.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/button.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/button.o: FastDelegate.h /usr/include/memory.h gmenu2x.h
../objs/gp2x/button.o: surfacecollection.h iconbutton.h translator.h
../objs/gp2x/button.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/button.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/button.o: inputmanager.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/button.o: surface.h sfontplus.h
../objs/gp2x/button.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/dialog.o: dialog.h gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/dialog.o: button.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/dialog.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/dialog.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
../objs/gp2x/dialog.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/dialog.o: /usr/include/bits/types.h
../objs/gp2x/dialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/dialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/dialog.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
../objs/gp2x/dialog.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
../objs/gp2x/dialog.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
../objs/gp2x/dialog.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
../objs/gp2x/dialog.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/dialog.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
../objs/gp2x/dialog.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
../objs/gp2x/dialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/dialog.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/dialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/dialog.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/dialog.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/dialog.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/dialog.o: FastDelegate.h /usr/include/memory.h translator.h
../objs/gp2x/dialog.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/dialog.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/dialog.o: inputmanager.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/dialog.o: surface.h sfontplus.h
../objs/gp2x/dialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/dirdialog.o: dirdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/dirdialog.o: iconbutton.h button.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/dirdialog.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/dirdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/dirdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/dirdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/dirdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/dirdialog.o: /usr/include/bits/types.h
../objs/gp2x/dirdialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/dirdialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/dirdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/dirdialog.o: /usr/include/sys/select.h
../objs/gp2x/dirdialog.o: /usr/include/bits/select.h
../objs/gp2x/dirdialog.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/dirdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/dirdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/dirdialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/dirdialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/dirdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/dirdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/dirdialog.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
../objs/gp2x/dirdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/dirdialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/dirdialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/dirdialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/dirdialog.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/dirdialog.o: /usr/include/iconv.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/dirdialog.o: FastDelegate.h /usr/include/memory.h translator.h
../objs/gp2x/dirdialog.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/dirdialog.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/dirdialog.o: inputmanager.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/dirdialog.o: surface.h sfontplus.h
../objs/gp2x/dirdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/dirdialog.o: browsedialog.h filelister.h buttonbox.h dialog.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/filedialog.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/filedialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/filedialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/filedialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/filedialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/filedialog.o: /usr/include/bits/types.h
../objs/gp2x/filedialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/filedialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/filedialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/filedialog.o: /usr/include/sys/select.h
../objs/gp2x/filedialog.o: /usr/include/bits/select.h
../objs/gp2x/filedialog.o: /usr/include/bits/sigset.h
../objs/gp2x/filedialog.o: /usr/include/bits/time.h
../objs/gp2x/filedialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/filedialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/filedialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/filedialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/filedialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/filedialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/filedialog.o: /usr/include/stdlib.h
../objs/gp2x/filedialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/filedialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/filedialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/filedialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/filedialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/filedialog.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/filedialog.o: /usr/include/iconv.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/filedialog.o: /usr/include/math.h /usr/include/bits/huge_val.h
../objs/gp2x/filedialog.o: /usr/include/bits/huge_valf.h
../objs/gp2x/filedialog.o: /usr/include/bits/huge_vall.h
../objs/gp2x/filedialog.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
../objs/gp2x/filedialog.o: /usr/include/bits/mathdef.h
../objs/gp2x/filedialog.o: /usr/include/bits/mathcalls.h
../objs/gp2x/filedialog.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
../objs/gp2x/filedialog.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/filedialog.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/filedialog.o: /usr/include/bits/local_lim.h
../objs/gp2x/filedialog.o: /usr/include/linux/limits.h filedialog.h
../objs/gp2x/filedialog.o: browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/filedialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/filedialog.o: FastDelegate.h /usr/include/memory.h translator.h
../objs/gp2x/filedialog.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/filedialog.o: /usr/include/bits/fcntl.h inputmanager.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/filedialog.o: surface.h sfontplus.h
../objs/gp2x/filedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/filedialog.o: buttonbox.h dialog.h
../objs/gp2x/filelister.o: /usr/include/sys/stat.h /usr/include/features.h
../objs/gp2x/filelister.o: /usr/include/sys/cdefs.h
../objs/gp2x/filelister.o: /usr/include/bits/wordsize.h
../objs/gp2x/filelister.o: /usr/include/gnu/stubs.h
../objs/gp2x/filelister.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/filelister.o: /usr/include/bits/types.h
../objs/gp2x/filelister.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/filelister.o: /usr/include/bits/stat.h /usr/include/sys/types.h
../objs/gp2x/filelister.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/filelister.o: /usr/include/bits/byteswap.h
../objs/gp2x/filelister.o: /usr/include/sys/select.h
../objs/gp2x/filelister.o: /usr/include/bits/select.h
../objs/gp2x/filelister.o: /usr/include/bits/sigset.h
../objs/gp2x/filelister.o: /usr/include/bits/time.h
../objs/gp2x/filelister.o: /usr/include/sys/sysmacros.h
../objs/gp2x/filelister.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/filelister.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/filelister.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/filelister.o: /usr/include/bits/local_lim.h
../objs/gp2x/filelister.o: /usr/include/linux/limits.h /usr/include/errno.h
../objs/gp2x/filelister.o: /usr/include/bits/errno.h
../objs/gp2x/filelister.o: /usr/include/linux/errno.h
../objs/gp2x/filelister.o: /usr/include/asm/errno.h
../objs/gp2x/filelister.o: /usr/include/asm-generic/errno.h
../objs/gp2x/filelister.o: /usr/include/asm-generic/errno-base.h filelister.h
../objs/gp2x/filelister.o: utilities.h gmenu2x.h surfacecollection.h
../objs/gp2x/filelister.o: iconbutton.h button.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/filelister.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/filelister.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/filelister.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/filelister.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/filelister.o: /usr/include/stdlib.h
../objs/gp2x/filelister.o: /usr/include/bits/waitflags.h
../objs/gp2x/filelister.o: /usr/include/bits/waitstatus.h
../objs/gp2x/filelister.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/filelister.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/filelister.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/filelister.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/filelister.o: /usr/include/iconv.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/filelister.o: FastDelegate.h /usr/include/memory.h translator.h
../objs/gp2x/filelister.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/filelister.o: /usr/include/bits/fcntl.h inputmanager.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/filelister.o: surface.h sfontplus.h
../objs/gp2x/filelister.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/filelister.o: debug.h
../objs/gp2x/gmenu2x.o: /usr/include/stdlib.h /usr/include/features.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
../objs/gp2x/gmenu2x.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/waitflags.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/endian.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/types.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/sysmacros.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/gmenu2x.o: /usr/include/alloca.h /usr/include/unistd.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/posix_opt.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/environments.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/confname.h /usr/include/getopt.h
../objs/gp2x/gmenu2x.o: /usr/include/math.h /usr/include/bits/huge_val.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/huge_valf.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/mathcalls.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/gmenu2x.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/gmenu2x.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
../objs/gp2x/gmenu2x.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/gmenu2x.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/gmenu2x.o: /usr/include/iconv.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/gmenu2x.o: /usr/include/signal.h /usr/include/bits/signum.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/siginfo.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/sigaction.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/sigcontext.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/sigstack.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/ucontext.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/sigthread.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/statvfs.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/statvfs.h /usr/include/errno.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
../objs/gp2x/gmenu2x.o: /usr/include/asm/errno.h
../objs/gp2x/gmenu2x.o: /usr/include/asm-generic/errno.h
../objs/gp2x/gmenu2x.o: /usr/include/asm-generic/errno-base.h gp2x.h
../objs/gp2x/gmenu2x.o: /usr/include/linux/types.h /usr/include/asm/types.h
../objs/gp2x/gmenu2x.o: /usr/include/asm-generic/types.h
../objs/gp2x/gmenu2x.o: /usr/include/asm-generic/int-ll64.h
../objs/gp2x/gmenu2x.o: /usr/include/asm/bitsperlong.h
../objs/gp2x/gmenu2x.o: /usr/include/asm-generic/bitsperlong.h
../objs/gp2x/gmenu2x.o: /usr/include/linux/posix_types.h
../objs/gp2x/gmenu2x.o: /usr/include/linux/stddef.h
../objs/gp2x/gmenu2x.o: /usr/include/asm/posix_types.h
../objs/gp2x/gmenu2x.o: /usr/include/asm/posix_types_64.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/fcntl.h /usr/include/fcntl.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/stat.h /usr/include/dirent.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/dirent.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/local_lim.h
../objs/gp2x/gmenu2x.o: /usr/include/linux/limits.h /usr/include/sys/ioctl.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/ioctls.h /usr/include/asm/ioctls.h
../objs/gp2x/gmenu2x.o: /usr/include/asm-generic/ioctls.h
../objs/gp2x/gmenu2x.o: /usr/include/linux/ioctl.h /usr/include/asm/ioctl.h
../objs/gp2x/gmenu2x.o: /usr/include/asm-generic/ioctl.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/ioctl-types.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/ttydefaults.h
../objs/gp2x/gmenu2x.o: /usr/include/linux/soundcard.h
../objs/gp2x/gmenu2x.o: /usr/include/linux/patchkey.h linkapp.h link.h
../objs/gp2x/gmenu2x.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/gmenu2x.o: surface.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/gmenu2x.o: linkaction.h menu.h sfontplus.h
../objs/gp2x/gmenu2x.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/gmenu2x.o: filedialog.h browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/gmenu2x.o: surfacecollection.h iconbutton.h translator.h
../objs/gp2x/gmenu2x.o: utilities.h touchscreen.h inputmanager.h buttonbox.h
../objs/gp2x/gmenu2x.o: dialog.h messagebox.h inputdialog.h settingsdialog.h
../objs/gp2x/gmenu2x.o: menusetting.h wallpaperdialog.h textdialog.h
../objs/gp2x/gmenu2x.o: menusettingint.h menusettingbool.h menusettingrgba.h
../objs/gp2x/gmenu2x.o: menusettingstring.h menusettingstringbase.h
../objs/gp2x/gmenu2x.o: menusettingmultistring.h menusettingfile.h
../objs/gp2x/gmenu2x.o: menusettingimage.h menusettingdir.h debug.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/mman.h /usr/include/bits/mman.h
../objs/gp2x/iconbutton.o: iconbutton.h button.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/iconbutton.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/iconbutton.o: /usr/include/sys/cdefs.h
../objs/gp2x/iconbutton.o: /usr/include/bits/wordsize.h
../objs/gp2x/iconbutton.o: /usr/include/gnu/stubs.h
../objs/gp2x/iconbutton.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/iconbutton.o: /usr/include/bits/types.h
../objs/gp2x/iconbutton.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/iconbutton.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/iconbutton.o: /usr/include/bits/byteswap.h
../objs/gp2x/iconbutton.o: /usr/include/sys/select.h
../objs/gp2x/iconbutton.o: /usr/include/bits/select.h
../objs/gp2x/iconbutton.o: /usr/include/bits/sigset.h
../objs/gp2x/iconbutton.o: /usr/include/bits/time.h
../objs/gp2x/iconbutton.o: /usr/include/sys/sysmacros.h
../objs/gp2x/iconbutton.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/iconbutton.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/iconbutton.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/iconbutton.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/iconbutton.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/iconbutton.o: /usr/include/stdlib.h
../objs/gp2x/iconbutton.o: /usr/include/bits/waitflags.h
../objs/gp2x/iconbutton.o: /usr/include/bits/waitstatus.h
../objs/gp2x/iconbutton.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/iconbutton.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/iconbutton.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/iconbutton.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/iconbutton.o: /usr/include/iconv.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/iconbutton.o: FastDelegate.h /usr/include/memory.h gmenu2x.h
../objs/gp2x/iconbutton.o: surfacecollection.h translator.h utilities.h
../objs/gp2x/iconbutton.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/iconbutton.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/iconbutton.o: inputmanager.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/iconbutton.o: surface.h sfontplus.h
../objs/gp2x/iconbutton.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/imagedialog.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/imagedialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/imagedialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/imagedialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/imagedialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/imagedialog.o: /usr/include/bits/types.h
../objs/gp2x/imagedialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/imagedialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/imagedialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/imagedialog.o: /usr/include/sys/select.h
../objs/gp2x/imagedialog.o: /usr/include/bits/select.h
../objs/gp2x/imagedialog.o: /usr/include/bits/sigset.h
../objs/gp2x/imagedialog.o: /usr/include/bits/time.h
../objs/gp2x/imagedialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/imagedialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/imagedialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/imagedialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/imagedialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/imagedialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/imagedialog.o: /usr/include/stdlib.h
../objs/gp2x/imagedialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/imagedialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/imagedialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/imagedialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/imagedialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/imagedialog.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/imagedialog.o: /usr/include/iconv.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/imagedialog.o: /usr/include/math.h /usr/include/bits/huge_val.h
../objs/gp2x/imagedialog.o: /usr/include/bits/huge_valf.h
../objs/gp2x/imagedialog.o: /usr/include/bits/huge_vall.h
../objs/gp2x/imagedialog.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
../objs/gp2x/imagedialog.o: /usr/include/bits/mathdef.h
../objs/gp2x/imagedialog.o: /usr/include/bits/mathcalls.h
../objs/gp2x/imagedialog.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
../objs/gp2x/imagedialog.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/imagedialog.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/imagedialog.o: /usr/include/bits/local_lim.h
../objs/gp2x/imagedialog.o: /usr/include/linux/limits.h imagedialog.h
../objs/gp2x/imagedialog.o: filedialog.h browsedialog.h filelister.h
../objs/gp2x/imagedialog.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/imagedialog.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/imagedialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/imagedialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/imagedialog.o: inputmanager.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/imagedialog.o: surface.h sfontplus.h
../objs/gp2x/imagedialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/imagedialog.o: buttonbox.h dialog.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/inputdialog.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/inputdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/inputdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/inputdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/inputdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/inputdialog.o: /usr/include/bits/types.h
../objs/gp2x/inputdialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/inputdialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/inputdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/inputdialog.o: /usr/include/sys/select.h
../objs/gp2x/inputdialog.o: /usr/include/bits/select.h
../objs/gp2x/inputdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/inputdialog.o: /usr/include/bits/time.h
../objs/gp2x/inputdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/inputdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/inputdialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/inputdialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/inputdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/inputdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/inputdialog.o: /usr/include/stdlib.h
../objs/gp2x/inputdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/inputdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/inputdialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/inputdialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/inputdialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/inputdialog.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/inputdialog.o: /usr/include/iconv.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/inputdialog.o: /usr/include/math.h /usr/include/bits/huge_val.h
../objs/gp2x/inputdialog.o: /usr/include/bits/huge_valf.h
../objs/gp2x/inputdialog.o: /usr/include/bits/huge_vall.h
../objs/gp2x/inputdialog.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
../objs/gp2x/inputdialog.o: /usr/include/bits/mathdef.h
../objs/gp2x/inputdialog.o: /usr/include/bits/mathcalls.h inputdialog.h
../objs/gp2x/inputdialog.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/inputdialog.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/inputdialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/inputdialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/inputdialog.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/inputdialog.o: surface.h sfontplus.h
../objs/gp2x/inputdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/inputdialog.o: dialog.h
../objs/gp2x/inputmanager.o: inputmanager.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/inputmanager.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/inputmanager.o: /usr/include/sys/cdefs.h
../objs/gp2x/inputmanager.o: /usr/include/bits/wordsize.h
../objs/gp2x/inputmanager.o: /usr/include/gnu/stubs.h
../objs/gp2x/inputmanager.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/inputmanager.o: /usr/include/bits/types.h
../objs/gp2x/inputmanager.o: /usr/include/bits/typesizes.h
../objs/gp2x/inputmanager.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/inputmanager.o: /usr/include/bits/endian.h
../objs/gp2x/inputmanager.o: /usr/include/bits/byteswap.h
../objs/gp2x/inputmanager.o: /usr/include/sys/select.h
../objs/gp2x/inputmanager.o: /usr/include/bits/select.h
../objs/gp2x/inputmanager.o: /usr/include/bits/sigset.h
../objs/gp2x/inputmanager.o: /usr/include/bits/time.h
../objs/gp2x/inputmanager.o: /usr/include/sys/sysmacros.h
../objs/gp2x/inputmanager.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/inputmanager.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/inputmanager.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/inputmanager.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/inputmanager.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/inputmanager.o: /usr/include/stdlib.h
../objs/gp2x/inputmanager.o: /usr/include/bits/waitflags.h
../objs/gp2x/inputmanager.o: /usr/include/bits/waitstatus.h
../objs/gp2x/inputmanager.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/inputmanager.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/inputmanager.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/inputmanager.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/inputmanager.o: /usr/include/iconv.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/inputmanager.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/inputmanager.o: utilities.h debug.h
../objs/gp2x/linkaction.o: linkaction.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/linkaction.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/linkaction.o: /usr/include/bits/wordsize.h
../objs/gp2x/linkaction.o: /usr/include/gnu/stubs.h
../objs/gp2x/linkaction.o: /usr/include/gnu/stubs-64.h link.h button.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/linkaction.o: /usr/include/sys/types.h /usr/include/bits/types.h
../objs/gp2x/linkaction.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/linkaction.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/linkaction.o: /usr/include/bits/byteswap.h
../objs/gp2x/linkaction.o: /usr/include/sys/select.h
../objs/gp2x/linkaction.o: /usr/include/bits/select.h
../objs/gp2x/linkaction.o: /usr/include/bits/sigset.h
../objs/gp2x/linkaction.o: /usr/include/bits/time.h
../objs/gp2x/linkaction.o: /usr/include/sys/sysmacros.h
../objs/gp2x/linkaction.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/linkaction.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/linkaction.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/linkaction.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/linkaction.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/linkaction.o: /usr/include/stdlib.h
../objs/gp2x/linkaction.o: /usr/include/bits/waitflags.h
../objs/gp2x/linkaction.o: /usr/include/bits/waitstatus.h
../objs/gp2x/linkaction.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/linkaction.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/linkaction.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/linkaction.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/linkaction.o: /usr/include/iconv.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/linkaction.o: surface.h
../objs/gp2x/linkaction.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/linkapp.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/linkapp.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
../objs/gp2x/linkapp.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/linkapp.o: /usr/include/bits/types.h
../objs/gp2x/linkapp.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/linkapp.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/linkapp.o: /usr/include/bits/byteswap.h
../objs/gp2x/linkapp.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/linkapp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/linkapp.o: /usr/include/sys/sysmacros.h
../objs/gp2x/linkapp.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/linkapp.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
../objs/gp2x/linkapp.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
../objs/gp2x/linkapp.o: /usr/include/bits/environments.h
../objs/gp2x/linkapp.o: /usr/include/bits/confname.h /usr/include/getopt.h
../objs/gp2x/linkapp.o: linkapp.h link.h button.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/linkapp.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/linkapp.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/linkapp.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/linkapp.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
../objs/gp2x/linkapp.o: /usr/include/bits/waitflags.h
../objs/gp2x/linkapp.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/linkapp.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/linkapp.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/linkapp.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/linkapp.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/linkapp.o: FastDelegate.h /usr/include/memory.h surface.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/linkapp.o: menu.h linkaction.h selector.h gmenu2x.h
../objs/gp2x/linkapp.o: surfacecollection.h iconbutton.h translator.h
../objs/gp2x/linkapp.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/linkapp.o: /usr/include/bits/fcntl.h inputmanager.h sfontplus.h
../objs/gp2x/linkapp.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/linkapp.o: dialog.h textmanualdialog.h textdialog.h debug.h
../objs/gp2x/link.o: link.h button.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/link.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/link.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
../objs/gp2x/link.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/link.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
../objs/gp2x/link.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/link.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
../objs/gp2x/link.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/link.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/link.o: /usr/include/sys/sysmacros.h
../objs/gp2x/link.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
../objs/gp2x/link.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/link.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
../objs/gp2x/link.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
../objs/gp2x/link.o: /usr/include/bits/waitflags.h
../objs/gp2x/link.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/link.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/link.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/link.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/link.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/link.o: FastDelegate.h /usr/include/memory.h surface.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/link.o: menu.h linkaction.h selector.h gmenu2x.h
../objs/gp2x/link.o: surfacecollection.h iconbutton.h translator.h
../objs/gp2x/link.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/link.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/link.o: inputmanager.h sfontplus.h
../objs/gp2x/link.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/link.o: dialog.h
../objs/gp2x/listview.o: listview.h gmenu2x.h surfacecollection.h
../objs/gp2x/listview.o: iconbutton.h button.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/listview.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/listview.o: /usr/include/sys/cdefs.h
../objs/gp2x/listview.o: /usr/include/bits/wordsize.h
../objs/gp2x/listview.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/listview.o: /usr/include/bits/types.h
../objs/gp2x/listview.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/listview.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/listview.o: /usr/include/bits/byteswap.h
../objs/gp2x/listview.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/listview.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/listview.o: /usr/include/sys/sysmacros.h
../objs/gp2x/listview.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/listview.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/listview.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/listview.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/listview.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/listview.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
../objs/gp2x/listview.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/listview.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/listview.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/listview.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/listview.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/listview.o: FastDelegate.h /usr/include/memory.h translator.h
../objs/gp2x/listview.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/listview.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/listview.o: inputmanager.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/listview.o: surface.h sfontplus.h
../objs/gp2x/listview.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/listview.o: listviewitem.h
../objs/gp2x/listviewitem.o: listview.h gmenu2x.h surfacecollection.h
../objs/gp2x/listviewitem.o: iconbutton.h button.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/listviewitem.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/listviewitem.o: /usr/include/sys/cdefs.h
../objs/gp2x/listviewitem.o: /usr/include/bits/wordsize.h
../objs/gp2x/listviewitem.o: /usr/include/gnu/stubs.h
../objs/gp2x/listviewitem.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/listviewitem.o: /usr/include/bits/types.h
../objs/gp2x/listviewitem.o: /usr/include/bits/typesizes.h
../objs/gp2x/listviewitem.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/listviewitem.o: /usr/include/bits/endian.h
../objs/gp2x/listviewitem.o: /usr/include/bits/byteswap.h
../objs/gp2x/listviewitem.o: /usr/include/sys/select.h
../objs/gp2x/listviewitem.o: /usr/include/bits/select.h
../objs/gp2x/listviewitem.o: /usr/include/bits/sigset.h
../objs/gp2x/listviewitem.o: /usr/include/bits/time.h
../objs/gp2x/listviewitem.o: /usr/include/sys/sysmacros.h
../objs/gp2x/listviewitem.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/listviewitem.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/listviewitem.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/listviewitem.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/listviewitem.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/listviewitem.o: /usr/include/stdlib.h
../objs/gp2x/listviewitem.o: /usr/include/bits/waitflags.h
../objs/gp2x/listviewitem.o: /usr/include/bits/waitstatus.h
../objs/gp2x/listviewitem.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/listviewitem.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/listviewitem.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/listviewitem.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/listviewitem.o: /usr/include/iconv.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/listviewitem.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/listviewitem.o: translator.h utilities.h touchscreen.h
../objs/gp2x/listviewitem.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/listviewitem.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/listviewitem.o: surface.h sfontplus.h
../objs/gp2x/listviewitem.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/listviewitem.o: listviewitem.h
../objs/gp2x/menu.o: /usr/include/sys/stat.h /usr/include/features.h
../objs/gp2x/menu.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
../objs/gp2x/menu.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/menu.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
../objs/gp2x/menu.o: /usr/include/time.h /usr/include/bits/stat.h
../objs/gp2x/menu.o: /usr/include/sys/types.h /usr/include/endian.h
../objs/gp2x/menu.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
../objs/gp2x/menu.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/menu.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/menu.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menu.o: /usr/include/bits/pthreadtypes.h /usr/include/dirent.h
../objs/gp2x/menu.o: /usr/include/bits/dirent.h
../objs/gp2x/menu.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/menu.o: /usr/include/bits/local_lim.h
../objs/gp2x/menu.o: /usr/include/linux/limits.h /usr/include/math.h
../objs/gp2x/menu.o: /usr/include/bits/huge_val.h
../objs/gp2x/menu.o: /usr/include/bits/huge_valf.h
../objs/gp2x/menu.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
../objs/gp2x/menu.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
../objs/gp2x/menu.o: /usr/include/bits/mathcalls.h gmenu2x.h
../objs/gp2x/menu.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menu.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menu.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menu.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menu.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
../objs/gp2x/menu.o: /usr/include/bits/waitflags.h
../objs/gp2x/menu.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/menu.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menu.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/menu.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/menu.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menu.o: FastDelegate.h /usr/include/memory.h translator.h
../objs/gp2x/menu.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menu.o: /usr/include/bits/fcntl.h inputmanager.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menu.o: surface.h sfontplus.h
../objs/gp2x/menu.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menu.o: linkapp.h link.h menu.h linkaction.h filelister.h
../objs/gp2x/menu.o: debug.h
../objs/gp2x/menusettingbool.o: menusettingbool.h menusetting.h buttonbox.h
../objs/gp2x/menusettingbool.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/menusettingbool.o: button.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/types.h
../objs/gp2x/menusettingbool.o: /usr/include/features.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingbool.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingbool.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/types.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingbool.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/select.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/select.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/time.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingbool.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusettingbool.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingbool.o: /usr/include/stdlib.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingbool.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusettingbool.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/menusettingbool.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingbool.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingbool.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingbool.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingbool.o: /usr/include/fcntl.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingbool.o: surface.h sfontplus.h
../objs/gp2x/menusettingbool.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusetting.o: menusetting.h buttonbox.h sfontplus.h surface.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusetting.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/menusetting.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusetting.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusetting.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusetting.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusetting.o: /usr/include/bits/types.h
../objs/gp2x/menusetting.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/menusetting.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/menusetting.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusetting.o: /usr/include/sys/select.h
../objs/gp2x/menusetting.o: /usr/include/bits/select.h
../objs/gp2x/menusetting.o: /usr/include/bits/sigset.h
../objs/gp2x/menusetting.o: /usr/include/bits/time.h
../objs/gp2x/menusetting.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusetting.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusetting.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusetting.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menusetting.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusetting.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusetting.o: /usr/include/stdlib.h
../objs/gp2x/menusetting.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusetting.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusetting.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusetting.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/menusetting.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/menusetting.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/menusetting.o: /usr/include/iconv.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusetting.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusetting.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/menusetting.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusetting.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusetting.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/menusetting.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingdir.o: menusettingdir.h menusettingstringbase.h
../objs/gp2x/menusettingdir.o: menusetting.h buttonbox.h iconbutton.h
../objs/gp2x/menusettingdir.o: button.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/types.h
../objs/gp2x/menusettingdir.o: /usr/include/features.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingdir.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingdir.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/types.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingdir.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/select.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/select.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/time.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingdir.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusettingdir.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingdir.o: /usr/include/stdlib.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingdir.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusettingdir.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/menusettingdir.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/menusettingdir.o: /usr/include/iconv.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingdir.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingdir.o: dirdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/menusettingdir.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingdir.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingdir.o: surface.h sfontplus.h
../objs/gp2x/menusettingdir.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingdir.o: browsedialog.h filelister.h dialog.h
../objs/gp2x/menusettingfile.o: menusettingfile.h menusettingstringbase.h
../objs/gp2x/menusettingfile.o: menusetting.h buttonbox.h iconbutton.h
../objs/gp2x/menusettingfile.o: button.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/types.h
../objs/gp2x/menusettingfile.o: /usr/include/features.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingfile.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingfile.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/types.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingfile.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/select.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/select.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/time.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingfile.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusettingfile.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingfile.o: /usr/include/stdlib.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingfile.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusettingfile.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/menusettingfile.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingfile.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingfile.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingfile.o: filedialog.h browsedialog.h filelister.h
../objs/gp2x/menusettingfile.o: gmenu2x.h surfacecollection.h translator.h
../objs/gp2x/menusettingfile.o: utilities.h touchscreen.h
../objs/gp2x/menusettingfile.o: /usr/include/fcntl.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingfile.o: surface.h sfontplus.h
../objs/gp2x/menusettingfile.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingfile.o: dialog.h
../objs/gp2x/menusettingimage.o: menusettingimage.h menusettingfile.h
../objs/gp2x/menusettingimage.o: menusettingstringbase.h menusetting.h
../objs/gp2x/menusettingimage.o: buttonbox.h imagedialog.h filedialog.h
../objs/gp2x/menusettingimage.o: browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/menusettingimage.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/types.h
../objs/gp2x/menusettingimage.o: /usr/include/features.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingimage.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingimage.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/types.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingimage.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/select.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/select.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/time.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingimage.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusettingimage.o: /usr/include/_G_config.h
../objs/gp2x/menusettingimage.o: /usr/include/wchar.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingimage.o: /usr/include/stdlib.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingimage.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusettingimage.o: /usr/include/xlocale.h
../objs/gp2x/menusettingimage.o: /usr/include/strings.h
../objs/gp2x/menusettingimage.o: /usr/include/inttypes.h
../objs/gp2x/menusettingimage.o: /usr/include/stdint.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingimage.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingimage.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingimage.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingimage.o: /usr/include/fcntl.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingimage.o: surface.h sfontplus.h
../objs/gp2x/menusettingimage.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingimage.o: dialog.h
../objs/gp2x/menusettingint.o: menusettingint.h menusetting.h buttonbox.h
../objs/gp2x/menusettingint.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/menusettingint.o: button.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingint.o: /usr/include/sys/types.h
../objs/gp2x/menusettingint.o: /usr/include/features.h
../objs/gp2x/menusettingint.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingint.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingint.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingint.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingint.o: /usr/include/bits/types.h
../objs/gp2x/menusettingint.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingint.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/menusettingint.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingint.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingint.o: /usr/include/sys/select.h
../objs/gp2x/menusettingint.o: /usr/include/bits/select.h
../objs/gp2x/menusettingint.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingint.o: /usr/include/bits/time.h
../objs/gp2x/menusettingint.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingint.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingint.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusettingint.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menusettingint.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingint.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingint.o: /usr/include/stdlib.h
../objs/gp2x/menusettingint.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingint.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingint.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusettingint.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/menusettingint.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/menusettingint.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/menusettingint.o: /usr/include/iconv.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingint.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingint.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingint.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/menusettingint.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingint.o: surface.h sfontplus.h
../objs/gp2x/menusettingint.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingmultistring.o: menusettingmultistring.h
../objs/gp2x/menusettingmultistring.o: menusettingstringbase.h menusetting.h
../objs/gp2x/menusettingmultistring.o: buttonbox.h gmenu2x.h
../objs/gp2x/menusettingmultistring.o: surfacecollection.h iconbutton.h
../objs/gp2x/menusettingmultistring.o: button.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/types.h
../objs/gp2x/menusettingmultistring.o: /usr/include/features.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingmultistring.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingmultistring.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/types.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingmultistring.o: /usr/include/time.h
../objs/gp2x/menusettingmultistring.o: /usr/include/endian.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/select.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/select.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/time.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingmultistring.o: /usr/include/stdio.h
../objs/gp2x/menusettingmultistring.o: /usr/include/libio.h
../objs/gp2x/menusettingmultistring.o: /usr/include/_G_config.h
../objs/gp2x/menusettingmultistring.o: /usr/include/wchar.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingmultistring.o: /usr/include/stdlib.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingmultistring.o: /usr/include/alloca.h
../objs/gp2x/menusettingmultistring.o: /usr/include/string.h
../objs/gp2x/menusettingmultistring.o: /usr/include/xlocale.h
../objs/gp2x/menusettingmultistring.o: /usr/include/strings.h
../objs/gp2x/menusettingmultistring.o: /usr/include/inttypes.h
../objs/gp2x/menusettingmultistring.o: /usr/include/stdint.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingmultistring.o: /usr/include/ctype.h
../objs/gp2x/menusettingmultistring.o: /usr/include/iconv.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingmultistring.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingmultistring.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingmultistring.o: /usr/include/fcntl.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingmultistring.o: inputmanager.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingmultistring.o: surface.h sfontplus.h
../objs/gp2x/menusettingmultistring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingrgba.o: menusettingrgba.h menusetting.h buttonbox.h
../objs/gp2x/menusettingrgba.o: surface.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/types.h
../objs/gp2x/menusettingrgba.o: /usr/include/features.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingrgba.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingrgba.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/types.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingrgba.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/select.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/select.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/time.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingrgba.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusettingrgba.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingrgba.o: /usr/include/stdlib.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingrgba.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusettingrgba.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/menusettingrgba.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingrgba.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingrgba.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/menusettingrgba.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingrgba.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingrgba.o: /usr/include/fcntl.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingrgba.o: sfontplus.h
../objs/gp2x/menusettingrgba.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingstringbase.o: menusettingstringbase.h menusetting.h
../objs/gp2x/menusettingstringbase.o: buttonbox.h gmenu2x.h
../objs/gp2x/menusettingstringbase.o: surfacecollection.h iconbutton.h
../objs/gp2x/menusettingstringbase.o: button.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingstringbase.o: /usr/include/sys/types.h
../objs/gp2x/menusettingstringbase.o: /usr/include/features.h
../objs/gp2x/menusettingstringbase.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingstringbase.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingstringbase.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/types.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingstringbase.o: /usr/include/time.h
../objs/gp2x/menusettingstringbase.o: /usr/include/endian.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingstringbase.o: /usr/include/sys/select.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/select.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/time.h
../objs/gp2x/menusettingstringbase.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingstringbase.o: /usr/include/stdio.h
../objs/gp2x/menusettingstringbase.o: /usr/include/libio.h
../objs/gp2x/menusettingstringbase.o: /usr/include/_G_config.h
../objs/gp2x/menusettingstringbase.o: /usr/include/wchar.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingstringbase.o: /usr/include/stdlib.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingstringbase.o: /usr/include/alloca.h
../objs/gp2x/menusettingstringbase.o: /usr/include/string.h
../objs/gp2x/menusettingstringbase.o: /usr/include/xlocale.h
../objs/gp2x/menusettingstringbase.o: /usr/include/strings.h
../objs/gp2x/menusettingstringbase.o: /usr/include/inttypes.h
../objs/gp2x/menusettingstringbase.o: /usr/include/stdint.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingstringbase.o: /usr/include/ctype.h
../objs/gp2x/menusettingstringbase.o: /usr/include/iconv.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingstringbase.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingstringbase.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingstringbase.o: /usr/include/fcntl.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingstringbase.o: surface.h sfontplus.h
../objs/gp2x/menusettingstringbase.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingstring.o: menusettingstring.h menusettingstringbase.h
../objs/gp2x/menusettingstring.o: menusetting.h buttonbox.h iconbutton.h
../objs/gp2x/menusettingstring.o: button.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/types.h
../objs/gp2x/menusettingstring.o: /usr/include/features.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingstring.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingstring.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/types.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingstring.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/select.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/select.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/time.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingstring.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menusettingstring.o: /usr/include/_G_config.h
../objs/gp2x/menusettingstring.o: /usr/include/wchar.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingstring.o: /usr/include/stdlib.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingstring.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/menusettingstring.o: /usr/include/xlocale.h
../objs/gp2x/menusettingstring.o: /usr/include/strings.h
../objs/gp2x/menusettingstring.o: /usr/include/inttypes.h
../objs/gp2x/menusettingstring.o: /usr/include/stdint.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingstring.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/menusettingstring.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingstring.o: inputdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/menusettingstring.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingstring.o: /usr/include/fcntl.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/menusettingstring.o: surface.h sfontplus.h
../objs/gp2x/menusettingstring.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/menusettingstring.o: dialog.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/messagebox.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/messagebox.o: /usr/include/sys/cdefs.h
../objs/gp2x/messagebox.o: /usr/include/bits/wordsize.h
../objs/gp2x/messagebox.o: /usr/include/gnu/stubs.h
../objs/gp2x/messagebox.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/messagebox.o: /usr/include/bits/types.h
../objs/gp2x/messagebox.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/messagebox.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/messagebox.o: /usr/include/bits/byteswap.h
../objs/gp2x/messagebox.o: /usr/include/sys/select.h
../objs/gp2x/messagebox.o: /usr/include/bits/select.h
../objs/gp2x/messagebox.o: /usr/include/bits/sigset.h
../objs/gp2x/messagebox.o: /usr/include/bits/time.h
../objs/gp2x/messagebox.o: /usr/include/sys/sysmacros.h
../objs/gp2x/messagebox.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/messagebox.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/messagebox.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/messagebox.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/messagebox.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/messagebox.o: /usr/include/stdlib.h
../objs/gp2x/messagebox.o: /usr/include/bits/waitflags.h
../objs/gp2x/messagebox.o: /usr/include/bits/waitstatus.h
../objs/gp2x/messagebox.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/messagebox.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/messagebox.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/messagebox.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/messagebox.o: /usr/include/iconv.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/messagebox.o: /usr/include/math.h /usr/include/bits/huge_val.h
../objs/gp2x/messagebox.o: /usr/include/bits/huge_valf.h
../objs/gp2x/messagebox.o: /usr/include/bits/huge_vall.h
../objs/gp2x/messagebox.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
../objs/gp2x/messagebox.o: /usr/include/bits/mathdef.h
../objs/gp2x/messagebox.o: /usr/include/bits/mathcalls.h messagebox.h
../objs/gp2x/messagebox.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/messagebox.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/messagebox.o: translator.h utilities.h touchscreen.h
../objs/gp2x/messagebox.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/messagebox.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/messagebox.o: surface.h sfontplus.h
../objs/gp2x/messagebox.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/selector.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/selector.o: /usr/include/sys/cdefs.h
../objs/gp2x/selector.o: /usr/include/bits/wordsize.h
../objs/gp2x/selector.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/selector.o: /usr/include/bits/types.h
../objs/gp2x/selector.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/selector.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/selector.o: /usr/include/bits/byteswap.h
../objs/gp2x/selector.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/selector.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/selector.o: /usr/include/sys/sysmacros.h
../objs/gp2x/selector.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/selector.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/selector.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/selector.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/selector.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/selector.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
../objs/gp2x/selector.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/selector.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/selector.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/selector.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/selector.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/selector.o: /usr/include/math.h /usr/include/bits/huge_val.h
../objs/gp2x/selector.o: /usr/include/bits/huge_valf.h
../objs/gp2x/selector.o: /usr/include/bits/huge_vall.h
../objs/gp2x/selector.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
../objs/gp2x/selector.o: /usr/include/bits/mathdef.h
../objs/gp2x/selector.o: /usr/include/bits/mathcalls.h
../objs/gp2x/selector.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
../objs/gp2x/selector.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/selector.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/selector.o: /usr/include/bits/local_lim.h
../objs/gp2x/selector.o: /usr/include/linux/limits.h menu.h linkaction.h
../objs/gp2x/selector.o: FastDelegate.h /usr/include/memory.h link.h button.h
../objs/gp2x/selector.o: surface.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/selector.o: linkapp.h selector.h gmenu2x.h surfacecollection.h
../objs/gp2x/selector.o: iconbutton.h translator.h utilities.h touchscreen.h
../objs/gp2x/selector.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/selector.o: inputmanager.h sfontplus.h
../objs/gp2x/selector.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/selector.o: dialog.h filelister.h debug.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/types.h
../objs/gp2x/settingsdialog.o: /usr/include/features.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/settingsdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/settingsdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/types.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/settingsdialog.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/endian.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/select.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/select.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/time.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/settingsdialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/settingsdialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/settingsdialog.o: /usr/include/stdlib.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/settingsdialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/settingsdialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/settingsdialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/settingsdialog.o: /usr/include/iconv.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/settingsdialog.o: /usr/include/math.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/huge_val.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/huge_valf.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/huge_vall.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/inf.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/nan.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/mathdef.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/mathcalls.h settingsdialog.h
../objs/gp2x/settingsdialog.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/settingsdialog.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/settingsdialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/settingsdialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/settingsdialog.o: surface.h sfontplus.h
../objs/gp2x/settingsdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/settingsdialog.o: menusetting.h buttonbox.h dialog.h
../objs/gp2x/sfontplus.o: sfontplus.h surface.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/sfontplus.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/sfontplus.o: /usr/include/sys/cdefs.h
../objs/gp2x/sfontplus.o: /usr/include/bits/wordsize.h
../objs/gp2x/sfontplus.o: /usr/include/gnu/stubs.h
../objs/gp2x/sfontplus.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/sfontplus.o: /usr/include/bits/types.h
../objs/gp2x/sfontplus.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/sfontplus.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/sfontplus.o: /usr/include/bits/byteswap.h
../objs/gp2x/sfontplus.o: /usr/include/sys/select.h
../objs/gp2x/sfontplus.o: /usr/include/bits/select.h
../objs/gp2x/sfontplus.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/sfontplus.o: /usr/include/sys/sysmacros.h
../objs/gp2x/sfontplus.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/sfontplus.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/sfontplus.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/sfontplus.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/sfontplus.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/sfontplus.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
../objs/gp2x/sfontplus.o: /usr/include/bits/waitstatus.h
../objs/gp2x/sfontplus.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/sfontplus.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/sfontplus.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/sfontplus.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/sfontplus.o: /usr/include/iconv.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/sfontplus.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/sfontplus.o: utilities.h debug.h
../objs/gp2x/surfacecollection.o: surfacecollection.h surface.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/surfacecollection.o: /usr/include/sys/types.h
../objs/gp2x/surfacecollection.o: /usr/include/features.h
../objs/gp2x/surfacecollection.o: /usr/include/sys/cdefs.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/wordsize.h
../objs/gp2x/surfacecollection.o: /usr/include/gnu/stubs.h
../objs/gp2x/surfacecollection.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/types.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/typesizes.h
../objs/gp2x/surfacecollection.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/endian.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/byteswap.h
../objs/gp2x/surfacecollection.o: /usr/include/sys/select.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/select.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/sigset.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/time.h
../objs/gp2x/surfacecollection.o: /usr/include/sys/sysmacros.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/surfacecollection.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/surfacecollection.o: /usr/include/_G_config.h
../objs/gp2x/surfacecollection.o: /usr/include/wchar.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/surfacecollection.o: /usr/include/stdlib.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/waitflags.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/waitstatus.h
../objs/gp2x/surfacecollection.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/surfacecollection.o: /usr/include/xlocale.h
../objs/gp2x/surfacecollection.o: /usr/include/strings.h
../objs/gp2x/surfacecollection.o: /usr/include/inttypes.h
../objs/gp2x/surfacecollection.o: /usr/include/stdint.h
../objs/gp2x/surfacecollection.o: /usr/include/bits/wchar.h
../objs/gp2x/surfacecollection.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/surfacecollection.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/surfacecollection.o: utilities.h debug.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_gfxPrimitives.h
../objs/gp2x/surface.o: /usr/include/math.h /usr/include/features.h
../objs/gp2x/surface.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
../objs/gp2x/surface.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/surface.o: /usr/include/bits/huge_val.h
../objs/gp2x/surface.o: /usr/include/bits/huge_valf.h
../objs/gp2x/surface.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
../objs/gp2x/surface.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
../objs/gp2x/surface.o: /usr/include/bits/mathcalls.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/surface.o: /usr/include/sys/types.h /usr/include/bits/types.h
../objs/gp2x/surface.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/surface.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/surface.o: /usr/include/bits/byteswap.h
../objs/gp2x/surface.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/surface.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/surface.o: /usr/include/sys/sysmacros.h
../objs/gp2x/surface.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
../objs/gp2x/surface.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/surface.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
../objs/gp2x/surface.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
../objs/gp2x/surface.o: /usr/include/bits/waitflags.h
../objs/gp2x/surface.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/surface.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/surface.o: /usr/include/strings.h /usr/include/inttypes.h
../objs/gp2x/surface.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/surface.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/surface.o: surface.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/surface.o: sfontplus.h
../objs/gp2x/surface.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/surface.o: utilities.h debug.h
../objs/gp2x/textdialog.o: textdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/textdialog.o: iconbutton.h button.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/textdialog.o: /usr/include/sys/types.h /usr/include/features.h
../objs/gp2x/textdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/textdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/textdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/textdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/textdialog.o: /usr/include/bits/types.h
../objs/gp2x/textdialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/textdialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/textdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/textdialog.o: /usr/include/sys/select.h
../objs/gp2x/textdialog.o: /usr/include/bits/select.h
../objs/gp2x/textdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/textdialog.o: /usr/include/bits/time.h
../objs/gp2x/textdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/textdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/textdialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/textdialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/textdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/textdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/textdialog.o: /usr/include/stdlib.h
../objs/gp2x/textdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/textdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/textdialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/textdialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/textdialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/textdialog.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/textdialog.o: /usr/include/iconv.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/textdialog.o: FastDelegate.h /usr/include/memory.h translator.h
../objs/gp2x/textdialog.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/textdialog.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/textdialog.o: inputmanager.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/textdialog.o: surface.h sfontplus.h
../objs/gp2x/textdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/textdialog.o: dialog.h
../objs/gp2x/textmanualdialog.o: textmanualdialog.h textdialog.h gmenu2x.h
../objs/gp2x/textmanualdialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/types.h
../objs/gp2x/textmanualdialog.o: /usr/include/features.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/textmanualdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/textmanualdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/types.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/textmanualdialog.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/endian.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/select.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/select.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/time.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/textmanualdialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/textmanualdialog.o: /usr/include/_G_config.h
../objs/gp2x/textmanualdialog.o: /usr/include/wchar.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/textmanualdialog.o: /usr/include/stdlib.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/textmanualdialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/textmanualdialog.o: /usr/include/xlocale.h
../objs/gp2x/textmanualdialog.o: /usr/include/strings.h
../objs/gp2x/textmanualdialog.o: /usr/include/inttypes.h
../objs/gp2x/textmanualdialog.o: /usr/include/stdint.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/wchar.h
../objs/gp2x/textmanualdialog.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/textmanualdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/textmanualdialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/textmanualdialog.o: /usr/include/fcntl.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/textmanualdialog.o: surface.h sfontplus.h
../objs/gp2x/textmanualdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/textmanualdialog.o: dialog.h
../objs/gp2x/touchscreen.o: /usr/include/unistd.h /usr/include/features.h
../objs/gp2x/touchscreen.o: /usr/include/sys/cdefs.h
../objs/gp2x/touchscreen.o: /usr/include/bits/wordsize.h
../objs/gp2x/touchscreen.o: /usr/include/gnu/stubs.h
../objs/gp2x/touchscreen.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/touchscreen.o: /usr/include/bits/posix_opt.h
../objs/gp2x/touchscreen.o: /usr/include/bits/environments.h
../objs/gp2x/touchscreen.o: /usr/include/bits/types.h
../objs/gp2x/touchscreen.o: /usr/include/bits/typesizes.h
../objs/gp2x/touchscreen.o: /usr/include/bits/confname.h
../objs/gp2x/touchscreen.o: /usr/include/getopt.h touchscreen.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/touchscreen.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/touchscreen.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/touchscreen.o: /usr/include/bits/byteswap.h
../objs/gp2x/touchscreen.o: /usr/include/sys/select.h
../objs/gp2x/touchscreen.o: /usr/include/bits/select.h
../objs/gp2x/touchscreen.o: /usr/include/bits/sigset.h
../objs/gp2x/touchscreen.o: /usr/include/bits/time.h
../objs/gp2x/touchscreen.o: /usr/include/sys/sysmacros.h
../objs/gp2x/touchscreen.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/touchscreen.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/touchscreen.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/touchscreen.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/touchscreen.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/touchscreen.o: /usr/include/stdlib.h
../objs/gp2x/touchscreen.o: /usr/include/bits/waitflags.h
../objs/gp2x/touchscreen.o: /usr/include/bits/waitstatus.h
../objs/gp2x/touchscreen.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/touchscreen.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/touchscreen.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/touchscreen.o: /usr/include/bits/wchar.h /usr/include/ctype.h
../objs/gp2x/touchscreen.o: /usr/include/iconv.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/touchscreen.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/touchscreen.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/touchscreen.o: /usr/include/bits/stat.h
../objs/gp2x/translator.o: translator.h utilities.h debug.h
../objs/gp2x/utilities.o: /usr/include/sys/stat.h /usr/include/features.h
../objs/gp2x/utilities.o: /usr/include/sys/cdefs.h
../objs/gp2x/utilities.o: /usr/include/bits/wordsize.h
../objs/gp2x/utilities.o: /usr/include/gnu/stubs.h
../objs/gp2x/utilities.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/utilities.o: /usr/include/bits/types.h
../objs/gp2x/utilities.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/utilities.o: /usr/include/bits/stat.h /usr/include/sys/types.h
../objs/gp2x/utilities.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/utilities.o: /usr/include/bits/byteswap.h
../objs/gp2x/utilities.o: /usr/include/sys/select.h
../objs/gp2x/utilities.o: /usr/include/bits/select.h
../objs/gp2x/utilities.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/utilities.o: /usr/include/sys/sysmacros.h
../objs/gp2x/utilities.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/utilities.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/utilities.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/utilities.o: /usr/include/bits/local_lim.h
../objs/gp2x/utilities.o: /usr/include/linux/limits.h /usr/include/strings.h
../objs/gp2x/utilities.o: /usr/include/math.h /usr/include/bits/huge_val.h
../objs/gp2x/utilities.o: /usr/include/bits/huge_valf.h
../objs/gp2x/utilities.o: /usr/include/bits/huge_vall.h
../objs/gp2x/utilities.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
../objs/gp2x/utilities.o: /usr/include/bits/mathdef.h
../objs/gp2x/utilities.o: /usr/include/bits/mathcalls.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/utilities.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/utilities.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/utilities.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/utilities.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/utilities.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
../objs/gp2x/utilities.o: /usr/include/bits/waitstatus.h
../objs/gp2x/utilities.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/utilities.o: /usr/include/xlocale.h /usr/include/inttypes.h
../objs/gp2x/utilities.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/utilities.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/utilities.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/utilities.o: utilities.h debug.h
../objs/gp2x/wallpaperdialog.o: wallpaperdialog.h gmenu2x.h
../objs/gp2x/wallpaperdialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_main.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_stdinc.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_config.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_platform.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/types.h
../objs/gp2x/wallpaperdialog.o: /usr/include/features.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/wallpaperdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/wallpaperdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/types.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/wallpaperdialog.o: /usr/include/time.h /usr/include/endian.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/endian.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/select.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/select.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/time.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/wallpaperdialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/wallpaperdialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/wallpaperdialog.o: /usr/include/stdlib.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/wallpaperdialog.o: /usr/include/alloca.h /usr/include/string.h
../objs/gp2x/wallpaperdialog.o: /usr/include/xlocale.h /usr/include/strings.h
../objs/gp2x/wallpaperdialog.o: /usr/include/inttypes.h /usr/include/stdint.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/wchar.h
../objs/gp2x/wallpaperdialog.o: /usr/include/ctype.h /usr/include/iconv.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/begin_code.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/close_code.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_audio.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_error.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_endian.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mutex.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_thread.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_rwops.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cdrom.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_cpuinfo.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_events.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_active.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keyboard.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_keysym.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_mouse.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_video.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_joystick.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_quit.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_loadso.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_timer.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_version.h
../objs/gp2x/wallpaperdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/wallpaperdialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/wallpaperdialog.o: /usr/include/fcntl.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/stat.h inputmanager.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_image.h
../objs/gp2x/wallpaperdialog.o: surface.h sfontplus.h
../objs/gp2x/wallpaperdialog.o: /opt/open2x/gcc-4.1.1-glibc-2.3.6/include/SDL/SDL_ttf.h
../objs/gp2x/wallpaperdialog.o: dialog.h filelister.h debug.h
