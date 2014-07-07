////////////////////////////////////////////////////////////////////////////////
////////////  Andy Wilson and Sebastian Martinez  //////////////////////////////
////////////  Based on NU32v2_stripchart by Nick Marchuk   /////////////////////
////////////  Monkeybot Plotting Application   /////////////////////////////////
////////////  May 2011 /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// serial library
import processing.serial.*; 
Serial myPort; 
float x = 100;
float y = 100;
float segLength = 75;
// buttons and labels
TextButtons[] serialButtons;
TextButtons Start;
TextButtons Stop;
Mag1Buttons Mag1ON;
Mag1Buttons Mag1OFF;
Mag2Buttons Mag2ON;
Mag2Buttons Mag2OFF;
PFont bigfont, smallfont, divfont;
String serialPortLabel, sentLabel, gotLabel;
int number_serial_buttons;

// boolean controls for program control
boolean SerialOK;
boolean StartOK;
boolean Mag1_ON;
boolean Mag2_ON;
boolean starterror;

int delay1;
int delay2;
int delay3;

int plotOK=0;

// plot buffers
int[] buffA = new int[1000];
int[] buffB = new int[1000];
int[] buffC = new int[1000];
int[] buffD = new int[1000];
int[] buffE = new int[1000];
int[] buffF = new int[1000];
int[] buffG= new int[1000];
int rollingIndex;

int angle1 = 0;
int angle2 = 0;

//////////////////////////////////////////////////////////////////////////////////////
////////////  setup  /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  size(1030, 762);
  background(230, 230, 230);
  smooth();
  frameRate(30);

  bigfont = loadFont("Gisha-Bold-24.vlw"); 
  smallfont = loadFont("Gisha-Bold-16.vlw");
  divfont = loadFont("Gisha-Bold-8.vlw");

  SerialOK = false;
  StartOK = false;
  starterror = false;
  Mag1_ON = false;
  Mag2_ON = false;

  serialPortLabel = "No serial port selected, select from 'Serial Ports'";
  sentLabel = "Sent: ";
  gotLabel = "Got: ";

  // serial
  println(Serial.list());
  number_serial_buttons = Serial.list().length;
  serialButtons = new TextButtons[number_serial_buttons];
  int index_serial = 0;
  for (index_serial = 0; index_serial < number_serial_buttons; index_serial++) {
    serialButtons[index_serial] = new TextButtons(50,50+index_serial*40,165,35,bigfont,Serial.list()[index_serial],"normal"); // x,y,w,h,font,text
  }

  Mag1ON = new Mag1Buttons(750,195,55,35,bigfont,"ON","green");
  Mag1OFF = new Mag1Buttons(820,195,55,35,bigfont,"OFF","red");
  Mag2ON = new Mag2Buttons(750,295,55,35,bigfont,"ON","green");
  Mag2OFF = new Mag2Buttons(820,295,55,35,bigfont,"OFF","red");
  Start = new TextButtons(720, 395, 90,35,bigfont,"  Start","normal");
  Stop = new TextButtons(875, 698, 80,35,bigfont," STOP","red");

  for (int i = 0; i < 1000; i++) {
    buffA[i] = 0;
    buffB[i] = 3;
    buffC[i] = 0;
    buffD[i] = 3;
    buffE[i] = 0;
    buffF[i] = 3;
  }

  rollingIndex = 0;
}

