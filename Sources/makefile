M68K_PREFIX=/usr/local/bin/m68k-elf-
M52X_PATH=/usr/local/lib/gcc/m68k-elf/4.5.2

GENFLAGS=-m5200 -w -gdwarf-2

GCC=$(M68K_PREFIX)gcc -c $(GENFLAGS) -Wall -I. -Ilibs/* -Ilibs

AR68=$(M68K_PREFIX)ar
RANLIB68=$(M68K_PREFIX)ranlib



# ajouter cette option pour utiliser l'appelation D0, D1 .. au lieu de %D0, %D1 ...
#REGNAMEOPT= --register-prefix-optional
AS68=$(M68K_PREFIX)as -m5200 -a $(REGNAMEOPT) --gdwarf-2 --warn --fatal-warnings

#Remarque: -lgcc (inclusion de libgcc.a) **DOIT** etre place apres la liste des objets
# sous peine de voir des symboles de cette librairie non trouves
# ajouter option -s (strip) pour supprimer les options de debug
LD68=$(M68K_PREFIX)ld -v -L$(M52X_PATH)/m5211/
#OUTFMT = --oformat srec
BINEXT=bin
ADRMAP = -Ttext 20002000

PGM = CentInertielleTest
PGM2 = 4xCopterV1.1
PGM3 = ReponseIndicielle

OBJS = libs/crt/crt.o launch_ITs.o libs/spiUtils/spiUtils.o libs/imuUtils/imuUtils.o libs/mfprintf/mfprintf.o libs/lib-iobase-evb5213/lib-iobase-evb5213.o $(PGM3).o
#OBJS = libs/spiUtils/spiUtils.o libs/crt/crt.o libs/mfprintf/mfprintf.o libs/lib-iobase-evb5213/lib-iobase-evb5213.o


all: $(PGM3).s19 

%.o : %.c
	$(GCC) $*.c -o $@

%.o : %.s
	$(AS68) -o $@ $*.s > $*.lst

#%.s19 : %.o
#	$(LD68) $(OBJS) $*.o -lm -lgcc --oformat srec -o $(PGM).s19 $(ADRMAP) -M > $(PGM).map


#$(PGM).s19: $(OBJS)
#	$(LD68) $(OBJS) -lm -lgcc --oformat srec -o $(PGM).s19 $(ADRMAP) -M > $(PGM).map

#$(PGM2).s19: $(OBJS)
#	$(LD68) $(OBJS) -lm -lgcc --oformat srec -o $(PGM2).s19 $(ADRMAP) -M > $(PGM2).map

$(PGM3).s19: $(OBJS)
	$(LD68) $(OBJS) -lm -lgcc --oformat srec -o $(PGM3).s19 $(ADRMAP) -M > $(PGM3).map	

clean: 
	rm -rf *o
	rm -rf *s19
	rm -rf *map
	rm -rf libs/crt/crt.o
	rm -rf libs/mfprintf/mfprintf.o
	rm -rf libs/spiUtils/spiUtils.o
	rm -rf libs/lib-iobase-evb5213/lib-iobase-evb5213.o



	

