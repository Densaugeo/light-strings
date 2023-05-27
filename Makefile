install-dev:
	python -m pip install --user platformio
	python -m platformio pkg install --library 'Adafruit/Adafruit NeoPixel'
	
	echo 'NOTE: Must run both build and flash to autoinstall platformio stuff'

build: src/main.cpp
	python -m platformio run -e nanoatmega328

build-and-flash: src/main.cpp
	python -m platformio run -e nanoatmega328 --target upload
