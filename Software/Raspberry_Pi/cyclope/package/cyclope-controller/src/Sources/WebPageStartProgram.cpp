/** @file WebPageStartProgram.cpp
 * See WebPageStartProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgramManager.hpp>
#include <string>
#include <WebPageExecuteProgram.hpp>
#include <WebPageIndex.hpp>
#include <WebPageStartProgram.hpp>

WebPageStartProgram::WebPageStartProgram() : WebPageBase("/start-program") {};

int WebPageStartProgram::generateContent(std::vector<UrlArgument *> &, std::string &referenceStringContent)
{
	referenceStringContent =
		"<div class=\"text-center\">\n"
		"	<h1>Start an AI program</h1>\n"
		"</div>\n";

	// Generate the list of available programs
	const std::string &referenceExecutePageUrl = webPageExecuteProgram.getBaseUrl();
	for (unsigned int i = 0; i < ArtificialIntelligenceProgramManager::getProgramsCount(); i++)
	{
		// Get access to the next program
		ArtificialIntelligenceProgramBase *pointerProgram = ArtificialIntelligenceProgramManager::getProgram(i);

		referenceStringContent +=
			"<p class=\"text-center\">\n"
			"	<a href=\"" + referenceExecutePageUrl + "?index=" + std::to_string(i) + "\">" + pointerProgram->getDescriptiveName() + "</a>\n"
			"</p>\n";
	}

	referenceStringContent +=
		"<br />\n"
		"<div class=\"div-button-center\">\n"
		"	<button onclick=\"location.href='" + webPageIndex.getBaseUrl() + "';\">Back</button>\n"
		"</div>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageStartProgram webPageStartProgram{};
