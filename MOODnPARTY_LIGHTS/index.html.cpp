#include <pgmspace.h>

char index_html[] PROGMEM = R"EOF(
<!DOCTYPE html>
<html lang='en' dir='ltr'>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>
<meta name='viewport' content='width=device-width, initial-scale=1.0'/>    
<link rel="icon" type="image/svg+xml" href="data:image/svg+xml,%3Csvg width='64' height='64' viewBox='-1 -1 18 18' fill='none' xmlns='http://www.w3.org/2000/svg'%3E%3Ccircle style='stroke:%23000' cx='8' cy='8' r='8'/%3E%3Cpath d='M8 8h8c0-1.5-.4-2.8-1.1-4L8 8z' fill='%23F5AC43'/%3E%3Cpath d='m8 8-6.9 4c.7 1.2 1.7 2.2 2.9 2.9L8 8z' fill='%23515EBB'/%3E%3Cpath d='M8 8v8c1.5 0 2.8-.4 4-1.1L8 8z' fill='%23D0449A'/%3E%3Cpath d='M4 14.9c1.2.7 2.5 1.1 4 1.1V8l-4 6.9z' fill='%237C39B1'/%3E%3Cpath d='M14.9 4c-.7-1.2-1.7-2.2-2.9-2.9L8 8l6.9-4z' fill='%23F8CE33'/%3E%3Cpath d='M8 8H0c0 1.5.4 2.8 1.1 4L8 8z' fill='%23177AC3'/%3E%3Cpath d='m8 8 4 6.9c1.2-.7 2.2-1.7 2.9-2.9L8 8z' fill='%23FE4A29'/%3E%3Cpath d='m8 8 6.9 4c.7-1.2 1.1-2.5 1.1-4H8z' fill='%23F97932'/%3E%3Cpath d='M8 8 1.1 4C.4 5.2 0 6.5 0 8h8z' fill='%231AB3D0'/%3E%3Cpath d='m8 8 4-6.9C10.8.4 9.5 0 8 0v8z' fill='%23FCF222'/%3E%3Cpath d='M8 0C6.5 0 5.2.4 4 1.1L8 8V0z' fill='%2389D31C'/%3E%3Cpath d='M8 8 4 1.1C2.8 1.8 1.8 2.8 1.1 4L8 8z' fill='%2333B634'/%3E%3Ccircle style='stroke:%23fff;fill:%231976ff;paint-order:stroke' cx='8' cy='8' r='3'/%3E%3C/svg%3E"/>
<title>{TT}</title>
<script>const param = {PM};</script>
<style>#colorDot0{background-color: #{C0};}#colorDot2{background-color: #{C2};}</style>
<script type='text/javascript' src='main.js'></script>
<link href='style.css' rel="stylesheet"/>
</head>
<body>
{HD}
<div class="tab">
<button class="tablinks" onclick="openTab(event, 'Colors')" id="defaultTab">Colors</button>
<button class="tablinks" onclick="openTab(event, 'Monomode')" >MonoColor</button>
<button class="tablinks" onclick="openTab(event, 'Duomode')">DuoColor</button>
<button class="tablinks" onclick="openTab(event, 'RGBMode')">RainbowColor</button>
<button class="tablinks" onclick="openTab(event, 'SpecMode')">SpecModes</button>
<button class="tablinks" onclick="openTab(event, 'Controls')">Controls</button>
<button class="tablinks last" onclick="openTab(event, 'About')">About</button>
<button class="tablinks last" onclick="openTab(event, 'Settings')">Settings</button>
<button class="tablinks last" onclick="openTab(event, 'WiFi')">WiFi</button>
<button class="tablinks last" onclick="openTab(event, 'GEM')" id="gem">&#x1F48E</button>
</div>

