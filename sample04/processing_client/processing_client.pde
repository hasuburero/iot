import processing.net.*;

String serverAddr = "";
Client client;

String str = "";
boolean flag = false;

void setup()
{
	size(300, 300);
	client = new Client(this, serverAddr, 5000);
}

void draw()
{
	background(0);
	if(str != null){
		text(str, 15, 15);
	}
}

void keyPressed()
{
	if(key == BACKSPACE){
		if(str.length() != 0){
			str = str.substring(0, str.length()-1);
		}
	}
	else if(key == ENTER){
		if(str != ""){
			client.write(str);
		}
		str = "";
	}
	else if(key == CODED){
		if(keyCode == SHIFT){
			print("shift key was pressed\n");
		}
	}
	else{
		str += key;
	}
}
