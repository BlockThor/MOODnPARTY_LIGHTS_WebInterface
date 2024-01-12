#include <pgmspace.h>

char index_html[] PROGMEM = R"EOF(
<!DOCTYPE html>
<html lang='en' dir='ltr'>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>
<meta name='viewport' content='width=device-width, initial-scale=1.0'/>    
<link rel="icon" type="image/svg+xml" href="data:image/svg+xml,%3Csvg width='64' height='64' viewBox='-1 -1 18 18' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Ccircle style='stroke:%23000' cx='8' cy='8' r='8'/%3E%3Cpath d='M8 8h8c0-1.5-.4-2.8-1.1-4L8 8z' fill='%23F5AC43'/%3E%3Cpath d='m8 8-6.9 4c.7 1.2 1.7 2.2 2.9 2.9L8 8z' fill='%23515EBB'/%3E%3Cpath d='M8 8v8c1.5 0 2.8-.4 4-1.1L8 8z' fill='%23D0449A'/%3E%3Cpath d='M4 14.9c1.2.7 2.5 1.1 4 1.1V8l-4 6.9z' fill='%237C39B1'/%3E%3Cpath d='M14.9 4c-.7-1.2-1.7-2.2-2.9-2.9L8 8l6.9-4z' fill='%23F8CE33'/%3E%3Cpath d='M8 8H0c0 1.5.4 2.8 1.1 4L8 8z' fill='%23177AC3'/%3E%3Cpath d='m8 8 4 6.9c1.2-.7 2.2-1.7 2.9-2.9L8 8z' fill='%23FE4A29'/%3E%3Cpath d='m8 8 6.9 4c.7-1.2 1.1-2.5 1.1-4H8z' fill='%23F97932'/%3E%3Cpath d='M8 8 1.1 4C.4 5.2 0 6.5 0 8h8z' fill='%231AB3D0'/%3E%3Cpath d='m8 8 4-6.9C10.8.4 9.5 0 8 0v8z' fill='%23FCF222'/%3E%3Cpath d='M8 0C6.5 0 5.2.4 4 1.1L8 8V0z' fill='%2389D31C'/%3E%3Cpath d='M8 8 4 1.1C2.8 1.8 1.8 2.8 1.1 4L8 8z' fill='%2333B634'/%3E%3Ccircle style='stroke:%23fff;fill:%231976ff;paint-order:stroke' cx='8' cy='8' r='3'/%3E%3C/svg%3E"/>
<title>OV CHENG Cabin LED Control</title>
<script>const param = {PM};</script>
<style>#colorDot0{background-color: #{C0};}#colorDot2{background-color: #{C2};}</style>
<script type='text/javascript' src='main.js'></script>
<link href='style.css' rel="stylesheet"/>
</head>
<body>
{MT}
<div class="tab">
<button class="tablinks" onclick="openTab(event, 'Colors')" id="defaultTab">Colors</button>
<button class="tablinks" onclick="openTab(event, 'Monomode')" >MonoColor</button>
<button class="tablinks" onclick="openTab(event, 'Duomode')">DuoColor</button>
<button class="tablinks" onclick="openTab(event, 'RGBMode')">RainbowColor</button>
<button class="tablinks" onclick="openTab(event, 'SpecMode')">SpecModes</button>
<button class="tablinks" onclick="openTab(event, 'Controls')">Controls</button>
<button class="tablinks" onclick="openTab(event, 'WiFi')">WiFi</button>
<button class="tablinks last" onclick="openTab(event, 'About')">About</button>
<button class="tablinks last" onclick="openTab(event, 'GEM')" id="gem">&#x1F48E</button>
</div>

