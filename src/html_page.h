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
   <h2>Total Volume: <span id = "total_volume">0</span><p>
    Total counter: <span id = "total_count">0</span><p></p></p></h2>

   Volume  <span id="volume_output">50</span> (ml) 
        <input type="range" min="0" max="100" value="50" class="slider" id="volume" onchange="onVolume()">
        <br><p>
   Push time <span id="push_output">3</span> (s) 
        <input type="range" min="3" max="8" value="3" class="slider" id="push_time" onchange="onPush()">
        <br><p>
   sleep_time <span id="sleep_output">50</span> (s) 
        <input type="range" min="0" max="100" value="50" class="slider" id="sleep_time" onchange="onSleep()">
        <br><p><p>
    <br><p><p>
    <a href="#" id="btnOnOff" ONCLICK='btn_OnOff()'> On-Off</a>
    <a href="#" id="btnPause" ONCLICK='btn_Pause()'> Pause </a>
    <a href="#" id="btnReset" ONCLICK='btn_Reset()'> Reset </a>

<!-----------------------------JavaScript--------------------------->
  <script>
     var first_load = true;
     InitWebSocket()
     function InitWebSocket()
     {
       websock = new WebSocket('ws://'+window.location.hostname+':81/'); 
       websock.onmessage = function(evt)
       {
          JSONobj = JSON.parse(evt.data);
          document.getElementById('btnOnOff').innerHTML = JSONobj.varOnOff;
          if(JSONobj.varOnOff == 'ON'){
            document.getElementById('btnOnOff').style.background='#FF0000';
            document.getElementById('btnOnOff').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }else{
            document.getElementById('btnOnOff').style.background='#111111';
            document.getElementById('btnOnOff').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }

          document.getElementById('btnPause').innerHTML = JSONobj.varPause;
          if(JSONobj.varPause == 'ON'){
            document.getElementById('btnPause').style.background='#FF0000';
            document.getElementById('btnPause').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }else{
            document.getElementById('btnPause').style.background='#111111';
            document.getElementById('btnPause').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }

          document.getElementById('btnReset').innerHTML = JSONobj.varReset;
          if(JSONobj.varReset == 'ON'){
            document.getElementById('btnReset').style.background='#FF0000';
            document.getElementById('btnReset').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }else{
            document.getElementById('btnReset').style.background='#111111';
            document.getElementById('btnOnOff').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }
          
          document.getElementById('total_volume').innerHTML = JSONobj.var_total_volume;
          document.getElementById('total_count').innerHTML = JSONobj.var_total_count;
          if (first_load){
            first_load = false;
            document.getElementById('volume').value = JSONobj.var_volume;
            document.getElementById('volume_output').innerHTML = JSONobj.var_volume;
            document.getElementById('push_time').value = JSONobj.var_push_time;
            document.getElementById('push_output').innerHTML = JSONobj.var_push_time;
            document.getElementById('sleep_time').value = JSONobj.var_sleep_time;
            docement.getElementById('sleep_output').innerHTML = JSONobj.var_sleep_time;
          }
       }
     }
     //-------------------------------------------------------------


    function onVolume(){
        output = document.getElementById("volume_output");
        output.innerHTML = document.getElementById("volume").value;
        payload = "var_volume=" + output.innerHTML;
        websock.send(payload);
    }
    function onPush(){
        output = document.getElementById("push_output");
        output.innerHTML = document.getElementById("push_time").value;
        payload = "var_push_time=" + output.innerHTML;
        websock.send(payload);
    }
    function onSleep(){
        output = document.getElementById("sleep_output");
        output.innerHTML = document.getElementById("sleep_time").value;
        payload = "var_sleep_time=" + output.innerHTML;
        websock.send(payload);
    }
     function btn_OnOff()
     {
        payload = 'varOnOff=ON';
        if(document.getElementById('btnOnOff').innerHTML == 'ON'){
            payload = 'varOnOff=OFF';
        }
        websock.send(payload);
     }

     function btn_Pause()
     {
        payload = 'varPause=Paused';
        if(document.getElementById('btnPause').innerHTML == 'Paused')
        {
            payload = 'varPause=Going';
        }
        websock.send(payload);
     }

     function btn_Reset()
     {
        payload = 'varReset=Reset';
        websock.send(payload);
     }
  </script>
</body>
</html>
)=====";
