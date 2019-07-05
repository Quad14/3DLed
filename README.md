# 3DLed
![Alt text](Pic1.png?raw=true "Title")
Displays the print progress on an led strip.
This uses an arduino nano to read the pwm signal of the fan pin on the 3d printer controller (Duet Wifi) and based on that value it sets the leds
on the strip to represent a percentage. The perl script does post processing on the gcode file from the slicer and adds in the commands to
change the fan pins PWM.

The Perl script is adapted from here: https://hackaday.com/2016/07/20/3d-printering-g-code-post-processing-with-perl/
The arduino script currently turns red for heating and turns bright blue to represent an increase. Default is light blue.

Tutorial:
In this example I used an arduino nano with a individually addressable led strip attached, strawberry perl, and Simplify 3D.
1. Cut the strip to the length that you would prefer and count the number of leds on that strip. Default in the arduino code is 45 leds.
2. Upload the arduino code to the nano. Make changes to the code as you see fit such as pinout and color.
3. Connect arduino pin A4 to the positive of an empty fan pin and the corresponding ground to ground.
4. Connect pin 6 of the arduino to the Data of the led strip and gnd of the arduino to the strips ground.
5. Connect an external 5v power supply to vcc and ground of the led strip. (Note: It is possible to get away with using the arduino's built in 5V regulator for smaller amounts of leds)
6. Install strawberry perry on the computer that will be doing the slicing.
7. Add this command to your slicers post processing. Path is were you placed the postprocessing script.
C:\Strawberry\perl\bin\perl.exe "PATH"\LedPostProcessingScript.pl "[output_filepath]"

