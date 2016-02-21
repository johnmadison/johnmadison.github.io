local AdvTiledLoader = require("AdvTiledLoader.Loader")
require("camera")
local anim8 = require 'anim8'
local image, animation







function love.load()


--HERE WE LOAD SPRITES--

	attackimage = love.graphics.newImage('sprites/attack.png')
  	local g = anim8.newGrid(34, 34, attackimage:getWidth(), attackimage:getHeight())
  	animation = anim8.newAnimation(g('1-11',1), 0.05)
  	
  	leftattackimage = love.graphics.newImage('sprites/cupattackleft.png')
  	local h = anim8.newGrid(34, 34, leftattackimage:getWidth(), leftattackimage:getHeight())
  	animation = anim8.newAnimation(g('1-11',1), 0.05)
  	
  	runimage = love.graphics.newImage('sprites/cuprun.png')
  	local i = anim8.newGrid(34, 34, runimage:getWidth(), runimage:getHeight())
  	animation = anim8.newAnimation(g('1-11',1), 0.05)
  	
  	leftrunimage = love.graphics.newImage('sprites/cuprunleft.png')
  	local j = anim8.newGrid(34, 34, leftrunimage:getWidth(), runimage:getHeight())
  	animation = anim8.newAnimation(g('1-11',1), 0.05)
  
  	carlton = love.graphics.newImage('sprites/carlton.png')
  	local k = anim8.newGrid(34, 34, carlton:getWidth(), carlton:getHeight())
  	carltonanimation = anim8.newAnimation(h('1-11', 1), 2)
  	
	love.graphics.setBackgroundColor( 225, 225, 255 )

	AdvTiledLoader.path = "maps/"
	map = AdvTiledLoader.load("maptest.tmx")
	map:setDrawRange(0, 0, map.width * map.tileWidth, map.height * map.tileHeight)
	
	camera:setBounds(0, 0, map.width * map.tileWidth - love.graphics.getWidth(), map.height * map.tileHeight - love.graphics.getHeight() )

	world = 	{
				gravity = 1200,
				ground = 512,
				}
				
	player = 	{
				x = 256,
				y = 256,
				x_vel = 0,
				y_vel = 0,
				jump_vel = -700,
				speed = 300,
				flySpeed = 600,
				state = "",
				h = 32,
				w = 32,
				standing = false,
				stand = love.graphics.newImage("sprites/cupstanding.png")
				
				}
	function player:jump()
		if self.standing then
			self.y_vel = self.jump_vel
			self.standing = false
			player.image = love.graphics.newImage("sprites/cupjump.png")
			
		end
	end
	
	function player:attack()
		
		player.image =  love.graphics.newImage("sprites/punch.png")
		
		
	end
	
	
	
	function player:right()
		self.x_vel = self.speed
	end 
	
	function player:left()
		self.x_vel = -1 * (self.speed)
	end
	
	function player:stop()
		self.x_vel = 0
	end
	
	function player:collide(event)
	
		if event == "floor" then
			self.y_vel = 0
			self.standing = true
		end
		
		if event == "cieling" then
			self.y_vel = 0
		end
	end
	

	function player:update(dt)
		local halfX = self.w / 2
		local halfY = self.h / 2
		
		self.y_vel = self.y_vel + (world.gravity * dt)
		
		self.x_vel = math.clamp(self.x_vel, -self.speed, self.speed)
		self.y_vel = math.clamp(self.y_vel, -self.flySpeed, self.flySpeed)
		
		local nextY = self.y + (self.y_vel*dt)
		if self.y_vel < 0 then
			if not (self:isColliding(map, self.x - halfX, nextY - halfY))
				and not (self:isColliding(map, self.x + halfX - 1, nextY - halfY)) then
				self.y = nextY
				self.standing = false
			else
				self.y = nextY + map.tileHeight - ((nextY - halfY) % map.tileHeight)
				self:collide("cieling")
			end
		end
		if self.y_vel > 0 then
			if not (self:isColliding(map, self.x-halfX, nextY + halfY))
				and not(self:isColliding(map, self.x + halfX - 1, nextY + halfY)) then
					self.y = nextY
					self.standing = false
			else
				self.y = nextY - ((nextY + halfY) % map.tileHeight)
				self:collide("floor")
			end
		end
		
		local nextX = self.x + (self.x_vel * dt)
		if self.x_vel > 0 then
			if not(self:isColliding(map, nextX + halfX, self.y - halfY))
				and not(self:isColliding(map, nextX + halfX, self.y + halfY - 1)) then
				self.x = nextX
			else
				self.x = nextX - ((nextX + halfX) % map.tileWidth)
			end
		elseif self.x_vel < 0 then
			if not(self:isColliding(map, nextX - halfX, self.y - halfY))
				and not(self:isColliding(map, nextX - halfX, self.y + halfY - 1)) then
				self.x = nextX
			else
				self.x = nextX + map.tileWidth - ((nextX - halfX) % map.tileWidth)
			end
		end
		
		self.state = self:getState()
	end
	
	function player:isColliding(map, x, y)
		local layer = map.tl["Solid"]
		local tileX, tileY = math.floor(x / map.tileWidth), math.floor(y / map.tileHeight)
		local tile = layer.tileData(tileX, tileY)
		return not(tile == nil)
	end
	
	
	
	function player:getState()
		local tempState = ""
		if self.standing then
			if self.x_vel > 0 then
				tempState = "right"
				player.image = love.graphics.newImage("sprites/dashfront.png")
				
			elseif self.x_vel < 0 then
				tempState = "left"
				player.image = love.graphics.newImage("sprites/dashback.png")
			else
				tempState = "stand"
				player.image = love.graphics.newImage("sprites/cupstanding.png")
			end
		end
		if self.y_vel > 0 then
			tempState = "fall"
		elseif self.y_vel < 0 then
			tempState = "jump"
			player.image = love.graphics.newImage("sprites/cupjump.png")
		elseif self.x_vel > 0 and hasJumped then 
			tempState = "right"
			player.image = love.graphics.newImage("sprites/dashfront.png")
		elseif self.x_vel < 0 and hasJumped then
			tempState = "left"
			player.image = love.graphics.newImage("sprites/dashback.png")
		end
		
		return tempState
	end
