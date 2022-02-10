CC = sdcc
ASM = sdasz80
PLATFORM = -mz80
EMULATOR = ./emulation/brunix/BrunixMac.app/Contents/MacOS/BrunixMac ./bin/diskimage.dsk
HEXBIN = /usr/local/bin/hex2bin

STARTUPDIR = startups
INCLUDEDIR = includes
LIBDIR = libs
SRCDIR = src

# See startup files for the correct ADDR_CODE and ADDR_DATA
CRT0 = crt0msx_msxdos_advanced.s
ADDR_CODE = 0x0178 # <------ This addres is in where the program starts
ADDR_DATA = 0 # <------ This addres is in where the data of the program starts

VERBOSE = -V
CCFLAGS = $(VERBOSE) $(PLATFORM) --code-loc $(ADDR_CODE) --data-loc $(ADDR_DATA) \
          --no-std-crt0 --opt-code-size --out-fmt-ihx

#Libraries that needed to compile (if you has included in your code)
OBJECTS = $(CRT0) putchar.s VDPgraph2.s text.c


SOURCE = test

#File that contains main routine
SOURCES = $(SOURCE).c

#Name of the compiled app
OUTFILE = $(SOURCE).com

.PHONY: all compile build clean emulator

all: clean compile build

compile: $(OBJECTS) $(SOURCES)

$(CRT0):
		@echo "Compiling $(CRT0)"
		@$(ASM) -o $(notdir $(@:.s=.rel)) $(STARTUPDIR)/$(CRT0)
%.s:
		@echo "Compiling $@"
		@$(ASM) -o $(notdir $(@:.s=.rel)) $(LIBDIR)/$@
		
%.c:
		@echo "Compiling $@"
		$(CC) $(VERBOSE) $(PLATFORM) -I$(INCLUDEDIR) -c -o $(notdir $(@:.c=.rel)) $(LIBDIR)/$@

$(SOURCES):
		$(CC) -I$(INCLUDEDIR) $(CCFLAGS) \
				$(addsuffix .rel, $(basename $(notdir $(OBJECTS)))) \
				$(SRCDIR)/$(SOURCES)

build: $(SOURCE).ihx
		@echo "Building $(OUTFILE)..."
		@$(HEXBIN) $(SOURCE).ihx
		@mv $(SOURCE).bin bin/${OUTFILE}
		@cp ./emulation/diskimage.dsk ./bin/diskimage.dsk
		@echo "Adding $(OUTFILE) to disk image..."
		@toolchain/msxtar -u -f ./bin/diskimage.dsk ./bin/${OUTFILE}
		@echo "Done."

clean:
		@echo "Cleaning ...."

			@rm *.lst || true 
			@rm *.ihx || true 
			@rm *.asm || true 
			@rm *.lk  || true 
			@rm *.noi || true 
			@rm *.sym || true 
			@rm *.rel || true 
			@rm *.map || true 

cleanall:
		@echo "Cleaning ...."

			@rm *.lst || true 
			@rm *.ihx || true 
			@rm *.asm || true 
			@rm *.lk  || true 
			@rm *.noi || true 
			@rm *.sym || true 
			@rm *.rel || true 
			@rm *.map || true 
			@rm ./bin/* || true

emulator: 
		@echo "Launching BRUNIX ...."
		@$(EMULATOR) &
