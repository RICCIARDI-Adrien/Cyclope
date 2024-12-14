/** @file WebPageStartProgram.cpp
 * See WebPageStartProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageStartProgram.hpp>

WebPageStartProgram::WebPageStartProgram() : WebPageBase("/start-program") {};

int WebPageStartProgram::generateContent(std::vector<UrlArgument *> &, std::string &referenceStringContent)
{
	referenceStringContent =
		"<p>TODO</p>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageIndex.getBaseUrl() + "\">Back</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageStartProgram webPageStartProgram{};
