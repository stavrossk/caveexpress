#include "UISettingsWindow.h"
#include "engine/client/ui/nodes/UINodeBackButton.h"
#include "engine/client/ui/nodes/UINodeBackToRootButton.h"
#include "engine/client/ui/nodes/UINodeCheckbox.h"
#include "engine/client/ui/nodes/UINodeLabel.h"
#include "engine/client/ui/nodes/UINodeButtonImage.h"
#include "engine/client/ui/nodes/UINodeButtonText.h"
#include "engine/client/ui/layouts/UIHBoxLayout.h"
#include "caveexpress/client/ui/nodes/UINodeSettingsBackground.h"
#include "caveexpress/client/ui/windows/modeselection/ModeSetListener.h"
#include "engine/client/sound/Sound.h"
#include "engine/common/ConfigManager.h"
#include "engine/common/ServiceProvider.h"
#include "engine/common/network/INetwork.h"

#include "engine/client/ui/windows/listener/TextureModeListener.h"
#include "engine/client/ui/windows/listener/JoystickNodeListener.h"
#include "engine/client/ui/windows/listener/SoundNodeListener.h"

UISettingsWindow::UISettingsWindow (IFrontend *frontend, ServiceProvider& serviceProvider, CampaignManager& campaignManager) :
		UIWindow(UI_WINDOW_SETTINGS, frontend, WINDOW_FLAG_MODAL)
{
	UINodeSettingsBackground *background = new UINodeSettingsBackground(frontend);
	add(background);

	UINode* last;
	last = addSection(nullptr, background, tr("Textures"),
			tr("Big"), new TextureModeListener("big", _frontend, serviceProvider),
			tr("Small"), new TextureModeListener("small", _frontend, serviceProvider));

	last = addSection(last, nullptr, tr("Game mode"),
			tr("Normal"), new ModeSetListener("easy", campaignManager),
			tr("Hard"), new ModeSetListener("hard", campaignManager));

	last = addSection(last, nullptr, tr("Sound/Music"),
			tr("On"), new SoundNodeListener(this, true),
			tr("Off"), new SoundNodeListener(this, false));

	if (System.canDisableJoystick() && frontend->hasJoystick()) {
		last = addSection(last, nullptr, tr("Joystick"),
			tr("On"), new JoystickNodeListener(true),
			tr("Off"), new JoystickNodeListener(false));
	}

	if (!wantBackButton())
		return;

	UINodeBackButton *backButton = new UINodeBackButton(frontend);
	const float gapBack = std::max(0.01f, getScreenPadding());
	backButton->alignTo(background, NODE_ALIGN_BOTTOM | NODE_ALIGN_LEFT, gapBack);
	add(backButton);
}

UINode* UISettingsWindow::addSection (UINode* centerUnderNode, UINode* background, const std::string& title, const std::string& option1, UINodeListener* option1Listener, const std::string& option2, UINodeListener* option2Listener)
{
	UINodeLabel *label = new UINodeLabel(_frontend, title);
	label->setFont(HUGE_FONT);
	label->setColor(colorWhite);
	if (background != nullptr) {
		label->alignTo(background, NODE_ALIGN_CENTER | NODE_ALIGN_TOP, 0.2f);
	} else {
		assert(centerUnderNode);
		label->centerUnder(centerUnderNode, 0.03f);
	}
	add(label);
	UINode *optionsPanel = new UINode(_frontend, title);
	{
		UIHBoxLayout *hlayout = new UIHBoxLayout(0.02f);
		optionsPanel->setLayout(hlayout);
		{
			UINodeButtonText *option1Text = new UINodeButtonText(_frontend, option1);
			option1Text->addListener(UINodeListenerPtr(option1Listener));
			option1Text->setFont(getFont(HUGE_FONT));
			optionsPanel->add(option1Text);

			UINodeButtonText *option2Text = new UINodeButtonText(_frontend, option2);
			option2Text->addListener(UINodeListenerPtr(option2Listener));
			option2Text->setFont(getFont(HUGE_FONT));
			optionsPanel->add(option2Text);
		}
	}
	add(optionsPanel);
	optionsPanel->centerUnder(label);
	return optionsPanel;
}
