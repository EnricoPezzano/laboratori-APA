all:
	g++ LVQuickSort.cpp -o startLVQS

	@echo "Avvio il programma, la sequenza verrà ordinata..."

	./startLVQS

	@echo "Creo gli istogrammi..."

	python3 make_ist.py

	@echo "Programma terminato con successo."

clean:
	rm -f istogramma.png comparison.dat espettazione.dat startLVQS