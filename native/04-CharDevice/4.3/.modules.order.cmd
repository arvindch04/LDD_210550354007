cmd_/home/pi/device-drivers/native/04-CharDevice/4.3/modules.order := {   echo /home/pi/device-drivers/native/04-CharDevice/4.3/char_driver.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/04-CharDevice/4.3/modules.order