<!--Tab content-->
<div id="Colors" class="tabcontent">
<h3>Colors</h3>
<div class='flex-row'>
<div class='flex-col'>
<label class='txt' for="color0">Main color:</label>
<div class="donutbox">
<canvas id='donut1' width='280' height='280' onclick="onDonut(event, this, '0')" onselectstart="function(){return false;}"></canvas>
<div id="colorDot0" onclick="clickColor('0')"></div>
<div id="focus0"></div>
</div>
<input type="color" id="color0" value="#{C0}"
oninput="onColor(event, this.value, '0')"><!--#{C0}-->
</div>
<div class='flex-col'>
<label class='txt' for="color2">Second color:</label>
<div class="donutbox">
<canvas id='donut2' width='280' height='280' onclick="onDonut(event, this, '2')"></canvas>
<div id="colorDot2" onclick="clickColor('2')"></div>
<div id="focus2"></div>
</div>
<input type="color" id="color2" value="#{C2}"
oninput="onColor(event, this.value, '2')"><!--#{C2}-->
</div>
<div class='flex-col'>
<div class='flex-row' style="width: 280px">
<label class='txt' for="color1">Background:</label>
<input type="color" value="#{C1}" id="color1"  oninput="onColor(event, this.value, '1')"><!--#{C1}-->


<ul class='flex-row-wrap'>
<li onClick="onColor(event, '#000000', '1')">Set Black</li>
<li onClick="onColor(event, '#040404', '1')">Set White</li>
<li onClick="onColor(event, '#040000', '1')">Set Red</li>
<li onClick="onColor(event, '#000400', '1')">Set Green</li>
<li onClick="onColor(event, '#000004', '1')">Set Blue</li>
<li onClick="onColor(event, '#040004', '1')">Set Violet</li>
</ul>
</div>
</div>
</div>
</div>
<div id="Monomode" class="tabcontent">
<h4> Mono Color Modes </h4>
<div class='flex-row'>
<ul id='monomodes' class='flex-row-wrap'> 
{M1}
</ul>
</div>
</div>
<div id="Duomode" class="tabcontent">
<h4> Duo Colors Modes </h4>
<div class='flex-row'>
<ul id='duomodes' class='flex-row-wrap'>
{M2}
</ul>
</div>
</div>
<div id="RGBMode" class="tabcontent">
<h4> Rainbow Colors Modes </h4>
<div class='flex-row'>
<ul id='rgbmodes' class='flex-row-wrap'> 
{M3}
</ul>
</div></div>

<div id="SpecMode" class="tabcontent">
<h4> Special Modes </h4>
<div class='flex-row'>
<div class='flex-col'>
<ul id='specmodes' class='flex-row-wrap'>
{M4}
</ul>
</div></div>
<h4>Very Special Modes</h4>
<div class='flex-row'><div class='flex-col'>
<ul class='flex-row-wrap'>
<li onClick="onMode(event,'59','nm')">From &#x1F499;&#x1F49B; with Love</li>
</ul>
</div></div>
</div>

