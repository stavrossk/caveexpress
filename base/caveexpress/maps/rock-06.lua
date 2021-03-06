function getName()
	return "Map 06"
end

function onMapLoaded()
end

function initMap()
	-- get the current map context
	local map = Map.get()
	map:addTile("tile-rock-02", 0, 0)
	map:addTile("tile-rock-03", 0, 1)
	map:addTile("tile-rock-02", 0, 2)
	map:addTile("tile-rock-03", 0, 3)
	map:addTile("tile-rock-big-01", 0, 4)
	map:addTile("tile-background-01", 0, 6)
	map:addTile("tile-ground-02", 0, 8)
	map:addTile("tile-rock-01", 0, 9)
	map:addTile("tile-rock-01", 0, 10)
	map:addTile("tile-rock-02", 0, 11)
	map:addTile("tile-rock-03", 1, 0)
	map:addTile("tile-rock-01", 1, 1)
	map:addTile("tile-rock-03", 1, 2)
	map:addTile("tile-rock-02", 1, 3)
	map:addTile("tile-background-03", 1, 6)
	map:addTile("tile-background-window-01", 1, 7)
	map:addTile("tile-ground-01", 1, 8)
	map:addTile("tile-rock-02", 1, 9)
	map:addTile("tile-rock-03", 1, 10)
	map:addTile("tile-rock-slope-right-02", 1, 11)
	map:addTile("liane-01", 1.3, 6)
	map:addTile("liane-01", 1.8, 6)
	map:addTile("tile-rock-02", 2, 0)
	map:addTile("tile-background-01", 2, 1)
	map:addTile("tile-background-02", 2, 2)
	map:addTile("tile-background-window-01", 2, 3)
	map:addTile("tile-ground-03", 2, 4)
	map:addTile("tile-rock-02", 2, 5)
	map:addTile("tile-background-02", 2, 6)
	map:addTile("tile-background-03", 2, 7)
	map:addTile("tile-ground-ledge-right-01", 2, 8)
	map:addTile("tile-background-03", 2, 9)
	map:addTile("tile-background-03", 2, 10)
	map:addTile("tile-background-03", 2, 11)
	map:addTile("liane-01", 2.3, 1)
	map:addTile("liane-01", 2.8, 1)
	map:addTile("tile-rock-03", 3, 0)
	map:addTile("tile-background-03", 3, 1)
	map:addTile("tile-background-03", 3, 2)
	map:addTile("tile-ground-03", 3, 4)
	map:addTile("tile-rock-01", 3, 5)
	map:addTile("tile-background-03", 3, 6)
	map:addTile("tile-background-02", 3, 7)
	map:addTile("tile-background-01", 3, 8)
	map:addTile("tile-background-01", 3, 9)
	map:addTile("tile-background-03", 3, 10)
	map:addTile("tile-background-03", 3, 11)
	map:addTile("liane-01", 3.2, 6)
	map:addTile("liane-01", 3.7, 1)
	map:addTile("tile-rock-01", 4, 0)
	map:addTile("tile-background-big-01", 4, 1)
	map:addTile("tile-background-cave-art-01", 4, 3)
	map:addTile("tile-ground-01", 4, 4)
	map:addTile("tile-rock-02", 4, 5)
	map:addTile("tile-background-01", 4, 6)
	map:addTile("tile-background-01", 4, 7)
	map:addTile("tile-background-01", 4, 8)
	map:addTile("tile-background-03", 4, 9)
	map:addTile("tile-background-01", 4, 10)
	map:addTile("tile-background-03", 4, 11)
	map:addTile("tile-rock-03", 5, 0)
	map:addTile("tile-background-03", 5, 3)
	map:addTile("tile-background-03", 5, 4)
	map:addTile("tile-background-03", 5, 5)
	map:addTile("tile-background-big-01", 5, 6)
	map:addTile("tile-background-03", 5, 8)
	map:addTile("tile-background-big-01", 5, 9)
	map:addTile("tile-background-03", 5, 11)
	map:addTile("liane-01", 5.4, 1)
	map:addTile("tile-rock-big-01", 6, 0)
	map:addTile("tile-background-03", 6, 2)
	map:addTile("tile-background-03", 6, 3)
	map:addTile("tile-background-01", 6, 4)
	map:addTile("tile-background-01", 6, 5)
	map:addTile("tile-background-03", 6, 8)
	map:addTile("tile-background-02", 6, 11)
	map:addTile("liane-01", 6.4, 2)
	map:addTile("tile-background-01", 7, 2)
	map:addTile("tile-background-03", 7, 3)
	map:addTile("tile-background-03", 7, 4)
	map:addTile("tile-background-01", 7, 5)
	map:addTile("tile-background-03", 7, 6)
	map:addTile("tile-background-03", 7, 7)
	map:addTile("tile-background-01", 7, 8)
	map:addTile("tile-background-big-01", 7, 9)
	map:addTile("tile-background-02", 7, 11)
	map:addTile("liane-01", 7.5, 2)
	map:addTile("tile-rock-03", 8, 0)
	map:addTile("tile-rock-big-01", 8, 1)
	map:addTile("tile-rock-03", 8, 3)
	map:addTile("tile-rock-slope-left-02", 8, 4)
	map:addTile("tile-background-01", 8, 5)
	map:addTile("tile-background-03", 8, 6)
	map:addTile("tile-background-01", 8, 7)
	map:addTile("tile-background-02", 8, 8)
	map:addTile("tile-background-02", 8, 11)
	map:addTile("tile-rock-02", 9, 0)
	map:addTile("tile-rock-big-01", 9, 3)
	map:addTile("tile-rock-01", 9, 5)
	map:addTile("tile-rock-01", 9, 6)
	map:addTile("tile-rock-slope-left-02", 9, 7)
	map:addTile("tile-background-03", 9, 8)
	map:addTile("tile-background-01", 9, 9)
	map:addTile("tile-background-big-01", 9, 10)
	map:addTile("tile-rock-02", 10, 0)
	map:addTile("tile-rock-03", 10, 1)
	map:addTile("tile-rock-02", 10, 2)
	map:addTile("tile-rock-02", 10, 5)
	map:addTile("tile-rock-01", 10, 6)
	map:addTile("tile-rock-slope-right-02", 10, 7)
	map:addTile("tile-background-01", 10, 8)
	map:addTile("tile-background-02", 10, 9)
	map:addTile("tile-rock-02", 11, 0)
	map:addTile("tile-rock-02", 11, 1)
	map:addTile("tile-rock-03", 11, 2)
	map:addTile("tile-rock-slope-right-02", 11, 3)
	map:addTile("tile-background-01", 11, 4)
	map:addTile("tile-background-01", 11, 5)
	map:addTile("tile-background-01", 11, 6)
	map:addTile("tile-background-01", 11, 7)
	map:addTile("tile-background-01", 11, 8)
	map:addTile("tile-background-cave-art-01", 11, 9)
	map:addTile("tile-background-03", 11, 10)
	map:addTile("tile-background-03", 11, 11)
	map:addTile("tile-background-03", 12, 0)
	map:addTile("tile-background-03", 12, 1)
	map:addTile("tile-background-03", 12, 2)
	map:addTile("tile-background-02", 12, 3)
	map:addTile("tile-background-03", 12, 4)
	map:addTile("tile-background-03", 12, 5)
	map:addTile("tile-background-03", 12, 6)
	map:addTile("tile-background-01", 12, 7)
	map:addTile("tile-background-01", 12, 8)
	map:addTile("tile-background-02", 12, 9)
	map:addTile("tile-background-03", 12, 10)
	map:addTile("tile-background-02", 12, 11)
	map:addTile("tile-background-03", 13, 0)
	map:addTile("tile-background-big-01", 13, 1)
	map:addTile("tile-background-cave-art-01", 13, 3)
	map:addTile("tile-background-03", 13, 4)
	map:addTile("tile-ground-04", 13, 5)
	map:addTile("tile-rock-03", 13, 6)
	map:addTile("tile-rock-01", 13, 7)
	map:addTile("tile-rock-03", 13, 8)
	map:addTile("tile-rock-slope-left-02", 13, 9)
	map:addTile("tile-background-03", 13, 10)
	map:addTile("tile-background-03", 13, 11)
	map:addTile("tile-background-02", 14, 0)
	map:addTile("tile-background-01", 14, 3)
	map:addTile("tile-background-03", 14, 4)
	map:addTile("tile-background-03", 14, 5)
	map:addTile("tile-background-03", 14, 6)
	map:addTile("tile-background-01", 14, 7)
	map:addTile("tile-packagetarget-rock-01-idle", 14, 8)
	map:addTile("tile-rock-big-01", 14, 9)
	map:addTile("tile-rock-01", 14, 11)
	map:addTile("tile-background-02", 15, 0)
	map:addTile("tile-background-03", 15, 1)
	map:addTile("tile-background-02", 15, 2)
	map:addTile("tile-background-03", 15, 3)
	map:addTile("tile-background-03", 15, 4)
	map:addTile("tile-background-03", 15, 5)
	map:addTile("tile-background-02", 15, 6)
	map:addTile("tile-background-01", 15, 7)
	map:addTile("tile-ground-04", 15, 8)
	map:addTile("tile-rock-01", 15, 11)

	map:addCave("tile-cave-02", 0, 7, "none", 1000)
	map:addCave("tile-cave-01", 3, 3, "none", 1000)

	map:addEmitter("tree", 12.5, 3, 1, 0, "")

	map:setSetting("width", "16")
	map:setSetting("height", "12")
	map:setSetting("fishnpc", "true")
	map:setSetting("flyingnpc", "false")
	map:setSetting("gravity", "9.81")
	if isTouch() then
		map:setSetting("packagetransfercount", "1")
	else
		map:setSetting("packagetransfercount", "3")
	end
	map:addStartPosition("6", "5")
	map:setSetting("points", "100")
	map:setSetting("referencetime", "40")
	map:setSetting("theme", "rock")
	map:setSetting("waterchangespeed", "0")
	map:setSetting("waterfallingdelay", "0")
	map:setSetting("waterheight", "3.4")
	map:setSetting("waterrisingdelay", "0")
	map:setSetting("wind", "0.0")
end
