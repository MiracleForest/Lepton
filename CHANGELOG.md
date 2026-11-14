# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.0] - 2026-11-14

First release: small vanilla+ modules for Minecraft Bedrock Edition, for dedicated servers and local worlds. Every
module can be turned off in `config/<unit>.json`. Players without the client mod get the blocks, items and mobs
through the resource pack, and forms, vanilla container screens or `/lepton` commands in place of the client mod's
screens. Bedrock limits are listed in [docs/SPEC.md §8](docs/SPEC.md#8-not-ported).

### Added

- Support for Minecraft 1.26.60 (LeviLamina 26.60.x, the default) and 1.26.51 (LeviLamina 26.51.x), each as a lip
  variant (`26_60`, `26_51`) with a server and a client build. Downloads: `lepton-server-win-x64-ll26.60.zip`,
  `lepton-client-win-x64-ll26.60.zip`, `lepton-server-win-x64-ll26.51.zip` and `lepton-client-win-x64-ll26.51.zip`.
- **Automation**: chains that connect blocks for pistons, iron rods, pistons that move block entities with a
  configurable push limit, gravisand, metal buttons, the obsidian pressure plate, the redstone randomizer, the ender
  watcher, dispensers that place blocks and plant seeds, the chute and the feeding trough.
- **Building**: vertical slabs, stone and brick variants, raw metal bricks, sturdy stone, lamps, palette blocks
  (shingles, framed glass, gold bars, industrial and Japanese palettes, thatch, grates), wood variants (vertical
  planks, bookshelves, ladders, posts, hedges, leaf carpets, hollow logs), compressed blocks, stools, rope, more potted
  plants, variant chests and furnaces, crystal lamps and glass item frames.
- **Management**: inventory sorting, easy transferring, chest searching, the hotbar changer, tool restock, quick
  armour swapping, expanded item interactions and item sharing.
- **Tools**: pickarangs, torch arrows, parrot eggs, skull pikes, bottled clouds, slime in a bucket, ancient tomes,
  colour runes, beacon redirection, the abacus, pathfinder maps, ambience and music discs, the trowel and the seed
  pouch.
- **Oddities**: matrix enchanting, the backpack, the Totem of Holding, copper pipes, crates, magnets and the tiny
  potato.
- **Mobs**: crabs, shibas, oretoises, stonelings, the Forgotten, foxhounds and wraiths.
- **Tweaks**: simple and hoe harvesting, reacharound placing, rotation lock, enhanced ladders, emotes, patting the
  dogs, double doors, better sponges, utility recipes, map washing, dyeable item frames, more banner layers and many
  smaller mob, farming and item tweaks.
- **World**: azalea, trumpet and ashen woods, new stones and permafrost, big stone clusters, corundum, fairy rings,
  fallen logs, monster boxes, the Glimmering Weald, Nether obsidian spikes, chorus vegetation and spiral spires.
- **Client** (needs the client mod): usage ticker, elytra indicator, improved tooltips, auto-walk and back-button
  keybinds, long-range pick block, greener grass, variant animal skins, bucket icons, soul candles and camera mode.
- **Experimental** (off by default): variant selector and hammer, game nerfs, spawner replacer, villager trade
  rerolling, vanilla stone clusters, adjustable chat, narrator readout and climate control remover.
- A configuration file per unit, reloaded with `/lepton reload`; the `/lepton` command with its sub-commands; English
  and Simplified Chinese translations; a companion protocol between the client mod and the server.

### Known issues

- On Minecraft 1.26.60, screens that Lepton shows as a dispenser or a double chest (the feeding trough's 3x3 menu,
  double variant chests) open as a single chest screen; the slots past the first 27 of a double variant chest are
  kept but not shown. 1.26.51 is not affected.
- On Minecraft 1.26.60, the `disableMushroomBlockRemoval` nerf has no effect.

[Unreleased]: https://github.com/MiracleForest/Lepton/compare/v0.1.0...HEAD
[0.1.0]: https://github.com/MiracleForest/Lepton/releases/tag/v0.1.0
