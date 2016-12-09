exe: control.c
	gcc control.c -o exe

run: exe
	./exe

clean:
	rm *~ *.out
