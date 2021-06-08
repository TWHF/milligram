main.o: main.cpp
	g++ -c main.cpp

bitwriter.o: bitwriter.cpp bitwriter.h
	g++ -c bitwriter.cpp

image_processor.o: image_processor.cpp image_processor.h
	g++ -c image_processor.cpp

encoder.o: encoder.cpp encoder.h
	g++ -c encoder.cpp

mge: image_processor.o encoder.o bitwriter.o main.o
	g++ image_processor.o encoder.o bitwriter.o main.o -o mge

debug: image_processor.o encoder.o bitwriter.o main.o
	g++ -g image_processor.o encoder.o bitwriter.o main.o -o mge

clean:
	rm *.o mge
