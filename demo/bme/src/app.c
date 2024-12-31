#include "api_hal_gpio.h"
#include "stdint.h"
#include "stdbool.h"
#include "api_debug.h"
#include "api_os.h"
#include "api_hal_pm.h"
#include "api_os.h"
#include "api_event.h"

#include "bme280.h"

#include "api_hal_i2c.h"

#define MAIN_TASK_STACK_SIZE    (1024 * 2)
#define MAIN_TASK_PRIORITY      0 
#define MAIN_TASK_NAME         "MAIN Test Task"

#define TEST_TASK_STACK_SIZE    (1024 * 2)
#define TEST_TASK_PRIORITY      1
#define TEST_TASK_NAME         "Reading Test Task"

static HANDLE mainTaskHandle = NULL;
static HANDLE secondTaskHandle = NULL;


#define I2C_ACC I2C2
#define I2C_ADD 0x76

float seaLevel = 1013.25;

void Reading_TestTask(void *pData)
{
    I2C_Config_t i2cConfig;
    i2cConfig.freq = I2C_FREQ_100K;
    I2C_Init(I2C2, i2cConfig);

    bme280_init();	

    

    while(1)
    {   
        bme280_startConvertion();
        OS_Sleep(200);
        if(bme280_status() == 0)
		{
			Trace(1,
				"%u, Temp: %.2f C, Press: %.3f hPa, Altitude: %.2f m",
				bme280_status(),
				(bme280_readTemperature() / 100.0),
				((bme280_readPressure() / 256.0) / 100.0),
                bme280_readAltitude(seaLevel)
			);
        }

        OS_Sleep(5000);
    }
}

void EventDispatch(API_Event_t* pEvent)
{
    switch(pEvent->id)
    {
        default:
            break;
    }
}

void MainTask(void *pData)
{
    API_Event_t* event=NULL;

    secondTaskHandle = OS_CreateTask(Reading_TestTask,
        NULL, NULL, TEST_TASK_STACK_SIZE, TEST_TASK_PRIORITY, 0, 0, TEST_TASK_NAME);

    while(1)
    {
        if(OS_WaitEvent(mainTaskHandle, (void**)&event, OS_TIME_OUT_WAIT_FOREVER))
        {
            EventDispatch(event);
            OS_Free(event->pParam1);
            OS_Free(event->pParam2);
            OS_Free(event);
        }
    }
}

void bme_Main(void)
{
    mainTaskHandle = OS_CreateTask(MainTask,
        NULL, NULL, MAIN_TASK_STACK_SIZE, MAIN_TASK_PRIORITY, 0, 0, MAIN_TASK_NAME);
    OS_SetUserMainHandle(&mainTaskHandle);
}
