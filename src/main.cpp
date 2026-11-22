#include <Geode/modify/SecretRewardsLayer.hpp>
#include "ThirdShinigamiEyePopup.hpp"

using namespace geode::prelude;

class $modify(MySecretRewardsLayer, SecretRewardsLayer) {
	void onSelectItem(CCObject* sender) {
		if (!Mod::get()->getSettingValue<bool>("enabled") || !sender || sender->getTag() < 0 || !typeinfo_cast<CCMenuItemSpriteExtra*>(sender) || CCScene::get()->getChildByType<ThirdShinigamiEyePopup>(0)) return SecretRewardsLayer::onSelectItem(sender);
		GJRewardItem* rewards = GameStatsManager::get()->getRewardForSecretChest(sender->getTag());
		if (!rewards || !rewards->m_rewardObjects) return;
		CCMenuItemSpriteExtra* senderAsButton = static_cast<CCMenuItemSpriteExtra*>(sender);
		Ref<CCMenuItemSpriteExtra> senderAsRefButton = senderAsButton;
		ThirdShinigamiEyePopup::create(rewards->m_rewardObjects, sender->getTag(), senderAsRefButton)->show();
	}
	// GD 2.2091 bindings have no iOS address for SecretRewardsLayer::onSpecialItem, GameStatsManager::getNextGoldChestID
	// or GameStatsManager::isSecretChestUnlocked. Hooking the first is a compile error on iOS (static_assert in the modify
	// codegen) and calling the other two throws std::runtime_error at runtime, so on iOS only onSelectItem is hooked.
	// Remove this guard once the bindings gain iOS addresses for all three.
#ifndef GEODE_IS_IOS
	void onSpecialItem(CCObject* sender) {
		if (!Mod::get()->getSettingValue<bool>("enabled") || !sender || sender->getTag() < 6 || sender->getTag() > 8 || !typeinfo_cast<CCMenuItemSpriteExtra*>(sender) || CCScene::get()->getChildByType<ThirdShinigamiEyePopup>(0)) return SecretRewardsLayer::onSpecialItem(sender);
		GJRewardItem* rewards = static_cast<GJRewardItem*>(GameStatsManager::get()->m_allSpecialChests->objectForKey(fmt::format("{:04d}", sender->getTag() - 2)));
		if (!rewards || !rewards->m_rewardObjects) return;
		CCMenuItemSpriteExtra* senderAsButton = static_cast<CCMenuItemSpriteExtra*>(sender);
		Ref<CCMenuItemSpriteExtra> senderAsRefButton = senderAsButton;
		ThirdShinigamiEyePopup::create(rewards->m_rewardObjects, sender->getTag() - 2, senderAsRefButton)->show();
	}
	void onGoldChest(CCObject* sender) {
		if (!Mod::get()->getSettingValue<bool>("enabled") || !sender || !typeinfo_cast<CCMenuItemSpriteExtra*>(sender) || CCScene::get()->getChildByType<ThirdShinigamiEyePopup>(0)) return SecretRewardsLayer::onGoldChest(sender);
		// GD 2.2091 has gold chests 6001-6030 (2.2081 only had 6001-6020); this returns 0 once all of them are opened.
		int nextGoldChestID = GameStatsManager::get()->getNextGoldChestID();
		if (nextGoldChestID <= 0) return SecretRewardsLayer::onGoldChest(sender);
		GJRewardItem* rewards = GameStatsManager::get()->getRewardForSecretChest(nextGoldChestID);
		if (!rewards || !rewards->m_rewardObjects) return;
		CCMenuItemSpriteExtra* senderAsButton = static_cast<CCMenuItemSpriteExtra*>(sender);
		Ref<CCMenuItemSpriteExtra> senderAsRefButton = senderAsButton;
		ThirdShinigamiEyePopup::create(rewards->m_rewardObjects, nextGoldChestID, senderAsRefButton)->show();
	}
#endif
};