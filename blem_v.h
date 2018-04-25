static ble_hids_t m_hids;                                                                         /**< Structure used to identify the HID service. */
static ble_bas_t  m_bas;                                                                          /**< Structure used to identify the battery service. */
static bool       m_in_boot_mode = false;                                                         /**< Current protocol mode. */
static uint16_t   m_conn_handle  = BLE_CONN_HANDLE_INVALID;                                       /**< Handle of the current connection. */

static sensorsim_cfg_t   m_battery_sim_cfg;                                                       /**< Battery Level sensor simulator configuration. */
static sensorsim_state_t m_battery_sim_state;                                                     /**< Battery Level sensor simulator state. */

APP_TIMER_DEF(m_battery_timer_id);                                                                /**< Battery timer. */

static pm_peer_id_t m_peer_id;                                                                    /**< Device reference handle to the current bonded central. */

static ble_uuid_t m_adv_uuids[] = {{BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE, BLE_UUID_TYPE_BLE}}; /**< Universally unique service identifiers. */

static pm_peer_id_t   m_whitelist_peers[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];  /**< List of peers currently in the whitelist. */
static uint32_t       m_whitelist_peer_cnt;                                 /**< Number of peers currently in the whitelist. */
static bool           m_is_wl_changed;                                      /**< Indicates if the whitelist has been changed since last time it has been updated in the Peer Manager. */

static void on_hids_evt(ble_hids_t * p_hids, ble_hids_evt_t * p_evt);

struct conv_sensor_data {
	/*! X-axis sensor data */
	float x;
	/*! Y-axis sensor data */
	float y;
	/*! Z-axis sensor data */
	float z;
};


static volatile bool spi_xfer_done;

static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */  


static uint8_t	m_rx_buf[SPI_BUFFER_SIZE];
struct bmi160_dev 	sensor;
static struct bmi160_sensor_data accel;
static struct bmi160_sensor_data gyro;
static struct bmi160_sensor_data gyro_degs;



struct bmi160_int_settg int_config_data_ready;
struct bmi160_int_settg int_config_no_motion;
static bool data_ready;
static bool f_mouse_click_send;

int8_t spi1_read_transfer(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t spi1_write_transfer(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
