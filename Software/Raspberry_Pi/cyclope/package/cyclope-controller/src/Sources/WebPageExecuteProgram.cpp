/** @file WebPageExecuteProgram.cpp
 * See WebPageExecuteProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageExecuteProgram.hpp>
#include <WebPageStartProgram.hpp>

WebPageExecuteProgram::WebPageExecuteProgram() : WebPageBase("/execute-program") {};

int WebPageExecuteProgram::generateContent(std::string &referenceStringContent)
{
	referenceStringContent =
		"<p>TEST</p>\n"
		"<br />\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageStartProgram.getBaseUrl() + "\">Back</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageExecuteProgram webPageExecuteProgram{};
