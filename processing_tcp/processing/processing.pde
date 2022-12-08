import processing.net.*;

PrintWriter output;

boolean myServerRunning = true;
Server myServer;

String s;
String str[];
String filename = "data1.csv";

void setup(){
  size(400, 400);
	background(0);
	myServer = new Server(this, 8080);
	println(Server.ip());
	
  println("new file");
  output = createWriter(filename);
  output.println("Time,Emotion,Temperature,Humidity,discomfort");
  output.flush();
}

void draw()
{
	if(myServerRunning == true){
		text("server", 15, 45);
		Client thisClient = myServer.available();

		if(thisClient != null){    
			if(thisClient.available() > 0){
				//thisClient.write("ABC\r\n");
				s = thisClient.readString();
				str = s.split(",");

        if(str[0].equals("connect")){
          println("str[0] = " + str[0]);
          remake();
        }
        else if(str.length == 3){
			s = String.valueOf(0.81*float(str[1])+float(str[2])*0.01*(0.99*float(str[1])-14.3)+46.3);
			output.print(getTime() + ",");
			output.print(str[0] + ",");
			output.print(str[1] + ",");
			output.print(str[2] + ",");
			output.println(s);
			print(getTime() + ",");
			print(str[0] + ",");
			print(str[1] + ",");
			println(str[2] + ",");
				}
			}
		}
	}
	else{
		text("server", 15, 45);
		text("stopped", 15, 65);
	}
}

void remake()
{
  println("new file");
  output.flush();
  output.close();  
  output = createWriter(filename);
  output.println("Time,Emotion,Temperature,Humidity,discomfort");
  output.flush();
}

void keyPressed()
{
	if(key == 'a'){
		output.flush();
		output.close();
		myServer.stop();
		myServerRunning = false;
		exit();
	}
}

String getTime()
{
	int s = second();
	int m = minute();
	int h = hour();
	return (h + ":" + m + ":" + s);
}
