CC=./nbc

BUSNO=003
DEVNO=

OUT=bin/ultrasonic.bin
SOURCES=src/ultrasonic.nxc

DEV=$(lsusb | grep "Lego")
ifeq ("$(DEV)", "")
	DEV="Device not connected"
endif

build:
	$(CC) -O=$(OUT) $(SOURCES)

upload: build
	$(CC) -r -b $(OUT)

clean:
	rm $(OUT)

fix_upload:
	sudo chmod a+rw /dev/bus/usb/$(BUSNO)/$(DEVNO)

show_devices:
	echo $(DEV)	