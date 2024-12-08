/** @file WebPageIndex.cpp
 * See WebPageIndex.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>
#include <WebPagePowerOff.hpp>

WebPageIndex::WebPageIndex() : WebPageBase("/") {};

int WebPageIndex::generateContent(std::string &referenceStringContent)
{
	referenceStringContent =
		"<div class=\"text-center\">\n"
		"	<h1>Cyclope Controller main menu</h1>\n"
		"</div>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageManualControl.getBaseUrl() + "\">Manual control</a><br />\n"
		"	<a href=\"" + webPagePowerOff.getBaseUrl() + "\">Power the robot off</a><br />\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageIndex webPageIndex{};
