#ifndef _ADS1115_H_
#define _ADS1115_H_

/**
    * Derived from the ADS1115 data sheet Quick Start Guide

1. The first byte sent by the master should be the ADS1115 address
    followed by a bit that instruct the device to listen for a subsuquent
    byte.
2. the second byte is the register pointer
3. the third and fourth byte sent from the master are written to the 
    register indicated by the second byte.
4. all read and write operations must be preceded by a start condition
    and followed by a stop condition.




*/

// ADDED INCLUDES
#include <stdint.h>
#include <bcm2835.h>
#include "I2Cdev.h"


// DEVICE REGISTERS
#define DEV_ADDR_GND            0b1001000   // 7bit address -> GND
#define DEV_ADDR_VDD            0b1001001   // address --> VDD
#define DEV_ADDR_SDA            0b1001010   // address --> SDA
#define DEV_ADDR_SCL            0b1001011   // address --> SCL

#define PTR_CONVER              0b00000000  // Conversion Register
#define PTR_CONFIG              0b00000001  // Config Register
#define PTR_LTR                 0b00000010  // Lo Thresh Register
#define PTR_HTR                 0b00000011  // Hi Thresh Register

#define PTR_REG_ADD_BIT         1
#define PTR_REG_ADD_LEN         2

// CONFIG REGISTER DEF
#define CONF_REG_OS_BIT         15
#define CONF_REG_MUX_BIT        14
#define CONF_REG_MUX_LEN        3
#define CONF_REG_PGA_BIT        11
#define CONF_REG_PGA_LEN        3
#define CONF_REG_MODE_BIT       8
#define CONF_DR2_BIT            7
#define CONF_COMP_MODE_BIT      4
#define CONF_COMP_POL_BIT       3
#define CONF_COMP_LAT_BIT       2
#define CONF_COMP_QUE_BIT       1
#define CONF_COMP_QUE_LEN       2

// OS Status
#define OS_STAT                 0b0

// MUX CONFIG
/**
 *      bits    |   purpose
 * -----------------------------
 *      000     |   AIN0 and AINN = AIN1 (default)
 *      001     |   AINP = AIN0 and AINN = AIN3 
 *      010     |   AINP = AIN1 and AINN = AIN3
 *      011     |   AINP = AIN2 and AINN = AIN3 
 *      100     |   AINP = AIN0 and AINN = GND
 *      101     |   AINP = AIN1 and AINN = GND
 *      110     |   AINP = AIN2 and AINN = GND
 *      111     |   AINP = AIN3 and AINN = GND
 */

#define MUX_1_D                 0b000   //  Default
#define MUX_2                   0b001
#define MUX_3                   0b010
#define MUX_4                   0b011
#define MUX_5                   0b100
#define MUX_6                   0b101
#define MUX_7                   0b110
#define MUX_8                   0b111

// PGA CONFIG 
/**
 *      bits    |   purpose
 *  ------------------------------
 *      000     |   ±6.144V(1) 
 *      001     |   ±4.096V(1) 
 *      010     |   ±2.048V (default)
 *      011     |   ±1.024V 
 *      100     |   ±0.512V
 *      101     |   ±0.256V
 *      110     |   ±0.256V
 *      111     |   ±0.256V
 *  
 *  (1) This parameter expresses the full-scale range of 
 *  the ADC scaling. In no event should more than VDD + 0.3V 
 *  be applied to this device.
 */

#define PGA_1                   0b000
#define PGA_2                   0b001
#define PGA_3_D                 0b010   //  Default
#define PGA_4                   0b011
#define PGA_5                   0b100
#define PGA_6                   0b101
#define PGA_7                   0b110
#define PGA_8                   0b111

// DEVICE OPERATION MODE
#define MODE_1                  0b0
#define MODE_2_D                0b1

// Data Rate 
/**
 *      bits    |   purpose
 * -------------+-----------------
 *      000     |   8SPS
 *      001     |   16SPS
 *      010     |   32SPS
 *      011     |   64SPS
 *      100     |   128SPS
 *      101     |   250SPS
 *      110     |   475SPS
 *      111     |   860SPS
 * 
 */

#define DR_8                    0b000
#define DR_16                   0b001
#define DR_32                   0b010
#define DR_64                   0b011
#define DR_128_D                0b100
#define DR_250                  0b101
#define DR_475                  0b110
#define DR_860                  0b111

// Comparator mode
#define COMP_MODE_1_D           0b0     // Traditional comparator with hystersis (Default)
#define COMP_MODE_2             0b1     // WINDOW COMPARATOR

// Comparator Polaroty
#define COMP_POL_1_D            0b0     // Active Low (Default)
#define COMP_POL_2              0b1     // Active High

// Comparator Que and Disable
#define COMP_QUE_1              0b00    // Assert after one conversion
#define COMP_QUE_2              0b01    // Assert after two conversions
#define COMP_QUE_3              0b10    // Assert after four conversions
#define COMP_QUE_4_D            0b11    // Disable compartor (Default)

#define COMP_LO_THRESH          0x8000
#define COMP_HI_THRESH          0x7FFF
 
#define CONFG_DEFAULT           0x8583

class ADS1115
{
public:
    ADS1115();
    ADS1115(uint8_t address);
    void initialize();
    void setConfig();
    void setConfig(
        uint8_t os_bit,
        uint8_t mux_bits,
        uint8_t pga_bits,
        uint8_t mode_bit,
        uint8_t dr_bits,
        uint8_t cm_bit,
        uint8_t cp_bit,
        uint8_t cl_bit,
        uint8_t cq_bits
        );
    void setDeviceAddress(uint8_t devAddress);

private:
    uint8_t deviceAddress;
    uint16_t config_bits;
};

#endif