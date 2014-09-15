# GeeksOnBoard
# 2014

CPPFLAGS= -c -g -Iinc -Wall -pedantic

uklad_rownan: obj/main.o obj/lzespolona.o obj/opcje.o inc/Wektor.hh inc/Macierz.hh inc/UkladRownanLiniowych.hh inc/opcje.hh
	g++ -Wall -pedantic -o uklad_rownan obj/main.o obj/lzespolona.o obj/opcje.o

obj/main.o: src/main.cpp inc/Wektor.hh inc/Macierz.hh inc/UkladRownanLiniowych.hh inc/opcje.hh
	g++ ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/lzespolona.o: src/lzespolona.cpp inc/lzespolona.hh
	g++ ${CPPFLAGS} -o obj/lzespolona.o src/lzespolona.cpp

obj/opcje.o: src/opcje.cpp inc/opcje.hh
	g++ ${CPPFLAGS} -o obj/opcje.o src/opcje.cpp

clean:
	rm -f obj/*.o uklad_rownan core*

doc:
	cd ../dox;  make
