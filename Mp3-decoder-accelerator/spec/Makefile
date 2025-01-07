LDLIBS= -lasound
mp3decoder: 
	g++ -std=c++11 *.cpp -o $@ $^ $(LDLIBS)
	
.PHONY: clean
clean:
	rm -f mp3decoder


