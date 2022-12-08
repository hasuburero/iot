void serialEvent(Serial port)
{
  if(mode == 3){
	try{
		String inData = port.readStringUntil('\n');
		inData = trim(inData);  //"  banana  " -> "banana"
		data = inData.split(",");
    if(data[0].equals("connect")){
      println("str[0] = " + data[0]);
      remake();
    }
    else if(data.length == 3){
      s = String.valueOf(0.81*float(data[1])+float(data[2])*0.01*(0.99*float(data[1])-14.3)+46.3);
      output.print(getTime() + ",");
      output.print(inData + ",");
      output.println(s);
      print(getTime() + ",");
      print(inData + ",");
      println(s);
      output.flush();
    }
	}
	catch(Exception e){
		println(e.toString());
	}
  }
}
