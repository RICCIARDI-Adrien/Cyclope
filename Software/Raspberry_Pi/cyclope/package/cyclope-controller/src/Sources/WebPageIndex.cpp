/** @file WebPageIndex.cpp
 * See WebPageIndex.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>
#include <WebPagePowerOff.hpp>
#include <WebPageStartProgram.hpp>

WebPageIndex::WebPageIndex() : WebPageBase("/") {};

int WebPageIndex::generateContent(std::string &referenceStringContent)
{
	referenceStringContent =
		"<div class=\"text-center\">\n"
		"	<h1>Cyclope Controller main menu</h1>\n"
		"</div>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageManualControl.getBaseUrl() + "\">Manual control</a><br /><br />\n"
		"	<a href=\"" + webPageStartProgram.getBaseUrl() + "\">Start an AI program</a><br /><br />\n"
		"	<a href=\"" + webPagePowerOff.getBaseUrl() + "\">Power the robot off</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageIndex webPageIndex{};
