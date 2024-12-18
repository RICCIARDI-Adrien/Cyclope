/** @file WebPageIndex.cpp
 * See WebPageIndex.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>
#include <WebPagePowerOff.hpp>
#include <WebPageStartProgram.hpp>

WebPageIndex::WebPageIndex() : WebPageBase("/") {};

int WebPageIndex::generateContent(std::vector<UrlArgument *> &, std::string &referenceStringContent)
{
	referenceStringContent =
		"<div class=\"text-center\">\n"
		"	<h1>Cyclope Controller main menu</h1>\n"
		"</div>\n"
		"<div class=\"div-button-center\">\n"
		"	<button onclick=\"location.href='" + webPageManualControl.getBaseUrl() + "';\">Manual control</button>\n"
		"</div>\n"
		"<div class=\"div-button-center\">\n"
		"	<button onclick=\"location.href='" + webPageStartProgram.getBaseUrl() + "';\">Start an AI program</button>\n"
		"</div>\n"
		"<div class=\"div-button-center\">\n"
		"	<button onclick=\"location.href='" + webPagePowerOff.getBaseUrl() + "';\">Power the robot off</button>\n"
		"</div>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageIndex webPageIndex{};
