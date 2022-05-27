SOURCE	= confronti.cpp
OUT		= LVQuickSort
CC		= g++
EX		= ./
PY		= python3

all:
	
	$(CC) confronti.cpp
	@echo "Sto ordinando la sequenza, potrebbero volerci alcuni minuti."
	$(EX)a.out
	$(PY) isto.py
	@echo "Istogrammi creati con successo"

histogram:
	$(PY) isto.py

clean:
	rm -f NormHist.png Hist.png a.out output.txt