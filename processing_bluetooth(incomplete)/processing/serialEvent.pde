void serialEvent(Serial port)
{
	try{
		String inData = port.readStringUntil('\n');
		inData = trim(inData);  //"  banana  " -> "banana"
		data = inData.split(",");
	}
	catch(Exception e){
		println(e.toString());
	}
}