<!--Tab content-->
<div id="Colors" class="tabcontent">
<h3>Colors</h3>
<div class='flex-row'>
<div class='flex-col'>
<label class='txt' for="color0">Main color:</label>
<div class="donutbox">
<canvas id='donut1' width='280' height='280' onclick="onDonut(event, this, '0')"></canvas>
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
<label><input type="radio" name="of" value='0' onchange="sendVal(event, this)"><div>Off</div></label>
<label><input type="radio" name="of" value='1' onchange="sendVal(event, this)"><div>On</div></label></span>
Brightness<span>                                                             
<label><input type="radio" name="br" value='8'   onchange="sendVal(event, this)"><div>Min</div></label>
<label><input type="radio" name="br" value='32'  onchange="sendVal(event, this)"><div>Less</div></label>
<label><input type="radio" name="br" value='64'  onchange="sendVal(event, this)"><div>Norm</div></label>
<label><input type="radio" name="br" value='128' onchange="sendVal(event, this)"><div>More</div></label>
<label><input type="radio" name="br" value='255' onchange="sendVal(event, this)"><div>Max</div></label></span>
Display speed<span>                                                          
<label><input type="radio" name="ds" value='4000' onchange="sendVal(event, this)"><div>Slower</div></label>
<label><input type="radio" name="ds" value='2000' onchange="sendVal(event, this)"><div>Slow  </div></label>
<label><input type="radio" name="ds" value='1000' onchange="sendVal(event, this)"><div>Norm  </div></label>
<label><input type="radio" name="ds" value='500' onchange="sendVal(event, this)" ><div>Fast  </div></label>
<label><input type="radio" name="ds" value='100' onchange="sendVal(event, this)" ><div>Faster</div></label></span>
</div></div>                                                                 
<div class='flex-col'>                                                       
<div class='form'>                                                           
<h4>Autoplay</h4>                                                            
Auto Play: One by One<span>                                                  
<label><input type="radio" name="ap" value='1' onchange="sendVal(event, this)"><div>All</div></label>
<label><input type="radio" name="ap" value='2' onchange="sendVal(event, this)"><div>Mono</div></label>
<label><input type="radio" name="ap" value='3' onchange="sendVal(event, this)"><div>Duo</div></label>
<label><input type="radio" name="ap" value='4' onchange="sendVal(event, this)"><div>Rainbow</div></label></span>
Auto Play: Random<span>                                                      
<label><input type="radio" name="ap" value='5' onchange="sendVal(event, this)"><div>All</div></label>
<label><input type="radio" name="ap" value='6' onchange="sendVal(event, this)"><div>Mono</div></label>
<label><input type="radio" name="ap" value='7' onchange="sendVal(event, this)"><div>Duo</div></label>
<label><input type="radio" name="ap" value='8' onchange="sendVal(event, this)"><div>Rainbow</div></label></span>
Next mode every <span>                                                       
<label><input type="radio" name="at" value='60'    onchange="sendVal(event, this)"><div>1min</div></label>
<label><input type="radio" name="at" value='900'   onchange="sendVal(event, this)"><div>15mins</div></label>
<label><input type="radio" name="at" value='1800'  onchange="sendVal(event, this)"><div>30mins</div></label>
<label><input type="radio" name="at" value='3600'  onchange="sendVal(event, this)"><div>1hrs</div></label>
<label><input type="radio" name="at" value='14400' onchange="sendVal(event, this)"><div>4hrs</div></label></span>
</div></div>                                                                 
<div class='flex-col'>                                                       
<div class='form'>                                                           
<h4>Additional parameters</h4>                                               
Direction<span>                                                              
<label><input type="radio" name="dr" value="r" onchange="sendVal(event, this)"><div>Reversed</div></label>
<label><input type="radio" name="dr" value="d" onchange="sendVal(event, this)"><div>Direct</div></label></span>
ELEMENT_SIZE<span>                                                           
<label><input type="radio" name="sz" value='0' onchange="sendVal(event, this)"><div>Small</div></label>
<label><input type="radio" name="sz" value='2' onchange="sendVal(event, this)"><div>Med</div></label>
<label><input type="radio" name="sz" value='4' onchange="sendVal(event, this)"><div>Large</div></label>
<label><input type="radio" name="sz" value='6' onchange="sendVal(event, this)"><div>XL</div></label></span>
FADE_RATE<span>                                                              
<label><input type="radio" name="fd" value= '16' onchange="sendVal(event, this)"><div>Faster</div></label>
<label><input type="radio" name="fd" value= '48' onchange="sendVal(event, this)"><div>Fast</div></label>
<label><input type="radio" name="fd" value= '64' onchange="sendVal(event, this)"><div>Med</div></label>
<label><input type="radio" name="fd" value= '80' onchange="sendVal(event, this)"><div>Slow</div></label>
<label><input type="radio" name="fd" value= '112' onchange="sendVal(event, this)"><div>Slower</div></label></span>
</div></div>
</div></div>