end



function love.draw()
	
	
	camera:set()
						
	
	--love.graphics.rectangle("fill", player.x - player.w/2, player.y - player.h/2, player.w, player.h)
	--love.graphics.draw(carlton, player.x - player.w/2, player.y - player.h/2)
	
						--SPRITES--
	
	if love.keyboard.isDown("c") and love.keyboard.isDown("right") then
	
		animation:draw(attackimage, player.x - player.w/2, player.y - player.h/2)
	
	elseif love.keyboard.isDown("c") and not love.keyboard.isDown("left") then
		
		animation:draw(attackimage, player.x - player.w/2, player.y - player.h/2)
		
	elseif love.keyboard.isDown("c") and love.keyboard.isDown("left") then
	
		animation:draw(leftattackimage, player.x - player.w/2, player.y - player.h/2)
		
	elseif love.keyboard.isDown("right") then
	
		animation:draw(runimage, player.x - player.w/2, player.y - player.h/2)
		
	elseif love.keyboard.isDown("left") then
	
		animation:draw(leftrunimage, player.x - player.w/2, player.y - player.h/2)
		
	elseif love.keyboard.isDown("q") then
		
		animation:draw(carlton, player.x - player.w/2, player.y - player.h/2)
		
	elseif love.keyboard.isDown("down") then
		local crouch = love.graphics.newImage("sprites/cupcrouch.png")
		love.graphics.draw(crouch, player.x - player.w/2, player.y - player.h/2)
	else              --STATIC IMAGES--
	
	
	love.graphics.draw(player.image, player.x - player.w/2, player.y - player.h/2)
	
	end
  	carltonanimation:draw(carlton, 300, 36)
	--love.graphics.setColor( 255, 255, 255 )
	animation:draw(carlton, 100, 100)
	map:draw()
	
	camera:unset()
end

function love.update(dt)
	animation:update(dt)
	if dt > 0.05 then
		dt = 0.05
	end
	
	if love.keyboard.isDown("right") then
		player:right()
	end
	
	if love.keyboard.isDown("left") then
		player:left()
	end
	
	
	
	if love.keyboard.isDown(" ") and not(hasJumped) then
		player:jump()
	end
	
	if love.keyboard.isDown("c") then
		player:attack()
	end
	
	if love.keyboard.isDown("c") and love.keyboard.isDown("right") then
		player:attack()
	end
	
	if player.x > map.width * map.tileWidth or player.y > map.height * map.tileHeight then
		love.event.quit()
	end
		
	
	
	player:update(dt)
	
	camera:setPosition( player.x - (love.graphics.getWidth()/2), player.y - (love.graphics.getHeight()/2))
end

function love.keyreleased(key)
	if (key == "right") or (key == "left") then
		
		player.x_vel = 0
		
	end
	if (key == "c") then
			player.image =  love.graphics.newImage("sprites/cupstanding.png")
	end
		
	
end