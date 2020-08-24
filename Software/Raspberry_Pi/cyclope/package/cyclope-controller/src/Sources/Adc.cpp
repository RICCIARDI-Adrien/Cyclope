/** @file Adc.cpp
 * See Adc.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Adc.hpp>
#include <Log.hpp>
#include <Sysfs.hpp>

/** All needed ADC sysfs files are stored in this directory. */
#define ADC_SYSFS_BASE_PATH "/sys/bus/iio/devices/iio:device0"

namespace Adc
{
	int getBatteryValues(int *pointerVoltageMillivolts, int *pointerChargePercentage)
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
}
