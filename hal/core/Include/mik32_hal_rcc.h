#ifndef MIK32_HAL_RCC
#define MIK32_HAL_RCC

#include "mcu32_memory_map.h"
#include "wakeup.h"
#include "power_manager.h"

/* Источники тактирования */
#define RCC_OSCILLATORTYPE_NONE            0b0000       /* Нет источника */
#define RCC_OSCILLATORTYPE_HSI32M          0b0001       /* Внутренний источник тактирования 32МГц */           
#define RCC_OSCILLATORTYPE_OSC32M          0b0010       /* Внешний источник тактирования 32МГц */    
#define RCC_OSCILLATORTYPE_LSI32K          0b0100       /* Внутренний источник тактирования 32КГц */    
#define RCC_OSCILLATORTYPE_OSC32K          0b1000       /* Внешний источник тактирования 32КГц */    

/* Источники тактирования RTC */
#define RCC_RTCCLKSOURCE_NO_CLK            0b00          /* Нет источника */
#define RCC_RTCCLKSOURCE_LSI32K            0b01          /* LSI32K - источник тактирования RTC */
#define RCC_RTCCLKSOURCE_OSC32K            0b10          /* OSC32K - источник тактирования RTC */

/* Источник тактирования RTC в составе ядра*/
#define RCC_RTCCLKCPUSOURCE_NO_CLK         0b00          /* Нет источника */
#define RCC_RTCCLKCPUSOURCE_LSI32K         0b01          /* LSI32K - источник тактирования RTC */
#define RCC_RTCCLKCPUSOURCE_OSC32K         0b10          /* OSC32K - источник тактирования RTC */

#define PMCLOCKAHB_DEFAULT                 0x1F          /* Ядро; RAM; EEPROm; SPIFI; DMA */
#define PMCLOCKAPB_M_DEFAULT               0x89          /* Блок управления питанием (PM - Power Monitor); Контроллер выводов; RTC батарейного домена*/
#define PMCLOCKAPB_P_DEFAULT               0x00

#define PM_CPU_RTC_CLK_MUX_OSC32K          0x00          /* OSC32K -источник тактирования RTC в составе ядра*/
#define PM_CPU_RTC_CLK_MUX_LSI32K          0x01          /* LSI32K -источник тактирования RTC в составе ядра*/

