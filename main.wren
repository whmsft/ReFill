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
		_lastTargetValue = -100
		_lastProgressbarValue = -100
		_mousePressedLastTick = false
	}
  update() {
		if (Mouse.isButtonPressed("left")) _progressbarValue = _progressbarValue+1
		if (_progressbarValue>100) _progressbarValue = 0

		if (_mousePressedLastTick && !Mouse.isButtonPressed("left")) {
			if ([_progressbarValue-_targetValue,_targetValue-_progressbarValue].sort()[-1] <= 10) {
				SCORE = SCORE+1
			} else SCORE = SCORE-1
			_lastTargetValue = _targetValue
			_lastProgressbarValue = _progressbarValue
			_targetValue = _randomNumberGenerator.int(101)
			_progressbarValue = 0
		}
		_mousePressedLastTick = Mouse.isButtonPressed("left")
	}
  draw(alpha) {
		Canvas.cls()
		Canvas.print(_targetValue, 4, 4, Color.white)
		Canvas.print(SCORE, 4, 16, Color.white)
		Canvas.rectfill(25, 600-25-200-20, 220, 220, Color.white)
		Canvas.rectfill(30, 600-30-200-10, 210, 210, Color.black)
		Canvas.rectfill(35, 600-35-_progressbarValue*2, 200, _progressbarValue*2, Color.white)
		if (!Mouse.isButtonPressed("left")) {
			(0...11).each{ |num|
				if (600-35-(_lastTargetValue-10+num*2)*2<600-35 && 600-35-(_lastTargetValue-10+num*2)*2>600-35-200) {
					Canvas.line(35, 600-35-(_lastTargetValue-10+num*2)*2, 235, 600-35-(_lastTargetValue-10+num*2)*2, Color.darkgray)
				}
			}
			Canvas.line(35, 600-35-_lastProgressbarValue*2, 235, 600-35-_lastProgressbarValue*2, Color.white)
		}
	}
}

var Game = main.new()
