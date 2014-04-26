#line 1 "C:/Users/Dan/Dropbox/PIC Projects/Thermometer with LCD/thermo.c"

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


char i;
long tlong;
unsigned int adc_rd;
signed long int Cnt=0;
unsigned char Str[7];

void main() {









 OSCCON=0x6E;






 CMCON=0x07;










 ADCON0=0x02;









 ADCON1=0x0C;



 TRISA=0xFF;
 TRISB=0x00;
 PORTB=0x00;

 Lcd_Init();

 Delay_ms(500);

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 Lcd_Out(1,1,"Inside: ");
 Lcd_Out(2,1,"Outside: ");

 for(;;){
 if(ADC_read(2) > 700)
 PORTB |= 0x80;
 else
 PORTB &= 0x7F;

 adc_rd = ADC_read(0);
 tlong = (long)adc_rd * 5500;
 tlong = tlong / 1023;
 tlong = tlong - 614;
 tlong = tlong / 10;
 Cnt = (int)tlong;
 IntToStr(Cnt,Str);
 Lcd_Out(1,9,Str);

 adc_rd = ADC_read(1);
 tlong = (long)adc_rd * 5500;
 tlong = tlong / 1023;
 tlong = tlong - 834;
 tlong = tlong / 10;
 Cnt = (int)tlong;
 IntToStr(Cnt,Str);
 Lcd_Out(2,9,Str);

 Delay_ms(250);
 }
}
