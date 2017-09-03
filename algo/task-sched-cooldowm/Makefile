run: task-sched-cooldowm
	./task-sched-cooldowm

task-sched-cooldowm: task-sched-cooldowm.cc
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -fr task-sched-cooldowm *.o *.dSYM
