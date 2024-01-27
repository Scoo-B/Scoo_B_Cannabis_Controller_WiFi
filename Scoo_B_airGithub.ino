



//RelaySWITCHES
#define Relayswitch_1  12  
#define Relayswitch_2  13 

#define RELAYswitch_ON LOW
#define RELAYswitch_OFF HIGH


//----------------------------------------------------
//               FLAG MARKERS
//----------------------------------------------------
byte ExhaustFAN  = 0;              // exhaust fan flag
byte HI_Temp     = 0;              // exhaust fan flag
byte HI_Hum      = 0;              // exhaust fan flag
byte CO2_Vent    = 0;              // exhaust fan flag


//******************************************************
//              DHT11
//******************************************************
float f1;        //variable for min/MAX
float f1_MAX = 0;
float f1_min = 100;

float f_avg = 68; // average temp

float h1;        //variable for min/MAX
float h1_MAX = 0;
float h1_min = 100;

float h1_avg = 50; // average temp

float hi1;        //variable for min/MAX
float hi1_MAX = 0;
float hi1_min = 100;

float hi1_avg = 68; // average temp

float DewPoint = 0;
float DP = 0;

//******************************************************
//              DHT11_Calibration 
//******************************************************
//float Final_Temp = 50;

//uses a "+"... so use a negative number to "-"
int calibrationFactor_f = -5;   // DHT11  +/-number value
int calibrationFactor_h = -22;   // DHT11  +/-number value

//******************************************************
//                    VPD
//******************************************************
float Air_T  = 0.0;
float RH     = 0.0;
float Leaf_T = 0.0;

// F to C conversion
float Air_Tc  = 0.0;
float Leaf_Tc = 0.0;

float VPsat = 0.0;
float VPair = 0.0;
float VPD   = 0.0;

//******************************************************
//         SCD40 CO2 Sensor (IC2)(co2) [0x62]
//******************************************************

float CO2LVL = 400; 
float CO2LVL_min = 400;
float CO2LVL_MAX = 400;

float SCD40_co2 = 0;


void setup() {
  // put your setup code here, to run once:

}

