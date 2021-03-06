function getName()
	return "Map 06"
end

function onMapLoaded()
end

function initMap()
	-- get the current map context
	local map = Map.get()
	map:addTile("tile-background-ice-07", 0, 0)
	map:addTile("tile-background-ice-07", 0, 1)
	map:addTile("tile-background-ice-03", 0, 2)
	map:addTile("tile-ground-ice-01", 0, 3)
	map:addTile("tile-rock-ice-02", 0, 4)
	map:addTile("tile-rock-ice-02", 0, 5)
	map:addTile("tile-rock-ice-03", 0, 6)
	map:addTile("tile-rock-ice-big-01", 0, 7)
	map:addTile("tile-rock-ice-03", 0, 9)
	map:addTile("tile-rock-ice-02", 0, 10)
	map:addTile("tile-rock-ice-02", 0, 11)
	map:addTile("tile-background-ice-03", 1, 0)
	map:addTile("tile-background-ice-07", 1, 1)
	map:addTile("tile-background-ice-03", 1, 2)
	map:addTile("tile-ground-ice-01", 1, 3)
	map:addTile("tile-rock-ice-02", 1, 4)
	map:addTile("tile-rock-ice-big-01", 1, 5)
	map:addTile("tile-rock-ice-02", 1, 9)
	map:addTile("tile-rock-ice-big-01", 1, 10)
	map:addTile("tile-background-ice-06", 2, 0)
	map:addTile("tile-background-ice-04", 2, 1)
	map:addTile("tile-background-ice-03", 2, 2)
	map:addTile("tile-rock-slope-ice-right-01", 2, 3)
	map:addTile("tile-rock-ice-02", 2, 4)
	map:addTile("tile-rock-ice-03", 2, 7)
	map:addTile("tile-rock-ice-big-01", 2, 8)
	map:addTile("tile-background-ice-04", 3, 0)
	map:addTile("tile-background-ice-02", 3, 1)
	map:addTile("tile-background-ice-01", 3, 2)
	map:addTile("tile-rock-slope-ice-left-02", 3, 3)
	map:addTile("tile-rock-slope-ice-right-01", 3, 4)
	map:addTile("tile-rock-ice-03", 3, 5)
	map:addTile("tile-rock-ice-big-01", 3, 6)
	map:addTile("tile-rock-ice-02", 3, 10)
	map:addTile("tile-rock-ice-01", 3, 11)
	map:addTile("tile-background-ice-05", 4, 0)
	map:addTile("tile-background-ice-05", 4, 1)
	map:addTile("tile-background-ice-03", 4, 2)
	map:addTile("tile-ground-ice-03", 4, 3)
	map:addTile("tile-background-ice-04", 4, 4)
	map:addTile("tile-packagetarget-ice-01-idle", 4, 5)
	map:addTile("tile-rock-ice-big-01", 4, 8)
	map:addTile("tile-rock-ice-01", 4, 10)
	map:addTile("tile-rock-ice-02", 4, 11)
	map:addTile("tile-background-ice-07", 5, 0)
	map:addTile("tile-background-ice-06", 5, 1)
	map:addTile("tile-background-ice-04", 5, 2)
	map:addTile("tile-ground-ice-04", 5, 3)
	map:addTile("tile-rock-ice-03", 5, 4)
	map:addTile("tile-rock-ice-03", 5, 5)
	map:addTile("tile-rock-ice-big-01", 5, 6)
	map:addTile("tile-ground-ledge-ice-right-02", 5, 10)
	map:addTile("tile-background-ice-04", 5, 11)
	map:addTile("tile-background-ice-02", 6, 0)
	map:addTile("tile-background-ice-cave-art-01", 6, 1)
	map:addTile("tile-background-ice-07", 6, 2)
	map:addTile("tile-ground-ice-03", 6, 3)
	map:addTile("tile-rock-ice-02", 6, 4)
	map:addTile("tile-rock-ice-01", 6, 5)
	map:addTile("tile-ground-ledge-ice-right-01", 6, 8)
	map:addTile("tile-background-ice-03", 6, 9)
	map:addTile("tile-background-ice-01", 6, 10)
	map:addTile("tile-background-ice-04", 6, 11)
	map:addTile("tile-background-ice-01", 7, 0)
	map:addTile("tile-background-ice-07", 7, 1)
	map:addTile("tile-background-ice-05", 7, 2)
	map:addTile("tile-ground-ice-03", 7, 3)
	map:addTile("tile-ground-ledge-ice-right-02", 7, 4)
	map:addTile("tile-background-ice-04", 7, 5)
	map:addTile("tile-background-ice-big-01", 7, 6)
	map:addTile("tile-background-ice-03", 7, 8)
	map:addTile("bridge-wall-ice-left-01", 7, 8)
	map:addTile("tile-background-ice-03", 7, 9)
	map:addTile("tile-background-ice-04", 7, 10)
	map:addTile("tile-background-ice-04", 7, 11)
	map:addTile("tile-background-ice-big-01", 8, 0)
	map:addTile("tile-background-ice-03", 8, 2)
	map:addTile("tile-ground-ledge-ice-right-01", 8, 3)
	map:addTile("tile-background-ice-03", 8, 4)
	map:addTile("tile-background-ice-05", 8, 5)
	map:addTile("tile-background-ice-07", 8, 8)
	map:addTile("bridge-plank-ice-01", 8, 8)
	map:addTile("tile-background-ice-cave-art-01", 8, 9)
	map:addTile("tile-background-ice-05", 8, 10)
	map:addTile("tile-background-ice-04", 8, 11)
	map:addTile("tile-background-ice-06", 9, 2)
	map:addTile("tile-background-ice-03", 9, 3)
	map:addTile("tile-background-ice-cave-art-01", 9, 4)
	map:addTile("tile-background-ice-04", 9, 5)
	map:addTile("tile-background-ice-big-01", 9, 6)
	map:addTile("tile-background-ice-01", 9, 8)
	map:addTile("bridge-wall-ice-right-01", 9, 8)
	map:addTile("tile-background-ice-05", 9, 9)
	map:addTile("tile-background-ice-05", 9, 10)
	map:addTile("tile-background-ice-04", 9, 11)
	map:addTile("tile-background-ice-06", 10, 0)
	map:addTile("tile-background-ice-07", 10, 1)
	map:addTile("tile-background-ice-02", 10, 2)
	map:addTile("tile-background-ice-06", 10, 3)
	map:addTile("tile-background-ice-07", 10, 4)
	map:addTile("tile-background-ice-04", 10, 5)
	map:addTile("tile-ground-ice-01", 10, 8)
	map:addTile("tile-ground-ice-01", 10, 9)
	map:addTile("tile-rock-ice-big-01", 10, 10)
	map:addTile("tile-ground-ledge-ice-left-02", 11, 0)
	map:addTile("tile-background-ice-01", 11, 1)
	map:addTile("tile-background-ice-04", 11, 2)
	map:addTile("tile-background-ice-06", 11, 3)
	map:addTile("tile-background-ice-06", 11, 4)
	map:addTile("tile-background-ice-02", 11, 5)
	map:addTile("tile-background-ice-03", 11, 6)
	map:addTile("tile-ground-ice-04", 11, 8)
	map:addTile("tile-rock-ice-02", 11, 9)
	map:addTile("tile-rock-ice-big-01", 12, 0)
	map:addTile("tile-ground-ledge-ice-left-01", 12, 2)
	map:addTile("tile-background-ice-05", 12, 3)
	map:addTile("tile-background-ice-07", 12, 4)
	map:addTile("tile-background-ice-07", 12, 5)
	map:addTile("tile-background-ice-03", 12, 6)
	map:addTile("tile-background-ice-window-02", 12, 7)
	map:addTile("tile-ground-ice-02", 12, 8)
	map:addTile("tile-rock-ice-01", 12, 9)
	map:addTile("tile-rock-ice-01", 12, 10)
	map:addTile("tile-rock-ice-02", 12, 11)
	map:addTile("tile-rock-ice-03", 13, 2)
	map:addTile("tile-ground-ledge-ice-left-02", 13, 3)
	map:addTile("tile-background-ice-07", 13, 4)
	map:addTile("tile-background-ice-05", 13, 5)
	map:addTile("tile-background-ice-07", 13, 6)
	map:addTile("tile-background-ice-02", 13, 7)
	map:addTile("tile-ground-ice-04", 13, 9)
	map:addTile("tile-rock-ice-03", 13, 10)
	map:addTile("tile-rock-ice-03", 13, 11)
	map:addTile("tile-rock-ice-01", 14, 0)
	map:addTile("tile-rock-ice-01", 14, 1)
	map:addTile("tile-rock-ice-03", 14, 2)
	map:addTile("tile-rock-ice-02", 14, 3)
	map:addTile("tile-ground-ledge-ice-left-02", 14, 4)
	map:addTile("tile-background-ice-03", 14, 5)
	map:addTile("tile-background-ice-05", 14, 6)
	map:addTile("tile-background-ice-06", 14, 7)
	map:addTile("tile-background-ice-window-01", 14, 8)
	map:addTile("tile-ground-ice-04", 14, 9)
	map:addTile("tile-rock-ice-big-01", 14, 10)
	map:addTile("tile-rock-ice-03", 15, 0)
	map:addTile("tile-rock-ice-02", 15, 1)
	map:addTile("tile-rock-ice-01", 15, 2)
	map:addTile("tile-rock-ice-03", 15, 3)
	map:addTile("tile-ground-ledge-ice-left-01", 15, 4)
	map:addTile("tile-background-ice-04", 15, 5)
	map:addTile("tile-background-ice-04", 15, 6)
	map:addTile("tile-background-ice-01", 15, 7)
	map:addTile("tile-background-ice-04", 15, 8)
	map:addTile("tile-ground-ice-02", 15, 9)

	map:addCave("tile-cave-ice-01", 11, 7, "none", 5000)
	map:addCave("tile-cave-ice-01", 13, 8, "none", 5000)

	map:addEmitter("npc-mammut", 3, 2, 1, 0, "")

	map:setSetting("fishnpc", "false")
	map:setSetting("flyingnpc", "true")
	map:setSetting("gravity", "9.81")
	map:setSetting("height", "12")
	map:setSetting("packagetransfercount", "3")
	map:addStartPosition("1", "2")
	map:setSetting("points", "100")
	map:setSetting("referencetime", "30")
	map:setSetting("theme", "ice")
	map:setSetting("waterheight", "1")
	map:setSetting("waterchangespeed", "0")
	map:setSetting("waterrisingdelay", "0")
	map:setSetting("width", "16")
	map:setSetting("wind", "0.0")
end
