daemon: daemon.c 
	gcc -Wall -g $^ -o $@

.PHONY: clean 
clean:
	rm log_cpu.log
	rm -rf daemon
