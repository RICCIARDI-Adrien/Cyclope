/** @file WebPageStartProgram.hpp
 * List all available AI programs and allow to select one.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_PAGE_START_PROGRAM_HPP
#define HPP_WEB_PAGE_START_PROGRAM_HPP

#include <WebPageBase.hpp>

class WebPageStartProgram : public WebPageBase
{
	public:
		// See base class documentation for description
		WebPageStartProgram();

		// See base class documentation for description
		virtual int generateContent(std::vector<UrlArgument *> &, std::string &referenceStringContent) override;
};

/** Give global access to the page statically allocated instance. */
extern WebPageStartProgram webPageStartProgram;

#endif
