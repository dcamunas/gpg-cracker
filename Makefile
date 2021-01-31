DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/
DIRFIL := files/

LDLIBS := -pthread -std=c++11
CC := g++

all : dirs compile

dirs:
	mkdir -p $(DIREXE)

compile: 
	$(CC) $(DIRSRC)gpg-cracker.cpp -o $(DIREXE)gpg-cracker -I $(DIRHEA) $(LDLIBS)


solution-letters:
	./$(DIREXE)gpg-cracker --len 4 --charset letters $(DIRFIL)hello.gpg

solution-minus:
	./$(DIREXE)gpg-cracker --len 4 --charset minus $(DIRFIL)hello.gpg

solution-digits:
	./$(DIREXE)gpg-cracker --len 4 --charset digits $(DIRFIL)hello.gpg

solution-file:
	./$(DIREXE)gpg-cracker --charset $(DIRFIL)rockyou.txt $(DIRFIL)hello.gpg

solution:
	./$(DIREXE)gpg-cracker --len 4 $(DIRFIL)hello.gpg

clean : 
	rm -rf *~ core $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~ 
