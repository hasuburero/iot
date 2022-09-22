String str = "Hello world!!";

void setup()
{
	size(300, 300);
	background(0);

	str = str.substring(0, str.length()-1);

	text(str, 15, 15);
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
		str = "";
	}
	else{
		str += key;
	}

}

