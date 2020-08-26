/** @file Adc.cpp
 * See Adc.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Adc.hpp>
#include <cstring>
#include <errno.h>
#include <Log.hpp>
#include <pthread.h>
#include <Sysfs.hpp>
#include <unistd.h>

/** All needed ADC sysfs files are stored in this directory. */
#define ADC_SYSFS_BASE_PATH "/sys/bus/iio/devices/iio:device0"

namespace Adc
{
	/** Hold the last processed battery voltage (in mV). */
	static int _batteryVoltageMillivolts;
	/** Hold the last processed battery voltage percentage. */
	static int _batteryVoltagePercentage;
	/** Make sure both battery voltage values are coherent. */
	static pthread_mutex_t _batteryVoltageMutex;
	
	static int _getBatteryValues(int *pointerVoltageMillivolts, int *pointerChargePercentage)
	{
		// Retrieve raw ADC value
		int rawValue;
		if (Sysfs::readFile(ADC_SYSFS_BASE_PATH "/in_voltage0_raw", &rawValue) != 0)
		{
			LOG(LOG_ERR, "Failed to retrieve raw value from ADC.");
			return -1;
		}
		
		// Convert raw value to millivolts
		*pointerVoltageMillivolts = (rawValue * 15522) / 1023; // Voltage divider value corresponding to 10-bit ADC value 1023 is 15.522V = 15522mV
		
		// Determine charge level. We assume that battery charge is 0% if voltage <= 8V (i.e. each 1.5V battery cell is down to 1V) and that battery charge is 100% if voltage >= 12V (i.e. each 1.5V battery cell is at least 1.5V)
		int adjustedVoltage = *pointerVoltageMillivolts - 8000; // Make 0% = 0mV, so 100% = 12000mV - 8000mV = 4000mV, to be able to use cross-multiplication
		*pointerChargePercentage = (adjustedVoltage * 100) / 4000;
		// Clamp percentage to expected percentage values
		if (*pointerChargePercentage < 0) *pointerChargePercentage = 0;
		else if (*pointerChargePercentage > 100) *pointerChargePercentage = 100;
		
		return 0;
	}
	
	/** Sample analog data and process them. */
	static void *_dataProcessingThread(void *)
	{
		int currentBatteryVoltageMillivolts, currentBatteryPercentage;
		
		while (1)
		{
			// Retrieve battery voltage
			if (_getBatteryValues(&currentBatteryVoltageMillivolts, &currentBatteryPercentage) != 0)
			{
				currentBatteryVoltageMillivolts = 0;
				currentBatteryPercentage = 0;
				LOG(LOG_ERR, "Failed to retrieve voltage values.");
			}
			
			// Atomically update shared variables
			pthread_mutex_lock(&_batteryVoltageMutex);
			_batteryVoltageMillivolts = currentBatteryVoltageMillivolts;
			_batteryVoltagePercentage = currentBatteryPercentage;
			pthread_mutex_unlock(&_batteryVoltageMutex);
			
			// Sample data each second
			usleep(1000000);
		}
	}
	
	int initialize()
	{
		// Create the thread
		pthread_t threadId;
		if (pthread_create(&threadId, nullptr, _dataProcessingThread, nullptr) != 0)
		{
			LOG(LOG_ERR, "Failed to create ADC thread (%s).", strerror(errno));
			return -1;
		}
		
		return 0;
	}
	
	void getBatteryValues(int *pointerVoltageMillivolts, int *pointerChargePercentage)
	{
		// Atomically retrieve values
		pthread_mutex_lock(&_batteryVoltageMutex);
		*pointerVoltageMillivolts = _batteryVoltageMillivolts;
		*pointerChargePercentage = _batteryVoltagePercentage;
		pthread_mutex_unlock(&_batteryVoltageMutex);
	}
}
