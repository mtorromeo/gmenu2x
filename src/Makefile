CHAINPREFIX=$(OPEN2X)
CROSS_COMPILE=$(CHAINPREFIX)/bin/arm-open2x-linux-

CC= $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

CFLAGS = -I"$(CHAINPREFIX)/include" `$(CHAINPREFIX)/bin/sdl-config --cflags` -DTARGET_GP2X -DTIXML_USE_STL -O3 -msoft-float -fomit-frame-pointer -ffast-math -funroll-loops -fno-exceptions -Wall -Wno-unknown-pragmas -Wno-format
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L$(CHAINPREFIX)/lib `$(CHAINPREFIX)/bin/sdl-config --libs` -lfreetype -lSDL_image -lSDL_ttf -lSDL_gfx -ljpeg -lpng12 -lSDL -lz -ldl

TARGET = ../build/gmenu2x
OBJDIR = ../objs/gp2x

SOURCES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(SOURCES))

#File types rules
$(OBJDIR)/%.o: %.cpp %.h
	$(CXX) $(CFLAGS) -o $@ -c $<

all: static

static: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OBJS)
	$(STRIP) $(TARGET)

shared: $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OBJS)
	$(STRIP) $(TARGET)

clean:
	-rm -f $(OBJDIR)/*.o $(TARGET)

depend:
	makedepend -p$(OBJDIR)/ -- $(CFLAGS) -- *.cpp
# DO NOT DELETE

../objs/gp2x/browsedialog.o: browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/browsedialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/browsedialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/browsedialog.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/browsedialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/browsedialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/browsedialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/browsedialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/browsedialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/browsedialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/browsedialog.o: /usr/include/sys/types.h
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
../objs/gp2x/browsedialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/browsedialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/browsedialog.o: surface.h sfontplus.h buttonbox.h dialog.h
../objs/gp2x/buttonbox.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/buttonbox.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/buttonbox.o: /usr/include/bits/wordsize.h
../objs/gp2x/buttonbox.o: /usr/include/gnu/stubs.h
../objs/gp2x/buttonbox.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/buttonbox.o: /usr/include/xlocale.h gmenu2x.h
../objs/gp2x/buttonbox.o: surfacecollection.h iconbutton.h translator.h
../objs/gp2x/buttonbox.o: utilities.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/buttonbox.o: /usr/include/bits/fcntl.h /usr/include/sys/types.h
../objs/gp2x/buttonbox.o: /usr/include/bits/types.h
../objs/gp2x/buttonbox.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/buttonbox.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/buttonbox.o: /usr/include/bits/byteswap.h
../objs/gp2x/buttonbox.o: /usr/include/sys/select.h
../objs/gp2x/buttonbox.o: /usr/include/bits/select.h
../objs/gp2x/buttonbox.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/buttonbox.o: /usr/include/sys/sysmacros.h
../objs/gp2x/buttonbox.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/buttonbox.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/buttonbox.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/buttonbox.o: sfontplus.h buttonbox.h
../objs/gp2x/button.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/button.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/button.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
../objs/gp2x/button.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/button.o: /usr/include/xlocale.h gmenu2x.h surfacecollection.h
../objs/gp2x/button.o: iconbutton.h translator.h utilities.h touchscreen.h
../objs/gp2x/button.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/button.o: /usr/include/sys/types.h /usr/include/bits/types.h
../objs/gp2x/button.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/button.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/button.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
../objs/gp2x/button.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
../objs/gp2x/button.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
../objs/gp2x/button.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/button.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/button.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/button.o: sfontplus.h
../objs/gp2x/dialog.o: dialog.h gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/dialog.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/dialog.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/dialog.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
../objs/gp2x/dialog.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/dialog.o: /usr/include/xlocale.h translator.h utilities.h
../objs/gp2x/dialog.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/dialog.o: /usr/include/bits/fcntl.h /usr/include/sys/types.h
../objs/gp2x/dialog.o: /usr/include/bits/types.h
../objs/gp2x/dialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/dialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/dialog.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
../objs/gp2x/dialog.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
../objs/gp2x/dialog.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
../objs/gp2x/dialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/dialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/dialog.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/dialog.o: sfontplus.h
../objs/gp2x/dirdialog.o: dirdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/dirdialog.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/dirdialog.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/dirdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/dirdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/dirdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/dirdialog.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/dirdialog.o: /usr/include/xlocale.h translator.h utilities.h
../objs/gp2x/dirdialog.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/dirdialog.o: /usr/include/bits/fcntl.h /usr/include/sys/types.h
../objs/gp2x/dirdialog.o: /usr/include/bits/types.h
../objs/gp2x/dirdialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/dirdialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/dirdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/dirdialog.o: /usr/include/sys/select.h
../objs/gp2x/dirdialog.o: /usr/include/bits/select.h
../objs/gp2x/dirdialog.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/dirdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/dirdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/dirdialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/dirdialog.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/dirdialog.o: sfontplus.h browsedialog.h filelister.h buttonbox.h
../objs/gp2x/dirdialog.o: dialog.h
../objs/gp2x/filedialog.o: /usr/include/sys/stat.h /usr/include/features.h
../objs/gp2x/filedialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/filedialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/filedialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/filedialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/filedialog.o: /usr/include/bits/types.h
../objs/gp2x/filedialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/filedialog.o: /usr/include/bits/stat.h /usr/include/sys/types.h
../objs/gp2x/filedialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/filedialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/filedialog.o: /usr/include/sys/select.h
../objs/gp2x/filedialog.o: /usr/include/bits/select.h
../objs/gp2x/filedialog.o: /usr/include/bits/sigset.h
../objs/gp2x/filedialog.o: /usr/include/bits/time.h
../objs/gp2x/filedialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/filedialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/filedialog.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/filedialog.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/filedialog.o: /usr/include/bits/local_lim.h
../objs/gp2x/filedialog.o: /usr/include/linux/limits.h filedialog.h
../objs/gp2x/filedialog.o: browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/filedialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/filedialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/filedialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/filedialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/filedialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/filedialog.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/filedialog.o: inputmanager.h surface.h sfontplus.h buttonbox.h
../objs/gp2x/filedialog.o: dialog.h
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
../objs/gp2x/filelister.o: utilities.h
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
../objs/gp2x/gmenu2x.o: /usr/include/bits/mathcalls.h /usr/include/signal.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/signum.h
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
../objs/gp2x/gmenu2x.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/gmenu2x.o: surface.h sfontplus.h linkaction.h menu.h
../objs/gp2x/gmenu2x.o: filedialog.h browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/gmenu2x.o: surfacecollection.h iconbutton.h translator.h
../objs/gp2x/gmenu2x.o: utilities.h touchscreen.h /usr/include/stdint.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/wchar.h inputmanager.h buttonbox.h
../objs/gp2x/gmenu2x.o: dialog.h messagebox.h inputdialog.h settingsdialog.h
../objs/gp2x/gmenu2x.o: menusetting.h wallpaperdialog.h textdialog.h
../objs/gp2x/gmenu2x.o: menusettingint.h menusettingbool.h menusettingrgba.h
../objs/gp2x/gmenu2x.o: menusettingstring.h menusettingstringbase.h
../objs/gp2x/gmenu2x.o: menusettingmultistring.h menusettingfile.h
../objs/gp2x/gmenu2x.o: menusettingimage.h menusettingdir.h
../objs/gp2x/gmenu2x.o: /usr/include/sys/mman.h /usr/include/bits/mman.h
../objs/gp2x/iconbutton.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/iconbutton.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/iconbutton.o: /usr/include/sys/cdefs.h
../objs/gp2x/iconbutton.o: /usr/include/bits/wordsize.h
../objs/gp2x/iconbutton.o: /usr/include/gnu/stubs.h
../objs/gp2x/iconbutton.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/iconbutton.o: /usr/include/xlocale.h gmenu2x.h
../objs/gp2x/iconbutton.o: surfacecollection.h translator.h utilities.h
../objs/gp2x/iconbutton.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/iconbutton.o: /usr/include/bits/fcntl.h /usr/include/sys/types.h
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
../objs/gp2x/iconbutton.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/iconbutton.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/iconbutton.o: sfontplus.h
../objs/gp2x/imagedialog.o: /usr/include/sys/stat.h /usr/include/features.h
../objs/gp2x/imagedialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/imagedialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/imagedialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/imagedialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/imagedialog.o: /usr/include/bits/types.h
../objs/gp2x/imagedialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/imagedialog.o: /usr/include/bits/stat.h /usr/include/sys/types.h
../objs/gp2x/imagedialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/imagedialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/imagedialog.o: /usr/include/sys/select.h
../objs/gp2x/imagedialog.o: /usr/include/bits/select.h
../objs/gp2x/imagedialog.o: /usr/include/bits/sigset.h
../objs/gp2x/imagedialog.o: /usr/include/bits/time.h
../objs/gp2x/imagedialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/imagedialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/imagedialog.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/imagedialog.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/imagedialog.o: /usr/include/bits/local_lim.h
../objs/gp2x/imagedialog.o: /usr/include/linux/limits.h imagedialog.h
../objs/gp2x/imagedialog.o: filedialog.h browsedialog.h filelister.h
../objs/gp2x/imagedialog.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/imagedialog.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/imagedialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/imagedialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/imagedialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/imagedialog.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/imagedialog.o: inputmanager.h surface.h sfontplus.h buttonbox.h
../objs/gp2x/imagedialog.o: dialog.h
../objs/gp2x/inputdialog.o: inputdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/inputdialog.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/inputdialog.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/inputdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/inputdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/inputdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/inputdialog.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/inputdialog.o: /usr/include/xlocale.h translator.h utilities.h
../objs/gp2x/inputdialog.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/inputdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/inputdialog.o: /usr/include/sys/types.h
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
../objs/gp2x/inputdialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/inputdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/inputdialog.o: surface.h sfontplus.h dialog.h
../objs/gp2x/inputmanager.o: inputmanager.h utilities.h
../objs/gp2x/linkaction.o: linkaction.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/linkaction.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/linkaction.o: /usr/include/bits/wordsize.h
../objs/gp2x/linkaction.o: /usr/include/gnu/stubs.h
../objs/gp2x/linkaction.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/linkaction.o: /usr/include/xlocale.h link.h button.h surface.h
../objs/gp2x/linkaction.o: sfontplus.h
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
../objs/gp2x/linkapp.o: linkapp.h link.h button.h FastDelegate.h
../objs/gp2x/linkapp.o: /usr/include/memory.h /usr/include/string.h
../objs/gp2x/linkapp.o: /usr/include/xlocale.h surface.h sfontplus.h menu.h
../objs/gp2x/linkapp.o: linkaction.h selector.h gmenu2x.h surfacecollection.h
../objs/gp2x/linkapp.o: iconbutton.h translator.h utilities.h touchscreen.h
../objs/gp2x/linkapp.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/linkapp.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/linkapp.o: inputmanager.h dialog.h textmanualdialog.h
../objs/gp2x/linkapp.o: textdialog.h
../objs/gp2x/link.o: link.h button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/link.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/link.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
../objs/gp2x/link.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/link.o: /usr/include/xlocale.h surface.h sfontplus.h menu.h
../objs/gp2x/link.o: linkaction.h selector.h gmenu2x.h surfacecollection.h
../objs/gp2x/link.o: iconbutton.h translator.h utilities.h touchscreen.h
../objs/gp2x/link.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/link.o: /usr/include/sys/types.h /usr/include/bits/types.h
../objs/gp2x/link.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/link.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/link.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
../objs/gp2x/link.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
../objs/gp2x/link.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
../objs/gp2x/link.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/link.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/link.o: /usr/include/bits/wchar.h inputmanager.h dialog.h
../objs/gp2x/listview.o: listview.h gmenu2x.h surfacecollection.h
../objs/gp2x/listview.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/listview.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/listview.o: /usr/include/sys/cdefs.h
../objs/gp2x/listview.o: /usr/include/bits/wordsize.h
../objs/gp2x/listview.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/listview.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/listview.o: translator.h utilities.h touchscreen.h
../objs/gp2x/listview.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/listview.o: /usr/include/sys/types.h /usr/include/bits/types.h
../objs/gp2x/listview.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/listview.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/listview.o: /usr/include/bits/byteswap.h
../objs/gp2x/listview.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/listview.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/listview.o: /usr/include/sys/sysmacros.h
../objs/gp2x/listview.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/listview.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/listview.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/listview.o: sfontplus.h listviewitem.h
../objs/gp2x/listviewitem.o: listview.h gmenu2x.h surfacecollection.h
../objs/gp2x/listviewitem.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/listviewitem.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/listviewitem.o: /usr/include/sys/cdefs.h
../objs/gp2x/listviewitem.o: /usr/include/bits/wordsize.h
../objs/gp2x/listviewitem.o: /usr/include/gnu/stubs.h
../objs/gp2x/listviewitem.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/listviewitem.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/listviewitem.o: translator.h utilities.h touchscreen.h
../objs/gp2x/listviewitem.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/listviewitem.o: /usr/include/sys/types.h
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
../objs/gp2x/listviewitem.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/listviewitem.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/listviewitem.o: surface.h sfontplus.h listviewitem.h
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
../objs/gp2x/menu.o: surfacecollection.h iconbutton.h button.h FastDelegate.h
../objs/gp2x/menu.o: /usr/include/memory.h /usr/include/string.h
../objs/gp2x/menu.o: /usr/include/xlocale.h translator.h utilities.h
../objs/gp2x/menu.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menu.o: /usr/include/bits/fcntl.h /usr/include/stdint.h
../objs/gp2x/menu.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/menu.o: sfontplus.h linkapp.h link.h menu.h linkaction.h
../objs/gp2x/menu.o: filelister.h
../objs/gp2x/menusettingbool.o: menusettingbool.h menusetting.h buttonbox.h
../objs/gp2x/menusettingbool.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/menusettingbool.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingbool.o: /usr/include/features.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingbool.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingbool.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingbool.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingbool.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingbool.o: /usr/include/fcntl.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingbool.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingbool.o: /usr/include/stdint.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingbool.o: surface.h sfontplus.h
../objs/gp2x/menusetting.o: menusetting.h buttonbox.h sfontplus.h gmenu2x.h
../objs/gp2x/menusetting.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/menusetting.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusetting.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/menusetting.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusetting.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusetting.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/menusetting.o: /usr/include/xlocale.h translator.h utilities.h
../objs/gp2x/menusetting.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menusetting.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusetting.o: /usr/include/sys/types.h
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
../objs/gp2x/menusetting.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/menusetting.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusetting.o: surface.h
../objs/gp2x/menusettingdir.o: menusettingdir.h menusettingstringbase.h
../objs/gp2x/menusettingdir.o: menusetting.h buttonbox.h iconbutton.h
../objs/gp2x/menusettingdir.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingdir.o: /usr/include/features.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingdir.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingdir.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingdir.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingdir.o: dirdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/menusettingdir.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingdir.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingdir.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingdir.o: surface.h sfontplus.h browsedialog.h
../objs/gp2x/menusettingdir.o: filelister.h dialog.h
../objs/gp2x/menusettingfile.o: menusettingfile.h menusettingstringbase.h
../objs/gp2x/menusettingfile.o: menusetting.h buttonbox.h iconbutton.h
../objs/gp2x/menusettingfile.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingfile.o: /usr/include/features.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingfile.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingfile.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingfile.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingfile.o: filedialog.h browsedialog.h filelister.h
../objs/gp2x/menusettingfile.o: gmenu2x.h surfacecollection.h translator.h
../objs/gp2x/menusettingfile.o: utilities.h touchscreen.h
../objs/gp2x/menusettingfile.o: /usr/include/fcntl.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingfile.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingfile.o: /usr/include/stdint.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingfile.o: surface.h sfontplus.h dialog.h
../objs/gp2x/menusettingimage.o: menusettingimage.h menusettingfile.h
../objs/gp2x/menusettingimage.o: menusettingstringbase.h menusetting.h
../objs/gp2x/menusettingimage.o: buttonbox.h imagedialog.h filedialog.h
../objs/gp2x/menusettingimage.o: browsedialog.h filelister.h gmenu2x.h
../objs/gp2x/menusettingimage.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/menusettingimage.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingimage.o: /usr/include/features.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingimage.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingimage.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingimage.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingimage.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingimage.o: /usr/include/fcntl.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingimage.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingimage.o: /usr/include/stdint.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingimage.o: surface.h sfontplus.h dialog.h
../objs/gp2x/menusettingint.o: menusettingint.h menusetting.h buttonbox.h
../objs/gp2x/menusettingint.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/menusettingint.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingint.o: /usr/include/features.h
../objs/gp2x/menusettingint.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingint.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingint.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingint.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingint.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingint.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingint.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/menusettingint.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingint.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/menusettingint.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingint.o: surface.h sfontplus.h
../objs/gp2x/menusettingmultistring.o: menusettingmultistring.h
../objs/gp2x/menusettingmultistring.o: menusettingstringbase.h menusetting.h
../objs/gp2x/menusettingmultistring.o: buttonbox.h gmenu2x.h
../objs/gp2x/menusettingmultistring.o: surfacecollection.h iconbutton.h
../objs/gp2x/menusettingmultistring.o: button.h FastDelegate.h
../objs/gp2x/menusettingmultistring.o: /usr/include/memory.h
../objs/gp2x/menusettingmultistring.o: /usr/include/features.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingmultistring.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingmultistring.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingmultistring.o: /usr/include/string.h
../objs/gp2x/menusettingmultistring.o: /usr/include/xlocale.h translator.h
../objs/gp2x/menusettingmultistring.o: utilities.h touchscreen.h
../objs/gp2x/menusettingmultistring.o: /usr/include/fcntl.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingmultistring.o: /usr/include/stdint.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingmultistring.o: inputmanager.h surface.h sfontplus.h
../objs/gp2x/menusettingrgba.o: menusettingrgba.h menusetting.h buttonbox.h
../objs/gp2x/menusettingrgba.o: surface.h sfontplus.h gmenu2x.h
../objs/gp2x/menusettingrgba.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/menusettingrgba.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingrgba.o: /usr/include/features.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingrgba.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingrgba.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingrgba.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingrgba.o: translator.h utilities.h touchscreen.h
../objs/gp2x/menusettingrgba.o: /usr/include/fcntl.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingrgba.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingrgba.o: /usr/include/stdint.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingstringbase.o: menusettingstringbase.h menusetting.h
../objs/gp2x/menusettingstringbase.o: buttonbox.h gmenu2x.h
../objs/gp2x/menusettingstringbase.o: surfacecollection.h iconbutton.h
../objs/gp2x/menusettingstringbase.o: button.h FastDelegate.h
../objs/gp2x/menusettingstringbase.o: /usr/include/memory.h
../objs/gp2x/menusettingstringbase.o: /usr/include/features.h
../objs/gp2x/menusettingstringbase.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingstringbase.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingstringbase.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingstringbase.o: /usr/include/string.h
../objs/gp2x/menusettingstringbase.o: /usr/include/xlocale.h translator.h
../objs/gp2x/menusettingstringbase.o: utilities.h touchscreen.h
../objs/gp2x/menusettingstringbase.o: /usr/include/fcntl.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingstringbase.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingstringbase.o: /usr/include/stdint.h
../objs/gp2x/menusettingstringbase.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingstringbase.o: inputmanager.h surface.h sfontplus.h
../objs/gp2x/menusettingstring.o: menusettingstring.h menusettingstringbase.h
../objs/gp2x/menusettingstring.o: menusetting.h buttonbox.h iconbutton.h
../objs/gp2x/menusettingstring.o: button.h FastDelegate.h
../objs/gp2x/menusettingstring.o: /usr/include/memory.h
../objs/gp2x/menusettingstring.o: /usr/include/features.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingstring.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingstring.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingstring.o: /usr/include/string.h
../objs/gp2x/menusettingstring.o: /usr/include/xlocale.h inputdialog.h
../objs/gp2x/menusettingstring.o: gmenu2x.h surfacecollection.h translator.h
../objs/gp2x/menusettingstring.o: utilities.h touchscreen.h
../objs/gp2x/menusettingstring.o: /usr/include/fcntl.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/types.h
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
../objs/gp2x/menusettingstring.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingstring.o: /usr/include/stdint.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingstring.o: surface.h sfontplus.h dialog.h
../objs/gp2x/messagebox.o: messagebox.h gmenu2x.h surfacecollection.h
../objs/gp2x/messagebox.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/messagebox.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/messagebox.o: /usr/include/sys/cdefs.h
../objs/gp2x/messagebox.o: /usr/include/bits/wordsize.h
../objs/gp2x/messagebox.o: /usr/include/gnu/stubs.h
../objs/gp2x/messagebox.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/messagebox.o: /usr/include/xlocale.h translator.h utilities.h
../objs/gp2x/messagebox.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/messagebox.o: /usr/include/bits/fcntl.h /usr/include/sys/types.h
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
../objs/gp2x/messagebox.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/messagebox.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/messagebox.o: sfontplus.h
../objs/gp2x/selector.o: /usr/include/sys/stat.h /usr/include/features.h
../objs/gp2x/selector.o: /usr/include/sys/cdefs.h
../objs/gp2x/selector.o: /usr/include/bits/wordsize.h
../objs/gp2x/selector.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/selector.o: /usr/include/bits/types.h
../objs/gp2x/selector.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/selector.o: /usr/include/bits/stat.h /usr/include/sys/types.h
../objs/gp2x/selector.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/selector.o: /usr/include/bits/byteswap.h
../objs/gp2x/selector.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/selector.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/selector.o: /usr/include/sys/sysmacros.h
../objs/gp2x/selector.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/selector.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/selector.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/selector.o: /usr/include/bits/local_lim.h
../objs/gp2x/selector.o: /usr/include/linux/limits.h menu.h linkaction.h
../objs/gp2x/selector.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/selector.o: /usr/include/string.h /usr/include/xlocale.h link.h
../objs/gp2x/selector.o: button.h surface.h sfontplus.h linkapp.h selector.h
../objs/gp2x/selector.o: gmenu2x.h surfacecollection.h iconbutton.h
../objs/gp2x/selector.o: translator.h utilities.h touchscreen.h
../objs/gp2x/selector.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/selector.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/selector.o: inputmanager.h dialog.h filelister.h
../objs/gp2x/settingsdialog.o: settingsdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/settingsdialog.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/settingsdialog.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/settingsdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/settingsdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/settingsdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/settingsdialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/settingsdialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/types.h
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
../objs/gp2x/settingsdialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/settingsdialog.o: surface.h sfontplus.h menusetting.h
../objs/gp2x/settingsdialog.o: buttonbox.h dialog.h
../objs/gp2x/sfontplus.o: sfontplus.h surface.h utilities.h
../objs/gp2x/surfacecollection.o: surfacecollection.h surface.h sfontplus.h
../objs/gp2x/surfacecollection.o: utilities.h
../objs/gp2x/surface.o: surface.h sfontplus.h utilities.h
../objs/gp2x/textdialog.o: textdialog.h gmenu2x.h surfacecollection.h
../objs/gp2x/textdialog.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/textdialog.o: /usr/include/memory.h /usr/include/features.h
../objs/gp2x/textdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/textdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/textdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/textdialog.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/textdialog.o: /usr/include/xlocale.h translator.h utilities.h
../objs/gp2x/textdialog.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/textdialog.o: /usr/include/bits/fcntl.h /usr/include/sys/types.h
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
../objs/gp2x/textdialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/textdialog.o: /usr/include/bits/wchar.h inputmanager.h surface.h
../objs/gp2x/textdialog.o: sfontplus.h dialog.h
../objs/gp2x/textmanualdialog.o: textmanualdialog.h textdialog.h gmenu2x.h
../objs/gp2x/textmanualdialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/textmanualdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/textmanualdialog.o: /usr/include/features.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/textmanualdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/textmanualdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/textmanualdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/textmanualdialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/textmanualdialog.o: /usr/include/fcntl.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/types.h
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
../objs/gp2x/textmanualdialog.o: /usr/include/bits/stat.h
../objs/gp2x/textmanualdialog.o: /usr/include/stdint.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/textmanualdialog.o: surface.h sfontplus.h dialog.h
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
../objs/gp2x/touchscreen.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/touchscreen.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/touchscreen.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/touchscreen.o: /usr/include/bits/byteswap.h
../objs/gp2x/touchscreen.o: /usr/include/sys/select.h
../objs/gp2x/touchscreen.o: /usr/include/bits/select.h
../objs/gp2x/touchscreen.o: /usr/include/bits/sigset.h
../objs/gp2x/touchscreen.o: /usr/include/bits/time.h
../objs/gp2x/touchscreen.o: /usr/include/sys/sysmacros.h
../objs/gp2x/touchscreen.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/touchscreen.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/touchscreen.o: /usr/include/bits/wchar.h
../objs/gp2x/translator.o: translator.h utilities.h
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
../objs/gp2x/utilities.o: /usr/include/xlocale.h /usr/include/math.h
../objs/gp2x/utilities.o: /usr/include/bits/huge_val.h
../objs/gp2x/utilities.o: /usr/include/bits/huge_valf.h
../objs/gp2x/utilities.o: /usr/include/bits/huge_vall.h
../objs/gp2x/utilities.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
../objs/gp2x/utilities.o: /usr/include/bits/mathdef.h
../objs/gp2x/utilities.o: /usr/include/bits/mathcalls.h utilities.h
../objs/gp2x/wallpaperdialog.o: wallpaperdialog.h gmenu2x.h
../objs/gp2x/wallpaperdialog.o: surfacecollection.h iconbutton.h button.h
../objs/gp2x/wallpaperdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/wallpaperdialog.o: /usr/include/features.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/wallpaperdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/wallpaperdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/wallpaperdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/wallpaperdialog.o: translator.h utilities.h touchscreen.h
../objs/gp2x/wallpaperdialog.o: /usr/include/fcntl.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/types.h
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
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/stat.h
../objs/gp2x/wallpaperdialog.o: /usr/include/stdint.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/wallpaperdialog.o: surface.h sfontplus.h dialog.h filelister.h
