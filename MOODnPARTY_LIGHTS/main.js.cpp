#include <pgmspace.h>

char main_js[] PROGMEM = R"EOF(
let activeButton = null;

function convert(integer) {
let str = integer.toString(16);
if (str.length === 1) return "0" + str;
else return str;
};

window.addEventListener('DOMContentLoaded', (event) => {

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
mode.addEventListener('click', (event) => onMode(event, index, 'nm'));
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
xhttp.open('GET', 'cmd?' + cmd);
xhttp.send(null);
}

function sendWiFi() {
let xhttp = new XMLHttpRequest();
const formData = new FormData(document.querySelector('#wifisave'));
xhttp.open('PUT', 'sendWiFi', true);
xhttp.send(formData);
setTimeout(() => {window.location.reload(true);}, 3000);
}

function sendApWiFi() {
let xhttp = new XMLHttpRequest();
const formData = new FormData(document.querySelector('#apsave'));
xhttp.open('PUT', 'sendApWiFi');
xhttp.send(formData);
setTimeout(() => {window.location.reload();}, 1000);
}

function submitVal(name, val) {
let xhttp = new XMLHttpRequest();
xhttp.open('GET', 'set?' + name + '=' + val);
xhttp.send(null);
}

function sendVal(event, item) {
event.preventDefault();
console.log("send: ", item.name + '=' + item.value);
let xhttp = new XMLHttpRequest();
xhttp.open('GET', 'set?' + item.name + '=' + item.value);
xhttp.send(null);
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
xhttp.open('GET', 'scan');
xhttp.send(null);
}

function f(link){
document.getElementById('n').value = link.innerText || link.textContent;
if(link.name == 'O'){
document.getElementById('pf').style.display = "none"; 
document.getElementById('pwbt').focus();
} else {
document.getElementById('pf').style.display = "";

}
}
function gem() {
document.getElementById('gem').style.visibility = 'visible';
}

)EOF";