//////////////////////////////////////////////////////////////////////////////////////
////////////  draw  //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void draw()
{   
  int i = 0;
  int index = 0;
  int plot = 0;
  background(230, 230, 230);

  // status background and text
  fill(255);
  rect(10,682,1000,65);
  fill(0);
  textFont(smallfont);
  text("Status",15,697);

  // status label
  if (SerialOK && StartOK) {
    fill(15,190,30);
    text(serialPortLabel,15,712); // serial port
    fill(0);
 //   text(sentLabel,15,730); // what has been sent
 //   text(gotLabel,15,745); // what has been sent

  }
  else if (SerialOK)
  {
    fill(15,190,30);
    text(serialPortLabel,15,712); // serial port
  }
  else
  {
    fill(165,5,5);
    text(serialPortLabel,15,712); // serial port
  }

  // serial buttons
  if (!SerialOK) {
    fill(255);
    rect(45,15,175,35+number_serial_buttons*40); 
    fill(0);
    textFont(smallfont);
    text("Serial Ports",55,40);
    for (index = 0; index < number_serial_buttons; index++) {
      serialButtons[index].update();
      serialButtons[index].display();
    }
    textFont(smallfont);
    fill(0);
    text("Welcome to the Monkeybot Plotting Tool",255,40);

    text("This tool runs the Monkeybot and plots on-board sensor data during the run.",255,90);
    text("",255,115);
    //115
    text("Delay values can be changed using keyboard shortcuts",255,140);
    text("The Monkeybot is started by first enabling both magnets, then pressing Start",255,190);
    // 215
    text("A swing right or left can be executed using the keyboard shortcuts",255,240);

    // 440
    text("Select your COM port on the left to begin.",255,365);
  }
  else {
    
     fill(0);
     textFont(smallfont);
     text("Delay 1:", 300, 710);
     text("Delay 2:", 450, 710);
     text("Delay 3:", 600, 710);
     text(delay1, 380,710);
     text(delay2, 530,710);
     text(delay3, 680,710);
     
     text("Swing Left: Q | Swing Right: W | Delay 1 +O -P | Delay 2 +K -L | Delay 3 +N -M",220,735);
    
    
    
    if(!StartOK) {
    
       fill(255);
       rect(600,100,300,400);  
       
       rect(150,100,300,400);  
       
       fill(0);
       textFont(bigfont);
       text("Monkeybot Control", 640, 150);
       text("Current Position", 200, 150);
       
       fill(200,200,200);
       rect(330,225,60,30); 
       rect(330,275,60,30); 
       
       fill(0);
       text("Angle 1:", 200, 250);
       text("Angle 2:", 200, 300);
       text(angle1, 340,250);
       text(angle2, 340,300);
          
      textFont(smallfont);
      text("Magnet 1:", 650,220);
      text("Magnet 2:", 650,320);
      strokeWeight(20.0);
      stroke(0,100);
      pushMatrix();
      segment(290, 350, float(angle1)*PI/180.0); 
      segment(segLength, 0, float(angle2-angle1)*PI/180.0);
      popMatrix();
      noStroke();
      strokeWeight(1.0);
      
      if(starterror) {
        fill(255,0,0);
        text("Both magnets must be", 675, 460);
        text("enabled to begin!", 690, 477);
      }
      
      Mag1ON.update();
      Mag1OFF.update();
      Mag1ON.display();
      Mag1OFF.display();
      
      Mag2ON.update();
      Mag2OFF.update();
      Mag2ON.display();
      Mag2OFF.display();
      
      Start.update();
      Start.display();
    }
    
    
    
    else {
      
    Stop.update();
    Stop.display();
    ///////////////////////////////////  Draw the plots /////////////////////////////////////////////////////////////
    textFont(divfont);
    fill(255);
    rect(10,10,1000,210);  // encoders
    rect(10,230,1000,210);  // accelerometers
    rect(10,450,1000,210);  // gyro 1
    
    for (i = 10; i < 1000; i=i+100) {
      line(i,10,i,20);
      line(i,660,i,650);
    }
    for (i = 220; i > 10; i=i-50) { //plot1
      line(10,i,20,i);
      line(1000,i,1010,i);
    }
      for (i = 440; i > 230; i=i-50) { //plot2
      line(10,i,20,i);
      line(1000,i,1010,i);
    }
      for (i = 660; i > 450; i=i-50) {//plot3
      line(10,i,20,i);
      line(1000,i,1010,i);
    }

    fill(0);
    text("0",1012,663);
    text("100",1012,563);
    text("200",1012,463);
    
    text("0",1012,443);
    text("100",1012,343);
    text("200",1012,243);
    
    text("0",1012,223);
    text("100",1012,123);
    text("200",1012,23);

    text("0",10,670);
    text("300",302,670);
    text("500",502,670);
    text("700",702,670);
    text("1000",998,670);

    textFont(smallfont);
    fill(255,0,0);  // red
    text("Motor",20,30);
    fill(0,255,0);  // green
    text("Gyro 1",20,250);
    fill(0,0,255);  // blue
    text("Gyro 2",20,270);
    fill(150,15,150);  // purple
    text("Current",20,470);


    noStroke();
    
        for (i = rollingIndex; i < 1000; i++) {
          fill(255,0,0);  // red
          ellipse(plot+10,220-buffA[i],4,4);      //plot 1
    
          fill(0,255,0);  // green                //plot 2
          ellipse(plot+10,440-buffB[i],4,4);
    
          fill(0,0,255);  // blue
          ellipse(plot+10,440-buffC[i],4,4);
    
          fill(150,15,150);  // purple
          ellipse(plot+10,660-buffD[i],4,4);    //plot 3
    
  //        fill(252,156,0);  // orange
  //        ellipse(plot+10,660-buffE[i],4,4);
    
  //        fill(0,252,246);  // light blue
  //        ellipse(plot+10,660-buffF[i],4,4);
    
          plot++;
        }
    
        for (i = 0; i < rollingIndex; i++) {
          fill(255,0,0);  // red
          ellipse(plot+10,220-buffA[i],4,4);
    
          fill(0,255,0);  // green
          ellipse(plot+10,440-buffB[i],4,4);
    
          fill(0,0,255);  // blue
          ellipse(plot+10,440-buffC[i],4,4);
    
          fill(150,15,150);  // purple
          ellipse(plot+10,660-buffD[i],4,4);
    
   //       fill(252,156,0);  // orange
   //       ellipse(plot+10,660-buffE[i],4,4);
    
  //        fill(0,252,246);  // light blue
   //       ellipse(plot+10,660-buffF[i],4,4);
    
          plot++;
        }
    }
  stroke(0);
}
}

