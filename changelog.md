# ThirdShinigamiEye Changelog
## v1.0.4
- Port to Geode v6.0.0-beta.1 and GD 2.2091 on all platforms.
- Gold chest preview now uses `GameStatsManager::getNextGoldChestID`, which covers gold chests 6001-6030 (previously capped at 6020).
- iOS: special chest and gold chest previews are disabled for now because the GD 2.2091 bindings have no iOS addresses for the functions they need.
## v1.0.3
- Port to Geode v6.0.0-alpha.1 and GD 2.2091 (Windows only).
- Replace the AdvancedLabel dependency with the built-in `geode::Label`.
## v1.0.2
- Port to GD 2.2081.
## v1.0.1
- Meaningless mod metadata update. Move along.
## v1.0.0
- Initial release (on GitHub).