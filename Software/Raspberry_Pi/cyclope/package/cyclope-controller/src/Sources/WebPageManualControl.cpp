/** @file WebPageManualControl.cpp
 * See WebPageManualControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>

WebPageManualControl::WebPageManualControl() : WebPageBase("/remote-control") {};

int WebPageManualControl::generateContent(std::vector<UrlArgument *> &, std::string &referenceStringContent)
{
	referenceStringContent =
		"<script>\n"
		"	// Global variables\n"
		"	let isLightEnabled = false;\n"
		"	let isUpDirectionKeyPressed = false;\n"
		"	let isDownDirectionKeyPressed = false;\n"
		"	let isLeftDirectionKeyPressed = false;\n"
		"	let isRightDirectionKeyPressed = false;\n"
		"	let isLastPressedDirectionKeyOnVerticalAxis = false;\n"
		"\n"
		"	// Catch all keyboard key press events\n"
		"	onkeydown = (event) =>\n"
		"	{\n"
		"		handleKeyEvent(true, event);\n"
		"	};\n"
		"\n"
		"	// Catch all keyboard key release events\n"
		"	onkeyup = (event) =>\n"
		"	{\n"
		"		handleKeyEvent(false, event);\n"
		"	};\n"
		"\n"
		"	// Make sure the robot is stopped when leaving the page\n"
		"	onbeforeunload = (event) =>\n"
		"	{\n"
		"		// Stop the robot\n"
		"		command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_STOP;\n"
		"		communicationProtocolSendCommand(command);\n"
		"\n"
		"		// Turn lights off\n"
		"		command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED + '0';\n"
		"		communicationProtocolSendCommand(command);\n"
		"	}\n"
		"\n"
		"	function handleKeyEvent(isKeyPressed, keyEvent)\n"
		"	{\n"
		"		// Ignore keys repetition\n"
		"		if (isKeyPressed === true)\n"
		"		{\n"
		"			if (keyEvent.repeat) return;\n"
		"		}\n"
		"\n"
		"		// Map the pressed key to a key index\n"
		"		switch (keyEvent.key)\n"
		"		{\n"
		"			case \"ArrowUp\":\n"
		"				isUpDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = true;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowDown\":\n"
		"				isDownDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = true;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowLeft\":\n"
		"				isLeftDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = false;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowRight\":\n"
		"				isRightDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = false;\n"
		"				break;\n"
		"\n"
		"			case \"L\":\n"
		"			case \"l\":\n"
		"				// This key is not considered as a button to hold\n"
		"				if (isKeyPressed === false) return;\n"
		"\n"
		"				// Toggle the light state\n"
		"				isLightEnabled = !isLightEnabled;\n"
		"				command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED;\n"
		"				if (isLightEnabled) command += '1';\n"
		"				else command += '0';\n"
		"				communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-lights-status\", answer); });\n"
		"				return; // The following code is only about motors management\n"
		"\n"
		"			// Ignore all other keys\n"
		"			default:\n"
		"				return;\n"
		"		}\n"
		"\n"
		"		// Handle the robot motion according to the pressed keys\n"
		"		// Stop the robot if all the direction keys are released\n"
		"		if (!isUpDirectionKeyPressed && !isDownDirectionKeyPressed && !isLeftDirectionKeyPressed && !isRightDirectionKeyPressed)\n"
		"		{\n"
		"			command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_STOP;\n"
		"			communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"		}\n"
		"		else\n"
		"		{\n"
		"			// Handle both vertical and horizontal direction movements\n"
		"			if ((isUpDirectionKeyPressed || isDownDirectionKeyPressed) && (isLeftDirectionKeyPressed || isRightDirectionKeyPressed))\n"
		"			{\n"
		"				// Keep trace of the last direction the user took to favor it, and when this key will be released the previous direction will be favored\n"
		"				if (isLastPressedDirectionKeyOnVerticalAxis)\n"
		"				{\n"
		"					if (isUpDirectionKeyPressed)\n"
		"					{\n"
		"						command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD;\n"
		"						communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"					}\n"
		"					else\n"
		"					{\n"
		"						command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD;\n"
		"						communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"					}\n"
		"				}\n"
		"				else\n"
		"				{\n"
		"					if (isLeftDirectionKeyPressed)\n"
		"					{\n"
		"						// Forward turn if going forward\n"
		"						if (isUpDirectionKeyPressed)\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_LEFT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"						}\n"
		"						// Backward turn if going backward\n"
		"						else\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD_LEFT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"						}\n"
		"					}\n"
		"					else\n"
		"					{\n"
		"						// Forward turn if going forward\n"
		"						if (isUpDirectionKeyPressed)\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_RIGHT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"						}\n"
		"						// Backward turn if going backward\n"
		"						else\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD_RIGHT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"						}\n"
		"					}\n"
		"				}\n"
		"			}\n"
		"			// Handle a single key press\n"
		"			else\n"
		"			{\n"
		"				if (isUpDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"				}\n"
		"				else if (isDownDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"				}\n"
		"				else if (isLeftDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_LEFT;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"				}\n"
		"				else if (isRightDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_RIGHT;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", answer); });\n"
		"				}\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"\n"
		"	function updateBatteryStatus()\n"
		"	{\n"
		"		communicationProtocolSendCommand(CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE).then((answer) =>\n"
		"		{\n"
		"			setUserInterfaceControlText(\"label-battery-status\", answer);\n"
		"		});\n"
		"	}\n"
		"	setInterval(updateBatteryStatus, 3000);\n" // Periodically poll the battery status
		"	updateBatteryStatus();\n" // Update the battery value as soon as possible
		"</script>\n"
		"\n"
		"<div class=\"text-center\">\n"
		"	<h1>Robot manual control</h1>\n"
		"</div>\n"
		"<table class=\"table-center\">\n"
		"	<tr>\n"
		"		<th>Robot motion (Arrows)</th>\n"
		"		<th>Battery</th>\n"
		"		<th>Lights (L)</th>\n"
		"	</tr>\n"
		"	<tr>\n"
		"		<td id=\"label-robot-motion-status\">Stopped</td>\n"
		"		<td id=\"label-battery-status\">UNKNOWN</td>\n"
		"		<td id=\"label-lights-status\">Disabled</td>\n"
		"	</tr>\n"
		"</table>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageIndex.getBaseUrl() + "\">Back</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageManualControl webPageManualControl{};
