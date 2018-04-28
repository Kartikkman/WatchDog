// Contains the declaration of the constants & function red. in the BLE 

#ifndef _BLE_APP_H_
#define _BLE_APP_H_

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include"gatts_table_creat_demo.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "gatts_table_creat_demo.h"
#include "esp_gatt_common_api.h"
#include"esp_err.h"


#define GATTS_TABLE_TAG "GATTS_TABLE_DEMO"

#define PROFILE_NUM                 1                           // There can be many profiles in an app
#define PROFILE_APP_IDX             0                           
#define ESP_APP_ID                  0x55
#define SAMPLE_DEVICE_NAME          "WATCH_DOG"
#define SVC_INST_ID                 0


/* The max length of characteristic value. When the gatt client write or prepare write, 
*  the data length must be less than GATTS_DEMO_CHAR_VAL_LEN_MAX. 
*/
#define GATTS_DEMO_CHAR_VAL_LEN_MAX 500
#define PREPARE_BUF_MAX_SIZE        1024
#define CHAR_DECLARATION_SIZE       (sizeof(uint8_t))


extern const uint16_t GATTS_SERVICE_UUID_TEST;     
extern const uint16_t GATTS_CHAR_UUID_TEST_A;      
extern const uint16_t character_declaration_uuid;  
extern const uint16_t character_client_config_uuid;
extern const uint8_t char_prop_read;               
extern const uint8_t char_prop_write;              
extern const uint8_t char_prop_read_write; 
extern const uint8_t char_prop_read_write_notify;  
extern const uint8_t heart_measurement_ccc[2];
extern const uint32_t char_value;


uint16_t conn_id;
esp_gatt_if_t interface;

extern const esp_gatts_attr_db_t gatt_db[HRS_IDX_NB];
extern esp_ble_adv_params_t adv_params;
extern esp_ble_adv_data_t scan_rsp_data;
extern esp_ble_adv_data_t adv_data;
static uint16_t handle_table[HRS_IDX_NB];

void sort_queue(uint8_t *value , uint16_t len ,uint8_t handle);
void parse_alert(uint8_t *value , uint16_t len );
void print_alerts();
void configure_BLE();
static void gatts_profile_event_handler(esp_gatts_cb_event_t event,esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

#endif