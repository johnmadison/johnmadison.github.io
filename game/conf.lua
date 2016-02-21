function love.conf(t)
	t.modules.joystick = true
	t.modules.audio = true
	t.modules.keyboard = true
	t.modules.event = true
	t.modules.image = true
	t.modules.graphics = true
	t.modules.timer = true
	t.modules.mouse = true
	t.modules.sound = true
	t.modules.thread = true
	t.modules.physics = true
	t.console = true
	t.title = "CupCake's Quest"
	t.author = "JRM"
	t.window.fullscreen = true
	t.window.vsync = true
	t.window.fsaa = 0
	t.window.height = 300
	t.window.width = 400
end