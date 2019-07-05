# 3DLed for Valparaiso University Accelerated 3D Printing Lab
![Alt text](Pic1.jpg?raw=true "Title")
This project displays the print progress on a strip of individually addressable leds.
This is done by using an arduino nano to read the pwm signal from the fan pin of the controller board and calculating how many leds to light up on the strip to represent the percentage of the print completed.
The perl script does post processing on the gcode file from the slicer and adds in the commands to
change the fan pins PWM.

The Perl script is adapted from here: https://hackaday.com/2016/07/20/3d-printering-g-code-post-processing-with-perl/
The arduino script currently turns red for heating and turns bright blue to represent an increase. Default is light blue.
==========================================================================================================================================
Tutorial:
Material List:
- Arduino Nano
- Simplify 3D
- Duet Wifi
- Strip of individually addressable Leds
------------------------------------------------------------------------------------------------------------------------------------------
1. Cut the led strip to the length that you would prefer and count the number of leds on that strip. Default number of leds in the Arduino code is 45.
2. Upload the code to the Arduino Nano.
3. Connect Arduino pin A4 to the positive of an empty fan pin and the corresponding ground to ground.
4. Connect pin 6 of the arduino to the Data of the led strip and gnd of the arduino to the strips ground.
5. Connect an external 5v power supply to vcc and ground of the led strip. (Note: It is possible to get away with using the arduino's built in 5V regulator for smaller amounts of leds. If your go this route check what the max current draw from your arduino 5V pin is and make sure your leds won't exceed it!!!!)
6. Install strawberry perry on the computer that will be doing the slicing.
7. Add this command to your slicers post processing. "PATH" is were you placed the postprocessing script. In our case we added this to the post processing of Simplify 3D.
C:\Strawberry\perl\bin\perl.exe "PATH"\LedPostProcessingScript.pl "[output_filepath]"
8. Try it out! You should see the number of leds that are on increment along with the progess of the print.
