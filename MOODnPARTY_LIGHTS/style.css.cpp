#include <pgmspace.h>

char style_css[] PROGMEM = R"EOF(
body, .txt{
font-family: Verdana, Helvetica, sans-serif;
max-width: 1300px;
margin-left: auto;
margin-right: auto;
padding: 0;
background-color: #202020;
color: #909090;
text-align: center;
user-select: none;
}
body {
background-image: radial-gradient(#555 1px, transparent 1px);
background-size: 16px 16px;
}
a{
  background: none;
  color: #999;
  text-underline-offset: 2px;
  text-decoration-thickness: 1px;
}
#wifilist + a{
  text-align: left;
}
canvas{
width: 280px;
height: 280px;
border-radius: 50%;
border: 2px solid black;
}
.donutbox{
width: 280px;
height: 280px;
cursor: pointer;
border-radius: 50%;
position: relative;
}
div#focus0, div#focus2 {
visibility: hidden;
pointer-events: none;
width: 24px;
height: 24px;
border-radius: 50%;
border: 2px ridge #000;
opacity: 50%;
position: absolute;
bottom: 131px;
left: 131px;
}
div#colorDot0, div#colorDot2 {
width: 100px;
height: 100px;
border-radius: 50%;
border: none;
position: absolute;
bottom: 90px;
left: 92px;
box-shadow: inset 0 0 12px #FFF;
}

label.txt{
padding: 16px;
cursor: pointer;
}
.flex-row {
display: flex;
flex-wrap: wrap;
flex-direction: row;
justify-content: center;
}

.flex-row-wrap {
display: flex;
flex-direction: row;
flex-wrap: wrap;
justify-content: center;
padding: 0;
margin: auto;
}

.flex-col {
display: flex;
flex-direction: column;
align-items: center;
margin: 0 10px 10px;
min-width: 30%;
}

input {
font-size: medium;
font-family: 'Courier New', Courier, monospace;
font-weight: bold;
width: 220px;
min-height: 32px;
margin-bottom: 2px;
cursor: pointer;
background-color: #d0d0d0;
color: #404040;
}
input[type='color'] {
position: absolute;
transform: translateX(-5px);
visibility: hidden;
}
input[type='button'] {
min-height: 40px;
padding: 10px;
margin: 3px;
border: 2px solid #404040;
border-radius: 5px;
color: #909090;
background-color: #202020;
}
input[type='button']:hover, ul li:hover{
border: 2px solid #909090;
}
input[type='button']:active, ul li:active{
background-color: #bbb;
}
input[type=radio]:checked {
background: #909090;
border: 2px solid #909090;
}
input[type=radio] + span {
opacity: 0.4;
}
input[type=radio]:checked + span {
opacity: 1;
}
input[type='text'], input[type='password'] {
	color: black;
	width: 194px;
	padding-left: 28px;
	cursor: text;
	position: ;
	left: 5px;
	border-radius: 6px;
	}
input::placeholder{
  color: #bbb;
}
.txt-cont{
	padding: 4px 8px;
}
.svg_icon {
	position: relative;
	left: 26px;
	top: 10px;
	width: 18px;
	height: 18px;
	z-index: 1;
}

ul {
list-style-type: none;
}
ul li {
display: block;
cursor: pointer;
margin: 3px;
padding: 10px;
border: 2px solid #404040;
border-radius: 5px;
color: #909090;
text-decoration: none;
min-width: 220px;
}

ul.control li{
min-width: 60px;
min-height: 24px;
}

ul.control {
display: flex;
flex-direction: row;
justify-content: flex-end;
align-items: center;
padding: 0;
}

ul li.active {
border: 2px solid #909090;
}

.tab {
padding: 2px 2px 0;
margin: 0 6px;
overflow: hidden;
border-top-left-radius: 9px;
background-color: #f1f1f1;
}

.tab button {
min-width: 7rem;
height: 3rem;
padding: 12px 16px;
border: none;
border-top-right-radius: 7px;
border-top-left-radius: 7px;
font-size: medium;
float: left;
cursor: pointer;
transition: 0.5s;
}
#gem{
visibility: hidden;
min-width: 1rem;
}
button.tablinks.last{
float: right;
}
.tab button:hover{
background-color: #ccc;
}
.tab button:active, button.tablinks.activetab {
background-color: #bbb;
}

.tabcontent {
margin: 0 6px;
padding: 1px 12px 12px;
background-color: #202020;
display: compact;
border: 1px solid #cccccc;
border-top: none;
animation: fadeEffect 0.3s;
}


.form {
width: 280px;
margin: 10px auto 16px;
padding: 4px 15px;
padding-bottom: 16px;
text-align: center;
border-radius: 3px;
box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);
}

.form > span {
display: flex;
font-family: monospace;
color: #909090;
}

.form span label {
padding: 0 1px 6px;
font-size: medium;
text-align: center;
margin-bottom: 8px;
width: 200px;
}

input[type=radio] {
background: none;
margin: 0;
padding: 2px;
border: 2px solid #404040;
border-radius: 5px;
color: #909090;
text-decoration: none;
width: 100%;
appearance: none;
min-height: 5px;
}

table{
min-width: 240px;
margin: auto auto 8px;
padding: 6px;
border-color: #909090;
}
th, td{
padding: 1px;
}
footer{
float: right;
padding: 10px;
cursor: pointer;
background-color: rgba(32,32,32,0.6);
}

@media screen and (max-width: 750px) {
.flex-row {
flex-direction: column;
}

body {
margin-right: 10px;
margin-left: 10px;
}

.tabcontent, .tab{
margin: 0 1px;
}
}

@keyframes fadeEffect {
from {
opacity: 0.2;
}
to {
opacity: 1;
}
}
)EOF";
