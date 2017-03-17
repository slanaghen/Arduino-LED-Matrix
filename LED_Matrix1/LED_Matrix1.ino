// define the pin layout for arduino board
// int powerPin = 5V     // +5V to the power bus
// int groundPin = Gnd   // Gnd to the ground bus
const int dataPin = 8;   // pin 14 on the 75HC595 #1, Data pin
const int clockPin = 9;  // pin 11 on the 75HC595 #1, Clock pin
const int latchPin = 10; // pin 12 on the 75HC595 #1, Latch pin

// This is the array used to hold the box pattern.
unsigned char box[8];
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
	box[0] = B11111111;
	box[1] = B10000001;
	box[2] = B10000001;
	box[3] = B10000001;
	box[4] = B10000001;
	box[5] = B10000001;
	box[6] = B10000001;
	box[7] = B11111111;
}

/**
 * This method is used by arduino to loop infinitely.
 */
void loop() {
	int row;
	// For each row...
	for (row = 0; row < 8; row++) {
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
		shiftOut(dataPin, clockPin, MSBFIRST, rowMask);  // rowMask, IC3
		// if checker bit is set and color bit is not set, light red
		shiftOut(dataPin, clockPin, MSBFIRST, box[row]);			// red, IC2
		// if checker bit is set and color bit is also set, light green
		shiftOut(dataPin, clockPin, MSBFIRST, dark);	// green, IC1

		// fire off new data pulse to LEDs
		digitalWrite(latchPin, HIGH);
	}

}


