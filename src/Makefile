# Copyright (c) 2015-2019 Damien Ciabrini
# This file is part of ngdevkit
#
# ngdevkit is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# ngdevkit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with ngdevkit.  If not, see <http://www.gnu.org/licenses/>.

all: cart nullbios

include ../Makefile.config

# ROM names and common targets
include ../Makefile.common
$(CART): $(PROM) $(CROM1) $(CROM2) $(SROM) $(VROM) $(MROM) | rom

OBJS=main paletteDefs tests
ELF=rom.elf

$(ELF):	$(OBJS:%=%.o)
	$(M68KGCC) -o $@ $^ `pkg-config --libs ngdevkit`

%.o: %.c
	$(M68KGCC) `pkg-config --cflags ngdevkit` -std=c99 -fomit-frame-pointer -g -c $< -o $@


# sound driver ROM: ngdevkit's nullsound
$(MROM): | rom
	$(Z80SDOBJCOPY) -I ihex -O binary $(NULLSOUNDDIR)/nullsound.ihx $@ --pad-to 131072

# sample ROM: empty
$(VROM): | rom
	dd if=/dev/zero bs=1024 count=512 of=$@

# fixed tile ROM: fonts from common assets
$(SROM_AND_CROM) srom_and_crom: rom
	cd .. && sromcrom -i resources/resources.json

# program ROM
$(PROM): $(ELF) | rom
	$(M68KOBJCOPY) -O binary -S -R .comment $< $@ && dd if=$@ of=$@ conv=notrunc,swab

neosd:
	rm -f rom/*.bin && \
	rm -f rom/output.* && \
	neosdconv -i rom -o rom/scaling.neo -y 2021 -n scaling -g Other -m city41 -# 45
	
tosd:
	make neosd && cp rom/scaling.neo /media/matt/7473-D0EE/ && umount /media/matt/7473-D0EE
	
mame:
	cp rom/puzzledp.zip ~/mame/roms && mame -w puzzledp

clean:
	rm -f *.png *.o *~ $(ELF) tmp.* rom/*.*

.PHONY: clean
