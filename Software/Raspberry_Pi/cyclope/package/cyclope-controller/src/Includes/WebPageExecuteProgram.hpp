/** @file WebPageExecuteProgram.hpp
 * Run an AI program until the user quits the page.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_PAGE_EXECUTE_PROGRAM_HPP
#define HPP_WEB_PAGE_EXECUTE_PROGRAM_HPP

#include <WebPageBase.hpp>

class WebPageExecuteProgram : public WebPageBase
{
	public:
		// See base class documentation for description
		WebPageExecuteProgram();

		// See base class documentation for description
		virtual int generateContent(std::vector<UrlArgument *> &referenceVectorUrlArguments, std::string &referenceStringContent) override;
};

/** Give global access to the page statically allocated instance. */
extern WebPageExecuteProgram webPageExecuteProgram;

#endif
