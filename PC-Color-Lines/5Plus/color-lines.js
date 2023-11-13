/*
	5+, Â©Copyright 2007 - bezumie.com, All Rights Reserved
	5+, Â©Copyright 2007 - bezumie.com, Ð’ÑÐ¸Ñ‡ÐºÐ¸ Ð¿Ñ€Ð°Ð²Ð° Ð·Ð°Ð¿Ð°Ð·ÐµÐ½Ð¸
*/
const language = document.documentElement.lang;
var gameIsOver;
var IMGS = ['ball1', 'ball2', 'ball3', 'ball4', 'ball5', 'ball6', 'ball7'];
var BALLS = IMGS.length;
var SEL = { r: false, c: false };
var CELL = { r: 0, c: 0 };
var FC;
var TBL = [];
var score;
var NXT = [];
var moving;
let topscore = 0;
if (window.localStorage) {
	topscore = localStorage.getItem('5plus-topscore') || 0;
	document.getElementById('topScore').innerHTML = topscore;
	document.getElementById('topScore').className = "";
}


function rand(a, b) {
	return Math.floor(Math.random() * (b - a + 1) + a);
}

function closeScreen(objName) {
	document.getElementById(objName).style.display = 'none';
}

function setScore(s) {
	score = s;
	document.getElementById('score').innerHTML = score;
}

function setPoints(s) {
	let el = document.getElementById('points');
	el.innerHTML = '+' + s;
	el.style.display = 'inline';
	setTimeout(() => {
		el.style.display = 'none';
	}, 1500);
}

