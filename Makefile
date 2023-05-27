install-dev:
	python -m pip install --user platformio
	python -m platformio pkg install --library 'Adafruit/Adafruit NeoPixel'
	
	# Try a build to trigger autoinstall of some stuff
	python -m platformio run -e nanoatmega328

build: src/main.cpp
	python -m platformio run -e nanoatmega328

build-and-flash: src/main.cpp
	python -m platformio run -e nanoatmega328 --target upload
