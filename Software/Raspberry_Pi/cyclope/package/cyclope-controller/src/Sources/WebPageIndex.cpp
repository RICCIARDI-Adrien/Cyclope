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
		"<script>\n"
		"	function onPowerOffButtonPressed()\n"
		"	{\n"
		"		dialogConfirm = document.getElementById(\"dialog-confirm\");\n"
		"		dialogConfirm.showModal();\n"
		"	}\n"
		"\n"
		"	function onNoButtonPressed()\n"
		"	{\n"
		"		dialogConfirm = document.getElementById(\"dialog-confirm\");\n" // For whatever reason, creating a global dialogConfirm variable used by all the functions does not work
		"		dialogConfirm.close();\n"
		"	}\n"
		"</script>\n"
		"\n"
		"<dialog id=\"dialog-confirm\">\n"
		"	<p>Do you really want to power the robot off ?</p>\n"
		"	<p>You will need to manually restart it.</p>\n"
		"	<button id=\"dialog-confirm-button-yes\" onclick=\"location.href='" + webPagePowerOff.getBaseUrl() + "';\">Yes</button>\n"
		"	<button id=\"dialog-confirm-button-no\" onclick=\"onNoButtonPressed()\" autofocus>No</button>\n"
		"</dialog>\n"
		"\n"
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
		"	<button onclick=\"onPowerOffButtonPressed()\">Power the robot off</button>\n"
		"</div>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageIndex webPageIndex{};