/* Тактирование различных модулей. На 30-м и 31-м бите стоит номер, который соответствует шине AHB, APB_M и APB_P */
#define HAL_CLOCK_MASK              (0b11 << 30)   
/* AHB. 31-й бит = 0, 30-й бит = 0 */
#define HAL_CLOCK_AHB_MASK              (0b00 << 30)                                      /* Идентификатор AHB шины */
#define HAL_CLOCK_AHB_CPU                   (PM_CLOCK_CPU_M         | HAL_CLOCK_AHB_MASK)    /* Тактирование ядра */
#define HAL_CLOCK_AHB_EEPROM                (PM_CLOCK_EEPROM_M      | HAL_CLOCK_AHB_MASK)    /* Тактирование EEPROM */
#define HAL_CLOCK_AHB_RAM                   (PM_CLOCK_RAM_M         | HAL_CLOCK_AHB_MASK)    /* Тактирование RAM */
#define HAL_CLOCK_AHB_SPIFI                 (PM_CLOCK_SPIFI_M       | HAL_CLOCK_AHB_MASK)    /* Тактирование SPIFI */
#define HAL_CLOCK_AHB_TCB                   (PM_CLOCK_TCB_M         | HAL_CLOCK_AHB_MASK)    /* Тактирование TCB */
#define HAL_CLOCK_AHB_DMA                   (PM_CLOCK_DMA_M         | HAL_CLOCK_AHB_MASK)    /* Тактирование DMA */
#define HAL_CLOCK_AHB_CRYPTO                (PM_CLOCK_CRYPTO_M      | HAL_CLOCK_AHB_MASK)    /* Тактирование ускорителя криптографии */
#define HAL_CLOCK_AHB_CRC32                 (PM_CLOCK_CRC32_M       | HAL_CLOCK_AHB_MASK)    /* Тактирование CRC32 */
/* APB_M. 31-й бит = 0, 30-й бит = 1 */ 
#define HAL_CLOCK_APB_M_MASK            (0b01 << 30)                                             /* Идентификатор APB_M шины */
#define HAL_CLOCK_APB_M_PM                    (PM_CLOCK_PM_M                  | HAL_CLOCK_APB_M_MASK) /* Тактирование блока управления питанием (PM - Power Monitor) */
#define HAL_CLOCK_APB_M_EPIC                  (PM_CLOCK_EPIC_M                | HAL_CLOCK_APB_M_MASK) /* Тактирование контроллера прерываний EPIC */
#define HAL_CLOCK_APB_M_TIMER32_0             (PM_CLOCK_TIMER32_0_M           | HAL_CLOCK_APB_M_MASK) /* Тактирование Timer32_0 */
#define HAL_CLOCK_APB_M_PAD_CONFIG            (PM_CLOCK_PAD_CONFIG_M          | HAL_CLOCK_APB_M_MASK) /* Тактирование контроллера выводов */
#define HAL_CLOCK_APB_M_WDT_BUS               (PM_CLOCK_WDT_BUS_M             | HAL_CLOCK_APB_M_MASK) /* Тактирование сторожевого таймера шины */
#define HAL_CLOCK_APB_M_OTP_CONTROLLER        (PM_CLOCK_OTP_CONTROLLER_M      | HAL_CLOCK_APB_M_MASK) /* Тактирование OTP */
#define HAL_CLOCK_APB_M_PVD_CONTROL           (PM_CLOCK_PVD_CONTROL_M         | HAL_CLOCK_APB_M_MASK) /* Тактирование монитора питания системного домена */
#define HAL_CLOCK_APB_M_WU                    (PM_CLOCK_WU_M                  | HAL_CLOCK_APB_M_MASK) /* Тактирование блока WU батарейного домена */
#define HAL_CLOCK_APB_M_RTC                   (PM_CLOCK_RTC_M                 | HAL_CLOCK_APB_M_MASK) /* Тактирование RTC батарейного домена */
/* APB_P. 31-й бит = 1, 30-й бит = 0 */ 
#define HAL_CLOCK_APB_P_MASK            (0b10 << 30)                                        /* Идентификатор APB_P шины */
#define HAL_CLOCK_APB_P_WDT                   (PM_CLOCK_WDT_M             | HAL_CLOCK_APB_P_MASK) /* Тактирование сторожевого таймера */
#define HAL_CLOCK_APB_P_UART_0                (PM_CLOCK_UART_0_M          | HAL_CLOCK_APB_P_MASK) /*Тактирование UART_0 */
#define HAL_CLOCK_APB_P_UART_1                (PM_CLOCK_UART_1_M          | HAL_CLOCK_APB_P_MASK) /*Тактирование UART_1 */
#define HAL_CLOCK_APB_P_TIMER16_0             (PM_CLOCK_TIMER16_0_M       | HAL_CLOCK_APB_P_MASK) /*Тактирование Timer16_0 */
#define HAL_CLOCK_APB_P_TIMER16_1             (PM_CLOCK_TIMER16_1_M       | HAL_CLOCK_APB_P_MASK) /*Тактирование Timer16_1 */
#define HAL_CLOCK_APB_P_TIMER16_2             (PM_CLOCK_TIMER16_2_M       | HAL_CLOCK_APB_P_MASK) /*Тактирование Timer 16_2 */
#define HAL_CLOCK_APB_P_TIMER32_1             (PM_CLOCK_TIMER32_1_M       | HAL_CLOCK_APB_P_MASK) /*Тактирование Timer32_1 */ 
#define HAL_CLOCK_APB_P_TIMER32_2             (PM_CLOCK_TIMER32_2_M       | HAL_CLOCK_APB_P_MASK) /*Тактирование Timer32_2 */
#define HAL_CLOCK_APB_P_SPI_0                 (PM_CLOCK_SPI_0_M           | HAL_CLOCK_APB_P_MASK) /*Тактирование SPI_0 */
#define HAL_CLOCK_APB_P_SPI_1                 (PM_CLOCK_SPI_1_M           | HAL_CLOCK_APB_P_MASK) /*Тактирование SPI_1 */
#define HAL_CLOCK_APB_P_I2C_0                 (PM_CLOCK_I2C_0_M           | HAL_CLOCK_APB_P_MASK) /*Тактирование I2C_0 */
#define HAL_CLOCK_APB_P_I2C_1                 (PM_CLOCK_I2C_1_M           | HAL_CLOCK_APB_P_MASK) /*Тактирование I2C_1 */
#define HAL_CLOCK_APB_P_GPIO_0                (PM_CLOCK_GPIO_0_M          | HAL_CLOCK_APB_P_MASK) /*Тактирование GPIO_0 */
#define HAL_CLOCK_APB_P_GPIO_1                (PM_CLOCK_GPIO_1_M          | HAL_CLOCK_APB_P_MASK) /*Тактирование GPIO_1 */
#define HAL_CLOCK_APB_P_GPIO_2                (PM_CLOCK_GPIO_2_M          | HAL_CLOCK_APB_P_MASK) /*Тактирование GPIO_2 */
#define HAL_CLOCK_APB_P_ANALOG_REG            (PM_CLOCK_ANALOG_REG_M      | HAL_CLOCK_APB_P_MASK) /*Тактирование регистров аналоговых блоков */


