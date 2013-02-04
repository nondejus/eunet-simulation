#include <ns3/log.h>
#include <ns3/uinteger.h>
#include "Terminal.h"

NS_LOG_COMPONENT_DEFINE("Terminal");

Terminal::Terminal(const std::string name) :
		SimpleNode(name) {
	NS_LOG_INFO("Terminal:creating " << name << "with PacketSink and UdpEchoServer");
	ns3::PacketSinkHelper packet_sink_helper("ns3::UdpSocketFactory",
			ns3::InetSocketAddress(ns3::Ipv4Address::GetAny(), discardPort));
	pPacketSink = packet_sink_helper.Install(*this).Get(0);
	pPacketSink->SetStartTime(ns3::Seconds(0.0));
	pPacketSink->SetStopTime(ns3::Seconds(10.0));

	ns3::UdpEchoServerHelper udp_echo_server_helper(echoPort);
	pUdpEchoServer = udp_echo_server_helper.Install(*this).Get(0);
	pUdpEchoServer->SetStartTime(ns3::Seconds(0.0));
	pUdpEchoServer->SetStopTime(ns3::Seconds(10.0));

//		ns3::UdpEchoClientHelper udp_echo_client_helper(*this, echoPort);
//		udpEchoClientApplications.Add(udp_echo_client_helper.Install(*this));
//
//		ns3::OnOffHelper on_off_helper("ns3::UdpSocketFactory",
//				ns3::Address(ns3::InetSocketAddress(*this, discardPort)));
//		onOffApplications.Add(on_off_helper.Install(*this));

} // a constructor

ns3::Ptr<ns3::Application> Terminal::installUdpEchoClient(
		ns3::Ipv4Address const& ipv4_address, ns3::UintegerValue max_packets,
		ns3::TimeValue interval, ns3::DataRateValue) {
	NS_LOG_INFO("Terminal:installUdpEchoClientApplication to " << ipv4_address
			<< " on " << this->operator ns3::Ipv4Address());
	ns3::UdpEchoClientHelper udp_echo_client_helper(*this, echoPort);
	ns3::ApplicationContainer ac = udp_echo_client_helper.Install(*this);
	ac.Get(0)->SetAttribute("Interval", interval);
	ac.Get(0)->SetAttribute("PacketSize", ns3::UintegerValue(1024));
	ac.Get(0)->SetAttribute("MaxPackets", max_packets);
	ac.Get(0)->SetStartTime(ns3::Seconds(0.0));
	ac.Get(0)->SetStopTime(ns3::Seconds(10.0));
	udpEchoClients.Add(ac);
	return ac.Get(0);
} // installUdpEchoClientApplication

ns3::Ptr<ns3::Application> Terminal::installOnOffApplication(
		ns3::Ipv4Address remote_address, ns3::DataRateValue data_rate_value,
		ns3::UintegerValue packet_size, ns3::UintegerValue max_bytes,
		ns3::StringValue on_time, ns3::StringValue off_time) {
	NS_LOG_INFO("Terminal:installOnOffApplication to "
			<< remote_address << " on " << this->operator ns3::Ipv4Address());
	ns3::OnOffHelper on_off_helper("ns3::UdpSocketFactory",
			ns3::Address(ns3::InetSocketAddress(remote_address, discardPort)));
	ns3::ApplicationContainer ac = on_off_helper.Install(*this);
	ac.Get(0)->SetAttribute("DataRate", data_rate_value);
	ac.Get(0)->SetAttribute("PacketSize", packet_size);
	ac.Get(0)->SetAttribute("MaxBytes", max_bytes);
	ac.Get(0)->SetAttribute("OnTime", on_time);
	ac.Get(0)->SetAttribute("OffTime", off_time);
	ac.Get(0)->SetStartTime(ns3::Seconds(0.0));
	ac.Get(0)->SetStopTime(ns3::Seconds(10.0));
	onOffApplications.Add(ac);
	return ac.Get(0);
} //installOnOffApplication