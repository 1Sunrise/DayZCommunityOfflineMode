# All rights reserved by @Arkensor 
# Arkensor's main page - https://github.com/Arkensor



# DayZCommunityOfflineMode CUSTOM PACK by Sunrise
This is a custom pack for DayZCommunityOfflineMode that I created to make the game more enjoyable.

```Custom character and weapons```

The pack includes a custom character with a starting inventory of clothes and weapons.

```Disabled auto-run```
Auto-run on key "X" was disabled because it conflicted with the game's shooting mode toggle function. This made it difficult to switch between firing modes while running. This parameter can be restored if desired.

```Disabled item spawn economy```
The item spawn economy was disabled because it was taxing on the system and caused FPS drops. This makes the game run more smoothly.

```Code```
Slightly improved the code and appeared hints. That is, now you can create your own custom character and also weapons to him.

```Unlimited Stamina```
For more convenience in the game I created a mod for infinite stamina. Now you can endlessly jump, run, climb over obstacles, hold your breath in the sight. Etc.

# Installation
Download [this](https://github.com/1Sunrise/DayZCommunityOfflineMode/releases/download/2.0/Missions.rar) rar archive.  
Make sure you are on the latest `STABLE` or `EXPERIMENTAL` version of the game.

Place the ```Missions``` and ```@MOD``` folders inside your DayZ game directory (```For example: C:\Program Files (x86)\Steam\steamapps\common\DayZ```).  

Now you can start the script ```DayZ/Missions/DayZCommunityOfflineMode.ChernarusPlus/DayZCommunityOfflineMode.bat``` to start the game. You will be loaded directly into the offline mode.  
Or add the following start parameter to your game: ```-mission=.\Missions\DayZCommunityOfflineMode.ChernarusPlus```

To uninstall this mod, simple delete all downloaded files, and rename your .disabled folders back to their original name.   
You might delete your whole ```Missions``` folder and validate your game files via steam to get the original DayZ files back.

# Controls
* Y (Z for QWERTZ-Keyboard) - Open the COM toolbar menu.
* X - Toggle Autojog/walk/run ```(Disactivated)```
* X + SHIFT - Enable Autorun (Just X to disable it again)
* X + CTRL - Enable Autowalk (Just X to disable it again)
* END - Teleport at the position you are looking at
* O - Spawn a random infected (Zombies)
* O + CTRL - Spawn a wolf (Agressive and will fight both players and infected)
* O + SHIFT - Spawn a random animal
* R - Reload the weapon and refill the ammo (Infinite ammo)
* P - Display your current position in the chat and print it to your logfiles (See logfiles section for their location)
* B - Toggle debug monitor
* INSERT - Toggle free camera. This teleports your player to the position you looked at when turning it off

# Object Editor Controls
* Click objects to select them.  
* Click and drag objects to move them.
* Click on nothing to deselect the current object.
* Middle Click to snap to ground (Might not be accurate)
* Spawn in new items using the object spawner menu that can be found in the toolbar.
* You can either enter values on the onject editor gui or hover above the value with your mouse and use the scroll wheel to in-/decrease them.

# Loot and infected spawn
Since I turned off the spavn items and zombies on the map, the fps will be more. But maybe some people will want this setting back. To do this:
* Go to the folder with the game
* Find the ```Missions``` folder.
* In the ```Missions``` folder go to the ```DayZCommunityOfflineMode.ChernarusPlus``` folder.
* In the ```DayZCommunityOfflineMode.ChernarusPlus``` folder go to the ``core`` folder.
* In the ```core``` folder go to the file called ```CommunityOfflineClient.c```.
* Open this file with Notepad and see the parameter ```protected bool HIVE_ENABLED = false;```. Change it to ```protected bool HIVE_ENABLED = true;```. Save the changes. Play.