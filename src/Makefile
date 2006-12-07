CHAINPREFIX=$(GP2XDEV)
CROSS_COMPILE=$(CHAINPREFIX)/bin/gp2x-

CC= $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

CFLAGS = -I"$(CHAINPREFIX)/include" `$(CHAINPREFIX)/bin/sdl-config --cflags` -DTARGET_GP2X -O2 -Wno-unused -msoft-float -fomit-frame-pointer -ffast-math -funroll-loops
CXXFLAGS = $(CFLAGS)
LDFLAGS = -static -L$(CHAINPREFIX)/lib `$(CHAINPREFIX)/bin/sdl-config --libs` -lfreetype -lSDL_image -lSDL_gfx -ljpeg -lpng12 -lSDL -lz

TARGET = gmenu2x
OBJS = gmenu2x.o surface.o surfacecollection.o link.o linkapp.o linkaction.o SFont.o asfont.o joystick.o menu.o utilities.o dirdialog.o filedialog.o inputdialog.o settingsdialog.o textdialog.o menusetting.o menusettingint.o menusettingbool.o menusettingrgba.o menusettingstring.o menusettingmultistring.o menusettingfile.o menusettingdir.o selector.o filelister.o messagebox.o

%.o: %.cpp
		$(CXX) $(CFLAGS) -c $<

%.o: %.c
		$(CC) $(CFLAGS) -c $<

all: $(TARGET)

$(TARGET): $(OBJS)
		@echo "Linking $(TARGET) ..."
		$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)
		$(STRIP) $(TARGET)

clean:
		rm -f *.o
		rm -f $(TARGET)
