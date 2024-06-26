#include "./ParsedMsg.hpp"
#include "./Param.hpp"

ParsedMsg::ParsedMsg() {}
ParsedMsg::~ParsedMsg() {}

void	ParsedMsg::setCommand(const std::string& command) {
	if (command.empty()) {
		throw std::invalid_argument("Empty command.");
	}
	try {
		this->command_ = command;
	} catch (std::exception& e) {
		throw std::invalid_argument("Command is not alphabet.");
	}
}

// middle     =  nospcrlfcl *( ":" / nospcrlfcl )
// trailing   =  *( ":" / " " / nospcrlfcl )
void	ParsedMsg::setParam(kTokenType tType, kParamType pType, const std::string& value) {
	try {
		Param	p;
		p.setTokenType(tType);
		p.setParamType(pType);
		p.setValue(value);
		this->params_.push_back(p);
	} catch (std::exception& e) {
		throw;
	}
}

const std::string&	ParsedMsg::getCommand() const {
	return (this->command_);
}

const std::vector<Param>&	ParsedMsg::getParams() const {
	return (this->params_);
}

void	ParsedMsg::printParsedMsg() const {
	if (this->command_.empty()) {
		return;
	}
	// std::cout << "[Parsed]    ____________________" << std::endl;
	// std::cout << "Type   : " << this->type_ << " | " << std::flush;
	std::cout << "Command: [" << this->command_ << "]" << std::endl;
	if (this->params_.empty()) {
		return;
	}
	for (std::vector<Param>::const_iterator it = this->params_.begin(); \
			it != this->params_.end(); it++) {
		it->printParam();
	}
	return;
}
