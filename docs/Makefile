
all: doxygen

doxygen:
	doxygen Doxyfile

run: doxygen
	http-server html

clean:
	rm -rfv html
