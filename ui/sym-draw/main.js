var canvasEl = document.querySelector('#canvas');
var ctx = canvasEl.getContext('2d');

var appState = {
  initialAngle: 0,
  numRepeat: 4,
  halfGridSize: 250,

  strokes: [],

  drawing: false,
  animationId: null,
  guideLineStyle: 'blue',
  sketchStyle: 'black'
};

function animate() {
  render(ctx, appState);
  appState.animationId = requestAnimationFrame(animate);
}

animate();

function render(ctx, appState) {
  clear(ctx, appState);
  drawGuide(ctx, appState);
  drawStrokes(ctx, appState);
}

function clear(ctx, appState) {
  var w = canvasEl.width, h = canvasEl.height;
  ctx.clearRect(0, 0, w, h);
}

function drawLine(ctx, p1, p2) {
  ctx.moveTo(p1.x, p1.y);
  ctx.lineTo(p2.x, p2.y);
}

function drawGuide(ctx, appState) {
  var i, numRepeat = appState.numRepeat;
  var d = appState.halfGridSize;
  var initialAngle = appState.initialAngle;
  var angle = 2 * Math.PI / numRepeat;
  var style = appState.guideLineStyle;
  var center = { x: d, y: d };
  var start = { x: 0, y: 0 }, end = { x: d, y: 0 };

  if (numRepeat > 1) {
    ctx.save();

    ctx.translate(d, d);
    ctx.rotate(initialAngle);

    ctx.strokeStyle = style;
    ctx.beginPath();
    for (i = 0; i < numRepeat; ++i) {
      drawLine(ctx, start, end);
      ctx.rotate(angle);
    }
    ctx.stroke();
    ctx.closePath();

    ctx.restore();
  }
}

function drawStrokesInPart(ctx, strokes) {
  strokes.forEach(function(stroke) {
    var i, len = stroke.length;
    if (len > 0) {
      ctx.beginPath();
      for (i = 1; i < len; ++i) {
        drawLine(ctx, stroke[i - 1], stroke[i]);
      }
      ctx.stroke();
      ctx.closePath();
    }
  });

}

function drawStrokes(ctx, appState) {
  var i, numRepeat = appState.numRepeat;
  var d = appState.halfGridSize;
  var initialAngle = appState.initialAngle;
  var angle = 2 * Math.PI / numRepeat;
  var style = appState.sketchStyle;
  var strokes = appState.strokes;

  ctx.save();
  ctx.translate(d, d);
  ctx.rotate(initialAngle);

  ctx.strokeStyle = style;
  for (i = 0; i < numRepeat; ++i) {
    drawStrokesInPart(ctx, strokes, i);
    ctx.rotate(angle);
  }

  ctx.restore();
}

function getXY(canvasEl, ev) {
  return { x: ev.offsetX, y: ev.offsetY };
}

function getPart0XY(xy, d, initialAngle, numRepeat) {
  var x = xy.x - d, y = xy.y - d;
  var curAngle = Math.atan2(y, x);
  var delta = curAngle - initialAngle;
  var unit = 2 * Math.PI / numRepeat;
  var partIndex = Math.floor(delta / unit);
  var rotatedAngle = initialAngle + partIndex * unit;
  var theta = -rotatedAngle;
  return {
    x: Math.cos(theta) * x - Math.sin(theta) * y,
    y: Math.sin(theta) * x + Math.cos(theta) * y,
    i: partIndex
  };
}

function onMouseDown(appState, ev) {
  appState.drawing = true;
  appState.strokes.push([]);

  var p = getXY(canvasEl, ev);
  p = getPart0XY(p, appState.halfGridSize, appState.initialAngle, appState.numRepeat);
  appState.strokes[appState.strokes.length - 1].push(p);
}

function onMouseMove(appState, ev) {
  if (appState.drawing !== true) return;
  var p = getXY(canvasEl, ev)
  p = getPart0XY(p, appState.halfGridSize, appState.initialAngle, appState.numRepeat);

  var strokes = appState.strokes[appState.strokes.length - 1];
  var lastPartIndex = strokes[strokes.length - 1].i;
  if (lastPartIndex != p.i) {
    appState.strokes.push([]);
  }
  appState.strokes[appState.strokes.length - 1].push(p);
}

function onMouseUp(appState, ev) {
  appState.drawing = false;
}

canvasEl.addEventListener('mousedown', onMouseDown.bind(null, appState));
canvasEl.addEventListener('mousemove', onMouseMove.bind(null, appState));
canvasEl.addEventListener('mouseup', onMouseUp.bind(null, appState));
