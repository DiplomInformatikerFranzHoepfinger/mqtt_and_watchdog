/*
 * main.c
 *
 *  Created on: 05.06.2022
 *      Author: franz
 */



extern void blink_example_main(void);

extern void mqtt_main(void);


void app_main(void){



	blink_example_main();
	mqtt_main();


}


