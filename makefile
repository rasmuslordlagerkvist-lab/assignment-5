CC = g++
CFLAGS = -std=c++17

slm : main.cpp ModelCreate.cpp ModelTextGenerator.cpp
	$(CC) $(CFLAGS) -o slm main.cpp ModelCreate.cpp ModelTextGenerator.cpp

clean:
	rm -f *.o slm

.PHONY : clean
