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
		int nextGoldChestID = 6001;
		while (nextGoldChestID < 6021) {
			if (!GameStatsManager::get()->isSecretChestUnlocked(nextGoldChestID)) break;
			nextGoldChestID += 1;
		}
		GJRewardItem* rewards = GameStatsManager::get()->getRewardForSecretChest(nextGoldChestID);
		if (!rewards || !rewards->m_rewardObjects) return;
		CCMenuItemSpriteExtra* senderAsButton = static_cast<CCMenuItemSpriteExtra*>(sender);
		Ref<CCMenuItemSpriteExtra> senderAsRefButton = senderAsButton;
		ThirdShinigamiEyePopup::create(rewards->m_rewardObjects, nextGoldChestID, senderAsRefButton)->show();
	}
};