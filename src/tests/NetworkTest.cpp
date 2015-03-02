#include "tests/NetworkTest.h"

#if NETWORKING == 1

#include "engine/common/network/Network.h"
#include "engine/common/Logger.h"
#include "caveexpress/shared/network/messages/ProtocolMessages.h"

class NetworkTestListener: public IClientCallback {
public:
	void onData (ByteStream& data){
		debug(LOG_NET, String::format("recv: %i", data.getSize()));
	}
};

class NetworkTestServerListener: public IServerCallback {
public:
	void onConnection (ClientId clientId){
		// debugVA("client connected: %i", clientId);
	}
};

namespace {
const uint8_t BYTE_ADD = 1;
const int16_t SHORT_ADD = 64;
const int32_t INT_ADD = 128;

const char *LOCALHOST = "localhost";
const int PORT = 4567;
}

static NetworkTestListener listener;
static NetworkTestServerListener serverListener;

TEST(NetworkTest, testOpenServer)
{
	Network network;
	ASSERT_TRUE(network.openServer(PORT, &serverListener)) << network.getError();
	network.closeServer();
}

TEST(NetworkTest, testOpenClient)
{
	Network network;
	ASSERT_TRUE(network.openServer(PORT, &serverListener)) << network.getError();
	ASSERT_TRUE(network.openClient(LOCALHOST, PORT, &listener)) << network.getError();
	network.closeClient();
	network.closeServer();
}

TEST(NetworkTest, testUpdate)
{
	Network network;
	ASSERT_TRUE(network.openServer(PORT, &serverListener)) << network.getError();
	ASSERT_TRUE(network.openClient(LOCALHOST, PORT, &listener)) << network.getError();
	network.update(0);
	network.closeClient();
	network.closeServer();
}

TEST(NetworkTest, testSendToClient)
{
	Network network;
	ASSERT_TRUE(network.openServer(PORT, &serverListener)) << network.getError();
	ASSERT_TRUE(network.openClient(LOCALHOST, PORT, &listener)) << network.getError();
	const DisconnectMessage msg;
	network.update(0);
	network.sendToClients(0, msg);
	network.update(0);
	network.closeClient();
	network.closeServer();
}

TEST(NetworkTest, testSendStringList)
{
	std::vector<std::string> names;
	names.push_back("Test1");
	names.push_back("Test2");
	PlayerListMessage msgNames(names);
	Network network;
	ASSERT_TRUE(network.openServer(PORT, &serverListener)) << network.getError();
	class NetworkNameListTestListener: public IClientCallback {
	public:
		NetworkNameListTestListener() :
				count(0) {
		}
		int count;
		void onData(ByteStream &data) override
		{
			ASSERT_EQ(protocol::PROTO_PLAYERLIST, data.readByte());
			PlayerListMessage msg(data);
			ASSERT_EQ("Test1", msg.getList()[0]);
			ASSERT_EQ("Test2", msg.getList()[1]);
			++count;
		}
	};
	NetworkNameListTestListener nameListener;
	ASSERT_TRUE(network.openClient(LOCALHOST, PORT, &nameListener)) << network.getError();
	network.update(0);
	network.sendToAllClients(msgNames);
	network.update(5000);
	network.sendToAllClients(msgNames);
	network.update(5000);
	network.sendToAllClients(msgNames);
	network.update(5000);
	ASSERT_EQ(3, nameListener.count);
	network.closeClient();
	network.closeServer();
}

TEST(NetworkTest, testSendToServer)
{
	Network network;
	ASSERT_TRUE(network.openServer(PORT, &serverListener)) << network.getError();
	ASSERT_TRUE(network.openClient(LOCALHOST, PORT, &listener)) << network.getError();
	network.update(0);
	const DisconnectMessage msg;
	ASSERT_EQ(1, network.sendToServer(msg));
	ASSERT_EQ(1, network.sendToClients(0, msg));
	network.update(0);
	network.closeClient();
	network.closeServer();
}

#endif
