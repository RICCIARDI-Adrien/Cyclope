/** @file WebPageManualControl.cpp
 * See WebPageManualControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>

WebPageManualControl::WebPageManualControl() : WebPageBase("/remote-control") {};

int WebPageManualControl::generateContent(std::string &referenceStringContent)
{
	referenceStringContent =
		"<h1>Robot manual control</h1>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageIndex.getBaseUrl() + "\">Back</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageManualControl webPageManualControl{};