<div id="WiFi" class="tabcontent">
<h4>WiFi Settings</h4>
<div class='flex-row'>
<div class='flex-col'>
<div class="form"><h4>Now you are connected:</h4>{WR}
</div>
</div>
<div class='flex-col'>
<div class="form"><h4>Scan for available networks:</h4>
<div id="wifilist">-> Scan for list <-
</div><br/>
<input type='button' value='Scan/Rescan' onclick="scanWiFi(event)"/>
</div></div>
<div class='flex-col'>
<form class="form" id="wifisave"><h4>Connect to network:</h4><span class="txt-cont"><svg xmlns="http://www.w3.org/2000/svg" class="svg_icon" viewBox="0 0 16 16">
<path d="M15.384 6.115a.485.485 0 0 0-.047-.736A12.444 12.444 0 0 0 8 3C5.259 3 2.723 3.882.663 5.379a.485.485 0 0 0-.048.736.518.518 0 0 0 .668.05A11.448 11.448 0 0 1 8 4c2.507 0 4.827.802 6.716 2.164.205.148.49.13.668-.049z"></path>
<path d="M13.229 8.271a.482.482 0 0 0-.063-.745A9.455 9.455 0 0 0 8 6c-1.905 0-3.68.56-5.166 1.526a.48.48 0 0 0-.063.745.525.525 0 0 0 .652.065A8.46 8.46 0 0 1 8 7a8.46 8.46 0 0 1 4.576 1.336c.206.132.48.108.653-.065zm-2.183 2.183c.226-.226.185-.605-.1-.75A6.473 6.473 0 0 0 8 9c-1.06 0-2.062.254-2.946.704-.285.145-.326.524-.1.75l.015.015c.16.16.407.19.611.09A5.478 5.478 0 0 1 8 10c.868 0 1.69.201 2.42.56.203.1.45.07.61-.091l.016-.015zM9.06 12.44c.196-.196.198-.52-.04-.66A1.99 1.99 0 0 0 8 11.5a1.99 1.99 0 0 0-1.02.28c-.238.14-.236.464-.04.66l.706.706a.5.5 0 0 0 .707 0l.707-.707z"></path>
</svg>
<input id="n" name="n" type="text" maxlength="32" placeholder="network"></span>
<span class="txt-cont" id="pf">
<svg xmlns="http://www.w3.org/2000/svg" class="svg_icon" viewBox="0 0 16 16">
<path d="M5.5 5a.5.5 0 0 0 0 1h5a.5.5 0 0 0 0-1h-5Zm0 2a.5.5 0 0 0 0 1h3a.5.5 0 0 0 0-1h-3Z"></path>
<path d="M8 2a2 2 0 0 0 2-2h2.5A1.5 1.5 0 0 1 14 1.5v13a1.5 1.5 0 0 1-1.5 1.5h-9A1.5 1.5 0 0 1 2 14.5v-13A1.5 1.5 0 0 1 3.5 0H6a2 2 0 0 0 2 2Zm0 1a3.001 3.001 0 0 1-2.83-2H3.5a.5.5 0 0 0-.5.5v13a.5.5 0 0 0 .5.5h9a.5.5 0 0 0 .5-.5v-13a.5.5 0 0 0-.5-.5h-1.67A3.001 3.001 0 0 1 8 3Z"></path>
</svg>
<input id="p" name="p" type="password" maxlength="64" placeholder="password"></span>

<br><input id="pwbt" type="button" value="Connect/Disconnect" onclick="sendWiFi(event)"></form>
</div></div></div>

