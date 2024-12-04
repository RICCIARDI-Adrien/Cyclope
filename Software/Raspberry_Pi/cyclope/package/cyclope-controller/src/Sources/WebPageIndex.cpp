/** @file WebPageIndex.cpp
 * See WebPageIndex.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>

WebPageIndex::WebPageIndex() : WebPageBase("/") {};

int WebPageIndex::generateContent(std::string &referenceStringContent)
{
	referenceStringContent =
		"<h1>Cyclope Controller main menu</h1>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageManualControl.getBaseUrl() + "\">Manual control</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageIndex webPageIndex{};
