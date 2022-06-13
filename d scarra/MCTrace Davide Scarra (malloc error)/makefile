SOURCE	= MCTrace.cpp
OUT		= MCTrace
CC		= g++
EX		= ./
PY		= python3

all:
	
	$(CC) MCTrace.cpp
	$(EX)a.out
	$(PY) isto.py
	@echo "Istogrammi creati con successo"

histogram:
	$(PY) isto.py

clean:
	rm -f 5M.png 10M.png 25M.png 100M.png a.out output.txt