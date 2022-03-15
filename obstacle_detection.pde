import processing.serial.Serial;

Serial myPort;

PImage bg1,bg2;
PFont font;

String result;
String distance;

void setup() {
  size (1920, 700); 
  myPort = new Serial(this, "COM3", 9600);
  myPort.bufferUntil('\n');
  bg1 = loadImage("232-thickbox_default-ultrasonic-sensor.jpg");
  bg2 = loadImage("1.-NRG%u2019s-Bat-Deterrent-Systems-NRG-Systems.jpg");
  font = loadFont("data\\Poppins-Bold-15.vlw");
}


void draw() {
  bg1.resize(150,100);
  bg2.resize(90,100);
  background(255,255,255);
  textSize(15);
  fill(255, 0,0);
  textAlign(CENTER);
  textFont(font);
    
  image(bg1, 880, 550);
  image(bg2, 910, 450);
  delay(900);
  
  result = "";
  
  if(myPort.available() > 0)
  {
    distance = myPort.readStringUntil('\n');
    
    if(distance !=null)
    {
      int dist = int(distance);
      
      result = "OBSTACLE DETECTED AT : ";

      result+=distance+"CM ";
    
      text(result, 960, 250-dist);
    } 
  }
}