void loop() {


 WiFiClient client = server.available();    // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();


// Display the HTML web page               // <== Start "header" of webpage ==<<<
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");

// refresh browser
client.println("<head><meta http-equiv=\"refresh\" content=\"300\">"); 
client.println("<link rel=\"icon\" href=\"data:,\">");

/*
//include jQuery
client.println("<script src=\"https://code.jquery.com/jquery-3.6.4.min.js\"></script>");          

//include Chart.js
client.println("<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>");  

//include JustGage
client.println("<script src=\"https://cdn.jsdelivr.net/gh/toorshia/justgaga@1.4.0/raphael-2.1.4.min.js\"></script>");          
client.println("<script src=\"https://cdn.jsdelivr.net/gh/toorshia/justgaga@1.4.0/justgage.js\"></script>");          
*/
             
// CSS to style 
client.println("<style>");
client.println("html { background-color: #4169E1; font-family: Lucida Console, monospace; display: inline-block; margin: 0px auto; text-align: center;}");
            
client.println(".button { background-color: #7CFC00; border: none; border-radius: 50%; color: white; padding: 50px;");
client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
client.println(".button2 {background-color: #f44336; border-radius: 50%;}");

client.println(".button6 {display: inline-block; padding: 40px; font-size: 24px; cursor: pointer; text-align: center; text-shadow: 3px 3px 7px  #000000; background-color: #fd0e03; border: none; border-radius: 50%; box-shadow: 0 9px #999;}");                                  
client.println(".button6:hover {background-color: #7CFC00}");
client.println(".button6:active {background-color: #7CFC10; box-shadow: 0 5px #666; transform: translateY(4px);}");

//Text/Fonts
client.println("h1 {text-shadow: 2px 2px 16px  #64f903;}");
client.println("h2 {text-shadow: 2px 2px 16px  #FF0000;}");
client.println("h3 {text-shadow: 2px 2px 16px  #0000FF;}");
client.println("h4 {text-shadow: 2px 2px 16px  #FFFF00;}");
client.println("h5 {text-shadow: 4px 4px 24px  #a3ff00;}");

client.println("p.main {text-align: center; text-shadow: 2px 2px 5px  #64f903; font-size: 25px;}");
client.println("p.minMAX {text-align: center; text-shadow: 2px 2px 5px  #f6fffc; font-size: 15px;}");
client.println("p.1 {text-align: center; text-shadow: 2px 2px 5px  #a3ff00; font-size: 30px;}");


//slider
client.println(".slidecontainer {margin: auto; width: 90%;}");
client.println(".slider {-webkit-appearance: none; margin: auto; width: 100%; height: 40px; background: yellow; border: 4px solid red; outline-style: solid; outline-color: black; outline-width: 5px; opacity: 0.7; -webkit-transition: .2s; transition: opacity .2s;}");
client.println(".slider:hover {opacity: 1;}");
client.println(".slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 40px; height: 40px; background: #7CFC00; cursor: pointer;}");
client.println(".slider::-moz-range-thumb {width: 40px; height: 40px; background: #7CFC10; cursor: pointer;}");

//slider 2
client.println(".slidecontainer2 {margin: auto; width: 90%;}");
client.println(".slider2 {-webkit-appearance: none; margin: auto; width: 100%; height: 40px; background: yellow; border: 4px solid red; outline-style: solid; outline-color: black; outline-width: 5px; opacity: 0.7; -webkit-transition: .2s; transition: opacity .2s;}");
client.println(".slider2:hover {opacity: 1;}");
client.println(".slider2::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 40px; height: 40px; background: #7CFC00; cursor: pointer;}");
client.println(".slider2::-moz-range-thumb {width: 40px; height: 40px; background: #7CFC10; cursor: pointer;}");

//columns 
client.println("{box-sizing: border-box;}");
/* Create three equal columns that floats next to each other */
client.println(".column {float: left; width: 47.00%; padding: 10px; height: 220px;}");
/* Clear floats after the columns */
client.println(".row:after {content: ""; display: table; clear: both;}");

//temp & hum Gage
//client.println("    #temperatureGauge, #humidityGauge { width: 200px; height: 200px; display: inline-block; margin: 10px; });");

client.println("</style>");

//sliders or buttons         
client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");          
                
client.println("</head>");



// Web Page Heading
client.println("<body>");                 // <== Start "body" of webpage ==<<<

client.println("<h1>Scoo_B's FLOWER ROOM Air Monitor</h1>");

/*
client.println("<div id=\"temperatureGauge\"></div>");                                    //////////////////HERE

// Initialize temperature gauge
client.println("<script>");
client.println("var temperatureValues = f1;"); // Example data for temperature
client.println("var temperatureGauge = new JustGage({ id: \"temperatureGauge\", value: temperatureValues[temperatureValues.length - 1], min: 0, max: 100, title: \"Temperature\", label: \"°F\" });");
client.println("</script>");


client.println("<div id=\"humidityGauge\"></div>");                                    //////////////////HERE

// Initialize humidity gauge
client.println("<script>");
client.println("var humidityValues = h1;"); // Example data for humidity
client.println("var humidityGauge = new JustGage({ id: \"humidityGauge\", value: humidityValues[humidityValues.length - 1], min: 0, max: 100, title: \"Humidity\", label: \"%\" });");
client.println("</script>");

//CHART
client.println("<canvas id=\"sensorChart\" width=\"400\" height=\"200\"></canvas>");

client.println("<script>");
// Sample data (replace this with your actual sensor readings)
client.println("var co2Values = SCD40_co2;"); // Example data for TDS
client.println("var vpdValues = VPD;"); // Example data for pH
client.println("var temperatureValues = f1;"); // Example data for temperature
client.println("var humidityValues = h1;"); // Example data for humidity

// Prepare data for the chart
client.println("var ctx = document.getElementById(\'sensorChart\').getContext(\'2d\');");
client.println("var myChart = new Chart(ctx, { type: \'line\', data: { labels: [\'Reading 1\', \'Reading 2\', \'Reading 3\', \'Reading 4\', \'Reading 5\'], datasets: [{ label: \'co2\', data: co2Values, borderColor: \'rgba(255, 99, 132, 1)\', borderWidth: 2, fill: false }, { label: \'VPD\', data: vpdValues, borderColor: \'rgba(54, 162, 235, 1)\', borderWidth: 2, fill: false }] }, options: { scales: { y: { beginAtZero: true } } } });");
client.println("</script>");
*/


client.println("<div class=\"row\">");
client.println("<div class=\"column\" style=\"background-color:#ddd;\">");

client.println("<h3>AIR Temperature</h3>");
client.println("<h3 style=\"font-size:300%;\">");
client.println(f1); 
client.println("*F");
client.println("</h3>");
//client.println("<br>");

  client.println("<p.minMAX>");
  client.println("min/MAX");
  client.println("<br>");
  client.println(f1_min);
  client.println("*F");
  client.println(" / ");
  client.println(f1_MAX);
  client.println("*F\t");
  client.println("</p.minMAX>");
  
client.println("</div>");

client.println("<div class=\"column\" style=\"background-color:#aaa;\">");

client.println("<h3>AIR Humidity</h3>");
client.println("<h3 style=\"font-size:300%;\">");
client.println(h1); 
client.println("%");
client.println("</h3>");
//client.println("<br>");

  client.println("<p.minMAX>");
  client.println("min/MAX");
  client.println("<br>");
  client.println(h1_min);
  client.println("%");
  client.println(" / ");
  client.println(h1_MAX);
  client.println("%\t");
  client.println("</p.minMAX>");
  
client.println("</div>");
client.println("</div>");

client.println("<div class=\"row\">");
client.println("<div class=\"column\" style=\"background-color:#aaa;\">");

client.println("<h2>VPD</h2>");
client.println("<h2 style=\"font-size:300%;\">");
client.println("<br>");
client.println(VPD); 
client.println("kPa");
client.println("</h2>");
client.println("<br>");

client.println("</div>");

client.println("<div class=\"column\" style=\"background-color:#ddd;\">");

client.println("<h1>co2 Monitor</h1>");

client.println("<h1 style=\"font-size:300%;\">");
client.println(SCD40_co2);
client.println("ppm");
client.println("</h1>");
client.println("<br>"); 

  client.println("<p.minMAX>");
  client.println("min/MAX");
  client.println("<br>");
  client.println(CO2LVL_min);
  client.println("ppm");
  client.println(" / ");
  client.println(CO2LVL_MAX);
  client.println("ppm\t");
  client.println("</p.minMAX>");

client.println("</div>");
client.println("</div>");


client.println("<div class=\"row\">");
client.println("<div class=\"column\" style=\"background-color:#ddd;\">");

client.println("<h4>DATE & TIME</h4>");  

client.println("<h4>");

DateTime now = rtc.now();

client.println(now.month(), DEC);
client.println("/");
client.println(now.day(), DEC);
client.println("/");      
client.println(now.year(), DEC);

client.println("<br>");
client.println("<br>");

client.println(daysOfTheWeek[now.dayOfTheWeek()]);

client.println("<br>");
client.println("<br>");


int hournow = 0;

if((now.hour()) >= 13){
  
hournow = ((now.hour()) - 12);

if(hournow == 0){
hournow = 12;
}

if((now.hour()) <= 0){
hournow = 12;
}


client.println(hournow);
}
else{
client.println(now.hour(), DEC);
}
client.println(":");
if(now.minute() < 10){
client.println("0");  
client.println(now.minute(), DEC); 
}
else{
client.println(now.minute(), DEC);
}
client.println(":");
if(now.second() < 10){
client.println("0");  
client.println(now.second(), DEC); 
}
else{
client.println(now.second(), DEC);
}

client.println("</h4>");

client.println("</div>");

client.println("<div class=\"column\" style=\"background-color:#aaa;\">");

client.println("<h4>AIR Dew Point</h4>");
client.println("<p.1>");
client.println(DP); 
client.println("*F");

client.println("<br>");

client.println("<h4>AIR Heat Index</h4>");
client.println("<p.1>");
client.println(hi1); 
client.println("*F");
client.println("</p.1>");
client.println("<br>");

client.println("</div>");
client.println("</div>");

client.println("<div class=\"row\">");
client.println("<div class=\"column\" style=\"background-color:#aaa;\">");

//_______/--------\________ 
//______  Button 1  _______
// web-button #1            
//client.println("<p><a href=\"/CO2_relay/on\"><button class=\"button button6\">CO2_relay</button></a></p>");

client.println("CO2 Relay");
 
client.println("<br>");

// Display current state, and ON/OFF buttons Relay_1
client.println("<p>Relayswitch_1 - State " + output1State + "</p>");
// If the output1State is off, it displays the ON button       
if (output1State=="off") {
client.println("<p><a href=\"/Relayswitch_1/off\"><button class=\"button\">ON</button></a></p>");
} else {
client.println("<p><a href=\"/Relayswitch_1/on\"><button class=\"button button2\">OFF</button></a></p>");
} 


client.println("</div>");

client.println("<div class=\"column\" style=\"background-color:#ddd;\">");


//_______/--------\________ 
//______  Button 2  _______
// web-button #2                
//client.println("<p><a href=\"/Exhaust/on\"><button class=\"button button6\">Exhaust</button></a></p>");

client.println("Exhaust Relay");
 
client.println("<br>");


// Display current state, and ON/OFF buttons Relay_2  
client.println("<p>Relayswitch_2 - State " + output2State + "</p>");
// If the output2State is off, it displays the ON button       
if (output2State=="off") {
client.println("<p><a href=\"/Relayswitch_2/off\"><button class=\"button\">ON</button></a></p>"); 
} else {
client.println("<p><a href=\"/Relayswitch_2/on\"><button class=\"button button2\">OFF</button></a></p>"); 
}



if(ExhaustFAN  == 1){
client.println("Exhaust ");
 
if(HI_Temp  == 1){
client.println("HI_Temp");
}
if(HI_Hum  == 1){
client.println("HI_Hum");
}
if(CO2_Vent  == 1){
client.println("CO2_Vent");
}
}else{
client.println("        ");
client.println("        ");
client.println("        ");
client.println("        ");
}

client.println("</div>");
client.println("</div>");

/*
client.println("<div class=\"row\">");
client.println("<div class=\"column\" style=\"background-color:#ddd;\">");


//_______/--------\________ 
//______  Button 3  _______
// web-button #3                
//client.println("<p><a href=\"/Exhaust/on\"><button class=\"button button6\">Exhaust</button></a></p>");

// Display current state, and ON/OFF buttons   
client.println("<p>VAC_Pressure - State " + output2State + "</p>");
// If the output2State is off, it displays the ON button       
if (output2State=="off") {
client.println("<p><a href=\"/VAC_Pressure/on\"><button class=\"button\">ON</button></a></p>");
} else {
client.println("<p><a href=\"/VAC_Pressure/off\"><button class=\"button button2\">OFF</button></a></p>");
}


client.println("</div>");
client.println("</div>");
*/


/*
//SLIDERS
//client.println("<p></p>");
client.println("<p class=\"main\">REVERSE = 0-90 |STOP| 90-180 = FORWARD</p>");
client.println("<p class=\"main\">FAST<-->SLOW |STOP| SLOW<-->FAST</p>");


//_________|Slider|__________
//---------------------------
client.println("<div class =\"slidecontainer\">");
client.println("<input type =\"range\" min = \"0\" max = \"180\" value=\"90\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");
client.println("<p>Value: <span id=\"servoPos\"></span></p>");
client.println("</div>");

client.println("<script>");
client.println("var slider = document.getElementById(\"servoSlider\");");
client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}");
client.println("</script>");


//________|Slider 2|_________
//---------------------------
client.println("<div class =\"slidecontainer2\">");
client.println("<input type =\"range\" min = \"0\" max = \"5000\" value=\"800\" class=\"slider2\" id=\"servoSlider2\" onchange=\"servo2(this2.value)\" value=\""+valueString2+"\"/>");
client.println("<p>fluxCapacitorDELAY: <span id=\"servoPos2\"></span></p>");
client.println("</div>");

client.println("<script>");
client.println("var slider2 = document.getElementById(\"servoSlider2\");");
client.println("var servoP2 = document.getElementById(\"servoPos2\"); servoP2.innerHTML = slider2.value;");
client.println("slider2.oninput = function() { slider2.value = this2.value; servoP2.innerHTML = this2.value; }");
client.println("$.ajaxSetup({timeout:1000}); function servo2(pos) { ");
client.println("$.get(\"/?value2=\" + pos + \"&\"); {Connection: close};}");
client.println("</script>");
*/


client.println("</body>");
client.println("</html>");   // <== end of webpage ==<<<






// Match the request, turns the GPIOs on and off 


//_______/--------\________ 
//______  Button 1  _______

            // turns the GPIOs on and off Relay_1
            if (header.indexOf("GET /Relayswitch_1/on") >= 0) {
              Serial.println("CO2_relay on");
              output1State = "off";
              digitalWrite(Relayswitch_1, RELAYswitch_ON);
            } 
            if (header.indexOf("GET /Relayswitch_1/off") >= 0) {
              Serial.println("CO2_relay off");
              output1State = "on";
              digitalWrite(Relayswitch_1, RELAYswitch_OFF);
            } 


//_______/--------\________              
//______  Button 2  _______ 
            
            if (header.indexOf("GET /Relayswitch_2/on") >= 0) {
              Serial.println("Exhaust on");
              output2State = "off";
              digitalWrite(Relayswitch_2, RELAYswitch_ON);
              ExhaustFAN = 1;
            } 
            if (header.indexOf("GET /Relayswitch_2/off") >= 0) {
              Serial.println("Exhaust off");
              output2State = "on";
              digitalWrite(Relayswitch_2, RELAYswitch_OFF);
              ExhaustFAN = 0;
              CO2_Vent   = 0;
              HI_Temp    = 0;
              HI_Hum     = 0;
            }





/*
//_______/--------\________              
//______  Button 3  _______ 
            
              if (header.indexOf("GET /VAC_Pressure/on") >= 0) {
              Serial.println("VAC_Pressure on");
              output2State = "off";
              digitalWrite(Relayswitch_2, LOW);
              VACPressure = 1;
              ExhaustFAN  = 1;
              NegPresure  = 1;
            } else if (header.indexOf("GET /VAC_Pressure/off") >= 0) {
              Serial.println("VAC_Pressure off");
              output2State = "on";
              digitalWrite(Relayswitch_2, HIGH);
              VACPressure = 0;
              ExhaustFAN  = 0;
              NegPresure  = 0;
            }
*/            

/*
//_________|Slider|__________
//---------------------------
//GET /?value=180& HTTP/1.1
if(header.indexOf("GET /?value=")>=0) {
   pos1 = header.indexOf('=');
   pos2 = header.indexOf('&');
   valueString = header.substring(pos1+1, pos2);
              
//Rotate the servo
   AUGER.attach(0);
   MIXER.attach(2);
   AUGER.write(valueString.toInt());
   MIXER.write(valueString.toInt());
   Serial.print("SpeedPOS");
   Serial.println(valueString); 
} 


//________|Slider 2|_________
//---------------------------
//GET /?value=180& HTTP/1.1
if(header.indexOf("GET /?value2=")>=0) {
   pos3 = header.indexOf('=');
   pos4 = header.indexOf('&');
   valueString2 = header.substring(pos3+1, pos4);
              
//Rotate the servo
   fluxCapacitorDELAY = (valueString2.toInt());
   Serial.print("fluxCapacitorDELAY = ");
   Serial.println(valueString2); 
}
*/


            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
      
    }
    // Clear the header variable
    header = "";
    client.flush();
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");      // The HTTP response ends with another blank line

  }





}
