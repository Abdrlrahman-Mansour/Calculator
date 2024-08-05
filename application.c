/* 
 * File:   application.c
 * Author: Abdelrahman Mansour
 *
 * Created on August 1, 2024, 10:13 PM
 */

#include "application.h"

void add_two_numbers(void);
void sub_two_numbers(void);
void mult_two_numbers(void);
void div_two_numbers(void);
void clear_lcd(void);
Std_ReturnType ret = E_NOT_OK;
uint8 keybad_value =0 ;
uint8 value = 0 ;
Std_ReturnType retpad = 0;
uint8 first_digit1,second_digit1;
uint8 first_digit2,second_digit2;
uint8 operator;
uint8 asignment;
uint8 on_off;
sint16 result;
sint16 str[7];
lcd_8bit_t lcd_obj = {
  .lcd_rs.port = PORTA_INDEX,
  .lcd_rs.pin = PIN5,
  .lcd_rs.direction = GPIO_OUTPUT ,
  .lcd_rs.direction = LOW ,
  .lcd_en.port = PORTA_INDEX,
  .lcd_en.pin = PIN6,
  .lcd_en.direction = GPIO_OUTPUT ,
  .lcd_en.direction = LOW ,
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].pin = PIN0,
  .lcd_data[0].direction = GPIO_OUTPUT,
  .lcd_data[0].logic = LOW,
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].pin = PIN1,
  .lcd_data[1].direction = GPIO_OUTPUT,
  .lcd_data[1].logic = LOW,
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].pin = PIN2,
  .lcd_data[2].direction = GPIO_OUTPUT,
  .lcd_data[2].logic = LOW,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].pin = PIN3,
  .lcd_data[3].direction = GPIO_OUTPUT,
  .lcd_data[3].logic = LOW,
  .lcd_data[4].port = PORTC_INDEX,
  .lcd_data[4].pin = PIN4,
  .lcd_data[4].direction = GPIO_OUTPUT,
  .lcd_data[4].logic = LOW,
  .lcd_data[5].port = PORTC_INDEX,
  .lcd_data[5].pin = PIN5,
  .lcd_data[5].direction = GPIO_OUTPUT,
  .lcd_data[5].logic = LOW,
  .lcd_data[6].port = PORTC_INDEX,
  .lcd_data[6].pin = PIN6,
  .lcd_data[6].direction = GPIO_OUTPUT,
  .lcd_data[6].logic = LOW,
  .lcd_data[7].port = PORTC_INDEX,
  .lcd_data[7].pin = PIN7,
  .lcd_data[7].direction = GPIO_OUTPUT,
  .lcd_data[7].logic = LOW,
};

keypad_t keypad_obj={
.keypad_r_pins[0].port =PORTD_INDEX,
.keypad_r_pins[0].pin = PIN0,
.keypad_r_pins[0].direction = GPIO_OUTPUT,
.keypad_r_pins[0].logic =LOW,
.keypad_r_pins[1].port =PORTD_INDEX,
.keypad_r_pins[1].pin = PIN1,
.keypad_r_pins[1].direction = GPIO_OUTPUT,
.keypad_r_pins[1].logic =LOW,
.keypad_r_pins[2].port =PORTD_INDEX,
.keypad_r_pins[2].pin = PIN2,
.keypad_r_pins[2].direction = GPIO_OUTPUT,
.keypad_r_pins[2].logic =LOW,
.keypad_r_pins[3].port =PORTD_INDEX,
.keypad_r_pins[3].pin = PIN3,
.keypad_r_pins[3].direction = GPIO_OUTPUT,
.keypad_r_pins[3].logic =LOW,
.keypad_c_pins[0].port =PORTD_INDEX,
.keypad_c_pins[0].pin = PIN4,
.keypad_c_pins[0].direction = GPIO_INPUT,
.keypad_c_pins[0].logic =LOW,
.keypad_c_pins[1].port =PORTD_INDEX,
.keypad_c_pins[1].pin = PIN5,
.keypad_c_pins[1].direction = GPIO_INPUT,
.keypad_c_pins[1].logic =LOW,
.keypad_c_pins[2].port =PORTD_INDEX,
.keypad_c_pins[2].pin = PIN6,
.keypad_c_pins[2].direction = GPIO_INPUT,
.keypad_c_pins[2].logic =LOW,
.keypad_c_pins[3].port =PORTD_INDEX,
.keypad_c_pins[3].pin = PIN7,
.keypad_c_pins[3].direction = GPIO_INPUT,
.keypad_c_pins[3].logic =LOW,
};

