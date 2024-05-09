SOURCE = ipv4netid
OUTPUT = out

output: $(SOURCE).c
	gcc $(SOURCE).c -o $(OUTPUT)

clean:
	rm $(OUTPUT).*
