# 3DLed
Displays the print progress on an led strip.
This uses an arduino nano to read the pwm signal of the fan pin on the 3d printer controller and based on that value it sets the leds
on the strip to represent a percentage. The perl script does post processing on the gcode file from the slicer and adds in the commands to
change the fan pins PWM.

The Perl script is adapted from here: https://hackaday.com/2016/07/20/3d-printering-g-code-post-processing-with-perl/
The arduino script currently turns red for heating and turns bright blue to represent an increase. Default is light blue.

Tutorial:
In this example I used and arduino nano with a individually addressable led strip attached, strawberry perl, and Simplify 3D.
1. Cut the strip to the length that you would prefer and count the number of leds on that strip.
2. Upload the arduino code to the nano. Make changes to the code as you see fit such as pinout and color.

