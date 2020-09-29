all:
	cd kdis && make
	cd kstat && make

lgtm:
	cd kdis && make lgtm
	cd kstat && make lgtm

clean:
	cd kdis && make clean
	cd kstat && make clean

