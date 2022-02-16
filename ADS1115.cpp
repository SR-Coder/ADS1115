

#include "ADS1115.h"
#include <iostream>

ADS1115::ADS1115()
{

}

ADS1115::ADS1115(uint8_t devAddress)
{

}

void ADS1115::initialize()
{
    bool result = I2Cdev::writeWord(DEV_ADDR_GND, PTR_CONFIG, config_bits);
    if(result){
        printf("Device initialized...");
    }
    else {
        printf("initialization failed... Check connections");
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