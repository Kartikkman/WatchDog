// Contains Declarations of Functions to configure the I2C , UART interface for the uC 

#include"config.h"

/*

To do the above I2C/UART communication , one needs to do the below steps : 

1.Configuring the Driver
2.Installing Driver 
3.Sending & receiving the Data 

*/

 // Function for configuring & Installing the Driver for UART ( Pin No , Baud Rate , Parity , Stop Bit , Flow Control )

void uart_config() {

    uart_config_t config ={ .baud_rate = BAUD_RATE , .data_bits = UART_DATA_8_BITS , .parity = UART_PARITY_DISABLE ,.stop_bits = UART_STOP_BITS_1, .flow_ctrl = UART_HW_FLOWCTRL_DISABLE };
    uart_param_config(UART_NUM_1 ,&config);                                      //first step ( Configuration of UART)
    uart_set_pin(UART_NUM_1, TX, RX, RTS , CTS);                                // Second Step ( Allocating Pins)     uart_driver_install(UART_NUM_1,UART_BUF_SIZE,0,0 ,NULL,0);
    uart_driver_install(UART_NUM_1,UART_BUF_SIZE ,UART_BUF_SIZE, 0, NULL, 0);   // Finally Installing the Driver acc. to the above mentioned Configuration 

}


// Function for configuring & Installing the Drive for I2C ( Pin No , Mode : Slave / Master , Clock Speed  , Address , Pull Up Modes) 

void configure_I2C()
{
    int i2c_master_port = I2C_NUM_0;

    i2c_config_t config = { .mode = I2C_MODE_MASTER , .sda_io_num = SDA, .sda_pullup_en = 0, .scl_io_num = SCL, .scl_pullup_en = 0 , .master ={.clk_speed = CLK_SPEED } };
    i2c_param_config(I2C_NUM_0 , &config);                      // Configuring the Driver , setting the pins , Clock Speed & Mode of Operation above 
    i2c_driver_install(I2C_NUM_0 , I2C_MODE_MASTER, 0, 0, 0);   // Installing the driver 
    // printf("Driver has been Installed ");
}
