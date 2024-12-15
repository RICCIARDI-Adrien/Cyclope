/** @file ArtificialIntelligenceProgramWanderWithNoGoal.hpp
 * The base class from which all AI programs are derived.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_WANDER_WITH_NO_GOAL_HPP
#define HPP_ARTIFICIAL_INTELLIGENCE_PROGRAM_WANDER_WITH_NO_GOAL_HPP

#include <ArtificialIntelligenceProgramBase.hpp>

class ArtificialIntelligenceProgramWanderWithNoGoal : public ArtificialIntelligenceProgramBase
{
	public:
		// See base class documentation for description
		ArtificialIntelligenceProgramWanderWithNoGoal(const char *pointerStringDescriptiveName) : ArtificialIntelligenceProgramBase{pointerStringDescriptiveName} {}

		// See base class documentation for description
		virtual void run() override;

	private:
		/** All decision state machine states. */
		typedef enum
		{
			WANDER_WITH_NO_GOAL_STATE_GO_FORWARD,
			WANDER_WITH_NO_GOAL_STATE_BACKWARD_SEQUENCE_GO_TO_SAFE_LOCATION,
			WANDER_WITH_NO_GOAL_STATE_BACKWARD_SEQUENCE_DETERMINE_NEXT_DIRECTION,
			WANDER_WITH_NO_GOAL_STATE_TURN
		} WanderWithNoGoalState;

		/** All possible robot directions. */
		typedef enum
		{
			WANDER_WITH_NO_GOAL_DIRECTION_FORWARD,
			WANDER_WITH_NO_GOAL_DIRECTION_BACKWARD,
			WANDER_WITH_NO_GOAL_DIRECTION_LEFT,
			WANDER_WITH_NO_GOAL_DIRECTION_RIGHT,
			WANDER_WITH_NO_GOAL_DIRECTIONS_COUNT
		} WanderWithNoGoalDirection;
};

#endif
