#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#if BUTTONS_NUMBER < 4
#error "Not enough resources on board to run example"
#endif

#if (NRF_SD_BLE_API_VERSION == 3)
#define NRF_BLE_MAX_MTU_SIZE            GATT_MTU_SIZE_DEFAULT                      /**< MTU size used in the softdevice enabling and to reply to a BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST event. */
#endif

#define IS_SRVC_CHANGED_CHARACT_PRESENT 0                                          /**< Include or not the service_changed characteristic. if not enabled, the server's database cannot be changed for the lifetime of the device*/

#define CENTRAL_LINK_COUNT              0                                          /**< Number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT           1                                          /**< Number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/

#define DEVICE_NAME                     "Nordic_Mouse"                             /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME               "NordicSemiconductor"                      /**< Manufacturer. Will be passed to Device Information Service. */

#define APP_TIMER_PRESCALER             0                                          /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE         4                                          /**< Size of timer operation queues. */

#define BATTERY_LEVEL_MEAS_INTERVAL     APP_TIMER_TICKS(2000, APP_TIMER_PRESCALER) /**< Battery level measurement interval (ticks). */
#define MIN_BATTERY_LEVEL               0                                         /**< Minimum simulated battery level. */
#define MAX_BATTERY_LEVEL               100                                        /**< Maximum simulated battery level. */
#define BATTERY_LEVEL_INCREMENT         1                                          /**< Increment between each simulated battery level measurement. */

#define PNP_ID_VENDOR_ID_SOURCE         0x02                                       /**< Vendor ID Source. */
#define PNP_ID_VENDOR_ID                0x1915                                     /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID               0xEEEE                                     /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION          0x0001                                     /**< Product Version. */

/*lint -emacro(524, MIN_CONN_INTERVAL) // Loss of precision */
#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(7.5, UNIT_1_25_MS)            /**< Minimum connection interval (7.5 ms). */
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(15, UNIT_1_25_MS)             /**< Maximum connection interval (15 ms). */
#define SLAVE_LATENCY                   20                                          /**< Slave latency. */
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(3000, UNIT_10_MS)             /**< Connection supervisory timeout (3000 ms). */

#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000, APP_TIMER_PRESCALER)  /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000, APP_TIMER_PRESCALER) /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAM_UPDATE_COUNT     3                                           /**< Number of attempts before giving up the connection parameter negotiation. */

#define SEC_PARAM_BOND                  1                                           /**< Perform bonding. */
#define SEC_PARAM_MITM                  0                                           /**< Man In The Middle protection not required. */
#define SEC_PARAM_LESC                  0                                           /**< LE Secure Connections not enabled. */
#define SEC_PARAM_KEYPRESS              0                                           /**< Keypress notifications not enabled. */
#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                        /**< No I/O capabilities. */
#define SEC_PARAM_OOB                   0                                           /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE          7                                           /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE          16                                          /**< Maximum encryption key size. */

#define MOVEMENT_SPEED                  5                                           /**< Number of pixels by which the cursor is moved each time a button is pushed. */
#define INPUT_REPORT_COUNT              3                                           /**< Number of input reports in this application. */
#define INPUT_REP_BUTTONS_LEN           3                                           /**< Length of Mouse Input Report containing button data. */
#define INPUT_REP_MOVEMENT_LEN          3                                           /**< Length of Mouse Input Report containing movement data. */
#define INPUT_REP_MEDIA_PLAYER_LEN      1                                           /**< Length of Mouse Input Report containing media player data. */
#define INPUT_REP_BUTTONS_INDEX         0                                           /**< Index of Mouse Input Report containing button data. */
#define INPUT_REP_MOVEMENT_INDEX        1                                           /**< Index of Mouse Input Report containing movement data. */
#define INPUT_REP_MPLAYER_INDEX         2                                           /**< Index of Mouse Input Report containing media player data. */
#define INPUT_REP_REF_BUTTONS_ID        1                                           /**< Id of reference to Mouse Input Report containing button data. */
#define INPUT_REP_REF_MOVEMENT_ID       2                                           /**< Id of reference to Mouse Input Report containing movement data. */
#define INPUT_REP_REF_MPLAYER_ID        3                                           /**< Id of reference to Mouse Input Report containing media player data. */

#define BASE_USB_HID_SPEC_VERSION       0x0101                                      /**< Version number of base USB HID Specification implemented by this application. */

#define SCHED_MAX_EVENT_DATA_SIZE       MAX(APP_TIMER_SCHED_EVT_SIZE, \
                                            BLE_STACK_HANDLER_SCHED_EVT_SIZE)                     /**< Maximum size of scheduler events. */
#ifdef SVCALL_AS_NORMAL_FUNCTION
#define SCHED_QUEUE_SIZE                 20                                         /**< Maximum number of events in the scheduler queue. More is needed in case of Serialization. */
#else
#define SCHED_QUEUE_SIZE                10                                                        /**< Maximum number of events in the scheduler queue. */
#endif

#define DEAD_BEEF                       0xDEADBEEF                                                /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

#define APP_FEATURE_NOT_SUPPORTED       BLE_GATT_STATUS_ATTERR_APP_BEGIN + 2                      /**< Reply when unsupported features are requested. */

#define APP_ADV_FAST_INTERVAL           0x0028                                                    /**< Fast advertising interval (in units of 0.625 ms. This value corresponds to 25 ms.). */
#define APP_ADV_SLOW_INTERVAL           0x0C80                                                    /**< Slow advertising interval (in units of 0.625 ms. This value corrsponds to 2 seconds). */

#define APP_ADV_FAST_TIMEOUT            30                                                        /**< The duration of the fast advertising period (in seconds). */
#define APP_ADV_SLOW_TIMEOUT            180                                                       /**< The duration of the slow advertising period (in seconds). */
#define PIN_IN							25
#define PIN_OUT							21

#define PIN_LED_BLUE  23
#define PIN_LED_GREEN 21
#define PIN_LED_RED   17
#define PIN_LED_WHITE 8
#define PIN_CS_BMI160 11

/* SPI*/
#define PIN_MOSI      7
#define PIN_MISO      0
#define PIN_SCK       30
#define PIN_MOSI      7
#define SPI_INSTANCE  0 /**< SPI instance index. */
#define SPI_BUFFER_SIZE					16

#define PIN_IMU_INT1  29
#define PIN_IMU_INT2  28

#define BUTTON_LEFT  0x01
#define BUTTON_RIGHT 0x02



