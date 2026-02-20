#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#define LOOP_DELAY_MS           10      // Loop sampling time (ms)
#define DEBOUNCE_TIME           40      // Debounce time (ms)
#define NROWS                   4       // Number of keypad rows
#define NCOLS                   4       // Number of keypad columns

#define ACTIVE                  0       // Keypad active state (0 = low, 1 = high)
#define NOPRESS                 '\0'    // NOPRESS character

char keypad_array[NROWS][NCOLS] = {   // Keypad layout
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void init_keypad(){

    int row_pins[] = {GPIO_NUM_3, GPIO_NUM_8, GPIO_NUM_18, GPIO_NUM_17};     // Pin numbers for rows
    for (i=0; i<NROWS;i++){
        gpio_reset_pin(row_pins[i]);
        gpio_set_direction(row_pins[i], GPIO_MODE_OUTPUT);
        if (ACTIVE){
            gpio_set_level(row_pins[i],1);
        }
        else{
            gpio_set_level(row_pins[i],0);
        }
    }
    int col_pins[] = {GPIO_NUM_16, GPIO_NUM_15, GPIO_NUM_7, GPIO_NUM_6};   // Pin numbers for columns
    for (i=0; i<NCOLS; i++){
        gpio_reset_pin(col_pins[i]);
        gpio_set_direction(col_pins[i], GPIO_MODE_INPUT);
        if (ACTIVE){
            gpio_pullup_en(col_pins[i]);
        }
        else{
            gpio_pulldown_en(col_pins[i]);
        }
    }
}
char scan_keypad(){
    if (ACTIVE ==0){
        int INACTIVE =1
    }
    else{
        INACTIVE =0
    }
    char key = NOPRESS;
    //set all rows inactive
    for (int i =0; i < NROWS; i++){
        gpio_set_level(row_pins[i], INACTIVE);
    }

    for (int i = 0; i < NROWS; i++){
        gpio_set_level(row_pins[i],ACTIVE);

        for (int j = 0; j < NCOLS; j++){
            if (gpio_get_level(col_pin[j]) == ACTIVE){
                key = keypad_array [i][j];
                return key;
            }
        }
        gpio_set_level(row_pins[i], INACTIVE);
    }
    return key;
}
typedef enum {
    WAIT_FOR_RELEASE, 
    WAIT_FOR_PRESS,
    DEBOUNCE,
}  State_t; 
State_t state;
int time = 0;
bool time_out = (time > DEBOUNCE_TIME)
char new_key;

void app_main(){
    while (1){
        init_keypad()
        new_key = scan_keypad();
        state = "WAIT_FOR_RELEASE";
        switch(state){

            case WAIT_FOR_RELEASE:

            if (new_key != NOPRESS){
                state = WAIT_FOR_RELEASE;
            }
            else{
                prinf(last_key)
                state = WAIT_FOR_PRESS;
            }
            break;
      
            case WAIT_FOR_PRESS:
            if (new_key != NOPRESS){
                last_key = new_key;
                time = 0;
                state = DEBOUNCE;
            }
            else{
                state = WAIT_FOR_PRESS;
            }
            break;
        
            case DEBOUNCE:
            for (i = 0; i < time_out; i ++){
                time += LOOP_DELAY_MS;
                if (time == time_out){
                    if ( new_key == last_key){
                        state = WAIT_FOR_RELEASE;
                    }
                    else {
                        state = WAIT_FOR_PRESS;
                    }
                }
                else {
                    state = WAIT_FOR_RELEASE;
                }
            }
            break;
        }
    }
}


