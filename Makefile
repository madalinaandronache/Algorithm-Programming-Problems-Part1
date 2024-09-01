# Exemplu de Makefile pentru soluții scrise în C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: servere colorare compresie criptat oferta

# Nu compilați aici, nici măcar ca dependențe de reguli.
run-p1:
	./servere
run-p2:
	./colorare
run-p3:
	./compresie
run-p4:
	./criptat
run-p5:
	./oferta

# Schimbați numele surselor (și, eventual, ale executabilelor - peste tot).
servere: servere.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
colorare: colorare.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
compresie: compresie.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
criptat: criptat.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
oferta: oferta.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Vom șterge executabilele.
clean:
	rm -f servere colorare compresie criptat oferta
