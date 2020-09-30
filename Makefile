all:
	cd kdis && make
	cd kstat && make

lgtm:
	cd kdis && make lgtm
	cd kstat && make lgtm
	cd kelf && make lgtm

clean:
	cd kdis && make clean
	cd kstat && make clean
	cd kelf && make clean

