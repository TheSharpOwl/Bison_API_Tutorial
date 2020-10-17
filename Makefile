example: Scanner.c Parser.y 
	bison -d Parser.y
	gcc Scanner.c Parser.tab.c -o program 
