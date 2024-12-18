/** @file ArtificialIntelligenceProgramFollowTennisBall.hpp
 * Try to discern a tennis ball with the camera and to follow it in the room.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_FOLLOW_TENNIS_BALL_HPP
#define HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_FOLLOW_TENNIS_BALL_HPP

#include <ArtificialIntelligenceProgramBase.hpp>

class ArtificialIntelligenceProgramFollowTennisBall : public ArtificialIntelligenceProgramBase
{
	public:
		// See base class documentation for description
		ArtificialIntelligenceProgramFollowTennisBall(const char *pointerStringDescriptiveName) : ArtificialIntelligenceProgramBase{pointerStringDescriptiveName} {}

		// See base class documentation for description
		virtual void run() override;
};

#endif