//////////////////////////////////////////////////////////////////////////////////////
////////////  mouseClicked  //////////////////////////////////////////////////////////
////////////  If a button is selected,  //////////////////////////////////////////////
////////////  perform a function releated to the buttons name  ///////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void mousePressed() {
  try {
    String buttonText = null;
    int index = 0;
    boolean serialButton = false;

    // check all of the buttons
    for (index = 0; index < number_serial_buttons; index++) {
      if (serialButtons[index].over()) {
        serialButton = true;
        buttonText = serialButtons[index].thetext;
      }
    }
     if (Mag1ON.over()) {
      buttonText = "Mag1ON";
    }
     if (Mag1OFF.over()) {
      buttonText = "Mag1OFF";
    }
       if (Mag2ON.over()) {
      buttonText = "Mag2ON";
    }
     if (Mag2OFF.over()) {
      buttonText = "Mag2OFF";
    }
     if (Start.over()) {
      buttonText = "Start";
    }
    if (Stop.over()) {
      buttonText = "Stop";
    }

    if (buttonText == null) {
      // nothing, no button was clicked
    }
    else {
      /////////////////////////////// Serial Button //////////////////////////////////////////////////////
      if (serialButton) {
        myPort = new Serial(this, buttonText, 38400);
        myPort.bufferUntil('\n'); 
        serialPortLabel = "'" + buttonText + "' selected";
        SerialOK = true;
      }
      ///////////////////////////// Other button /////////////////////////////////////////////////////////
      if (buttonText == "Mag1ON") {
        Mag1_ON = true;
        myPort.write('e');
      }
      if (buttonText == "Mag1OFF") {
        Mag1_ON = false;
        myPort.write('f');
      }
         if (buttonText == "Mag2ON") {
        Mag2_ON = true;
        myPort.write('g');
      }
      if (buttonText == "Mag2OFF") {
        Mag2_ON = false;
        myPort.write('h');
      }
       if (buttonText == "Start") {
        if(Mag1_ON && Mag2_ON) {
          StartOK = true;
       //   myPort.write('s');
        }
        else {
          starterror=true;
        }
      }
      if (buttonText == "Stop") {
        myPort.write('x');
        StartOK = false;
        sentLabel = "Sent: Stop command";
      }
    }
  }
  catch (NullPointerException e) {
    println("NullPointerException in MousePressed");
    exit();
  }
}

