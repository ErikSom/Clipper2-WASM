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

	const size = path.size();

	for (let i = 0; i < size; i++) {
		const point = path.get(i);

		const x = Number(point.x) + offsetX;
		const y = Number(point.y) + offsetY;

		if (i === 0) {
			ctx.moveTo(x, y);
		} else {
			ctx.lineTo(x, y);
		}
	}

	if(closed){
		const point = path.get(0);
		const x = Number(point.x) + offsetX;
		const y = Number(point.y) + offsetY;
		ctx.lineTo(x, y);
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