typedef struct
{
    uint8_t OscillatorEnable;           /*  Осциллятор, который должен быть включен.
                                            Этот параметр может быть RCC_OSCILLATORTYPE_NONE,  RCC_OSCILLATORTYPE_HSI32M,
                                            RCC_OSCILLATORTYPE_LSI32K, RCC_OSCILLATORTYPE_OSC32K  */

    uint8_t OscillatorSystem;              /*  Источник тактирования системы.
                                            Этот параметр должен быть числом между Min = 0 и Max = 255 */        

    uint8_t AHBDivider;                 /*  Делитель частоты AHB.
                                            Этот параметр должен быть числом между Min = 0 и Max = 255 */

    uint8_t APBMDivider;                /*  Делитель частоты APB_M.
                                            Этот параметр должен быть числом между Min = 0 и Max = 255 */

    uint8_t APBPDivider;                /*  Делитель частоты APB_P.
                                            Этот параметр должен быть числом между Min = 0 и Max = 255 */
    
    uint8_t HSI32MCalibrationValue;     /*  Поправочный коэффициент HSI32M.
                                            Этот параметр должен быть числом между Min = 0 и Max = 63 */

    uint8_t LSI32KCalibrationValue;     /*  Поправочный коэффициент LSI32K.
                                            Этот параметр должен быть числом между Min = 0 и Max = 15 */

    uint32_t RTCClockSelection;         /*  Источник тактирования RTC. */

    uint32_t RTCClockCPUSelection;      /*  Источник тактирования RTC в составе ядра. */

} RCC_OscInitTypeDef;


typedef struct
{
    uint32_t PMClockAHB;                /*  Выбор тактирования устройств на шине AHB. */

    uint32_t PMClockAPB_M;              /*  Выбор тактирования устройств на шине APB_M. */

    uint32_t PMClockAPB_P;              /*  Выбор тактирования устройств на шине APB_P. */

} RCC_PeriphCLKInitTypeDef;


void HAL_RCC_OscEnable(uint32_t Oscillator);
void HAL_RCC_OscDisable(uint32_t Oscillator);
void HAL_RCC_SetOscSystem(uint32_t OscillatorSystem);
void HAL_RCC_DividerAHB(uint32_t DividerAHB);
void HAL_RCC_DividerAPB_M(uint32_t DividerAPB_M);
void HAL_RCC_DividerAPB_P(uint32_t DividerAPB_P);
void HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInit);
void HAL_RCC_ClockConfig(RCC_PeriphCLKInitTypeDef *PeriphClkInit);
void HAL_RCC_ClockSet(uint32_t Periphery);
void HAL_RCC_ClockClear(uint32_t Periphery);
void HAL_RCC_RTCClock(uint32_t Oscillator);
void HAL_RCC_CPURTCClock(uint32_t Oscillator);


#endif