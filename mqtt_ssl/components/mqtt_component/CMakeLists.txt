idf_component_register(SRCS "app_main.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES 
                    	nvs_flash
                    	protocol_examples_common
                    	mqtt
                    	app_update)
