import "dome" for Window
import "input" for Mouse
import "random" for Random
import "graphics" for Canvas, Color

var SCORE = 0

class main {
  construct new() {}
  init() {
    Window.title = "ReFill"
		Window.resize(270, 600)
		Canvas.resize(270, 600)
		_randomNumberGenerator = Random.new()
		_progressbarValue = 0
		_targetValue = _randomNumberGenerator.int(101)
		_mousePressedLastTick = false
	}
  update() {
		if (Mouse.isButtonPressed("left")) _progressbarValue = _progressbarValue+2
		if (_progressbarValue>100) _progressbarValue = 0
		
		if (_mousePressedLastTick && !Mouse.isButtonPressed("left")) {
			if ((_progressbarValue-_targetValue).abs <= 15) {
				_targetValue = _randomNumberGenerator.int(101)
				SCORE = SCORE+1
			} else SCORE = SCORE-1
			_progressbarValue = 0
		}
		_mousePressedLastTick = Mouse.isButtonPressed("left")
	}
  draw(alpha) {
		Canvas.cls()
		Canvas.print(_targetValue, 4, 4, Color.white)
		Canvas.print(SCORE, 4, 16, Color.white)
		Canvas.rectfill(35, 600-35-_progressbarValue*2, 200, _progressbarValue*2, Color.white)
		Canvas.rect(35, 600-35-200, 200, 200, Color.white)
	}
}

var Game = main.new()
