#include "Animation.h"
#include <fstream>
#include "Vector.h"

// Default constructor
Animation::Animation()
{
}

// Constructor allowing the loading of a script at creation
Animation::Animation(const char * sScriptFile)
{
	// Load animation
	load(sScriptFile);
}

// Copy constructor
Animation::Animation(const Animation & animation)
{
	// Copy the frames of animation to this
	m_frames = animation.m_frames;
	// Copy the initialisation frame of animation to this
	m_initFrame = animation.m_initFrame;
}

// Move constructor
Animation::Animation(Animation && animation)
{
	// Move the frames of animation to this
	m_frames = std::move(animation.m_frames);
	// Move the initialisation frame of animation to this
	m_initFrame = std::move(animation.m_initFrame);
}

// Destructor
Animation::~Animation()
{
}

// Copy assignment operator
Animation & Animation::operator=(const Animation & animation)
{
	// Copy the frames of animation to this
	m_frames = animation.m_frames;
	// Copy the initialisation frame of animation to this
	m_initFrame = animation.m_initFrame;

	return *this;
}

// Move assignment operator
Animation & Animation::operator=(Animation && animation)
{
	// Move the frames of animation to this
	m_frames = std::move(animation.m_frames);
	// Move the initialisation frame of animation to this
	m_initFrame = std::move(animation.m_initFrame);

	return *this;
}

// Load the animation from sScriptFile
bool Animation::load(const char * sScriptFile)
{
	// The parse used to load the animation is based on a
	// finite state transducer

	// Open the script file
	std::fstream script(sScriptFile);

	// Will contain the line being currently processed
	std::string line;
	// Will contain all the lines that compose the frame being currently created
	Vector<std::string>lines;
	// THe frame being currently created
	Frame fr;

	// State of the parser
	FSTParserState state = FSTParserState::Start;
	// Hold if an error has occured, assumes one has until the end of the script is reached
	bool ret = false;

	// Convenience string holding the keywords limiting the frames
	std::string init("INIT");
	std::string frame("FRAME");
	std::string end("END");

	// If the file was not opened correctly, there was an error
	if (!script.is_open()) {
		return false;
	}

	// Extract a line from the script until the eof is reached, the parser enteres error mode
	// or the end of the script is reached
	while (state!=FSTParserState::Err && state!=FSTParserState::End && std::getline(script, line)) {
		// Goes to parser state
		switch (state)
		{
		// The parser juste started loading the script
		case Animation::FSTParserState::Start:
			// If the line is not "INIT", "FRAME" or "END"
			// (The first lines are title)
			if (line.find(init) == std::string::npos &&
				line.find(frame) == std::string::npos &&
				line.find(end) == std::string::npos) {
				// Move parse to Title state
				state = FSTParserState::Title;
			}
			else {
				// Else, move the parser to Error state
				state = FSTParserState::Err;
			}
			break;
		// The parser is currently reading the title
		case Animation::FSTParserState::Title:
			// If the line is either "END" or "FRAME" (no init frame)
			if (line.find(frame) != std::string::npos && line.find(end) != std::string::npos) {
				// Move the parser to Error state
				state = FSTParserState::Err;
			}
			// Else if the line is "INIT" (reached init frame)
			else if (line.find(init)!=std::string::npos) {
				// Move parser to Init state
				state = FSTParserState::Init;
			}
			// Else do nothing since the title is useless
			break;
		// The parser is currently reading the init frame
		case Animation::FSTParserState::Init:
			// If the line is "END" (no animation frame) or "INIT" (second init frame)
			if (line.find(init) != std::string::npos && line.find(end) != std::string::npos) {
				// Move the parser to Error state
				state = FSTParserState::Err;
			}
			// Else if the line is "FRAME" (end of init frame is reached)
			else if (line.find(frame) != std::string::npos) {
				// Load the init frame with the lines composing it
				if (m_initFrame.load(lines)) {
					// If it was successful, move the parser to Frame state
					state = FSTParserState::Frame;
					// Clear the lines that were used to create the init frame
					lines.clear();
				}
				else {
					// If an error occured, move the parser to Error state
					state = FSTParserState::Err;
				}
			}
			// If the line is something different, it is considered part of the init frame and
			// added to the list of lines composing it
			else {
				lines.push_back(line);
			}
			break;
		// The parser is currently 
		case Animation::FSTParserState::Frame:
			// If the line is "INIT" (a second init frame)
			if (line.find(init) != std::string::npos) {
				// Move the parser to Error state
				state = FSTParserState::Err;
			}
			// Else if the line is "FRAME" (the end of the current frame was reached)
			else if (line.find(frame) != std::string::npos) {
				// Load the frame with the lines composing it
				if (fr.load(lines)) {
					// If it was successful, add the frame to the animation
					m_frames.push_back(fr);
					// Clear the lines that were used to create the current frame
					lines.clear();
				}
				else {
					// If an error occured, move the parser to Error state
					state = FSTParserState::Err;
				}
			}
			// Else if the line is "END" (the end of the script was reached)
			else if (line.find(end) != std::string::npos) {
				// Load the last frame with the lines composing it
				if (fr.load(lines)) {
					// If it was successful, add the frame to the animation
					m_frames.push_back(Frame(lines));
					// No error occurred during the parsing
					ret = true;
					// Move the parser to the End state
					state = FSTParserState::End;
				}
				else {
					// If an error occured, move the parser to Error state
					state = FSTParserState::Err;
				}
			}
			// If the line is something different, it is considered part of the current frame and
			// added to the list of lines composing it
			else {
				lines.push_back(line);
			}
			break;
		// The parser encountered an error
		case Animation::FSTParserState::Err:
			// Immediatly move to End state to exit reading the script
			state = FSTParserState::End;
			break;
		// The parser will finish on the next iteration
		case Animation::FSTParserState::End:
			break;
		default:
			break;
		}
	}

	// Return if no error occurred
	return ret;
}

// Unload the animation
bool Animation::unload()
{
	// Remove all the frames from this
	m_frames.clear();
	// Clear the initialisation frame
	m_initFrame.unload();

	// Should not fail
	return true;
}

// Play animation forward
bool Animation::playForward()
{
	// Displays the initialisation frame
	if (!m_initFrame.display()) {
		// If an error occures during dispaly, stop and return an error
		return false;
	}

	// Run through all the frames...
	for (list<Frame>::iterator it = m_frames.begin(); it != m_frames.end(); ++it) {
		// And display each of them in succession
		if (!it->display()) {
			// If an error occures during dispaly, stop and return an error
			return false;
		}
	}

	// Return no error if all goes well
	return true;
}

// Play animation backward
bool Animation::playBackward()
{
	// Displays the initialisation frame
	if (!m_initFrame.display()) {
		// If an error occures during dispaly, stop and return an error
		return false;
	}

	// Run through all the frames...
	for (list<Frame>::backward_iterator it = m_frames.rbegin(); it != m_frames.rend(); ++it) {
		// And display each of them in succession
		if (!it->display()) {
			// If an error occures during dispaly, stop and return an error
			return false;
		}
	}

	// Return no error if all goes well
	return true;
}
