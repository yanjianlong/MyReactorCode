# ${mkdir obj}
# ${mkdir bin}
src := ${shell ls *.cpp}
objpath = ./obj/%.o
srcpath = %.cpp
objs := ${patsubst ${srcpath}, ${objpath}, ${src}}
exefile := ./bin/server
${exefile} : ${objs}
	g++ -o $@ $^ -lpthread 
${objpath} : ${srcpath}
	g++ -c -g -o $@ $<
.PTHONY : clean
clean:
	rm -f ${exefile} ${objs}
