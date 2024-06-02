SOURCE = main
FUNCTIONS = ipv4netid
OUTPUT = a

output: $(SOURCE).c
	gcc $(SOURCE).c $(FUNCTIONS).c -o $(OUTPUT)

clean:
	rm $(OUTPUT)*
