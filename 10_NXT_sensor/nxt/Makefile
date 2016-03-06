CC=./nbc

BUSNO=003
DEVNO=

OUT=bin/ultrasonic.bin
SOURCES=src/ultrasonic.nxc

build:
	$(CC) -O=$(OUT) $(SOURCES)

upload:
	$(CC) -r -b $(OUT)

fix_upload:
	sudo chmod a+rw /dev/bus/usb/$(BUSNO)/$(DEVNO)

clean:
	rm $(OUT)
