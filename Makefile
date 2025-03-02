PY=python3.13

ifdef FLASH
TARGET=--target upload
else
TARGET=
endif

install-dev:
	$(PY) -m venv venv-$(PY)
	venv-$(PY)/bin/python -m pip install --upgrade pip
	venv-$(PY)/bin/python -m pip install platformio==6.1.16
	venv-$(PY)/bin/python -m platformio pkg install --library \
		'Adafruit/Adafruit NeoPixel'
	
	# Documented at https://docs.platformio.org/en/latest/core/installation/udev-rules.html
	curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
	
	@printf '\n\033[38;2;255;224;0m!!!! NOTE: Must run builds with FLASH=1 '
	@printf 'to autoinstall platformio stuff !!!!\033[0m\n\n'

twinkle: src/twinkle.cpp
	venv-$(PY)/bin/python -m platformio run -e pico-twinkle $(TARGET)

conway: src/conway.cpp
	venv-$(PY)/bin/python -m platformio run -e pico-conway $(TARGET)
