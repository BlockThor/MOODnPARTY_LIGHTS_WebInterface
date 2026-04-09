#include <pgmspace.h>

char main_js[] PROGMEM = R"EOF(
let activeButton = null;

let loop = setInterval(function () {
    const now = new Date();
    document.getElementById('time').innerText = now.toTimeString().slice(0, 5);//now.toTimeString().replace('(', '\n(');
}, 1000);

function convert(integer) {
let str = integer.toString(16);
if (str.length === 1) return "0" + str;
else return str;
};

document.addEventListener('DOMContentLoaded', () => {
    document.title = param.TT;
    document.getElementById("HD").value = param.HD;
    document.getElementById("color0").value = param.C0;
    document.getElementById("color2").value = param.C2;
    document.getElementById("ltime").innerText = param.Tm;
    document.getElementById("time-in").value = param.T1;
    document.getElementById("time-out").value = param.T2;
    document.getElementById("AN").value = param.AN;
    document.getElementById("SN").value = param.SN;
    document.getElementById("SP").value = param.SP;
    document.getElementById("monomodes").insertAdjacentHTML("afterbegin", param.M1);
    document.getElementById("duomodes").insertAdjacentHTML("afterbegin", param.M2);
    document.getElementById("rgbmodes").insertAdjacentHTML("afterbegin", param.M3);
    document.getElementById("specmodes").insertAdjacentHTML("afterbegin", param.M4);
    document.getElementById("allmodes").insertAdjacentHTML("afterbegin", param.M4);
    document.getElementById("FT").textContent = param.FT;
    document.getElementById("AB").insertAdjacentHTML("afterbegin", param.AB);
    document.getElementById("WR").insertAdjacentHTML("afterbegin", param.WR);

    document.getElementById("colorDot0").style.backgroundColor = param.C0;
    document.getElementById("colorDot2").style.backgroundColor = param.C2;

let donut1 = document.getElementById('donut1');
let donut2 = document.getElementById('donut2');

let ctx = donut1.getContext('2d',{willReadFrequently: true});
drawC(ctx, donut1.width / 2, donut1.height / 2, donut1.width / 3);
ctx = donut2.getContext('2d',{willReadFrequently: true});
drawC(ctx, donut2.width / 2, donut2.height / 2, donut2.width / 3);

document.querySelectorAll('ul#allmodes li').forEach(initAllMode);
document.querySelectorAll('ul#monomodes li').forEach(initMonoMode);
document.querySelectorAll('ul#duomodes li').forEach(initDuoMode);
document.querySelectorAll('ul#rgbmodes li').forEach(initRGBMode);
document.querySelectorAll('ul#specmodes li').forEach(initSpecMode);
document.getElementById("defaultTab").click();

let radioItems = document.querySelectorAll('input[type="radio"]');
radioItems.forEach((e) => {
if (param[e.name] == e.value) {
e.checked = true;
}
});
});

function drawC(_ctx, xc, yc, r) {
const colors = ['#F00', '#FF0', '#0F0', '#0FF', '#00F', '#F0F'];
let partL = (2 * Math.PI) / colors.length;
let start = 0;
let gradient = null;
let startColor = null, endColor = null;

for (let i = 0; i < colors.length; i++) {
startColor = colors[i];
endColor = colors[(i + 1) % colors.length];

let xStart = xc + Math.cos(start) * r;
let xStop = xc + Math.cos(start + partL) * r;
let yStart = yc + Math.sin(start) * r;
let yStop = yc + Math.sin(start + partL) * r;

_ctx.beginPath();

gradient = _ctx.createLinearGradient(xStart, yStart, xStop, yStop);
gradient.addColorStop(0, startColor);
gradient.addColorStop(1.0, endColor);

_ctx.strokeStyle = gradient;
_ctx.arc(xc, yc, r, start, start + partL + 0.01);
_ctx.lineWidth = r;
_ctx.stroke();
_ctx.closePath();

start += partL;
}

let grd = _ctx.createRadialGradient(xc, yc, 0, xc, yc, xc);
grd.addColorStop(0, "#FFF");
grd.addColorStop(0.45, "#FFF");
grd.addColorStop(0.6, "#FFFFFF00");
grd.addColorStop(0.85, "#00000000");
grd.addColorStop(1, "#000");

_ctx.fillStyle = grd;
_ctx.fillRect(0, 0, xc * 2, yc * 2);
}

function initAllMode(mode, index) {
mode.addEventListener('click', (event) => onMode(event, index, 'mn'));
}

function initMonoMode(mode, index) {
mode.addEventListener('click', (event) => onMode(event, index, 'mm'));
}
function initDuoMode(mode, index) {
mode.addEventListener('click', (event) => onMode(event, index, 'md'));
}
function initRGBMode(mode, index) {
mode.addEventListener('click', (event) => onMode(event, index, 'mr'));
}
function initSpecMode(mode, index) {
mode.addEventListener('click', (event) => onMode(event, index, 'ms'));
}

