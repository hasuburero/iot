import processing.net.*;

PrintWriter output;

boolean myServerRunning = true;
Server myServer;

boolean flag = false;

String s;
String str[];
String mess = "";
String filename = "output.csv";	//ファイル名．csv形式を使用

void setup()
{
	size(300, 300);

	myServer = new Server(this, 50000);	//50000番ポートを使用
	println(Server.ip());

	println("new file");
	output = createWriter(filename);	//新しいファイルを作成し，PrintWriterオブジェクトを生成する．正しく保存するためにはflush()とclose()メソッドを実行数必要がある．
	output.println("time,sin(rad)");
	output.flush();

	String[] fontList = PFont.list();
	printArray(fontList);
	PFont myfont = createFont("Georgia", 32);
	textFont(myfont);
}

void draw()
{
	background(0);
	if(mess != null){
		text(mess, 15, 32);
	}

	if(myServerRunning == true){
		Client thisClient = myServer.available();

		if(thisClient != null){
			if(thisClient.available() > 0){	//文字数(byte)
				s = thisClient.readString(); //文字列の取得
				if(!s.equals(" ")){
					str = s.split(",");	//javaのsplitメソッド．指定した文字列で区切って配列に分割

					if(str[0].equals("start")){
						println("str[0] = " + str[0]);
						createFile();
					}
					else if(str.length == 1){
						for(String strs : str){
							output.print(getTime() + ",");
							output.println(strs);
							print(getTime() + ",");
							println(strs);
						}
					}
				}
				if(flag){
					thisClient.write(mess);	//clientにメッセージを送信
					flag = false;
					mess = "";
				}
			}
		}
	}
	else{
		//text("server stopped", , );
	}

}

void createFile()
{
	println("new file");
	output.flush();	//ファイルに出力
	output.close();	//書き込み終了
	output = createWriter(filename);
	output.println("time,sin(rad)");
	output.flush();
}

void keyPressed()
{
	if(key == BACKSPACE){
		if(mess.length() != 0){
			mess = mess.substring(0, mess.length() - 1);
		}
	}
	else if(key == ENTER){
		if(mess != ""){
			flag = true;
		}
	}
	else if(key == ESC){
		output.flush();
		output.close();
		myServer.stop();
		myServerRunning = false;
		exit();
	}
	else if(key == CODED){
		if(keyCode == SHIFT){
			println("shift key was pressed");
		}
	}
	else{
		mess += key;
	}
}

String getTime()
{
	int s = second();
	int m = minute();
	int h = hour();
	return (h + ":" + m + ":" + s);
}
