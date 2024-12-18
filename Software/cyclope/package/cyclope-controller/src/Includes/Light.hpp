/** @file Light.hpp
 * Turn on or turn off front board leds.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_LIGHT_HPP
#define HPP_LIGHT_HPP

namespace Light
{
	/** Configure control GPIO and turn light off.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int initialize();
	
	/** Turn light on or off.
	 * @param isEnabled Set to false to turn light off, set to true to turn light on.
	 * @return -1 if an error occurred,
	 * @return 0 on success.
	 */
	int setEnabled(bool isEnabled);
}

#endif
