all:
	cd kdis && make
	cd kelf && make
	cd kstat && make
	cd knf && make

lgtm:
	cd kdis && make lgtm
	cd kelf && make lgtm
	cd kstat && make lgtm
	cd knf && make lgtm

clean:
	cd kdis && make clean
	cd kelf && make clean
	cd kstat && make clean
	cd knf && make clean

