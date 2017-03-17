// define the pin layout for arduino board
// int powerPin = 5V     // +5V to the power bus
// int groundPin = Gnd   // Gnd to the ground bus
const int dataPin = 8;   // pin 14 on the 75HC595 #1, Data pin
const int clockPin = 9;  // pin 11 on the 75HC595 #1, Clock pin
const int latchPin = 10; // pin 12 on the 75HC595 #1, Latch pin

// This is the array used to hold the box pattern.
unsigned char box[4][8];
// This is used to clear a row of LEDs.
unsigned char dark;

/**
 * Setup is used by arduino to set initial conditions.
 */
void setup() {
	// Set the specified pins to be used as outputs
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	// start by clearing (turning off power) to all pins
	digitalWrite(latchPin, LOW);
	digitalWrite(dataPin, LOW);
	digitalWrite(clockPin, LOW);

	// This is used to turn off all LEDs in a row.
	dark = B00000000;

	// Create a large box pattern, turning on all LEDs on the perimeter.
	box[0][0] = B11111111;
	box[0][1] = B10000001;
	box[0][2] = B10000001;
	box[0][3] = B10000001;
	box[0][4] = B10000001;
	box[0][5] = B10000001;
	box[0][6] = B10000001;
	box[0][7] = B11111111;

	// Create a smaller box pattern
	box[1][0] = B00000000;
	box[1][2] = B01111110;
	box[1][3] = B01000010;
	box[1][4] = B01000010;
	box[1][5] = B01000010;
	box[1][6] = B01111110;
	box[1][0] = B00000000;

	// And a smaller-yet box pattern
	box[2][0] = B00000000;
	box[2][1] = B00000000;
	box[2][2] = B00111100;
	box[2][3] = B00100100;
	box[2][4] = B00100100;
	box[2][5] = B00111100;
	box[2][6] = B00000000;
	box[2][7] = B00000000;

	// And the smallest box pattern
	box[3][0] = B00000000;
	box[3][1] = B00000000;
	box[3][2] = B00000000;
	box[3][3] = B00011000;
	box[3][4] = B00011000;
	box[3][5] = B00000000;
	box[3][6] = B00000000;
	box[3][7] = B00000000;
}

/**
 * This method is used by arduino to loop infinitely.
 */
void loop() {
	unsigned char red, green;
	int row, pattern, color, pulseNumber;
	// For each color (red and green)...
	for (color = 0; color < 2; color++) {
		// For each pattern...
		for (pattern = 0; pattern < 4; pattern++) {
			// This loop is used to provide multiple pulses to the LED with the
			// same colored pattern in order to hold that image.
			for (pulseNumber = 0; pulseNumber < 50; pulseNumber++) {
				// For each row...
				for (row = 0; row < 8; row++) {
					// Set the color and pattern to display with this pulse.
					if (color == 0) {
						red = dark;
						green = box[pattern][row];
					} else {
						green = dark;
						red = box[pattern][row];
					}
					// Create a bit mask for the common cathode row.
					// We want to send power to all rows so that all rows are displayed.
					unsigned char rowMask = B11111111; // use 1's for common cathode and 0's for common anode.
					bitWrite(rowMask, row, LOW); // use LOW for common cathode, HIGH for common anode.

					// hold LEDs and load new data pulse
					digitalWrite(latchPin, LOW);
					// mechanism for representing a king is to blink that checker
					// first show all colored checkers (blinks kings on)
					// the first byte sent is pushed through the first through to the last IC
					// in the series of three ICs.  The last byte sent is pushed to the first IC.
					shiftOut(dataPin, clockPin, MSBFIRST, rowMask);      // rowMask, IC3
					// if checker bit is set and color bit is not set, light red
					shiftOut(dataPin, clockPin, MSBFIRST, red);	// red, IC2
					// if checker bit is set and color bit is also set, light green
					shiftOut(dataPin, clockPin, MSBFIRST, green);// green, IC1

					// fire off new data pulse to LEDs
					digitalWrite(latchPin, HIGH);
				}
			}
		}
	}
}


