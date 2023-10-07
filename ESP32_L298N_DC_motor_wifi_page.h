const char motorControlHeader_1[]  PROGMEM = R"header1(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Rover</title>
    <style>
        * {
            box-sizing: border-box;
            text-align: center;
            font-size: medium;
            font-weight: bold;
        }
        .App {
            display: flex;
            margin-top: 100px;
            border: 10px solid black;
            height: 80vh;
            align-items: center;
            justify-content: center;
            border-radius: 40px;
        }
        button {
            all: unset;
            width: 100px;
            height: 30px;
            font-size: 16px;
            background: transparent;
            border: none;
            position: relative;
            color: #f0f0f0;
            cursor: pointer;
            z-index: 1;
            padding: 10px 20px;
            align-items: center;
            justify-content: center;
            white-space: nowrap;
            user-select: none;
            -webkit-user-select: none;
            touch-action: manipulation;
            margin: 10px;
        }
        button::after,
        button::before {
            content: '';
            position: absolute;
            bottom: 0;
            right: 0;
            z-index: -99999;
            transition: all .4s;
        }
        button::before {
            transform: translate(0%, 0%);
            width: 100%;
            height: 100%;
            background: #28282d;
            border-radius: 10px;
        }
        button::after {
            transform: translate(10px, 10px);
            width: 35px;
            height: 35px;
            background: #ffffff15;
            backdrop-filter: blur(5px);
            -webkit-backdrop-filter: blur(5px);
            border-radius: 50px;
        }
        button:hover::before {
            transform: translate(5%, 20%);
            width: 110%;
            height: 110%;
        }
        button:hover::after {
            border-radius: 10px;
            transform: translate(0, 0);
            width: 100%;
            height: 100%;
        }
        button:active::after {
            transition: 0s;
            transform: translate(0, 5%);
        }
        h1 {
            color: #333333;
            font-family: 'Bitter', serif;
            font-size: 40px;
            font-weight: normal;
            line-height: 54px;
            margin: 0 0 14px;
        }
        .motor1, .motor2 {
            background-color: rgb(255, 255, 255);
            border: 2px solid black;
            border-radius: 10px;
            width: 500px;
            height: 370px;
            margin: 10px;
            padding: 10px;
            text-align: center;
        }
        #rangeValue1, #rangeValue2 {
            position: relative;
            display: block;
            text-align: center;
            font-size: 6em;
            color: #999;
            font-weight: 400;
        }
        .range {
            width: 400px;
            height: 15px;
            -webkit-appearance: none;
            background: #111;
            outline: none;
            border-radius: 15px;
            overflow: hidden;
            box-shadow: inset 0 0 5px rgba(0, 0, 0, 1);
        }
        .range::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 15px;
            height: 15px;
            border-radius: 50%;
            background: #00fd0a;
            cursor: pointer;
            border: 4px solid #333;
            box-shadow: -407px 0 0 400px #00fd0a;
        }
    </style>
</head>
<body>
    <div class="App">
        <div class="motor1">
            <div class="Header">
                <h1>MOTOR 1 CONTROLS</h1>
                <div>
                    <span id="rangeValue1">0</span>
                    <input class="range" type="range" value="0" min="0" max="255" oninput = "rangeSlide(this.value, 'rangeValue1')">
                </div>
            </div>
            <div class="Footer">
                <h1>Direction</h1>
                <button id="dir1" onclick="changeDirection('dir1')">Clockwise</button>
                <button id="StartStop1" onclick="changeMovement('StartStop1')">Start</button>
            </div>
        </div>
        <div class="motor2">
            <div class="Header">
                <h1>MOTOR 2 CONTROLS</h1>
                <div>
                    <span id="rangeValue2">0</span>
                    <input class="range" type="range" value="0" min="0" max="255" oninput="rangeSlide(this.value, 'rangeValue2')">
                </div>
            </div>
            <div class="Footer">
                <h1>Direction</h1>
                <button id="dir2" onclick="changeDirection('dir2')">Clockwise</button>
                <button id="StartStop2" onclick="changeMovement('StartStop2')">Start</button>
            </div>
        </div>
    </div>
    <script type="text/javascript">
        function rangeSlide(value, id) {
            document.getElementById(id).textContent = value;
        }
        function changeDirection(buttonId){
            var button = document.getElementById(buttonId);
            if(button.innerHTML === "Clockwise") {
                button.innerHTML = "Anti-Clockwise";
            } else {
                button.innerHTML = "Clockwise";
            }
        }
        function changeMovement(buttonId){
            var button = document.getElementById(buttonId);
            if(button.innerHTML === "Start") {
                button.innerHTML = "Stop";
            } else {
                button.innerHTML = "Start";
            }
        }
    </script>
</body>
</html>
)header1";




////////////////for motor 1 part 1///////////////
const char motor1Control_p1[] PROGMEM = R"robojaxSpeed3(
<h2>Motor 1 Control</h2>
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/speed?do=m1slower">< Slower</a>
            </div>        

        </div><!--fixedCell -->


        <div class="progress_bar bar1">)robojaxSpeed3";


////////////////for motor 1 part 2///////////////
const char motor1Control_p2[] PROGMEM = R"robojaxSpeed4(%</strong></div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/speed?do=m1faster">Faster ></a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row -->


</div><!--table -->
<hr align="center" width="50%">
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/direction?dir=m1CCW">CCW</a>
            </div>        

        </div><!--fixedCell -->


        <div class="buttonsDiv">
            <a class="startStop" href="/stop?do=)robojaxSpeed4";
            
 ////////////////for motor 1 part 3///////////////           
const char motor1Control_p3[] PROGMEM = R"robojaxSpeed5(            
            </a>
        </div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/direction?dir=m1CW">CW</a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row - Robojax.com -->


</div><!-- ---- table motor 1 ended -->)robojaxSpeed5";

///////////////// motor 1 end******************************************
///////////////////////*************************************


////////////////for motor 2 part 1///////////////
const char motor2Control_p1[] PROGMEM = R"robojaxSpeed3(
<!-- ---- motor 2 started here ---- -->
<h2>Motor 2 Control</h2>

<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/speed?do=m2slower">< Slower</a>
            </div>        

        </div><!--fixedCell -->
        <div class="progress_bar bar2">)robojaxSpeed3";


////////////////for motor 2 part 2///////////////
const char motor2Control_p2[] PROGMEM = R"robojaxSpeed4(%</strong></div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/speed?do=m2faster">Faster ></a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row -->


</div><!--table -->
<hr align="center" width="50%">
<div class="table">
    <div class="row">
        <div class="fixedCell">
            <div class="nextprev">
            <a class="rj-left rj-btn" href="/direction?dir=m2CCW">CCW</a>
            </div>        

        </div><!--fixedCell -->
        <div class="buttonsDiv">
            <a class="startStop" href="/stop?do=)robojaxSpeed4";
            
 ////////////////for motor 2 part 3///////////////           
const char motor2Control_p3[] PROGMEM = R"robojaxSpeed5(            
            </a>
        </div> 

        <div class="fixedCell">
        
          <div class="nextprev">       
          <a class="rj-right rj-btn" href="/direction?dir=m2CW">CW</a>
          </div>       

        </div><!--fixedCell -->
    </div><!--row - Robojax.com -->


</div><!--table -->)robojaxSpeed5";

///////////////// motor one end******************************************
///////////////////////*************************************
