/*
 * lcdI2C.h
 *
 *  Created on: 27-Dec-2021
 *      Author: pmvanker
 */
#include "bus.h"
#include "i2c.h"
#include "lcd.h"
#include <cstdint>

namespace pmvankerNano{

class LiquidCrystal_I2C : public I2CDevice {
public:
	LiquidCrystal_I2C(uint8_t bus,uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
	void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
	void clear();
	void home();
	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void printLeft();
	void printRight();
	void leftToRight();
	void rightToLeft();
	void shiftIncrement();
	void shiftDecrement();
	void noBacklight();
	void backlight();
	void autoscroll();
	void noAutoscroll();
	void createChar(uint8_t, uint8_t[]);
	void setCursor(uint8_t, uint8_t);
	void command(uint8_t);
	void init();

	////compatibility API function aliases
	void blink_on();						// alias for blink()
	void blink_off();       					// alias for noBlink()
	void cursor_on();      	 					// alias for cursor()
	void cursor_off();      					// alias for noCursor()
	void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
	void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
	void printstr(const char[]);
	void print(const char ch);

private:
	void init_priv();
	void send(uint8_t, uint8_t);
	void write4bits(uint8_t);
	void expanderWrite(uint8_t);
	void pulseEnable(uint8_t);
	uint8_t _Addr;
	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;
	uint8_t _numlines;
	uint8_t _cols;
	uint8_t _rows;
	uint8_t _backlightval;
};

};



