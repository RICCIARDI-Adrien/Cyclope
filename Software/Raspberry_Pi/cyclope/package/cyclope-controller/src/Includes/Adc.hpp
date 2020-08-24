/** @file Adc.hpp
 * Read analog values from on-board ADC.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_ADC_HPP
#define HPP_ADC_HPP

namespace Adc
{
	/** Sample battery voltage from ADC and convert it to usable values.
	 * @param pointerVoltageMillivolts On output, contain the battery voltage in mV.
	 * @param pointerPercentage On output, contain the battery charge percentage. See method implementation for more details about computing charge percentage.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int getBatteryValues(int *pointerVoltageMillivolts, int *pointerChargePercentage);
}

#endif
