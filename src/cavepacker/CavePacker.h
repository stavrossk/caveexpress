#pragma once

#include "engine/GameRegistry.h"
#include "engine/client/ClientMap.h"
#include "engine/common/campaign/CampaignManager.h"
#include "engine/common/campaign/persister/IGameStatePersister.h"

class CavePacker: public IGame {
private:
	IGameStatePersister* _persister;
	CampaignManager *_campaignManager;
	ClientMap *_map;
	IFrontend *_frontend;
	ServiceProvider* _serviceProvider;

public:
	CavePacker();
	virtual ~CavePacker();

	void connect () override;
	void initUI (IFrontend* frontend, ServiceProvider& serviceProvider) override;
	void initSoundCache () override;
	void update (uint32_t deltaTime) override;
	void onData (ClientId clientId, ByteStream &data) override;
	std::string getMapName () override;
	void init (IFrontend *frontend, ServiceProvider& serviceProvider) override;
	void shutdown () override;
	int getPlayers () override;
	void connect (ClientId clientId) override;
	int disconnect (ClientId clientId) override;
	void mapReload () override;
	void mapShutdown () override;
	bool mapLoad (const std::string& map) override;
	IMapManager* getMapManager () override;
	UIWindow* createPopupWindow (IFrontend* frontend, const std::string& text, int flags, UIPopupCallbackPtr callback) override;
};

static GameRegisterStatic CAVEEXPRESS("cavepacker", GamePtr(new CavePacker()));