/** @file WebPagePowerOff.cpp
 * See WebPagePowerOff.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <cstdlib>
#include <Log.hpp>
#include <WebPagePowerOff.hpp>

WebPagePowerOff::WebPagePowerOff() : WebPageBase("/power-off") {};

int WebPagePowerOff::generateContent(std::string &referenceStringContent)
{
	referenceStringContent =
		"<div class=\"text-center\">\n"
		"	<h1>The robot has been powered off.</h1>\n"
		"</div>\n";

	LOG(LOG_INFO, "Received the power off command, shutting the system down.");
	system("poweroff");

	return 0;
}

// The statically allocated instance of the page
WebPagePowerOff webPagePowerOff{};
