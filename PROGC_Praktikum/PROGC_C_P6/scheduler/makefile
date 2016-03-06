# ------------------------------------------------------------------
# --  _____       ______  _____                                    -
# -- |_   _|     |  ____|/ ____|                                   -
# --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
# --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur   -
# --  _| |_| | | | |____ ____) |  (University of Applied Sciences) -
# -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
# ------------------------------------------------------------------
# --
# -- Project     : mini scheduler
# -- Description : a simple time-sliced scheduler (non-preemptive)
# --
# -----------------------------------------------------------------
# --
# -- Change History
# -- Date     | Name     | Modification
# ------------|----------|-----------------------------------------
# -- 10.02.11 | fisa     | file created
# -----------------------------------------------------------------

CC      = gcc
CFLAGS  = -Wall
LDFLAGS = 

OBJ = main.o scheduler.o

BIN = scheduler

prog: $(OBJ)
	$(CC) $(CFLAGS) -o scheduler $(OBJ) $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<