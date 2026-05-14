const canvas = document.createElement('canvas');
const ctx = canvas.getContext('2d');

let offsetX = 0;
let offsetY = 0;

function initCanvas(width, height) {
	document.body.appendChild(canvas);
	canvas.width = width;
	canvas.height = height
}

function offsetCanvas(x, y) {
	offsetX = x;
	offsetY = y;
}

function drawPaths(paths, color = 'black', closed = true) {
	const size = paths.size();
	for (let i = 0; i < size; i++) {
		drawPath(paths.get(i), color, closed);
	}
}

function drawPath(path, color = 'black', closed = true) {
	ctx.strokeStyle = color;
	ctx.beginPath();

	const v = path.view();
	if (v.length === 0) return;

	ctx.moveTo(Number(v[0]) + offsetX, Number(v[1]) + offsetY);
	for (let i = 3; i < v.length; i += 3) {
		ctx.lineTo(Number(v[i]) + offsetX, Number(v[i + 1]) + offsetY);
	}

	if (closed) {
		ctx.lineTo(Number(v[0]) + offsetX, Number(v[1]) + offsetY);
	}

	ctx.stroke();
}

function drawText(text, x, y, color = 'black', font = '12px sans-serif') {
	ctx.fillStyle = color;
	ctx.font = font;
	ctx.fillText(text, x, y);
}

function clearPaths() {
	ctx.clearRect(0, 0, canvas.width, canvas.height);
}
