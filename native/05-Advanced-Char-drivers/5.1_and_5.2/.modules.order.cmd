cmd_/home/pi/device-drivers/native/05-Advanced-Char-drivers/5.1_and_5.2/modules.order := {   echo /home/pi/device-drivers/native/05-Advanced-Char-drivers/5.1_and_5.2/IOCTL_calculator.ko; :; } | awk '!x[$$0]++' - > /home/pi/device-drivers/native/05-Advanced-Char-drivers/5.1_and_5.2/modules.order