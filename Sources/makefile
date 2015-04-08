M68K_PREFIX=/usr/local/bin/m68k-elf-
M52X_PATH=/usr/local/lib/gcc/m68k-elf/4.5.2

GENFLAGS=-m528x -w -gdwarf-2

GCC=$(M68K_PREFIX)gcc -c $(GENFLAGS) -Wall -I. -Ilibs/* -Ilibs
OBJCOPY = $(M68K_PREFIX)objcopy

AR68=$(M68K_PREFIX)ar
RANLIB68=$(M68K_PREFIX)ranlib

AS68=$(M68K_PREFIX)as -m528x -a $(REGNAMEOPT) --gdwarf-2 --warn --fatal-warnings

LD68=$(M68K_PREFIX)ld -v -L$(M52X_PATH)/m5211
OUTFMT = --oformat srec
BINEXT=bin
ADRMAP = -Tmemory.x

#Pour compiler un autre fichier principal l'ajouter dans la variable ci-dessous séparé par un espace. On peut aussi laisser un seul fichier
PGMs = MainController Sandbox

OBJS = libs/crt/crt.o launch_ITs.o libs/spiUtils/spiUtils.o libs/sensorUtils/sensorUtils.o libs/mfprintf/mfprintf.o libs/lib-iobase-evb5213/lib-iobase-evb5213.o


.PRECIOUS: $(OBJS)

all: $(PGMs:=.s19)

%.o : %.c
	$(GCC) $*.c -o $@

%.o : %.s
	$(AS68) -o $@ $*.s > $*.lst


# traduction "quand on me demande un .s19, recompiler les obj (liste ci dessus) et le nom du fichier .s19 demandé, mais en .o"
# % réfère à ce qui est demandé, si on demande Toto.s19 alors % = Toto, de même pour $* dans les lignes de commande
# ici on compile tout une première fois dans un .s19 à l'aide de memory.x qui défini "qui va ou" dans la mémoire
# ce premier .19 est séparé en deux, une partie pour la rom à uploader avec la sonde, et une partie pour la ram, à uploader avec dBug
# l'option -j permet de spécifier quelles sections du .s19 original il faut conserver, leur nom est auto-défini et peut être affiché via
# la commande m68k-elf-objdump -s fichier.s19 
#
# On renomme ici le fichier principal en Main.o pour que memory.x reste correcte quelque soit le fichier
%.s19: $(OBJS) %.o 
	mv $*.o Main.o
	$(LD68) $(OBJS) Main.o -lm -lgcc $(OUTFMT) -o s19/$*_full.s19 $(ADRMAP) -M > $*.map
	$(OBJCOPY) -j.sec1 s19/$*_full.s19 -O srec s19/$*_rom.s19
	$(OBJCOPY) -j.sec2 s19/$*_full.s19 -O srec s19/$*_ram.s19

clean: 
	rm -rf *map
	rm -rf libs/crt/crt.o
	rm -rf libs/mfprintf/mfprintf.o
	rm -rf libs/sensorUtils/sensorUtils.o
	rm -rf libs/spiUtils/spiUtils.o
	rm -rf libs/lib-iobase-evb5213/lib-iobase-evb5213.o

	