//////////////////////////////////////////////////////////////////////////////////////
////////////  key pressed ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void keyReleased() { 

  if (SerialOK) {
    myPort.write(key);
    sentLabel = sentLabel + key;
  }
  else { // not in serial mode yet
    if (key == 'e') {
      exit();
    }
    if (key == '1') {
      myPort = new Serial(this, Serial.list()[0], 38400);
      myPort.bufferUntil('\n'); 
      serialPortLabel = "'" + Serial.list()[0] + "' selected";
      SerialOK = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////
////////////  serial event   /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void serialEvent(Serial thisPort) { 
  try {
   
    if (SerialOK && plotOK==0){
      
       // read the serial buffer as a string until a newline appears
      String myString = thisPort.readStringUntil('\n');
      //print(myString);

      // if you got any bytes other than the newline
      if (myString != null) {

        myString = trim(myString); // ditch the newline
        if (myString.substring(0,1).equals("m")) {
          gotLabel = "Got: " + myString.substring(2,myString.length());
          //println(myString.substring(2,myString.length()));
        }
        else {
          int sensors[] = int(split(myString, ' '));

            if (sensors.length == 6) {
            plotOK = sensors[0];
            angle1 = sensors[1];
            angle2 = -sensors[2];
            delay1 = sensors[3];
            delay2 = sensors[4];
            delay3 = sensors[5];
            }
            else {
              plotOK =1;
            }
        }
      }    
    }
    else if (SerialOK) {
      // read the serial buffer as a string until a newline appears
      String myString = thisPort.readStringUntil('\n');
      //print(myString);

      // if you got any bytes other than the newline
      if (myString != null) {

        myString = trim(myString); // ditch the newline
        if (myString.substring(0,1).equals("m")) {
          gotLabel = "Got: " + myString.substring(2,myString.length());
          //println(myString.substring(2,myString.length()));
        }
        else {
          int sensors[] = int(split(myString, ' '));
          
          if (sensors.length == 5) {
            plotOK = sensors[0];
            buffA[rollingIndex] = sensors[1]/4;
            buffB[rollingIndex] = sensors[2]/4;
            buffC[rollingIndex] = sensors[3]/4;
            buffD[rollingIndex] = sensors[4]/4;
     //       buffE[rollingIndex] = sensors[5]/4;
     //       buffF[rollingIndex] = sensors[6]/4;
     //       buffG[rollingIndex] = sensors[7]/4;

          rollingIndex++;
          if (rollingIndex == 1000) {
            rollingIndex = 0;
          }
          }
          else{
            plotOK = 0;
          }
        }
      }
    }
  }
  catch (NullPointerException e) {
    println("nullpointer in serial");
  }
} // end serialEvent

//////////////////////////////////////////////////////////////////////////////////////
////////////  exit   /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


public void stop() {
  //println("inside stop");
  try {
    if (SerialOK) {
      // Clear the buffer, or available() will still be > 0
      myPort.clear();
      // Close the port
      myPort.stop();
    }
    super.stop();
    //println("exiting...");
  }
  catch (NullPointerException e) {
    println("NullPointerException in stop");
  }
} 

//////////////////////////////////////////////////////////////////////////////////////
////////////  button class  //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class Button
{
  int x, y;
  int w, h;
  color basecolor, highlightcolor, clickcolor, activecolor, inactivecolor;
  PFont thefont;
  boolean over = false;
  boolean pressed = false;   

  void pressed() {
    if(over && mousePressed) {
      pressed = true;
    } 
    else {
      pressed = false;
    }
  }

  boolean overRect(int x, int y, int width, int height) {
    if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
      return true;
    } 
    else {
      return false;
    }
  }
}

