/*
 * TerminalSet.h
 *
 *  Created on: Feb 1, 2013
 *      Author: sasaki
 */

#ifndef TERMINALSET_H_
#define TERMINALSET_H_
#include <memory>
#include <vector>
#include <functional>
#include <ns3/net-device-container.h>
#include "Terminal.h"

class TerminalSet: public ns3::Object {
	const std::string& description;
	std::vector<ns3::Ptr<Terminal> > terminals;
//
//private:
//	void copyNewSimpleNode(
//			const std::vector<ns3::Ptr<SimpleNode> >::iterator& i);

public:
	TerminalSet(const int number_of_terminals = 15,
			const std::string& description_ = "terminal_set");
	const Terminal& operator[](const int index) const;
	Terminal& operator[](const int index);
	size_t size() const {
		return terminals.size();
	}
	virtual ~TerminalSet() {
	}
	void Assign(ns3::Ipv4AddressHelper& ipv4_address_helper) {
		for (size_t i = 0; i < terminals.size(); ++i) {
			terminals[i]->Assign(ipv4_address_helper);
		}
	}
private:
	TerminalSet(const TerminalSet&);
	TerminalSet operator=(const TerminalSet&);
};

#endif /* TERMINALSET_H_ */