function onDonut(event, t, n) {
event.preventDefault();
let imageData = t.getContext('2d').getImageData(event.offsetX, event.offsetY, 1, 1);
let focus = document.getElementById('focus' + n);
focus.style.left = event.offsetX - 12 + 'px';
focus.style.top = event.offsetY - 12 + 'px';
focus.style.visibility = 'visible';


let hexColor = '#' + convert(imageData.data[0].toString(16)) + convert(imageData.data[1].toString(16)) + convert(imageData.data[2].toString(16));
document.getElementById('color' + n).value = hexColor;
document.getElementById('colorDot' + n).style.backgroundColor = hexColor;
let resColor = Number(imageData.data[0]) * 65535 + Number(imageData.data[1]) * 255 + Number(imageData.data[2]);
let colorValue = parseInt(hexColor.substr(1, 6), 16);
submitVal('c' + n, colorValue);
}

function clickColor(n) {
document.getElementById("color" + n).click();
}

function onColor(event, color, n) {
event.preventDefault();
if (n !== '1') {
document.getElementById('colorDot' + n).style.backgroundColor = color;
document.getElementById('focus' + n).style.visibility = 'hidden';
}
let colorValue = parseInt(color.substr(1, 6), 16);
submitVal('c' + n, colorValue);
}

function onMode(event, mode, n) {
event.preventDefault();
document.getElementsByName('ap').forEach((e) => {
e.checked = false;
});
if (activeButton) activeButton.classList.remove('active')
activeButton = event.target;
activeButton.classList.add('active');
submitVal(n, mode);
}


function openTab(evt, tabName) {
let i, tabcontent, tablinks;

tabcontent = document.getElementsByClassName("tabcontent");
for (i = 0; i < tabcontent.length; i++) {
tabcontent[i].style.display = "none";
}

tablinks = document.getElementsByClassName("tablinks");
for (i = 0; i < tablinks.length; i++) {
tablinks[i].classList.remove('activetab');
}

document.getElementById(tabName).style.display = "block";
evt.currentTarget.classList.add('activetab');
}

function sendCmd(cmd) {
  let xhttp = new XMLHttpRequest();
  console.log('Send CMD: ', cmd);
  xhttp.open('POST', '/cmd', true);
  xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhttp.send('command=' + encodeURIComponent(cmd));
}

function sendTime() {
  const now = new Date();
  let sTime = Math.floor(now.getTime() / 1000) - now.getTimezoneOffset() * 60;
  console.log('Send time: ', sTime);

  let xhttp = new XMLHttpRequest();
  xhttp.open('PUT', '/time', true);
  xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhttp.send('timestamp=' + sTime);

  document.getElementById('ltime').innerText = now.toTimeString().slice(0, 5);
}
function sendTimers() {
  // Read HH:MM strings
    const inStr = document.getElementById('time-in').value;   // e.g. "07:30"
    const outStr = document.getElementById('time-out').value; // e.g. "23:30"

  // Convert "HH:MM" to Unix timestamp for today
  function hhmmToUnix(hhmm) {
    if (!hhmm) return 0;
    const parts = hhmm.split(':');
    const h = parseInt(parts[0], 10) || 0;
    const m = parseInt(parts[1], 10) || 0;
    
    const now = new Date();
    now.setHours(h, m, 0, 0);
    return Math.floor(now.getTime() / 1000);
  }

  const onUnix  = hhmmToUnix(inStr);
  const offUnix = hhmmToUnix(outStr);

  console.log('Send timers (Unix): on=', onUnix, 'off=', offUnix);

  const body = 'on=' + encodeURIComponent(onUnix) + '&off=' + encodeURIComponent(offUnix);

  const xhttp = new XMLHttpRequest();
  xhttp.open('PUT', '/timer', true);
  xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhttp.onreadystatechange = function () {
    if (xhttp.readyState === 4) {
      if (xhttp.status === 200) {
        console.log('Schedule updated');
      } else {
        console.warn('Failed to update schedule', xhttp.status, xhttp.responseText);
      }
    }
  };
  xhttp.send(body);
}

function sendWiFi() {
let xhttp = new XMLHttpRequest();
const formData = new FormData(document.querySelector('#wifisave'));
xhttp.open('PUT', '/sendWiFi', true);
xhttp.send(formData);
setTimeout(() => {window.location.reload(true);}, 3000);
}

function sendApWiFi() {
let xhttp = new XMLHttpRequest();
const formData = new FormData(document.querySelector('#apsave'));
xhttp.open('PUT', '/sendApWiFi', true);
xhttp.send(formData);
setTimeout(() => {window.location.reload();}, 1000);
}

function submitVal(name, val) {
let xhttp = new XMLHttpRequest();
xhttp.open('POST', '/set', true);
xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
xhttp.send(name + '=' + encodeURIComponent(val));
}

function sendVal(event, item) {
event.preventDefault();
console.log("send: ", item.name + '=' + item.value);
let xhttp = new XMLHttpRequest();
xhttp.open('POST', '/set', true);
xhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
xhttp.send(item.name + '=' + encodeURIComponent(item.value));
}

function scanWiFi(event) {
// get list of modes from ESP
console.log('Scan start');
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function () {
if (xhttp.readyState == 4 && xhttp.status == 200) {
console.log('If pass');
document.getElementById('wifilist').innerHTML = xhttp.responseText;
} else {
console.log('If NOT pass');
console.log(xhttp.readyState);
console.log(xhttp.status);
}
};
xhttp.open('GET', '/scan', true);
xhttp.send(null);
}

function gem() {
document.getElementById('gem').style.visibility = 'visible';
}

)EOF";
