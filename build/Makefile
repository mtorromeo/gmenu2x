CHAINPREFIX=$(GP2XDEV)
CROSS_COMPILE=$(CHAINPREFIX)/bin/arm-open2x-linux-

CC= $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

CFLAGS = -I"$(CHAINPREFIX)/include" `$(CHAINPREFIX)/bin/sdl-config --cflags` -DTARGET_GP2X -O3 -Wno-unused -msoft-float -fomit-frame-pointer -ffast-math -funroll-loops
CXXFLAGS = $(CFLAGS)
LDFLAGS = -static -L$(CHAINPREFIX)/lib `$(CHAINPREFIX)/bin/sdl-config --libs` -lfreetype -lSDL_image -lSDL_gfx -ljpeg -lpng12 -lSDL -lz

TARGET = gmenu2x
OBJS = ../objs/gp2x/gmenu2x.o ../objs/gp2x/surface.o ../objs/gp2x/surfacecollection.o ../objs/gp2x/link.o ../objs/gp2x/linkapp.o ../objs/gp2x/linkaction.o ../objs/gp2x/asfont.o ../objs/gp2x/sfontplus.o ../objs/gp2x/joystick.o ../objs/gp2x/menu.o ../objs/gp2x/utilities.o ../objs/gp2x/dirdialog.o ../objs/gp2x/filedialog.o ../objs/gp2x/imagedialog.o ../objs/gp2x/inputdialog.o ../objs/gp2x/settingsdialog.o ../objs/gp2x/textdialog.o ../objs/gp2x/textmanualdialog.o ../objs/gp2x/wallpaperdialog.o ../objs/gp2x/menusetting.o ../objs/gp2x/menusettingint.o ../objs/gp2x/menusettingbool.o ../objs/gp2x/menusettingrgba.o ../objs/gp2x/menusettingstring.o ../objs/gp2x/menusettingmultistring.o ../objs/gp2x/menusettingfile.o ../objs/gp2x/menusettingimage.o ../objs/gp2x/menusettingdir.o ../objs/gp2x/selector.o ../objs/gp2x/filelister.o ../objs/gp2x/messagebox.o ../objs/gp2x/translator.o

../objs/gp2x/%.o: ../src/%.cpp
		$(CXX) $(CFLAGS) -o $@ -c $<

../objs/gp2x/%.o: ../src/%.c
		$(CC) $(CFLAGS) -o $@ -c $<

all: dir $(TARGET)

dir:
	@if [ ! -d ../objs/gp2x ]; then mkdir -p ../objs/gp2x; fi

$(TARGET): $(OBJS)
		@echo "Linking $(TARGET)..."
		$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)
		$(STRIP) $(TARGET)

clean:
		-rm -f ../objs/gp2x/*.o $(TARGET)
