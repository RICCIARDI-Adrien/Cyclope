/** @file WebPageIndex.cpp
 * See WebPageIndex.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>

WebPageIndex::WebPageIndex() : WebPageBase("/") {};

int WebPageIndex::generateContent(std::string &referenceStringContent)
{
	// TEST
	referenceStringContent = "<p>index</p>";

	return 0;
}

// The statically allocated instance of the page
WebPageIndex webPageIndex{};
