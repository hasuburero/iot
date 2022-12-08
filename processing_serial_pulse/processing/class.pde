class Button{
	int x;
	int y;
	int sizex;
	int sizey;
	Button(int x, int y, int sizex, int sizey){
		this.x = x;
		this.y = y;
		this.sizex = sizex;
		this.sizey = sizey;
	}
}

class Textbox{
	String str;
	int x;
	int y;
	int sizex;
	int sizey;
	boolean flag;
	Textbox(int x, int y, int sizex, int sizey){
		this.x = x;
		this.y = y;
		this.sizex = sizex;
		this.sizey = sizey;
		str = "";
		flag = false;
	}
	void addstring(char key){
		if(key == BACKSPACE){
			if(str.length() != 0){
				str = str.substring(0, str.length() - 1);
			}
		}
		else if(key == ENTER){
			if(str != ""){
				flag = true;
			}
		}
		else if(key != CODED){
			if(str.length() <20){
				str += key;
			}
		}
	}
}
