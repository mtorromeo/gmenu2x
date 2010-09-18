CHAINPREFIX=$(OPEN2X)
CROSS_COMPILE=$(CHAINPREFIX)/bin/arm-open2x-linux-

CC= $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

CFLAGS = -I"$(CHAINPREFIX)/include" `$(CHAINPREFIX)/bin/sdl-config --cflags` -DTARGET_GP2X -DTIXML_USE_STL -O3 -msoft-float -fomit-frame-pointer -ffast-math -funroll-loops -Wall -Wno-unknown-pragmas -Wno-format
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

../objs/gp2x/button.o: button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/button.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/button.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
../objs/gp2x/button.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/button.o: /usr/include/xlocale.h gmenu2x.h
../objs/gp2x/button.o: /usr/include/google/dense_hash_map
../objs/gp2x/button.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/button.o: /usr/include/stdio.h /usr/include/bits/types.h
../objs/gp2x/button.o: /usr/include/bits/typesizes.h /usr/include/libio.h
../objs/gp2x/button.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/button.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/button.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/button.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/button.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/button.o: /usr/include/bits/waitflags.h
../objs/gp2x/button.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
../objs/gp2x/button.o: /usr/include/bits/endian.h
../objs/gp2x/button.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
../objs/gp2x/button.o: /usr/include/time.h /usr/include/sys/select.h
../objs/gp2x/button.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
../objs/gp2x/button.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
../objs/gp2x/button.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
../objs/gp2x/button.o: /usr/include/google/type_traits.h surfacecollection.h
../objs/gp2x/button.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/button.o: sfontplus.h utilities.h iconbutton.h translator.h
../objs/gp2x/button.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/button.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/button.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/button.o: inputmanager.h
../objs/gp2x/dirdialog.o: /usr/include/sys/stat.h /usr/include/features.h
../objs/gp2x/dirdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/dirdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/dirdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/dirdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/dirdialog.o: /usr/include/bits/types.h
../objs/gp2x/dirdialog.o: /usr/include/bits/typesizes.h /usr/include/time.h
../objs/gp2x/dirdialog.o: /usr/include/bits/stat.h /usr/include/sys/types.h
../objs/gp2x/dirdialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/dirdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/dirdialog.o: /usr/include/sys/select.h
../objs/gp2x/dirdialog.o: /usr/include/bits/select.h
../objs/gp2x/dirdialog.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/dirdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/dirdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/dirdialog.o: /usr/include/dirent.h /usr/include/bits/dirent.h
../objs/gp2x/dirdialog.o: /usr/include/bits/posix1_lim.h
../objs/gp2x/dirdialog.o: /usr/include/bits/local_lim.h
../objs/gp2x/dirdialog.o: /usr/include/linux/limits.h dirdialog.h gmenu2x.h
../objs/gp2x/dirdialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/dirdialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/dirdialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/dirdialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/dirdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/dirdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/dirdialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/dirdialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/dirdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/dirdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/dirdialog.o: /usr/include/alloca.h
../objs/gp2x/dirdialog.o: /usr/include/google/type_traits.h
../objs/gp2x/dirdialog.o: surfacecollection.h
../objs/gp2x/dirdialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/dirdialog.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/dirdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/dirdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/dirdialog.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/dirdialog.o: /usr/include/bits/fcntl.h /usr/include/stdint.h
../objs/gp2x/dirdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/dirdialog.o: filelister.h
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
../objs/gp2x/filedialog.o: filelister.h gmenu2x.h
../objs/gp2x/filedialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/filedialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/filedialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/filedialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/filedialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/filedialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/filedialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/filedialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/filedialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/filedialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/filedialog.o: /usr/include/alloca.h
../objs/gp2x/filedialog.o: /usr/include/google/type_traits.h
../objs/gp2x/filedialog.o: surfacecollection.h
../objs/gp2x/filedialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/filedialog.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/filedialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/filedialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/filedialog.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/filedialog.o: /usr/include/bits/fcntl.h /usr/include/stdint.h
../objs/gp2x/filedialog.o: /usr/include/bits/wchar.h inputmanager.h
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
../objs/gp2x/gmenu2x.o: linkaction.h menu.h sfontplus.h surface.h
../objs/gp2x/gmenu2x.o: filedialog.h filelister.h gmenu2x.h
../objs/gp2x/gmenu2x.o: /usr/include/google/dense_hash_map
../objs/gp2x/gmenu2x.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/gmenu2x.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/gmenu2x.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/gmenu2x.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/gmenu2x.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/gmenu2x.o: /usr/include/assert.h
../objs/gp2x/gmenu2x.o: /usr/include/google/type_traits.h surfacecollection.h
../objs/gp2x/gmenu2x.o: /usr/include/google/dense_hash_map utilities.h
../objs/gp2x/gmenu2x.o: iconbutton.h translator.h touchscreen.h
../objs/gp2x/gmenu2x.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/gmenu2x.o: inputmanager.h messagebox.h inputdialog.h
../objs/gp2x/gmenu2x.o: settingsdialog.h menusetting.h wallpaperdialog.h
../objs/gp2x/gmenu2x.o: textdialog.h menusettingint.h menusettingbool.h
../objs/gp2x/gmenu2x.o: menusettingrgba.h menusettingstring.h
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
../objs/gp2x/iconbutton.o: /usr/include/google/dense_hash_map
../objs/gp2x/iconbutton.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/iconbutton.o: /usr/include/stdio.h /usr/include/bits/types.h
../objs/gp2x/iconbutton.o: /usr/include/bits/typesizes.h /usr/include/libio.h
../objs/gp2x/iconbutton.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/iconbutton.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/iconbutton.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/iconbutton.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/iconbutton.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/iconbutton.o: /usr/include/bits/waitflags.h
../objs/gp2x/iconbutton.o: /usr/include/bits/waitstatus.h
../objs/gp2x/iconbutton.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/iconbutton.o: /usr/include/bits/byteswap.h
../objs/gp2x/iconbutton.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/iconbutton.o: /usr/include/sys/select.h
../objs/gp2x/iconbutton.o: /usr/include/bits/select.h
../objs/gp2x/iconbutton.o: /usr/include/bits/sigset.h
../objs/gp2x/iconbutton.o: /usr/include/bits/time.h
../objs/gp2x/iconbutton.o: /usr/include/sys/sysmacros.h
../objs/gp2x/iconbutton.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/iconbutton.o: /usr/include/alloca.h
../objs/gp2x/iconbutton.o: /usr/include/google/type_traits.h
../objs/gp2x/iconbutton.o: surfacecollection.h
../objs/gp2x/iconbutton.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/iconbutton.o: sfontplus.h utilities.h translator.h touchscreen.h
../objs/gp2x/iconbutton.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/iconbutton.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/iconbutton.o: /usr/include/bits/wchar.h inputmanager.h
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
../objs/gp2x/imagedialog.o: filedialog.h filelister.h gmenu2x.h
../objs/gp2x/imagedialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/imagedialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/imagedialog.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/imagedialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/imagedialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/imagedialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/imagedialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/imagedialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/imagedialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/imagedialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/imagedialog.o: /usr/include/alloca.h
../objs/gp2x/imagedialog.o: /usr/include/google/type_traits.h
../objs/gp2x/imagedialog.o: surfacecollection.h
../objs/gp2x/imagedialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/imagedialog.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/imagedialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/imagedialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/imagedialog.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/imagedialog.o: /usr/include/bits/fcntl.h /usr/include/stdint.h
../objs/gp2x/imagedialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/inputdialog.o: inputdialog.h gmenu2x.h
../objs/gp2x/inputdialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/inputdialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/inputdialog.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/inputdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/inputdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/inputdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/inputdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/inputdialog.o: /usr/include/bits/types.h
../objs/gp2x/inputdialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/inputdialog.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/inputdialog.o: /usr/include/wchar.h
../objs/gp2x/inputdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/inputdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/inputdialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/inputdialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/inputdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/inputdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/inputdialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/inputdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/inputdialog.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/inputdialog.o: /usr/include/sys/select.h
../objs/gp2x/inputdialog.o: /usr/include/bits/select.h
../objs/gp2x/inputdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/inputdialog.o: /usr/include/bits/time.h
../objs/gp2x/inputdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/inputdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/inputdialog.o: /usr/include/alloca.h
../objs/gp2x/inputdialog.o: /usr/include/google/type_traits.h
../objs/gp2x/inputdialog.o: surfacecollection.h
../objs/gp2x/inputdialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/inputdialog.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/inputdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/inputdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/inputdialog.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/inputdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/inputdialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/inputdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/inputmanager.o: inputmanager.h utilities.h
../objs/gp2x/linkaction.o: linkaction.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/linkaction.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/linkaction.o: /usr/include/bits/wordsize.h
../objs/gp2x/linkaction.o: /usr/include/gnu/stubs.h
../objs/gp2x/linkaction.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/linkaction.o: /usr/include/xlocale.h link.h button.h
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
../objs/gp2x/linkapp.o: /usr/include/xlocale.h menu.h linkaction.h selector.h
../objs/gp2x/linkapp.o: gmenu2x.h /usr/include/google/dense_hash_map
../objs/gp2x/linkapp.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/linkapp.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/linkapp.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/linkapp.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/linkapp.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/linkapp.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/linkapp.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/linkapp.o: /usr/include/bits/waitflags.h
../objs/gp2x/linkapp.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/linkapp.o: /usr/include/google/type_traits.h surfacecollection.h
../objs/gp2x/linkapp.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/linkapp.o: sfontplus.h utilities.h iconbutton.h translator.h
../objs/gp2x/linkapp.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/linkapp.o: /usr/include/bits/fcntl.h /usr/include/stdint.h
../objs/gp2x/linkapp.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/linkapp.o: textmanualdialog.h textdialog.h
../objs/gp2x/link.o: link.h button.h FastDelegate.h /usr/include/memory.h
../objs/gp2x/link.o: /usr/include/features.h /usr/include/sys/cdefs.h
../objs/gp2x/link.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
../objs/gp2x/link.o: /usr/include/gnu/stubs-64.h /usr/include/string.h
../objs/gp2x/link.o: /usr/include/xlocale.h menu.h linkaction.h selector.h
../objs/gp2x/link.o: gmenu2x.h /usr/include/google/dense_hash_map
../objs/gp2x/link.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/link.o: /usr/include/stdio.h /usr/include/bits/types.h
../objs/gp2x/link.o: /usr/include/bits/typesizes.h /usr/include/libio.h
../objs/gp2x/link.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/link.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/link.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/link.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/link.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/link.o: /usr/include/bits/waitflags.h
../objs/gp2x/link.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
../objs/gp2x/link.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
../objs/gp2x/link.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/link.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/link.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/link.o: /usr/include/sys/sysmacros.h
../objs/gp2x/link.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
../objs/gp2x/link.o: /usr/include/google/type_traits.h surfacecollection.h
../objs/gp2x/link.o: /usr/include/google/dense_hash_map surface.h sfontplus.h
../objs/gp2x/link.o: utilities.h iconbutton.h translator.h touchscreen.h
../objs/gp2x/link.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/link.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/link.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/listview.o: listview.h gmenu2x.h
../objs/gp2x/listview.o: /usr/include/google/dense_hash_map
../objs/gp2x/listview.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/listview.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/listview.o: /usr/include/sys/cdefs.h
../objs/gp2x/listview.o: /usr/include/bits/wordsize.h
../objs/gp2x/listview.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
../objs/gp2x/listview.o: /usr/include/bits/types.h
../objs/gp2x/listview.o: /usr/include/bits/typesizes.h /usr/include/libio.h
../objs/gp2x/listview.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/listview.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/listview.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/listview.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/listview.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/listview.o: /usr/include/bits/waitflags.h
../objs/gp2x/listview.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
../objs/gp2x/listview.o: /usr/include/bits/endian.h
../objs/gp2x/listview.o: /usr/include/bits/byteswap.h
../objs/gp2x/listview.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/listview.o: /usr/include/sys/select.h /usr/include/bits/select.h
../objs/gp2x/listview.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
../objs/gp2x/listview.o: /usr/include/sys/sysmacros.h
../objs/gp2x/listview.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/listview.o: /usr/include/alloca.h
../objs/gp2x/listview.o: /usr/include/google/type_traits.h
../objs/gp2x/listview.o: surfacecollection.h
../objs/gp2x/listview.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/listview.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/listview.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/listview.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/listview.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/listview.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/listview.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/listview.o: inputmanager.h listviewitem.h
../objs/gp2x/listviewitem.o: listview.h gmenu2x.h
../objs/gp2x/listviewitem.o: /usr/include/google/dense_hash_map
../objs/gp2x/listviewitem.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/listviewitem.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/listviewitem.o: /usr/include/sys/cdefs.h
../objs/gp2x/listviewitem.o: /usr/include/bits/wordsize.h
../objs/gp2x/listviewitem.o: /usr/include/gnu/stubs.h
../objs/gp2x/listviewitem.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/listviewitem.o: /usr/include/bits/types.h
../objs/gp2x/listviewitem.o: /usr/include/bits/typesizes.h
../objs/gp2x/listviewitem.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/listviewitem.o: /usr/include/wchar.h
../objs/gp2x/listviewitem.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/listviewitem.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/listviewitem.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/listviewitem.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/listviewitem.o: /usr/include/bits/waitflags.h
../objs/gp2x/listviewitem.o: /usr/include/bits/waitstatus.h
../objs/gp2x/listviewitem.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/listviewitem.o: /usr/include/bits/byteswap.h
../objs/gp2x/listviewitem.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/listviewitem.o: /usr/include/sys/select.h
../objs/gp2x/listviewitem.o: /usr/include/bits/select.h
../objs/gp2x/listviewitem.o: /usr/include/bits/sigset.h
../objs/gp2x/listviewitem.o: /usr/include/bits/time.h
../objs/gp2x/listviewitem.o: /usr/include/sys/sysmacros.h
../objs/gp2x/listviewitem.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/listviewitem.o: /usr/include/alloca.h
../objs/gp2x/listviewitem.o: /usr/include/google/type_traits.h
../objs/gp2x/listviewitem.o: surfacecollection.h
../objs/gp2x/listviewitem.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/listviewitem.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/listviewitem.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/listviewitem.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/listviewitem.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/listviewitem.o: /usr/include/bits/fcntl.h
../objs/gp2x/listviewitem.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/listviewitem.o: /usr/include/bits/wchar.h inputmanager.h
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
../objs/gp2x/menu.o: /usr/include/google/dense_hash_map
../objs/gp2x/menu.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menu.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/menu.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/menu.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menu.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menu.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menu.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menu.o: /usr/include/bits/waitflags.h
../objs/gp2x/menu.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/menu.o: /usr/include/google/type_traits.h surfacecollection.h
../objs/gp2x/menu.o: /usr/include/google/dense_hash_map surface.h sfontplus.h
../objs/gp2x/menu.o: utilities.h iconbutton.h button.h FastDelegate.h
../objs/gp2x/menu.o: /usr/include/memory.h /usr/include/string.h
../objs/gp2x/menu.o: /usr/include/xlocale.h translator.h touchscreen.h
../objs/gp2x/menu.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/menu.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/menu.o: inputmanager.h linkapp.h link.h menu.h linkaction.h
../objs/gp2x/menu.o: filelister.h
../objs/gp2x/menusettingbool.o: menusettingbool.h iconbutton.h button.h
../objs/gp2x/menusettingbool.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingbool.o: /usr/include/features.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingbool.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingbool.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingbool.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingbool.o: menusetting.h inputmanager.h gmenu2x.h
../objs/gp2x/menusettingbool.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingbool.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingbool.o: /usr/include/stdio.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/types.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingbool.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/menusettingbool.o: /usr/include/wchar.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingbool.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingbool.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingbool.o: /usr/include/endian.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/select.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/select.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/time.h
../objs/gp2x/menusettingbool.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingbool.o: /usr/include/alloca.h
../objs/gp2x/menusettingbool.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingbool.o: surfacecollection.h
../objs/gp2x/menusettingbool.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/menusettingbool.o: sfontplus.h utilities.h translator.h
../objs/gp2x/menusettingbool.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingbool.o: /usr/include/stdint.h
../objs/gp2x/menusettingbool.o: /usr/include/bits/wchar.h
../objs/gp2x/menusetting.o: menusetting.h inputmanager.h gmenu2x.h
../objs/gp2x/menusetting.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusetting.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusetting.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/menusetting.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusetting.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusetting.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusetting.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusetting.o: /usr/include/bits/types.h
../objs/gp2x/menusetting.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusetting.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/menusetting.o: /usr/include/wchar.h
../objs/gp2x/menusetting.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusetting.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusetting.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusetting.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusetting.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusetting.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusetting.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/menusetting.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusetting.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/menusetting.o: /usr/include/sys/select.h
../objs/gp2x/menusetting.o: /usr/include/bits/select.h
../objs/gp2x/menusetting.o: /usr/include/bits/sigset.h
../objs/gp2x/menusetting.o: /usr/include/bits/time.h
../objs/gp2x/menusetting.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusetting.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusetting.o: /usr/include/alloca.h
../objs/gp2x/menusetting.o: /usr/include/google/type_traits.h
../objs/gp2x/menusetting.o: surfacecollection.h
../objs/gp2x/menusetting.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/menusetting.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/menusetting.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusetting.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusetting.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menusetting.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusetting.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/menusetting.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingdir.o: menusettingdir.h gmenu2x.h
../objs/gp2x/menusettingdir.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingdir.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingdir.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingdir.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingdir.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/types.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingdir.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/menusettingdir.o: /usr/include/wchar.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingdir.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingdir.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingdir.o: /usr/include/endian.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/select.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/select.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/time.h
../objs/gp2x/menusettingdir.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingdir.o: /usr/include/alloca.h
../objs/gp2x/menusettingdir.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingdir.o: surfacecollection.h
../objs/gp2x/menusettingdir.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/menusettingdir.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/menusettingdir.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingdir.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingdir.o: translator.h touchscreen.h
../objs/gp2x/menusettingdir.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/menusettingdir.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingdir.o: menusetting.h dirdialog.h
../objs/gp2x/menusettingfile.o: menusettingfile.h gmenu2x.h
../objs/gp2x/menusettingfile.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingfile.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingfile.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingfile.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingfile.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/types.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingfile.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/menusettingfile.o: /usr/include/wchar.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingfile.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingfile.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingfile.o: /usr/include/endian.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/select.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/select.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/time.h
../objs/gp2x/menusettingfile.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingfile.o: /usr/include/alloca.h
../objs/gp2x/menusettingfile.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingfile.o: surfacecollection.h
../objs/gp2x/menusettingfile.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/menusettingfile.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/menusettingfile.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingfile.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingfile.o: translator.h touchscreen.h
../objs/gp2x/menusettingfile.o: /usr/include/fcntl.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingfile.o: /usr/include/stdint.h
../objs/gp2x/menusettingfile.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingfile.o: menusetting.h filedialog.h filelister.h
../objs/gp2x/menusettingimage.o: menusettingimage.h gmenu2x.h
../objs/gp2x/menusettingimage.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingimage.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingimage.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingimage.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingimage.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/types.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingimage.o: /usr/include/libio.h
../objs/gp2x/menusettingimage.o: /usr/include/_G_config.h
../objs/gp2x/menusettingimage.o: /usr/include/wchar.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingimage.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingimage.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingimage.o: /usr/include/endian.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/select.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/select.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/time.h
../objs/gp2x/menusettingimage.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingimage.o: /usr/include/alloca.h
../objs/gp2x/menusettingimage.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingimage.o: surfacecollection.h
../objs/gp2x/menusettingimage.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/menusettingimage.o: sfontplus.h utilities.h iconbutton.h
../objs/gp2x/menusettingimage.o: button.h FastDelegate.h
../objs/gp2x/menusettingimage.o: /usr/include/memory.h /usr/include/string.h
../objs/gp2x/menusettingimage.o: /usr/include/xlocale.h translator.h
../objs/gp2x/menusettingimage.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingimage.o: /usr/include/stdint.h
../objs/gp2x/menusettingimage.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingimage.o: menusettingfile.h menusetting.h
../objs/gp2x/menusettingimage.o: imagedialog.h filedialog.h filelister.h
../objs/gp2x/menusettingint.o: menusettingint.h iconbutton.h button.h
../objs/gp2x/menusettingint.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingint.o: /usr/include/features.h
../objs/gp2x/menusettingint.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingint.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingint.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingint.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingint.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingint.o: menusetting.h inputmanager.h gmenu2x.h
../objs/gp2x/menusettingint.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingint.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingint.o: /usr/include/stdio.h /usr/include/bits/types.h
../objs/gp2x/menusettingint.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingint.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/menusettingint.o: /usr/include/wchar.h
../objs/gp2x/menusettingint.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingint.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingint.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingint.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusettingint.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingint.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingint.o: /usr/include/endian.h
../objs/gp2x/menusettingint.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingint.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingint.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/menusettingint.o: /usr/include/sys/select.h
../objs/gp2x/menusettingint.o: /usr/include/bits/select.h
../objs/gp2x/menusettingint.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingint.o: /usr/include/bits/time.h
../objs/gp2x/menusettingint.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingint.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingint.o: /usr/include/alloca.h
../objs/gp2x/menusettingint.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingint.o: surfacecollection.h
../objs/gp2x/menusettingint.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/menusettingint.o: sfontplus.h utilities.h translator.h
../objs/gp2x/menusettingint.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menusettingint.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingint.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/menusettingint.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingmultistring.o: menusettingmultistring.h gmenu2x.h
../objs/gp2x/menusettingmultistring.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingmultistring.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingmultistring.o: /usr/include/stdio.h
../objs/gp2x/menusettingmultistring.o: /usr/include/features.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingmultistring.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingmultistring.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/types.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingmultistring.o: /usr/include/libio.h
../objs/gp2x/menusettingmultistring.o: /usr/include/_G_config.h
../objs/gp2x/menusettingmultistring.o: /usr/include/wchar.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingmultistring.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingmultistring.o: /usr/include/assert.h
../objs/gp2x/menusettingmultistring.o: /usr/include/stdlib.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingmultistring.o: /usr/include/endian.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/types.h
../objs/gp2x/menusettingmultistring.o: /usr/include/time.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/select.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/select.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/time.h
../objs/gp2x/menusettingmultistring.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingmultistring.o: /usr/include/alloca.h
../objs/gp2x/menusettingmultistring.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingmultistring.o: surfacecollection.h
../objs/gp2x/menusettingmultistring.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingmultistring.o: surface.h sfontplus.h utilities.h
../objs/gp2x/menusettingmultistring.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/menusettingmultistring.o: /usr/include/memory.h
../objs/gp2x/menusettingmultistring.o: /usr/include/string.h
../objs/gp2x/menusettingmultistring.o: /usr/include/xlocale.h translator.h
../objs/gp2x/menusettingmultistring.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingmultistring.o: /usr/include/stdint.h
../objs/gp2x/menusettingmultistring.o: /usr/include/bits/wchar.h
../objs/gp2x/menusettingmultistring.o: inputmanager.h menusetting.h
../objs/gp2x/menusettingrgba.o: menusettingrgba.h gmenu2x.h
../objs/gp2x/menusettingrgba.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingrgba.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingrgba.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingrgba.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingrgba.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/types.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingrgba.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/menusettingrgba.o: /usr/include/wchar.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingrgba.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingrgba.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingrgba.o: /usr/include/endian.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/select.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/select.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/time.h
../objs/gp2x/menusettingrgba.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingrgba.o: /usr/include/alloca.h
../objs/gp2x/menusettingrgba.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingrgba.o: surfacecollection.h
../objs/gp2x/menusettingrgba.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/menusettingrgba.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/menusettingrgba.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/menusettingrgba.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/menusettingrgba.o: translator.h touchscreen.h
../objs/gp2x/menusettingrgba.o: /usr/include/fcntl.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingrgba.o: /usr/include/stdint.h
../objs/gp2x/menusettingrgba.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingrgba.o: menusetting.h
../objs/gp2x/menusettingstring.o: menusettingstring.h gmenu2x.h
../objs/gp2x/menusettingstring.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingstring.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/menusettingstring.o: /usr/include/stdio.h
../objs/gp2x/menusettingstring.o: /usr/include/features.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/cdefs.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/wordsize.h
../objs/gp2x/menusettingstring.o: /usr/include/gnu/stubs.h
../objs/gp2x/menusettingstring.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/types.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/typesizes.h
../objs/gp2x/menusettingstring.o: /usr/include/libio.h
../objs/gp2x/menusettingstring.o: /usr/include/_G_config.h
../objs/gp2x/menusettingstring.o: /usr/include/wchar.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/menusettingstring.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/menusettingstring.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/waitflags.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/waitstatus.h
../objs/gp2x/menusettingstring.o: /usr/include/endian.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/endian.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/byteswap.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/types.h
../objs/gp2x/menusettingstring.o: /usr/include/time.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/select.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/select.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/sigset.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/time.h
../objs/gp2x/menusettingstring.o: /usr/include/sys/sysmacros.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/menusettingstring.o: /usr/include/alloca.h
../objs/gp2x/menusettingstring.o: /usr/include/google/type_traits.h
../objs/gp2x/menusettingstring.o: surfacecollection.h
../objs/gp2x/menusettingstring.o: /usr/include/google/dense_hash_map
../objs/gp2x/menusettingstring.o: surface.h sfontplus.h utilities.h
../objs/gp2x/menusettingstring.o: iconbutton.h button.h FastDelegate.h
../objs/gp2x/menusettingstring.o: /usr/include/memory.h /usr/include/string.h
../objs/gp2x/menusettingstring.o: /usr/include/xlocale.h translator.h
../objs/gp2x/menusettingstring.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/fcntl.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/stat.h
../objs/gp2x/menusettingstring.o: /usr/include/stdint.h
../objs/gp2x/menusettingstring.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/menusettingstring.o: menusetting.h inputdialog.h
../objs/gp2x/messagebox.o: messagebox.h gmenu2x.h
../objs/gp2x/messagebox.o: /usr/include/google/dense_hash_map
../objs/gp2x/messagebox.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/messagebox.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/messagebox.o: /usr/include/sys/cdefs.h
../objs/gp2x/messagebox.o: /usr/include/bits/wordsize.h
../objs/gp2x/messagebox.o: /usr/include/gnu/stubs.h
../objs/gp2x/messagebox.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/messagebox.o: /usr/include/bits/types.h
../objs/gp2x/messagebox.o: /usr/include/bits/typesizes.h /usr/include/libio.h
../objs/gp2x/messagebox.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/messagebox.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/messagebox.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/messagebox.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/messagebox.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/messagebox.o: /usr/include/bits/waitflags.h
../objs/gp2x/messagebox.o: /usr/include/bits/waitstatus.h
../objs/gp2x/messagebox.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/messagebox.o: /usr/include/bits/byteswap.h
../objs/gp2x/messagebox.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/messagebox.o: /usr/include/sys/select.h
../objs/gp2x/messagebox.o: /usr/include/bits/select.h
../objs/gp2x/messagebox.o: /usr/include/bits/sigset.h
../objs/gp2x/messagebox.o: /usr/include/bits/time.h
../objs/gp2x/messagebox.o: /usr/include/sys/sysmacros.h
../objs/gp2x/messagebox.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/messagebox.o: /usr/include/alloca.h
../objs/gp2x/messagebox.o: /usr/include/google/type_traits.h
../objs/gp2x/messagebox.o: surfacecollection.h
../objs/gp2x/messagebox.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/messagebox.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/messagebox.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/messagebox.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/messagebox.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/messagebox.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/messagebox.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/messagebox.o: inputmanager.h
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
../objs/gp2x/selector.o: button.h linkapp.h selector.h gmenu2x.h
../objs/gp2x/selector.o: /usr/include/google/dense_hash_map
../objs/gp2x/selector.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/selector.o: /usr/include/stdio.h /usr/include/libio.h
../objs/gp2x/selector.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/selector.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/selector.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/selector.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/selector.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/selector.o: /usr/include/bits/waitflags.h
../objs/gp2x/selector.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
../objs/gp2x/selector.o: /usr/include/google/type_traits.h
../objs/gp2x/selector.o: surfacecollection.h
../objs/gp2x/selector.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/selector.o: sfontplus.h utilities.h iconbutton.h translator.h
../objs/gp2x/selector.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/selector.o: /usr/include/bits/fcntl.h /usr/include/stdint.h
../objs/gp2x/selector.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/selector.o: filelister.h
../objs/gp2x/selectordetector.o: selectordetector.h utilities.h
../objs/gp2x/settingsdialog.o: settingsdialog.h gmenu2x.h
../objs/gp2x/settingsdialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/settingsdialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/settingsdialog.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/settingsdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/settingsdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/types.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/settingsdialog.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/settingsdialog.o: /usr/include/wchar.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/settingsdialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/settingsdialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/settingsdialog.o: /usr/include/endian.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/endian.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/select.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/select.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/time.h
../objs/gp2x/settingsdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/settingsdialog.o: /usr/include/alloca.h
../objs/gp2x/settingsdialog.o: /usr/include/google/type_traits.h
../objs/gp2x/settingsdialog.o: surfacecollection.h
../objs/gp2x/settingsdialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/settingsdialog.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/settingsdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/settingsdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/settingsdialog.o: translator.h touchscreen.h
../objs/gp2x/settingsdialog.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/stat.h /usr/include/stdint.h
../objs/gp2x/settingsdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/settingsdialog.o: menusetting.h
../objs/gp2x/sfontplus.o: sfontplus.h surface.h utilities.h
../objs/gp2x/surfacecollection.o: surfacecollection.h
../objs/gp2x/surfacecollection.o: /usr/include/google/dense_hash_map
../objs/gp2x/surfacecollection.o: surface.h sfontplus.h utilities.h
../objs/gp2x/surface.o: surface.h sfontplus.h utilities.h
../objs/gp2x/textdialog.o: textdialog.h gmenu2x.h
../objs/gp2x/textdialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/textdialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/textdialog.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/textdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/textdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/textdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/textdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/textdialog.o: /usr/include/bits/types.h
../objs/gp2x/textdialog.o: /usr/include/bits/typesizes.h /usr/include/libio.h
../objs/gp2x/textdialog.o: /usr/include/_G_config.h /usr/include/wchar.h
../objs/gp2x/textdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/textdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/textdialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/textdialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/textdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/textdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/textdialog.o: /usr/include/endian.h /usr/include/bits/endian.h
../objs/gp2x/textdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/textdialog.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/textdialog.o: /usr/include/sys/select.h
../objs/gp2x/textdialog.o: /usr/include/bits/select.h
../objs/gp2x/textdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/textdialog.o: /usr/include/bits/time.h
../objs/gp2x/textdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/textdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/textdialog.o: /usr/include/alloca.h
../objs/gp2x/textdialog.o: /usr/include/google/type_traits.h
../objs/gp2x/textdialog.o: surfacecollection.h
../objs/gp2x/textdialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/textdialog.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/textdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/textdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/textdialog.o: translator.h touchscreen.h /usr/include/fcntl.h
../objs/gp2x/textdialog.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
../objs/gp2x/textdialog.o: /usr/include/stdint.h /usr/include/bits/wchar.h
../objs/gp2x/textdialog.o: inputmanager.h
../objs/gp2x/textmanualdialog.o: textmanualdialog.h textdialog.h gmenu2x.h
../objs/gp2x/textmanualdialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/textmanualdialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/textmanualdialog.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/textmanualdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/textmanualdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/types.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/textmanualdialog.o: /usr/include/libio.h
../objs/gp2x/textmanualdialog.o: /usr/include/_G_config.h
../objs/gp2x/textmanualdialog.o: /usr/include/wchar.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/textmanualdialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/textmanualdialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/textmanualdialog.o: /usr/include/endian.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/endian.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/select.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/select.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/time.h
../objs/gp2x/textmanualdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/textmanualdialog.o: /usr/include/alloca.h
../objs/gp2x/textmanualdialog.o: /usr/include/google/type_traits.h
../objs/gp2x/textmanualdialog.o: surfacecollection.h
../objs/gp2x/textmanualdialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/textmanualdialog.o: sfontplus.h utilities.h iconbutton.h
../objs/gp2x/textmanualdialog.o: button.h FastDelegate.h
../objs/gp2x/textmanualdialog.o: /usr/include/memory.h /usr/include/string.h
../objs/gp2x/textmanualdialog.o: /usr/include/xlocale.h translator.h
../objs/gp2x/textmanualdialog.o: touchscreen.h /usr/include/fcntl.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/stat.h
../objs/gp2x/textmanualdialog.o: /usr/include/stdint.h
../objs/gp2x/textmanualdialog.o: /usr/include/bits/wchar.h inputmanager.h
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
../objs/gp2x/utilities.o: /usr/include/linux/limits.h utilities.h
../objs/gp2x/wallpaperdialog.o: wallpaperdialog.h gmenu2x.h
../objs/gp2x/wallpaperdialog.o: /usr/include/google/dense_hash_map
../objs/gp2x/wallpaperdialog.o: /usr/include/google/sparsehash/sparseconfig.h
../objs/gp2x/wallpaperdialog.o: /usr/include/stdio.h /usr/include/features.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/cdefs.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/wordsize.h
../objs/gp2x/wallpaperdialog.o: /usr/include/gnu/stubs.h
../objs/gp2x/wallpaperdialog.o: /usr/include/gnu/stubs-64.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/types.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/typesizes.h
../objs/gp2x/wallpaperdialog.o: /usr/include/libio.h /usr/include/_G_config.h
../objs/gp2x/wallpaperdialog.o: /usr/include/wchar.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/stdio_lim.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/sys_errlist.h
../objs/gp2x/wallpaperdialog.o: /usr/include/google/sparsehash/densehashtable.h
../objs/gp2x/wallpaperdialog.o: /usr/include/assert.h /usr/include/stdlib.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/waitflags.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/waitstatus.h
../objs/gp2x/wallpaperdialog.o: /usr/include/endian.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/endian.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/byteswap.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/types.h /usr/include/time.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/select.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/select.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/sigset.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/time.h
../objs/gp2x/wallpaperdialog.o: /usr/include/sys/sysmacros.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/pthreadtypes.h
../objs/gp2x/wallpaperdialog.o: /usr/include/alloca.h
../objs/gp2x/wallpaperdialog.o: /usr/include/google/type_traits.h
../objs/gp2x/wallpaperdialog.o: surfacecollection.h
../objs/gp2x/wallpaperdialog.o: /usr/include/google/dense_hash_map surface.h
../objs/gp2x/wallpaperdialog.o: sfontplus.h utilities.h iconbutton.h button.h
../objs/gp2x/wallpaperdialog.o: FastDelegate.h /usr/include/memory.h
../objs/gp2x/wallpaperdialog.o: /usr/include/string.h /usr/include/xlocale.h
../objs/gp2x/wallpaperdialog.o: translator.h touchscreen.h
../objs/gp2x/wallpaperdialog.o: /usr/include/fcntl.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/fcntl.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/stat.h
../objs/gp2x/wallpaperdialog.o: /usr/include/stdint.h
../objs/gp2x/wallpaperdialog.o: /usr/include/bits/wchar.h inputmanager.h
../objs/gp2x/wallpaperdialog.o: filelister.h
