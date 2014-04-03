src := $(shell ls *.cpp) 
objs := $(patsubst %.cpp, %.o, $(src)) 
test : $(objs)
	g++ -o $@ $^ 
%.o : %.c
	g++ -c -g -o $@ $<
.PTHONY : clean
clean:
	rm -f test *.o