<div id="Controls" class="tabcontent">
<h4>Control Panel</h4>
<div class='flex-row'><div class='flex-col'>
<div class='form'>
<h4>Lights</h4>
OFF / ON<span>
<label><input type="radio" name="of" value='0' onchange="sendVal(event, this)"><span>Off</span></label>
<label><input type="radio" name="of" value='1' onchange="sendVal(event, this)"><span>On</span></label></span>
Brightness<span>
<label><input type="radio" name="br" value='8'   onchange="sendVal(event, this)"><span>Min</span></label>
<label><input type="radio" name="br" value='32'  onchange="sendVal(event, this)"><span>Less</span></label>
<label><input type="radio" name="br" value='64'  onchange="sendVal(event, this)"><span>Norm</span></label>
<label><input type="radio" name="br" value='128' onchange="sendVal(event, this)"><span>More</span></label>
<label><input type="radio" name="br" value='255' onchange="sendVal(event, this)"><span>Max</span></label></span>
Display speed<span>
<label><input type="radio" name="ds" value='4000' onchange="sendVal(event, this)"><span>Slower</span></label>
<label><input type="radio" name="ds" value='2000' onchange="sendVal(event, this)"><span>Slow  </span></label>
<label><input type="radio" name="ds" value='1000' onchange="sendVal(event, this)"><span>Norm  </span></label>
<label><input type="radio" name="ds" value='500' onchange="sendVal(event, this)" ><span>Fast  </span></label>
<label><input type="radio" name="ds" value='100' onchange="sendVal(event, this)" ><span>Faster</span></label></span>
</div></div>
<div class='flex-col'>
<div class='form'>
<h4>Autoplay</h4>
Auto Play: One by One<span>
<label><input type="radio" name="ap" value='1' onchange="sendVal(event, this)"><span>All</span></label>
<label><input type="radio" name="ap" value='2' onchange="sendVal(event, this)"><span>Mono</span></label>
<label><input type="radio" name="ap" value='3' onchange="sendVal(event, this)"><span>Duo</span></label>
<label><input type="radio" name="ap" value='4' onchange="sendVal(event, this)"><span>Rainbow</span></label></span>
Auto Play: Random<span>
<label><input type="radio" name="ap" value='5' onchange="sendVal(event, this)"><span>All</span></label>
<label><input type="radio" name="ap" value='6' onchange="sendVal(event, this)"><span>Mono</span></label>
<label><input type="radio" name="ap" value='7' onchange="sendVal(event, this)"><span>Duo</span></label>
<label><input type="radio" name="ap" value='8' onchange="sendVal(event, this)"><span>Rainbow</span></label></span>
Next mode every <span>
<label><input type="radio" name="at" value='60'    onchange="sendVal(event, this)"><span>1min</span></label>
<label><input type="radio" name="at" value='900'   onchange="sendVal(event, this)"><span>15mins</span></label>
<label><input type="radio" name="at" value='1800'  onchange="sendVal(event, this)"><span>30mins</span></label>
<label><input type="radio" name="at" value='3600'  onchange="sendVal(event, this)"><span>1hrs</span></label>
<label><input type="radio" name="at" value='14400' onchange="sendVal(event, this)"><span>4hrs</span></label></span>
</div></div>
<div class='flex-col'>
<div class='form'>
<h4>Additional parameters</h4>
Direction<span>
<label><input type="radio" name="dr" value="r" onchange="sendVal(event, this)"><span>Reversed</span></label>
<label><input type="radio" name="dr" value="d" onchange="sendVal(event, this)"><span>Direct</span></label></span>
ELEMENT_SIZE<span>
<label><input type="radio" name="sz" value='0' onchange="sendVal(event, this)"><span>Small</span></label>
<label><input type="radio" name="sz" value='2' onchange="sendVal(event, this)"><span>Med</span></label>
<label><input type="radio" name="sz" value='4' onchange="sendVal(event, this)"><span>Large</span></label>
<label><input type="radio" name="sz" value='6' onchange="sendVal(event, this)"><span>XL</span></label></span>
FADE_RATE<span>
<label><input type="radio" name="fd" value= '16' onchange="sendVal(event, this)"><span>Faster</span></label>
<label><input type="radio" name="fd" value= '48' onchange="sendVal(event, this)"><span>Fast</span></label>
<label><input type="radio" name="fd" value= '64' onchange="sendVal(event, this)"><span>Med</span></label>
<label><input type="radio" name="fd" value= '80' onchange="sendVal(event, this)"><span>Slow</span></label>
<label><input type="radio" name="fd" value= '112' onchange="sendVal(event, this)"><span>Slower</span></label></span>
</div></div>
</div></div>
<div id="WiFi" class="tabcontent">
<h4>WiFi Settings</h4>
<div class='flex-row'>
<div class='flex-col'>
<div class="form"><h4>Now you are connected:</h4>{WR}</div>
</div>
<div class='flex-col'>
<div class="form"><h4>Scan for available networks:</h4>
<div id="wifilist">-> Scan for list <-
</div><br/>
<input type='button' value='Scan/Rescan' onclick="scanWiFi(event)"/>
</div></div>
<div class='flex-col'>
<form class='form' name='wifisave'><h4>Connect to network:</h4>
<input type='text' maxlength='32' placeholder='network' name='n'/>
<br/>
<input type='password' maxlength='64' placeholder='password' name='p'/>
<br/><br/>
<input type='button' value='Connect/Disconnect' onclick='sendWiFi(event)'></form>
</div></div></div>

<div id="GEM" class="tabcontent">
<h4> All Modes </h4>
<div class='flex-row'>
<ul id='allmodes' class='flex-row-wrap'>
{M0}
</ul>
</div></div>
<div id="About" class="tabcontent">
<div class='flex-row'>
<div class='flex-col'>
{AB}
</div></div>
</div></div>

<footer onclick="gem();">{FT}</footer>
</body>
</html>
)EOF";
