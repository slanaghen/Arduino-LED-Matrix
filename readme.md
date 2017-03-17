#LED MATRIX
	
##PURPOSE  
This exercise deals with driving a matrix of LEDs on an Arduino board. This will be a further extension of the work you have done with the Sparkfun Inventor’s Kit (SIK). You’ve used a shift register to light multiple LEDs. We’re going to take that one step further and use multiple shift registers to light many more LEDs: 128 to be precise!

Exercise objectives are:

1. Given a schematic layout, wire a circuit to drive an 8x8 dual color LED matrix display.
2. Given a series of Arduino programs:
  a. Drive your circuit to display a solid red box around the LED matrix.
  b. Animate that red box to become smaller and smaller.
  c. Alternate the same animation in red and then green.

The C source code is contained in the Baseline.zip file. You'll see an Arduino sketch with its own .ino source file: LED_Matrix1.ino. This contains the code used for the static red box display.

##OVERVIEW
Turning on and off an LED is very fast. By sending a pulse to light one row, then the next, then the next, and so on until all 8 rows have been briefly lit, it appears to the human eye as a flash of the whole board. Sending the same pulse multiple times will hold the image on the matrix and make it appear as a solid pattern. 

You should have a dual color LED matrix. We are going to design a circuit using that matrix and program it to display an animated two-color pattern. We learned how to drive 8 LEDs with only a few pins on the Arduino board. We will need to drive 24 pins (8 red, 8 green and 8 row cathodes) so we will use 3 shift registers. We daisy chain them together so that when we call shiftOut() multiple times, the data will cascade to each of the shift registers in turn.

##Materials

For this exercise, you will need:
- 2 breadboards
- 1 Dual Color LED Matrix (YSM-1288CR3G2C2)
- 16 330 ohm resistors
- 3 shift registers (74HC595)
- 20 or 22 AWG gauge solid (not stranded) wire and wire stripper (or use an assortment of pre-bent, pre-stripped wire)

You may need to combine your SIK with components from others in order to have the components necessary to complete this exercise.


##Circuit Assembly

Assemble the board as shown in the schematic below. This circuit contains more components with many more wires than you have used on the basic circuits you have assembled previously. You will need to consider how you lay the components out on the board and how to arrange the wires.

Figure 1: Circuit Schematic


##Activity 1: Solid red box

Once the hardware assembly is complete, we will test it using the baseline code (LED_Matrix1.ino) that will drive the circuit. First we are going to display a red box around the matrix. A bit pattern representing a box around the perimeter of the matrix is defined. We used a binary representation to make this clear, but we could just as easily have written:

box[0] = 0xFF;		or  
box[0] = 255;		instead of  
box[0] = B11111111;  

Once that setup is done, we send that pattern to the shift register controlling the red LEDs in an infinite loop. We do this with the code provided in the zip file.

##Activity 2: Animated red box

Next, write code to animate the image and make it appear that the red box is getting smaller. To do this, write a source file named LED_Matrix2.ino that will:

* Create three more bit patterns representing boxes of decreasing size and store in an array of patterns. 
* Add an outer loop to cycle through each pattern in the array of patterns. 
* Add a loop between the inner display loop and the outer pattern loop. This is to display the same pattern many times, to control the speed of the animation.

Compile and test your code. 

##Activity 3: Dual color animated display

Finally, write code to alternate colors between red and green LEDs in the box animation. To do this, write a source file named LED_Matrix3.ino that will
* Add an outer loop to alternate between the two colors. 
* On the inner-most loop, set the color as well as the pattern.

Compile and test your code.

##Conclusion

As you can see, once the circuit is in place, you can produce different results on the same hardware by making software changes. 

##Help & Hints
* The wires provided in the Sparkfun kit are great for simple circuits, but you may want to cut and strip your own custom-length wires and keep them well organized (bent at right angles and close to the board) when laying out a more complex circuit. For example, some of the wires you will use for this circuit are very short. Having wires of the appropriate length will minimize clutter on your circuit. 
* The terms “LED matrix” and “LED array” mean the same thing.
* The picture below, while not identical to the circuit you will create in this exercise, is representative of how you would wire the LED matrix. Your circuit would not include the two extra LEDs that are separate from the LED matrix. Also notice that the LED matrix is plugged in across two breadboards. A more organized circuit layout will greatly simplify troubleshooting. 



