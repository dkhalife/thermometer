// LCD module connections
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;
// End LCD module connections

char i;
long tlong;
unsigned int adc_rd;
signed long int Cnt=0;
unsigned char Str[7];

void main() {
        //**
        //  Oscillator Configuration:
        //  0b0
        //  - 4 MHz (110)
        //  - Primary system clock (1)
        //  - Stable frequency (1)
        //  - System clock : Internal RC (10)
        //  - Total : 0b01101110
        //**
        OSCCON=0x6E;
        
        //**
        //  Comparator Configuration:
        //  Disable all
        //  - Total : 0b00000111;
        //**
        CMCON=0x07;
        
        //**
        //  A/D Configuration:
        //  0b00
        //  - Select An0 (0000)
        //  - Convertor idle (0)
        //  - A/D Convertor enabled (1)
        //  - Total : 0b00000010;
        //**
        
        ADCON0=0x02;
        //**
        //  A/D Configuration:
        //  0b00
        //  VRef - = VSS (0)
        //  VRef + = VDD (0)
        //  - An0, An1, An2 Analogue (1100)
        //  - Total : 0b00001100;
        //**
        
        ADCON1=0x0C;
        //**
        //  PORT Directions
        //**
        TRISA=0xFF;
        TRISB=0x00;
        PORTB=0x00;
        
        Lcd_Init();                        // Initialize LCD

        Delay_ms(500);
        
        Lcd_Cmd(_LCD_CLEAR);               // Clear display
        Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off

        Lcd_Out(1,1,"Inside: ");
        Lcd_Out(2,1,"Outside: ");

       for(;;){
                if(ADC_read(2) > 700)
                     PORTB |= 0x80;
                else
                     PORTB &= 0x7F;
                
                adc_rd  = ADC_read(0);                 // get ADC value from 0th channel
                tlong = (long)adc_rd * 5500;           // covert adc reading to milivolts
                tlong = tlong / 1023;                  // 0..1023 -> 0-4000mV
                tlong = tlong - 614;                   // 500mV at 0 C
                tlong = tlong / 10;                    // 10mV = 1C
                Cnt   = (int)tlong;
                IntToStr(Cnt,Str);
                Lcd_Out(1,9,Str);
                
                adc_rd  = ADC_read(1);                 // get ADC value from 0th channel
                tlong = (long)adc_rd * 5500;           // covert adc reading to milivolts
                tlong = tlong / 1023;                  // 0..1023 -> 0-4000mV
                tlong = tlong - 834;                   // 500mV at 0 C
                tlong = tlong / 10;                    // 10mV = 1C
                Cnt   = (int)tlong;
                IntToStr(Cnt,Str);
                Lcd_Out(2,9,Str);
                
                Delay_ms(250);
        }
}