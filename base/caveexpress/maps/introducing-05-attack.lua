function getName()
	return "Attack"
end

function onMapLoaded()
end

function initMap()
	-- get the current map context
	local map = Map.get()
	map:addTile("tile-rock-big-01", 0, 0)
	map:addTile("tile-rock-03", 0, 2)
	map:addTile("tile-rock-slope-right-02", 0, 3)
	map:addTile("tile-background-04", 0, 4)
	map:addTile("tile-ground-ledge-right-01", 0, 5)
	map:addTile("tile-background-04", 0, 6)
	map:addTile("tile-rock-01", 0, 7)
	map:addTile("tile-rock-big-01", 0, 8)
	map:addTile("tile-rock-03", 0, 10)
	map:addTile("tile-rock-01", 1, 2)
	map:addTile("tile-background-04", 1, 3)
	map:addTile("tile-background-03", 1, 4)
	map:addTile("tile-ground-ledge-left-01", 1, 5)
	map:addTile("tile-background-03", 1, 6)
	map:addTile("tile-rock-03", 1, 7)
	map:addTile("tile-rock-01", 1, 10)
	map:addTile("tile-rock-02", 2, 0)
	map:addTile("tile-rock-01", 2, 1)
	map:addTile("tile-rock-01", 2, 2)
	map:addTile("tile-background-03", 2, 3)
	map:addTile("tile-background-02", 2, 4)
	map:addTile("tile-ground-ledge-right-01", 2, 5)
	map:addTile("tile-background-03", 2, 6)
	map:addTile("tile-ground-01", 2, 7)
	map:addTile("tile-rock-01", 2, 8)
	map:addTile("tile-rock-slope-right-02", 2, 9)
	map:addTile("tile-background-04", 2, 10)
	map:addTile("tile-rock-03", 3, 0)
	map:addTile("tile-rock-01", 3, 1)
	map:addTile("tile-rock-slope-right-02", 3, 2)
	map:addTile("tile-background-04", 3, 3)
	map:addTile("tile-background-01", 3, 4)
	map:addTile("tile-ground-ledge-right-02", 3, 5)
	map:addTile("tile-background-04", 3, 6)
	map:addTile("tile-background-02", 3, 7)
	map:addTile("bridge-wall-left-01", 3, 7)
	map:addTile("tile-background-04", 3, 8)
	map:addTile("tile-background-04", 3, 9)
	map:addTile("tile-background-04", 3, 10)
	map:addTile("tile-rock-01", 4, 0)
	map:addTile("tile-rock-03", 4, 1)
	map:addTile("tile-background-04", 4, 2)
	map:addTile("tile-background-03", 4, 3)
	map:addTile("tile-background-03", 4, 4)
	map:addTile("tile-background-04", 4, 5)
	map:addTile("tile-background-04", 4, 6)
	map:addTile("tile-background-02", 4, 7)
	map:addTile("bridge-wall-right-01", 4, 7)
	map:addTile("tile-background-04", 4, 8)
	map:addTile("tile-background-04", 4, 9)
	map:addTile("tile-background-04", 4, 10)
	map:addTile("tile-rock-03", 5, 0)
	map:addTile("tile-rock-slope-right-02", 5, 1)
	map:addTile("tile-background-01", 5, 2)
	map:addTile("tile-background-04", 5, 3)
	map:addTile("tile-background-03", 5, 4)
	map:addTile("tile-background-04", 5, 5)
	map:addTile("tile-background-04", 5, 6)
	map:addTile("tile-ground-03", 5, 7)
	map:addTile("tile-rock-03", 5, 8)
	map:addTile("tile-rock-01", 5, 9)
	map:addTile("tile-rock-03", 5, 10)
	map:addTile("tile-rock-slope-right-02", 6, 0)
	map:addTile("tile-background-02", 6, 1)
	map:addTile("tile-background-01", 6, 2)
	map:addTile("tile-background-03", 6, 3)
	map:addTile("tile-background-04", 6, 4)
	map:addTile("tile-background-04", 6, 5)
	map:addTile("tile-background-04", 6, 6)
	map:addTile("tile-ground-04", 6, 7)
	map:addTile("tile-rock-big-01", 6, 8)
	map:addTile("tile-rock-01", 6, 10)
	map:addTile("tile-background-04", 7, 0)
	map:addTile("tile-background-02", 7, 1)
	map:addTile("tile-background-04", 7, 2)
	map:addTile("tile-background-03", 7, 3)
	map:addTile("tile-background-04", 7, 4)
	map:addTile("tile-background-04", 7, 5)
	map:addTile("tile-background-03", 7, 6)
	map:addTile("tile-packagetarget-rock-01-idle", 7, 7)
	map:addTile("tile-rock-02", 7, 10)
	map:addTile("tile-background-02", 8, 0)
	map:addTile("tile-background-02", 8, 1)
	map:addTile("tile-background-04", 8, 2)
	map:addTile("tile-background-01", 8, 3)
	map:addTile("tile-rock-slope-left-01", 8, 4)
	map:addTile("tile-background-04", 8, 5)
	map:addTile("tile-background-04", 8, 6)
	map:addTile("tile-ground-01", 8, 7)
	map:addTile("tile-rock-03", 8, 8)
	map:addTile("tile-rock-01", 8, 9)
	map:addTile("tile-rock-01", 8, 10)
	map:addTile("tile-background-03", 9, 0)
	map:addTile("tile-background-02", 9, 1)
	map:addTile("tile-background-04", 9, 2)
	map:addTile("tile-background-03", 9, 3)
	map:addTile("tile-ground-01", 9, 4)
	map:addTile("tile-background-03", 9, 5)
	map:addTile("tile-background-04", 9, 6)
	map:addTile("tile-ground-02", 9, 7)
	map:addTile("tile-rock-01", 9, 8)
	map:addTile("tile-rock-big-01", 9, 9)
	map:addTile("tile-rock-slope-left-02", 10, 0)
	map:addTile("tile-background-02", 10, 1)
	map:addTile("tile-background-02", 10, 2)
	map:addTile("tile-background-04", 10, 3)
	map:addTile("tile-ground-02", 10, 4)
	map:addTile("tile-background-04", 10, 5)
	map:addTile("tile-background-cave-art-01", 10, 6)
	map:addTile("tile-ground-03", 10, 7)
	map:addTile("tile-rock-03", 10, 8)
	map:addTile("tile-rock-01", 11, 0)
	map:addTile("tile-rock-slope-left-02", 11, 1)
	map:addTile("tile-background-02", 11, 2)
	map:addTile("tile-background-01", 11, 3)
	map:addTile("tile-ground-01", 11, 4)
	map:addTile("tile-background-04", 11, 5)
	map:addTile("tile-background-cave-art-01", 11, 6)
	map:addTile("tile-ground-01", 11, 7)
	map:addTile("tile-rock-02", 11, 8)
	map:addTile("tile-rock-03", 11, 9)
	map:addTile("tile-rock-01", 11, 10)
	map:addTile("tile-rock-02", 12, 0)
	map:addTile("tile-rock-03", 12, 1)
	map:addTile("tile-background-03", 12, 2)
	map:addTile("tile-background-02", 12, 3)
	map:addTile("tile-ground-02", 12, 4)
	map:addTile("tile-background-02", 12, 5)
	map:addTile("tile-background-04", 12, 6)
	map:addTile("tile-ground-03", 12, 7)
	map:addTile("tile-rock-01", 12, 8)
	map:addTile("tile-rock-01", 12, 9)
	map:addTile("tile-rock-03", 12, 10)
	map:addTile("tile-rock-big-01", 13, 0)
	map:addTile("tile-rock-slope-left-02", 13, 2)
	map:addTile("tile-background-04", 13, 3)
	map:addTile("tile-ground-01", 13, 4)
	map:addTile("tile-background-02", 13, 5)
	map:addTile("tile-background-03", 13, 6)
	map:addTile("tile-ground-02", 13, 7)
	map:addTile("tile-rock-big-01", 13, 8)
	map:addTile("tile-rock-02", 13, 10)
	map:addTile("tile-rock-01", 14, 2)
	map:addTile("tile-rock-03", 14, 3)
	map:addTile("tile-rock-01", 14, 4)
	map:addTile("tile-rock-03", 14, 5)
	map:addTile("tile-rock-03", 14, 6)
	map:addTile("tile-rock-02", 14, 7)
	map:addTile("tile-rock-01", 14, 10)

	map:addEmitter("item-stone", 4, 2, 1, 2500, "")
	map:addEmitter("tree", 5, 5, 1, 0, "")
	map:addEmitter("item-package", 7.5, 2, 1, 4000, "")
	map:addEmitter("npc-walking", 10, 6, 1, 0, "right=false")

	map:setSetting("width", "15")
	map:setSetting("height", "11")
	map:setSetting("fishnpc", "false")
	map:setSetting("flyingnpc", "false")
	map:setSetting("gravity", "9.81")
	map:setSetting("introwindow", "introattack")
	map:setSetting("packagetransfercount", "1")
	map:addStartPosition("0", "6")
	map:setSetting("points", "100")
	map:setSetting("referencetime", "20")
	map:setSetting("sideborderfail", "false")
	map:setSetting("theme", "rock")
	map:setSetting("tutorial", "true")
	map:setSetting("waterchangespeed", "0")
	map:setSetting("waterfallingdelay", "0")
	map:setSetting("waterheight", "0.5")
	map:setSetting("waterrisingdelay", "0")
	map:setSetting("wind", "0")
end
