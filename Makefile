ifdef FLASH
TARGET=--target upload
else
TARGET=
endif

install-dev:
	python -m pip install --user platformio
	python -m platformio pkg install --library 'Adafruit/Adafruit NeoPixel'
	
	# Documented at https://docs.platformio.org/en/latest/core/installation/udev-rules.html
	curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
	
	echo 'NOTE: Must run builds with FLASH=1 to autoinstall platformio stuff'

twinkle: src/twinkle.cpp
	python -m platformio run -e pico-twinkle $(TARGET)

conway: src/conway.cpp
	python -m platformio run -e pico-conway $(TARGET)