class TextButtons extends Button 
{
  String thetext;
  color bgcolor;

  TextButtons(int ix, int iy, int iw, int ih, PFont ithefont, String itext, String buttoncolor) 
  {
    x = ix;
    y = iy;
    w = iw;
    h = ih;
    thefont = ithefont;
    thetext = itext;
    
    if (buttoncolor == "red") {
    basecolor = color(255,0,0);
    highlightcolor = color(200,0,0);
    clickcolor = color(255,100,100);//(10,240,100);
    }
    else {
    basecolor = color(52,173,232);
    highlightcolor = color(0,102,153);
    clickcolor = color(152,200,224);//(10,240,100);
   }
  }

  void update() 
 {
    over();
    pressed();
    if(pressed) {
      bgcolor = clickcolor;
    } 
    else if (over) {
      bgcolor = highlightcolor;
    } 
    else {
      bgcolor = basecolor;
    }
  }


  boolean over() 
  {
    if( overRect(x, y, w, h) ) {
      over = true;
      return true;
    } 
    else {
      over = false;
      return false;
    }
  }

  void display() 
  {
    textFont(thefont);
    fill(bgcolor);
    rect(x,y,w,h);
    fill(255,255,255);
    text(thetext,x+5,y+h-10);
  }
}

class Mag1Buttons extends Button 
{
  String thetext;
  color bgcolor;

  Mag1Buttons(int ix, int iy, int iw, int ih, PFont ithefont, String itext, String buttoncolor) 
  {
    x = ix;
    y = iy;
    w = iw;
    h = ih;
    thefont = ithefont;
    thetext = itext;
    
    if(buttoncolor == "red"){
    activecolor = color(100,100,100);
    highlightcolor = color(255,0,0);
    inactivecolor = color(255,0,0);//(10,240,100);
    }
    else
    {
    activecolor = color(0,200,0);
    highlightcolor = color(0,200,0);
    inactivecolor = color(100,100,100);//(10,240,100);
    }
    
  }

  void update() 
    {
    over();
    if (over) {
      bgcolor = highlightcolor;
    } 
    else if(Mag1_ON) {
      bgcolor = activecolor;
    }
    else {
      bgcolor = inactivecolor;
    }
  }
 
  boolean over() 
  {
    if( overRect(x, y, w, h) ) {
      over = true;
      return true;
    } 
    else {
      over = false;
      return false;
    }
  }

  void display() 
  {
    textFont(thefont);
    fill(bgcolor);
    rect(x,y,w,h);
    fill(255,255,255);
    text(thetext,x+5,y+h-10);
  }
}

class Mag2Buttons extends Button 
{
  String thetext;
  color bgcolor;

  Mag2Buttons(int ix, int iy, int iw, int ih, PFont ithefont, String itext, String buttoncolor) 
  {
    x = ix;
    y = iy;
    w = iw;
    h = ih;
    thefont = ithefont;
    thetext = itext;
    
    if(buttoncolor == "red"){
    activecolor = color(100,100,100);
    highlightcolor = color(255,0,0);
    inactivecolor = color(255,0,0);//(10,240,100);
    }
    else
    {
    activecolor = color(0,200,0);
    highlightcolor = color(0,200,0);
    inactivecolor = color(100,100,100);//(10,240,100);
    }
    
  }

  void update() 
    {
    over();
    if (over) {
      bgcolor = highlightcolor;
    } 
    else if(Mag2_ON) {
      bgcolor = activecolor;
    }
    else {
      bgcolor = inactivecolor;
    }
  }
 
  boolean over() 
  {
    if( overRect(x, y, w, h) ) {
      over = true;
      return true;
    } 
    else {
      over = false;
      return false;
    }
  }

  void display() 
  {
    textFont(thefont);
    fill(bgcolor);
    rect(x,y,w,h);
    fill(255,255,255);
    text(thetext,x+5,y+h-10);
  }
}

void segment(float x, float y, float a) {
  translate(x, y);
  rotate(a);
  line(0, 0, segLength, 0);
}

