/*
 * SimpleApplication.h
 *
 *  Created on: Feb 2, 2013
 *      Author: sasaki
 */

#ifndef SIMPLEAPPLICATION_H_
#define SIMPLEAPPLICATION_H_

#include <ns3/address.h>
#include <ns3/on-off-helper.h>
#include <ns3/inet-socket-address.h>
#include <ns3/random-variable.h>
#include <ns3/data-rate.h>
#include <ns3/uinteger.h>
#include <ns3/string.h>

class SimpleOnOffHelper: public ns3::OnOffHelper {
	static const int remotePort = 9;
	static ns3::ExponentialVariable exponentialVariable;
	//ns3::OnOffHelper onOffHelper;
public:
	SimpleOnOffHelper(ns3::Ipv4Address const & remote_address) :
			ns3::OnOffHelper("ns3::UdpSocketFactory",
					ns3::Address(
							ns3::InetSocketAddress(remote_address, remotePort))) {

//		SetAttribute("OnTime",
//				ns3::RandomVariableValue( ns3::ConstantVariable(5)));
//		SetAttribute("OffTime",
//				ns3::RandomVariableValue(ns3::ConstantVariable(0)));
		SetAttribute("DataRate", ns3::DataRateValue(ns3::DataRate("100kbps")));
		SetAttribute("PacketSize", ns3::StringValue("1024"));
		SetAttribute("MaxBytes", ns3::UintegerValue(100000000));
		SetAttribute("OnTime",
				ns3::StringValue("ns3::ConstantRandomVariable[Constant=5]"));
		SetAttribute("OffTime",
				ns3::StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	}
	virtual ~SimpleOnOffHelper() {
	}
};

#endif /* SIMPLEAPPLICATION_H_ */
