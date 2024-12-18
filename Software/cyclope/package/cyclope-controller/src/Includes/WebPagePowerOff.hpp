/** @file WebPagePowerOff.hpp
 * Cleanly power the robot off.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_PAGE_POWER_OFF_HPP
#define HPP_WEB_PAGE_POWER_OFF_HPP

#include <WebPageBase.hpp>

class WebPagePowerOff : public WebPageBase
{
	public:
		// See base class documentation for description
		WebPagePowerOff();

		// See base class documentation for description
		virtual int generateContent(std::vector<UrlArgument *> &, std::string &referenceStringContent) override;
};

/** Give global access to the page statically allocated instance. */
extern WebPagePowerOff webPagePowerOff;

#endif
