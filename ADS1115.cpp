

#include "ADS1115.h"
#include <iostream>

/**
 * @brief Construct a new ADS1115::ADS1115 object and sets the device address to the default device address of 0b1001000, additionally sets the default config to 0x8583.
 * 
 */
ADS1115::ADS1115()
{
    deviceAddress = DEV_ADDR_GND;
    setConfig();
}

/**
 * @brief Construct a new ADS1115::ADS1115 objec
 * 
 * @param devAddress 
 */
ADS1115::ADS1115(uint8_t devAddress)
{
    deviceAddress = devAddress;
}

void ADS1115::initialize()
{
    bool result = I2Cdev::writeWord(deviceAddress, PTR_CONFIG, config_bits);
    if(result){
        printf("Device initialized... \n");
    }
    else {
        printf("initialization failed... Check connections \n");
    }
}

/**
 * @brief Sets the device to the default configuration 0x8583
 * 
 */
void ADS1115::setConfig()
{
    config_bits = CONFG_DEFAULT;
}


/**
 * @brief Sets the devices address to one of 4 values:
 * @param . ADDR Pin |   Slave Address
 * @param .---------+-----------------
 * @param . Ground  |   1001000
 * @param .   VDD   |   1001001
 * @param .   SDA   |   1001010
 * @param .   SCL   |   1001011     
 * 
 * @param devAddress Depending on what source is attached to the address pin will determine what address needs to be set, the default is ground.
 */
void ADS1115::setDeviceAddress(uint8_t devAddress)
{
    deviceAddress = devAddress;
}

/** 
 * @brief Setter for the config_bits variable allowing exact configuration of the device
 * 
 * @param os_bit  Operational status/single-shot conversion start
 * @param mux_bits MUX[2:0]: Input multiplexer configuration (ADS1115 only)
 * @param pga_bits PGA[2:0]: Programmable gain amplifier configuration (ADS1114 and ADS1115 only)
 * @param mode_bit MODE: Device operating mode
 * @param dr_bits DR[2:0]: Data rate
 * @param cm_bit COMP_MODE: Comparator mode (ADS1114 and ADS1115 only)
 * @param cp_bit COMP_POL: Comparator polarity (ADS1114 and ADS1115 only)
 * @param cl_bit COMP_LAT: Latching comparator (ADS1114 and ADS1115 only)
 * @param cq_bits COMP_QUE: Comparator queue and disable (ADS1114 and ADS1115 only)
 */
void ADS1115::setConfig(uint8_t os_bit, uint8_t mux_bits, uint8_t pga_bits, uint8_t mode_bit, uint8_t dr_bits, uint8_t cm_bit, uint8_t cp_bit, uint8_t cl_bit, uint8_t cq_bits)
{
    config_bits = 0;
    config_bits = config_bits + (os_bit << 15) + (mux_bits << 12) + (pga_bits << 9) + (mode_bit << 8) + (dr_bits << 5) + (cm_bit << 4) + (cp_bit << 3) + (cl_bit << 2) + cq_bits;
}