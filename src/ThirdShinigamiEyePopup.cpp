#include "ThirdShinigamiEyePopup.hpp"

ThirdShinigamiEyePopup* ThirdShinigamiEyePopup::create(CCArray* rewards, int chestID, const Ref<CCMenuItemSpriteExtra> button) {
	auto* ret = new ThirdShinigamiEyePopup(rewards, chestID, button);
	if (ret->init()) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

std::string ThirdShinigamiEyePopup::getDisplayNameUnlockType(UnlockType p0) {
	if (!enumForUnlockType.contains(static_cast<int>(p0))) return "Unknown";
	return enumForUnlockType.at(static_cast<int>(p0));
}

std::string ThirdShinigamiEyePopup::getDisplayNameSpecialRewardItem(SpecialRewardItem p0) {
	if (!enumForSpecialRewardItem.contains(static_cast<int>(p0))) return "Unknown";
	return enumForSpecialRewardItem.at(static_cast<int>(p0));
}

IconType ThirdShinigamiEyePopup::getCorrespondingIconType(UnlockType p0) {
	return sometimesIFuckingHateRobtop.at(p0);
}

std::string ThirdShinigamiEyePopup::getEmojiForRewardType(SpecialRewardItem p0) {
	if (!rewardToEmoji.contains(p0)) return "[?]";
	return rewardToEmoji.at(p0);
}

std::string ThirdShinigamiEyePopup::formatColor(ccColor3B color) {
	return fmt::format("#{:02X}{:02X}{:02X}", color.r, color.g, color.b);
}


CCNode* ThirdShinigamiEyePopup::generateBaseRow() {
	CCNode* ret = CCNode::create();
	ret->setContentSize({185.f, 30.f});
	ret->setAnchorPoint({0.f, .5f});
	ret->setLayout(RowLayout::create()->setGap(35.f)->setAxisAlignment(AxisAlignment::Start)->setDefaultScaleLimits(.1f, .5f));
	return ret;
}

void ThirdShinigamiEyePopup::addSpriteToRewardRow(UnlockType unlockType, int iconID, CCNode *ret, CCSprite *coloredSprite) {
	const std::string& determinedString = (unlockType != UnlockType::Col1 && unlockType != UnlockType::Col2) ? fmt::format("{} #{}", getDisplayNameUnlockType(unlockType), iconID) : fmt::format("{} {}", getDisplayNameUnlockType(unlockType), ThirdShinigamiEyePopup::formatColor(GameManager::get()->colorForIdx(iconID)));
	CCLabelBMFont* spriteRewardLabel = CCLabelBMFont::create(determinedString.c_str(), "bigFont.fnt");
	coloredSprite->setID("reward-sprite"_spr);
	spriteRewardLabel->setID("reward-label"_spr);
	ret->addChild(coloredSprite);
	ret->addChild(spriteRewardLabel);
	ret->setLayout(RowLayout::create()->setGap(20.f)->setAxisAlignment(AxisAlignment::Start)->setDefaultScaleLimits(.1f, .5f));
}

CCNode* ThirdShinigamiEyePopup::generateIconRow(UnlockType unlockType, int iconID) {
	CCNode* ret = ThirdShinigamiEyePopup::generateBaseRow();
	// force alignment (it's invisible)
	SimplePlayer* twitterWasAMistake = SimplePlayer::create(0);
	twitterWasAMistake->updatePlayerFrame(0, IconType::Cube);
	twitterWasAMistake->setOpacity(0);
	twitterWasAMistake->setID("padding-start"_spr);
	ret->addChild(twitterWasAMistake);

	switch (unlockType) {
		case UnlockType::GJItem:
			addSpriteToRewardRow(unlockType, iconID, ret, CCSprite::createWithSpriteFrameName(fmt::format("gjItem_{:02d}_001.png", iconID).c_str()));
			break;
		case UnlockType::Death:
			addSpriteToRewardRow(unlockType, iconID, ret, CCSprite::createWithSpriteFrameName(fmt::format("explosionIcon_{:02d}_001.png", iconID).c_str()));
			break;
		case UnlockType::Streak:
			addSpriteToRewardRow(unlockType, iconID, ret, CCSprite::createWithSpriteFrameName(fmt::format("player_special_{:02d}_001.png", iconID).c_str()));
			break;
		case UnlockType::ShipFire:
			addSpriteToRewardRow(unlockType, iconID, ret, CCSprite::createWithSpriteFrameName(fmt::format("shipfireIcon_{:02d}_001.png", iconID).c_str()));
			break;
		case UnlockType::Col1:
		case UnlockType::Col2: {
			CCSprite* coloredSprite = CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
			coloredSprite->setColor(GameManager::get()->colorForIdx(iconID));
			CCLabelBMFont* dummyLabel = CCLabelBMFont::create(unlockType == UnlockType::Col2 ? "2" : "1", "bigFont.fnt");
			dummyLabel->setScale(.65f);
			dummyLabel->setID("color-indicator"_spr);
			coloredSprite->addChildAtPosition(dummyLabel, Anchor::Center);
			addSpriteToRewardRow(unlockType, iconID, ret, coloredSprite);
			break;
		}
		case UnlockType::Cube:
		case UnlockType::Ship:
		case UnlockType::Ball:
		case UnlockType::Bird:
		case UnlockType::Dart:
		case UnlockType::Robot:
		case UnlockType::Spider:
		case UnlockType::Swing:
		case UnlockType::Jetpack: {
			SimplePlayer* fakeIcon = SimplePlayer::create(0);
			fakeIcon->updatePlayerFrame(iconID, getCorrespondingIconType(unlockType));
			fakeIcon->setColors(GameManager::get()->colorForIdx(GameManager::get()->m_playerColor.value()), GameManager::get()->colorForIdx(GameManager::get()->m_playerColor2.value()));
			if (GameManager::get()->m_playerGlow) fakeIcon->setGlowOutline(GameManager::get()->colorForIdx(GameManager::get()->m_playerGlowColor.value()));
			fakeIcon->setID("reward-icon-preview"_spr);
			ret->addChild(fakeIcon);
			ret->addChild(CCLabelBMFont::create(fmt::format("{} #{}", getDisplayNameUnlockType(unlockType), iconID).c_str(), "bigFont.fnt"));
			break;
		}
		// ship fire template: CCSprite::createWithSpriteFrameName(fmt::format("shipfireIcon_{:02d}_001.png", iconID).c_str());
		// trail template: CCSprite::createWithSpriteFrameName(fmt::format("player_special_{:02d}_001.png", iconID).c_str());
		// death effect template: CCSprite::createWithSpriteFrameName(fmt::format("explosionIcon_{:02d}_001.png", iconID).c_str());
		default: {
			geode::Label* advLabel = geode::Label::create("", "bigFont.fnt");
			advLabel->setEmojiRegistry(getTSEEmojiRegistry());
			advLabel->setText(fmt::format(" {} {} ID {}", unlockToEmoji.at(unlockType), getDisplayNameUnlockType(unlockType), iconID));
			advLabel->setID("basic-reward-label"_spr);
			advLabel->setTag(11112025);
			ret->addChild(advLabel);
			break;
		}
	}
	SimplePlayer* twitterWasAMistakeAgain = SimplePlayer::create(0);
	twitterWasAMistakeAgain->updatePlayerFrame(0, IconType::Cube);
	twitterWasAMistakeAgain->setOpacity(0);
	twitterWasAMistakeAgain->setID("padding-end"_spr);
	ret->addChild(twitterWasAMistakeAgain);
	ret->updateLayout();
	return ret;
}

CCNode *ThirdShinigamiEyePopup::generateRewardRow(int quantity, SpecialRewardItem rewardType) {
	CCNode* ret = ThirdShinigamiEyePopup::generateBaseRow();
	geode::Label* rewardLabel = geode::Label::create("", "bigFont.fnt");
	rewardLabel->setEmojiRegistry(getTSEEmojiRegistry());
	std::string displayName = getDisplayNameSpecialRewardItem(rewardType);
	if (quantity == 1) displayName.pop_back();
	rewardLabel->setText(fmt::format(" {} {}x {}", getEmojiForRewardType(rewardType), quantity, displayName));
	rewardLabel->setID("special-reward-label"_spr);
	ret->addChild(rewardLabel);
	ret->updateLayout();
	return ret;
}

bool ThirdShinigamiEyePopup::init() {
	if (!geode::Popup::init(250.f, 240.f, "GJ_square02.png")) return false;

	this->setTitle("Rewards Preview");
	this->m_title->setID("rewards-preview-title"_spr);

	CCNode* containerNode = CCNode::create();
	containerNode->setLayout(ColumnLayout::create()->setGap(5.f)->setCrossAxisOverflow(false)->setAutoScale(true)->setAxisReverse(false));
	containerNode->setID("rewards-container-node"_spr);

	unsigned int i = m_rewards->count();
	for (GJRewardObject* item : CCArrayExt<GJRewardObject*>(m_rewards)) {
		CCNode* node = item->m_specialRewardItem != SpecialRewardItem::CustomItem ? generateRewardRow(item->m_total, item->m_specialRewardItem) : generateIconRow(item->m_unlockType, item->m_itemID);
		node->setID(fmt::format("{}/reward-item-{}", GEODE_MOD_ID, i));
		containerNode->addChild(node);
		i--;
	}

	m_mainLayer->addChildAtPosition(containerNode, Anchor::Center);
	containerNode->setAnchorPoint({.5f, .5f});
	containerNode->setContentSize({175.f, 150.f});
	containerNode->updateLayout();

	CCMenuItemSpriteExtra* openButton = CCMenuItemSpriteExtra::create(ButtonSprite::create("Open!", "goldFont.fnt", "GJ_button_01.png"), this, menu_selector(ThirdShinigamiEyePopup::onActuallyOpenTheChest));
	openButton->setID("open-button"_spr);
	m_buttonMenu->addChild(openButton);
	openButton->setPosition(m_mainLayer->getContentSize() / 2.f);
	openButton->setPositionY(25.f);

	this->setTag(m_chestID);
	this->setID("ThirdShinigamiEyePopup"_spr);
	this->m_buttonMenu->setID("button-menu"_spr);
	this->m_closeBtn->setID("close-button"_spr);
	this->m_bgSprite->setID("background"_spr);
	this->m_mainLayer->setID("main-layer"_spr);

	return true;
}