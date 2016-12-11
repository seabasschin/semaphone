control: control.c write
	gcc control.c -o control

write: writing.c 
	gcc writing.c -o write

clean:
	rm *~ *.out
