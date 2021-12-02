// =====================
//HTML code for webpage
//=====================
const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE HTML>
<html>
<head>
  <title>Convolution Integral PTE.LTD.</title>
</head>
<!-------------------------------C S S------------------------------>
<style>
  #btn
  {
    display: inline-block;
    text-decoration: none;
    background: #8CD460;
    color: rgba(255,255,255, 0.80);
    font-weight: bold;
    font: 60px arial, sans-serif;
    width: 150px;
    height: 150px;
    line-height: 150px;
    border-radius: 50%;
    text-align: center;
    vertical-align: middle;
    overflow: hidden;
    box-shadow: 0px 0px 0px 8px #8CD460;
    border: solid 2px rgba(255,255,255, 0.47);
    transition: 0.5s;
  }
  body {text-align:center; font-family:"Calibri"; background-color:rgba(0, 3, 8, 0.26)}
  h1   {color: rgba(0, 0, 255, 0.87); font-size: 50px;}
</style>
<!------------------------------H T M L----------------------------->
<body>
   <h1>Convolution Integral PTE.LTD.  <br>Smooking Machine  2021</h1>
   Volume  <span id="volume_output">50</span> (ml) 
        <input type="range" min="0" max="100" value="50" class="slider" id="volume" onchange="onVolume()">
        <br><p>
   Push time <span id="push_output">3</span> (s) 
        <input type="range" min="3" max="8" value="3" class="slider" id="push_time" onchange="onPush()">
        <br><p>
   sleep_time <span id="sleep_output">50</span> (s) 
        <input type="range" min="0" max="100" value="50" class="slider" id="sleep_time" onchange="onSleep()">
        <br><p><p>
   <a href="#" id="btnOnOff" ONCLICK='btn_OnOff()'> On-Off</a>
   <a href="#" id="btnPause" ONCLICK='btn_Pause()'> Pause </a>
   <a href="#" id="btnReset" ONCLICK='btn_Reset()'> Reset </a>
<!-----------------------------JavaScript--------------------------->
  <script>
     
     InitWebSocket()
     function InitWebSocket()
     {
       websock = new WebSocket('ws://'+window.location.hostname+':81/'); 
       websock.onmessage = function(evt)
       {
          JSONobj = JSON.parse(evt.data);
          document.getElementById('btnOnOff').innerHTML = JSONobj.LEDonoff;
          if(JSONobj.LEDonoff == 'ON')
          {
            document.getElementById('btnOnOff').style.background='#FF0000';
            document.getElementById('btnOnOff').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }
          else
          {
            document.getElementById('btnOnOff').style.background='#111111';
            document.getElementById('btnOnOff').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }
       }
     }
     //-------------------------------------------------------------


    function onVolume(){
        output = document.getElementById("volume_output");
        output.innerHTML = document.getElementById("volume").value;
    }
    function onPush(){
        output = document.getElementById("push_output");
        output.innerHTML = document.getElementById("push_time").value;
    }
    function onSleep(){
        output = document.getElementById("sleep_output");
        output.innerHTML = document.getElementById("sleep_time").value;
    }
     function btn_OnOff()
     {
        payload = 'LEDonoff=ON';
        if(document.getElementById('btnOnOff').innerHTML == 'ON')
        {
            payload = 'LEDonoff=OFF';
        }
        websock.send(payload);
     }

     function btn_Pause()
     {
        payload = 'LEDonoff=ON';
        if(document.getElementById('btnOnOff').innerHTML == 'ON')
        {
            payload = 'LEDonoff=OFF';
        }
        websock.send(payload);
     }

     function btn_Reset()
     {
        payload = 'LEDonoff=ON';
        if(document.getElementById('btnOnOff').innerHTML == 'ON')
        {
            payload = 'LEDonoff=OFF';
        }
        websock.send(payload);
     }
  </script>
</body>
</html>
)=====";