function gameOver() {
	gameIsOver = true;
	document.getElementById('gameOver').style.display = 'block';
	if (score > topscore) {
		topscore = score;
		document.getElementById('topScore').innerHTML = topscore;
		document.getElementById('topScore').className = "new";
		localStorage && localStorage.setItem('5plus-topscore', topscore);
	}
	gtag && gtag('event', 'game_end', { 'language': language, 'game': '5+' });
}
function newGame() {
	document.location = document.location;
}
function getimg(r, c) {
	if ((r >= ROWS) || (c >= COLS) || (c < 0) || (r < 0)) { return false; }
	return TBL[r][c].img;
}
function getball(r, c) {
	if ((r >= ROWS) || (c >= COLS) || (r < 0) || (r < 0)) { return false; }
	return TBL[r][c].ball;
}
function setball(r, c, ball, img) {
	TBL[r][c].ball = ball;
	TBL[r][c].img = img;
}
function check5from(r1, c1) {
	var b1 = getball(r1, c1);//first
	if (!b1) return false;
	var b, r, c;
	var q = new Array();
	// nadyasno!
	var qt = [];
	qt[0] = getimg(r1, c1);
	r = r1;
	c = c1 + 1;
	while (c < COLS) {
		b = getball(r, c);
		if (b && (b == b1)) { qt.push(getimg(r, c)); }
		else { break; }
		c++;
	}
	if (qt.length >= 5) { q = q.concat(qt); }
	// nadolu
	var qt = [];
	qt[0] = getimg(r1, c1);
	r = r1 + 1;
	c = c1;
	while (r < ROWS) {
		b = getball(r, c);
		if (b && (b == b1)) { qt.push(getimg(r, c)); }
		else { break; }
		r++;
	}
	if (qt.length >= 5) { q = q.concat(qt); }
	// nadolu i nadyasno
	var qt = []; // resultat nadyasno
	qt[0] = getimg(r1, c1);
	r = r1 + 1;
	c = c1 + 1;
	while ((r < ROWS) && (c < COLS)) {
		b = getball(r, c);
		if (b && (b == b1)) { qt.push(getimg(r, c)); }
		else { break; }
		c++;
		r++;
	}
	if (qt.length >= 5) { q = q.concat(qt); }
	// nadolu i nadlyavo
	var qt = []; // resultat nadyasno
	qt[0] = getimg(r1, c1);
	r = r1 + 1;
	c = c1 - 1;
	while ((r < ROWS) && (c >= 0)) {
		b = getball(r, c);
		if (b && (b == b1)) { qt.push(getimg(r, c)); }
		else { break; }
		c--;
		r++;
	}
	if (qt.length >= 5) { q = q.concat(qt); }
	if (q.length) { return q; }
	else { return false; }
}
function check5() {
	var r, c, i, p;
	var q = 0;
	var pp = [];
	for (r = 0; r < ROWS; r++) {
		for (c = 0; c < COLS; c++) {
			p = check5from(r, c);
			if (p !== false) { pp = pp.concat(p); }
		}
	}
	for (i = 0; i < pp.length; i++) {
		if (removeball(pp[i])) { q++; }
	}
	var s = 0;
	if (q) {
		for (i = 1; i <= q; i++) {
			if (i < 6) { s++; }
			else { s += i - 4 };
		}
		setPoints(s);
		setScore(score + s);
	}
	return q;
}
function newball(r, c, ball) {
	var tc = TBL[r][c].tc;
	let img = new Image();
	img.src = '5Plus/ball' + ball + '.png';
	img.id = 'i_' + r + '_' + c;
	img.onmousedown = balld;
	img.ondragstart = function () { return false; };
	tc.appendChild(img);
	setball(r, c, ball, img);
	FC--;
}
function addballs(cnt) {
	var i = 0;
	var r, c, b;
	while (i < cnt) {
		r = rand(0, ROWS - 1);
		c = rand(0, COLS - 1);
		if (!getball(r, c)) {
			b = NXT.pop();
			if (!b) {
				b = rand(1, BALLS);
			}
			newball(r, c, b);
			check5();
			if (!FC) {
				gameOver();
				return;
			}
			i++;
		}
	}

	var nxt = document.getElementById('next');
	nxt.innerHTML = '';
	var img;
	for (i = 0; i < cnt; i++) {
		b = rand(1, BALLS);
		NXT.push(b);
		img = new Image();
		img.src = '5Plus/ball' + b + '.png';
		nxt.appendChild(img);
	}
}
var path = [];
function stepball() {
	moving = true;
	var step = path.pop();
	var img = getimg(SEL.r, SEL.c);
	var t = TBL[step.r][step.c].tc;
	t.appendChild(img);
	var b = getball(SEL.r, SEL.c);
	setball(SEL.r, SEL.c, 0, undefined);
	SEL.r = step.r;
	SEL.c = step.c;
	setball(step.r, step.c, b, img);
	if (path.length) {
		setTimeout('stepball()', 75);
	}
	else {
		img.id = 'i_' + step.r + '_' + step.c;
		unselball();
		if (!check5()) {
			addballs(3);
		}
		moving = false;
	}
}
function moveball(r, c) {
	var tbl = [];
	var i, j;
	for (i = 0; i < ROWS; i++) {
		tbl[i] = [];
		for (j = 0; j < COLS; j++) {
			if (getball(i, j)) { tbl[i][j] = 'b' }
			else { tbl[i][j] = 0; }
		}
	}
	tbl[SEL.r][SEL.c] = 1;
	var p = 1;
	var found;
	var countdown = 0;
	while (!countdown) {
		found = false;
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLS; j++) {
				if (tbl[i][j] === p) {
					if ((i == r) && (j == c)) { countdown = p; break; }
					else {
						if ((i < ROWS - 1) && (tbl[i + 1][j] === 0)) { tbl[i + 1][j] = p + 1; }
						if ((i > 0) && (tbl[i - 1][j] === 0)) { tbl[i - 1][j] = p + 1; }
						if ((j < COLS - 1) && (tbl[i][j + 1] === 0)) { tbl[i][j + 1] = p + 1; }
						if ((j > 0) && (tbl[i][j - 1] === 0)) { tbl[i][j - 1] = p + 1; }
					}
					found = true;
				}
			}
			if (countdown) { break; }
		}
		p++;
		if (!found) break;
	}
	if (countdown) {
		i = r;
		j = c;
		while (countdown > 1) {
			path.push({ r: i, c: j });
			countdown--;
			if ((i < ROWS - 1) && (tbl[i + 1][j] === countdown)) { i++; }
			else if ((i > 0) && (tbl[i - 1][j] === countdown)) { i--; }
			else if ((j < COLS - 1) && (tbl[i][j + 1] === countdown)) { j++; }
			else if ((j > 0) && (tbl[i][j - 1] === countdown)) { j--; }
		}
		stepball();
	}
}
function removeball(obj) {
	if (!obj) { return false; }
	if (!document.getElementById(obj.id)) { return false; }
	var s = obj.id.split('_');
	var r = s[1] - 0;
	var c = s[2] - 0;
	TBL[r][c].tc.removeChild(obj);
	delete obj;
	setball(r, c, 0, undefined);
	FC++;
	return true;
}
function selball(r, c) {
	SEL.r = r;
	SEL.c = c;
	getimg(r, c).className += ' selected';
}
function unselball() {
	getimg(SEL.r, SEL.c).className = getimg(SEL.r, SEL.c).className.replace(' selected', '');
	SEL.c = false;
	SEL.r = false;
}
function celld(e) {
	if (gameIsOver || moving) {
		return;
	}
	e.preventDefault();
	var s = this.id.split('_');
	var r = s[1] - 0;
	var c = s[2] - 0;
	if (getball(r, c) || (SEL.r === false)) { return; }
	moveball(r, c);
}
function balld(e) {
	if (gameIsOver || moving) {
		return;
	}
	e.preventDefault();
	var s = this.id.split('_');
	var r = s[1] - 0;
	var c = s[2] - 0;
	if (SEL.r === false) {
		selball(r, c);
	}
	else if (getimg(SEL.r, SEL.c) == this) {
		unselball();
	}
	else {
		unselball();
		selball(r, c);
	}
}
function setCell(r, c) {
	TBL[CELL.r][CELL.c].tc.style.background = '';
	CELL.r = r;
	CELL.c = c;
	TBL[r][c].tc.style.background = '#90b0ff';
}
function keyd(e) {
	if (gameIsOver) {
		return;
	}
	if (e) var k = e.which;
	else var k = window.event.keyCode;
	var c = CELL.c;
	var r = CELL.r;
	switch (k) {
		case 32:
			if (moving) {
				e.preventDefault();
				break;
			}
			if (TBL[r][c].ball) {
				if (SEL.r === false) {
					selball(r, c);
				}
				else {
					unselball();
					selball(r, c);
				}
			}
			else {
				if (!getball(r, c) && (SEL.r !== false)) {
					moveball(r, c);
				}
			}
			e.preventDefault();
			break;
		case 37:
			c--;
			if (c < 0) { c = COLS - 1; }
			setCell(r, c);
			e.preventDefault();
			break;
		case 38:
			r--;
			if (r < 0) { r = ROWS - 1; }
			setCell(r, c);
			e.preventDefault();
			break;
		case 39:
			c++;
			if (c >= COLS) { c = 0; }
			setCell(r, c);
			e.preventDefault();
			break;
		case 40:
			r++;
			if (r >= ROWS) r = 0;
			setCell(r, c);
			e.preventDefault();
			break;
	}
}
function init() {
	for (r = 0; r < ROWS; r++) {
		TBL[r] = [];
		for (c = 0; c < COLS; c++) {
			t = document.getElementById('t_' + r + '_' + c);
			TBL[r][c] = {
				ball: 0,
				tc: t,
				img: null
			};
			t.onmousedown = celld;
			t.ondragstart = function () {
				return false;
			}
				;
		}
	}
	FC = ROWS * COLS;
	score = 0;
	for (b = 0; b < 3; b++) {
		NXT.push(rand(1, BALLS));
	}
	addballs(3);
	document.onkeydown = keyd;
	gameIsOver = false;
}
window.addEventListener('load', function () {
	init();
});
