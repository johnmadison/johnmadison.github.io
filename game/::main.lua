local AdvTiledLoader = require("AdvTiledLoader")

function love.load()

   love.graphics.setNewFont(12)
   love.graphics.setColor(0,0,0)
   love.graphics.setBackgroundColor(0,255,25)
   
   AdvTiledLoader.path = "maps/"
   map = AdvTiledLoader:load("map.tmx")
   map:setDrawRange(0,0, map.width * map.tileWidth, map.height * map.tileHeight)
end

function love.draw()
	map:draw()
end

function love.update(dt)
end