int main() {
    ret = lcd_8bit_init(&lcd_obj);
    ret = keypad_init(&keypad_obj);

    while (1) {
        ret = lcd_8bit_send_command(&lcd_obj , LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF);
        do{
        first_digit1 = 0;
        ret = keypad_get_value(&keypad_obj , &first_digit1);
        
        }while(first_digit1 == 0);
        __delay_ms(250);
        ret = lcd_8bit_send_char_data_pos(&lcd_obj,1,1,first_digit1);
        
        do{
        ret = keypad_get_value(&keypad_obj , &second_digit1);
        
        }while(second_digit1 == 0);
        __delay_ms(250);
        ret = lcd_8bit_send_char_data_pos(&lcd_obj,1,2,second_digit1);
        
         do{
        
        ret = keypad_get_value(&keypad_obj , &operator);
        
        }while(operator == 0);
        __delay_ms(250);
        ret = lcd_8bit_send_char_data_pos(&lcd_obj,1,4,operator);
         do{
        ret = keypad_get_value(&keypad_obj , &first_digit2);
        }while(first_digit2 == 0);
        __delay_ms(250);
        ret = lcd_8bit_send_char_data_pos(&lcd_obj,1,6,first_digit2);
        do{
        ret = keypad_get_value(&keypad_obj , &second_digit2);
        }while(second_digit2 == 0);
        __delay_ms(250);
        ret = lcd_8bit_send_char_data_pos(&lcd_obj,1,7,second_digit2);
        do{
        ret = keypad_get_value(&keypad_obj , &asignment);
        }while(asignment == 0);
        __delay_ms(250);
        ret = lcd_8bit_send_char_data_pos(&lcd_obj,1,9,asignment);
        if(asignment == '='){
        switch(operator){
            case '+' :
                add_two_numbers();
                break;
            case '-' :
                sub_two_numbers();
                break;
            case '*' :
                mult_two_numbers();
                break;
            case '/' :
                div_two_numbers();
                break;
            default :
                break;

        }
       }
        else{/*Nothing*/}
        clear_lcd();
    } 
    return (EXIT_SUCCESS);
}

void add_two_numbers(void){
   uint8 first_number, second_number ;
   first_number= (second_digit1-48)+10*(first_digit1-48);
   second_number = (second_digit2-48)+10*(first_digit2-48);
   result = first_number + second_number;  
   ret = convert_uint8_to_string(result , str);
   ret = lcd_8bit_send_string_pos(&lcd_obj,1,11,str);
   
}
void sub_two_numbers(void){
   uint8 first_number, second_number ;
   first_number= (second_digit1-48)+10*(first_digit1-48);
   second_number = (second_digit2-48)+10*(first_digit2-48);
   result = first_number - second_number;  
   ret = convert_uint32_to_string(result , str);
   ret = lcd_8bit_send_string_pos(&lcd_obj,1,11,str);
}
void mult_two_numbers(void){
   uint8 first_number, second_number ;
   first_number= (second_digit1-48)+10*(first_digit1-48);
   second_number = (second_digit2-48)+10*(first_digit2-48);
   result = first_number * second_number;  
   ret = convert_uint32_to_string(result , str);
   ret = lcd_8bit_send_string_pos(&lcd_obj,1,11,str);      
}
void div_two_numbers(void){
   uint8 first_number, second_number ;
   first_number= (second_digit1-48)+10*(first_digit1-48);
   second_number = (second_digit2-48)+10*(first_digit2-48);
   result = first_number / second_number;  
   ret = convert_uint32_to_string(result , str);
   ret = lcd_8bit_send_string_pos(&lcd_obj,1,11,str);  
}
void clear_lcd(void){
    do{
        ret = keypad_get_value(&keypad_obj , &on_off);
    }while(on_off == 0);
    __delay_ms(250);
    ret = lcd_8bit_send_command(&lcd_obj , LCD_CLEAR);
    first_digit1 = 0;
    on_off = 0;
    second_digit1 = 0;
    first_digit2 = 0;
    second_digit2 = 0;
    asignment = 0;
    operator = 0;
}