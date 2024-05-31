ifdef FLASH
TARGET=--target upload
else
TARGET=
endif

install-dev:
	python -m pip install --user platformio
	python -m platformio pkg install --library 'Adafruit/Adafruit NeoPixel'
	
	echo 'NOTE: Must run builds with FLASH=1 to autoinstall platformio stuff'

twinkle: src/twinkle.cpp
	python -m platformio run -e pico-twinkle $(TARGET)

conway: src/conway.cpp
	python -m platformio run -e pico-conway $(TARGET)
