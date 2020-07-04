ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Windows)
	MKDIR=mkdir -p --
	RM   =rm -f
	RMDIR=rm -rf
endif
ifeq ($(detected_OS),Linux)
	MKDIR=mkdir -p
	RM   =rm -f
	RMDIR=rm -rf
endif

PROG=burningship

IFLAGS =$(IDIR) #-I$(MCAP)
LFLAGS =`wx-config --libs` -L"fractal-app/lib" -lfractalapp

CC     =g++

SDIR   =./src
IDIR   =-I./include -I./fractal-app/include
ODIR   =./obj

CFLAGS_OPTIMIZE=-ffast-math -O3
CFLAGS_PARANOID=-pthread -g -O -Wall -pedantic -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings# -Wunsafe-loop-optimizations -Winline -Weffc++ -Wpadded
CFLAGS =$(IFLAGS) $(CFLAGS_PARANOID) $(CFLAGS_OPTIMIZE) `wx-config --cxxflags`

all: $(PROG)

$(PROG): $(ODIR)/BurningShip.o $(ODIR)/FractalApp.o
	make -C fractal-app
	$(CC) $(CFLAGS) -o $(PROG) $(ODIR)/BurningShip.o $(ODIR)/FractalApp.o $(LFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(ODIR):
	$(MKDIR) $@

clean:
	$(RMDIR) $(ODIR)
	$(RM) $(PROG)

cleanall: clean
	make -C fractal-app clean
