#pragma once

#include <AdvancedLabel.hpp>

using namespace geode::prelude;

inline std::unordered_map<int, std::string> enumForUnlockType {
	{0x1, "Cube"},
	{0x2, "Primary Color"},
	{0x3, "Secondary Color"},
	{0x4, "Ship"},
	{0x5, "Ball"},
	{0x6, "UFO"},
	{0x7, "Wave"},
	{0x8, "Robot"},
	{0x9, "Spider"},
	{0xA, "Trail"},
	{0xB, "Death Effect"},
	{0xC, "Secret Item"},
	{0xD, "Swing"},
	{0xE, "Jetpack"},
	{0xF, "Ship Fire"},
};

inline std::unordered_map<int, std::string> enumForSpecialRewardItem {
	{0x1, "Fire Shards"},
	{0x2, "Ice Shards"},
	{0x3, "Poison Shards"},
	{0x4, "Shadow Shards"},
	{0x5, "Lava Shards"},
	{0x6, "Bonus Keys"},
	{0x7, "Orbs"},
	{0x8, "Diamonds"},
	{0x9, "Custom Items"},
	{0xA, "Earth Shards"},
	{0xB, "Blood Shards"},
	{0xC, "Metal Shards"},
	{0xD, "Light Shards"},
	{0xE, "Soul Shards"},
	{0xF, "Gold Keys"},
};

inline std::unordered_map<UnlockType, IconType> sometimesIFuckingHateRobtop {
	{UnlockType::Cube, IconType::Cube},
	{UnlockType::Ship, IconType::Ship},
	{UnlockType::Ball, IconType::Ball},
	{UnlockType::Bird, IconType::Ufo},
	{UnlockType::Dart, IconType::Wave},
	{UnlockType::Robot, IconType::Robot},
	{UnlockType::Spider, IconType::Spider},
	{UnlockType::Swing, IconType::Swing},
	{UnlockType::Jetpack, IconType::Jetpack},
};

inline std::unordered_map<SpecialRewardItem, std::string> rewardToEmoji {
	{SpecialRewardItem::CustomItem, "❓"},
	{SpecialRewardItem::Diamonds, "💎"},
	{SpecialRewardItem::BonusKey, "🔐"},
	{SpecialRewardItem::GoldKey, "🔑"},
	{SpecialRewardItem::Orbs, "🔮"},
	// i hate shards tier 1
	{SpecialRewardItem::FireShard, "🔥"},
	{SpecialRewardItem::IceShard, "🧊"},
	{SpecialRewardItem::PoisonShard, "🧪"},
	{SpecialRewardItem::ShadowShard, "🦇"},
	{SpecialRewardItem::LavaShard, "🌋"},
	// i hate shards tier 2
	{SpecialRewardItem::EarthShard, "🌱"},
	{SpecialRewardItem::BloodShard, "🩸"},
	{SpecialRewardItem::MetalShard, "🧲"},
	{SpecialRewardItem::LightShard, "💡"},
	{SpecialRewardItem::SoulShard, "👻"},
};

inline std::unordered_map<UnlockType, std::string> unlockToEmoji {
	{UnlockType::Cube, "⬛"},
	{UnlockType::Col1, "🎨"},
	{UnlockType::Col2, "🎨"},
	{UnlockType::Ship, "✈️"},
	{UnlockType::Ball, "⚽"},
	{UnlockType::Bird, "🛸"},
	{UnlockType::Dart, "↗️"},
	{UnlockType::Robot, "🤖"},
	{UnlockType::Spider, "🕷"},
	{UnlockType::Streak, "🌠"},
	{UnlockType::Death, "🪦"},
	{UnlockType::GJItem, "🎁"},
	{UnlockType::Swing, "🛝"},
	{UnlockType::Jetpack, "🚀"},
	{UnlockType::ShipFire, "⛽"},
};

static const Label::EmojiMap g_emojis = {
	{U"❓", "gj_explosionBtn_off_001.png"},
	{U"💎", "GJ_bigDiamond_001.png"},
	{U"🔐", "GJ_bigKey_001.png"},
	{U"🔑", "GJ_bigGoldKey_001.png"},
	{U"🔮", "currencyOrbIcon_001.png"},
	{U"🔥", "fireShardBig_001.png"},
	{U"🧊", "iceShardBig_001.png"},
	{U"🧪", "poisonShardBig_001.png"},
	{U"🦇", "shadowShardBig_001.png"},
	{U"🌋", "lavaShardBig_001.png"},
	{U"🌱", "shard0201ShardBig_001.png"},
	{U"🩸", "shard0202ShardBig_001.png"},
	{U"🧲", "shard0203ShardBig_001.png"},
	{U"💡", "shard0204ShardBig_001.png"},
	{U"👻", "shard0205ShardBig_001.png"},
	{U"⬛", "gj_iconBtn_off_001.png"},
	{U"🎨", "GJ_colorBtn_001.png"},
	{U"✈️", "gj_shipBtn_off_001.png"},
	{U"⚽", "gj_ballBtn_off_001.png"},
	{U"🛸", "gj_birdBtn_off_001.png"},
	{U"↗️", "gj_dartBtn_off_001.png"},
	{U"🤖", "gj_robotBtn_off_001.png"},
	{U"🕷", "gj_spiderBtn_off_001.png"},
	{U"🌠", "player_special_02_001.png"},
	{U"🪦", "explosionIcon_01_001.png"},
	{U"🎁", "storeItemIcon_001.png"},
	{U"🛝", "gj_swingBtn_off_001.png"},
	{U"🚀", "gj_jetpackBtn_off_001.png"},
	{U"⛽", "shipfireIcon_02_001.png"},
};

class ThirdShinigamiEyePopup final : public geode::Popup {
protected:
	explicit ThirdShinigamiEyePopup(CCArray* rewards, int chestID, const Ref<CCMenuItemSpriteExtra> &button) {
		m_rewards = rewards;
		m_chestID = chestID;
		m_button = button;
	}
	CCArray* m_rewards {};
	int m_chestID;
	Ref<CCMenuItemSpriteExtra> m_button;
public:
	static ThirdShinigamiEyePopup* create(CCArray* rewards, int chestID, Ref<CCMenuItemSpriteExtra> button);
	bool init() override;

	static CCNode* generateBaseRow();
	static void addSpriteToRewardRow(UnlockType unlockType, int iconID, CCNode *ret, CCSprite *coloredSprite);

	static CCNode* generateRewardRow(int, SpecialRewardItem);
	static CCNode* generateIconRow(UnlockType, int);
	static std::string getDisplayNameUnlockType(UnlockType p0);
	static std::string getDisplayNameSpecialRewardItem(SpecialRewardItem p0);
	static IconType getCorrespondingIconType(UnlockType p0);
	static std::string getEmojiForRewardType(SpecialRewardItem p0);
	static std::string formatColor(ccColor3B color);

	void onActuallyOpenTheChest(CCObject* sender) {
		m_button->activate();
		Loader::get()->queueInMainThread([this]() { this->onClose(nullptr); });
	}
};