<div id="Settings" class="tabcontent">
<h4> Settings </h4>
<div class='flex-row'><div class='flex-col'>
<form class='form'>
<h4>Hardware</h4>
<span class="txt">Number of LEDs
<input type="number" name="sn" value='{SN}' min='5' max="1024" onchange="sendVal(event, this)">
</span>
<span class="txt">Port pin
<input type="number" name="sp" value='{SP}' min='0' max='16' onchange="sendVal(event, this)">
</span>
<span class="txt">Type of LEDs
<select name="st" onchange="sendVal(event, this)">
  <option value="6">NEO_RGB</option>
  <option value="9">NEO_RBG</option>
  <option value="82" selected>NEO_GRB</option>
  <option value="161">NEO_GBR</option>
  <option value="88">NEO_BRG</option>
  <option value="164">NEO_BGR</option>
</select>
</span>
<button type='reset'>Reset</button>
<input type='button' name='sb' value='Save' onclick="sendCmd('sst')"/>
</form></div>
<div class='flex-col'>
<form class='form' id="apsave">
<h4>Self WiFi (SP)</h4>
<span class="txt-cont"><svg xmlns="http://www.w3.org/2000/svg" class="svg_icon" viewBox="0 0 16 16">
<path d="M15.384 6.115a.485.485 0 0 0-.047-.736A12.444 12.444 0 0 0 8 3C5.259 3 2.723 3.882.663 5.379a.485.485 0 0 0-.048.736.518.518 0 0 0 .668.05A11.448 11.448 0 0 1 8 4c2.507 0 4.827.802 6.716 2.164.205.148.49.13.668-.049z"></path>
<path d="M13.229 8.271a.482.482 0 0 0-.063-.745A9.455 9.455 0 0 0 8 6c-1.905 0-3.68.56-5.166 1.526a.48.48 0 0 0-.063.745.525.525 0 0 0 .652.065A8.46 8.46 0 0 1 8 7a8.46 8.46 0 0 1 4.576 1.336c.206.132.48.108.653-.065zm-2.183 2.183c.226-.226.185-.605-.1-.75A6.473 6.473 0 0 0 8 9c-1.06 0-2.062.254-2.946.704-.285.145-.326.524-.1.75l.015.015c.16.16.407.19.611.09A5.478 5.478 0 0 1 8 10c.868 0 1.69.201 2.42.56.203.1.45.07.61-.091l.016-.015zM9.06 12.44c.196-.196.198-.52-.04-.66A1.99 1.99 0 0 0 8 11.5a1.99 1.99 0 0 0-1.02.28c-.238.14-.236.464-.04.66l.706.706a.5.5 0 0 0 .707 0l.707-.707z"></path>
</svg>
    <input id="an" name="an" type="text" maxlength="20" placeholder="network"></span>
<script type="text/javascript">document.getElementById("an").value = "{AN}" </script>
<span class="txt-cont" id="p">
<svg xmlns="http://www.w3.org/2000/svg" class="svg_icon" viewBox="0 0 16 16">
<path d="M5.5 5a.5.5 0 0 0 0 1h5a.5.5 0 0 0 0-1h-5Zm0 2a.5.5 0 0 0 0 1h3a.5.5 0 0 0 0-1h-3Z"></path>
<path d="M8 2a2 2 0 0 0 2-2h2.5A1.5 1.5 0 0 1 14 1.5v13a1.5 1.5 0 0 1-1.5 1.5h-9A1.5 1.5 0 0 1 2 14.5v-13A1.5 1.5 0 0 1 3.5 0H6a2 2 0 0 0 2 2Zm0 1a3.001 3.001 0 0 1-2.83-2H3.5a.5.5 0 0 0-.5.5v13a.5.5 0 0 0 .5.5h9a.5.5 0 0 0 .5-.5v-13a.5.5 0 0 0-.5-.5h-1.67A3.001 3.001 0 0 1 8 3Z"></path>
</svg>
    <input id="ap" name="ap" type="password" autocomplete="current-password" maxlength="20" placeholder="password"></span>
    <input type='button' value='Save' onclick="sendApWiFi(event)"/>
</form></div>
<div class='flex-col'>
<form class='form'>
<h4>Restart</h4>
<input type='button' value='Restart Now' onclick="sendCmd('restart');setTimeout(() => {window.location.reload();}, 1000);"/>
</form></div>
</div></div>

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
