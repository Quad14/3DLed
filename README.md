# 3DLed
Displays the print progress on an led strip.
This uses an arduino nano to read the pwm signal of the fan pin on the 3d printer controller and based on that value it sets the leds
on the strip to represent a percentage. The perl script does post processing on the gcode file from the slicer and adds in the commands to
change the fan pins PWM.
