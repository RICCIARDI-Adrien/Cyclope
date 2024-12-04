/** @file WebPageIndex.hpp
 * The web site root page. It allows to reach all controls of the web interface.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_PAGE_INDEX_HPP
#define HPP_WEB_PAGE_INDEX_HPP

#include <WebPageBase.hpp>

class WebPageIndex: public WebPageBase
{
	public:
		// See base class documentation for description
		WebPageIndex();

		// See base class documentation for description
		virtual int generateContent(std::string &referenceStringContent) override;
};

/** Give global access to the page statically allocated instance. */
extern WebPageIndex webPageIndex;

#endif
