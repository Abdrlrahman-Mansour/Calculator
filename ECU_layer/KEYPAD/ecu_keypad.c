/* 
 * File:   ecu_keypad.c
 * Author: Abdelrahman Mansour
 *
 * Created on July 2, 2024, 6:05 AM
 */
#include "ecu_keypad.h"

 const uint8 btn_values[keypad_rows][keypad_columns]={{'7','8','9','/'},
                                                            {'4','5','6','*'},
                                                            {'1','2','3','-'},
                                                            {'#','0','=','+'}};

/**
 * 
 * @param keypad_obj
 * @return 
 */
 Std_ReturnType keypad_init(const keypad_t *keypad_obj){
  Std_ReturnType ret = E_OK;
  uint8 r_counter=0 , c_counter=0;
  if(NULL == keypad_obj){
      ret = E_NOT_OK;
  }
  else {
      for(r_counter = 0 ; r_counter <keypad_rows ;r_counter++){
          ret = gpio_pin_direction_init(&(keypad_obj->keypad_r_pins[r_counter]));
          ret = gpio_pin_write_logic(&(keypad_obj->keypad_r_pins[r_counter]),keypad_obj->keypad_r_pins[r_counter].logic);
          
      }
      for(c_counter = 0 ; c_counter <keypad_columns ;c_counter++ ){
          ret = gpio_pin_direction_init(&(keypad_obj->keypad_c_pins[c_counter]));
      }
  }
  return ret;
 }
 /**
  * 
  * @param keypad_obj
  * @param value
  * @return 
  */
 Std_ReturnType keypad_get_value(const keypad_t *keypad_obj ,uint8 *value){
  Std_ReturnType ret = E_NOT_OK;
    uint8 r_counter=0 , c_counter=0, l_counter=0;
    uint8 col_logic=0;
  if((NULL == keypad_obj) || (NULL == value)){
      ret = E_NOT_OK;
  }
  else {
      for(r_counter = 0 ; r_counter <keypad_rows ;r_counter++){
          for(l_counter = 0 ;l_counter <keypad_rows ;l_counter++){
              ret = gpio_pin_write_logic(&(keypad_obj->keypad_r_pins[l_counter]),LOW);
          }
          ret = gpio_pin_write_logic(&(keypad_obj->keypad_r_pins[r_counter]),HIGH);
          
          for(c_counter = 0 ; c_counter <keypad_columns ;c_counter++){
              ret = gpio_pin_read_logic(&(keypad_obj->keypad_c_pins[c_counter]),&col_logic);
              if(HIGH == col_logic){
                  *value = btn_values[r_counter][c_counter];
              }
          }
         
      }
       ret = E_OK;
  }
  return ret;
 }
 
char keypad_u8check_press(void){
char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
	 char row,coloumn,x;
	 char returnval=NOTPRESSED;
	 for(row=0;row<4;row++)
	 {
		DIO_write('D',0,1);
		DIO_write('D',1,1);
		DIO_write('D',2,1);
		DIO_write('D',3,1);
		DIO_write('D',row,0);
	
		for(coloumn=0;coloumn<4;coloumn++)
		{
			x=DIO_u8read('D',(coloumn+4));
			if(x==0)
			 {
				 returnval=arr[row][coloumn];
				 break;
			 }  
		}	
		if(x==0)
		{
			break;
		}
	}	 
	 return returnval ;	 

}

