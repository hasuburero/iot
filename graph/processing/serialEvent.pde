void serialEvent(Serial port)
{
	try{
		String inData = port.readStringUntil('\n');
		inData = trim(inData);
		data = inData.split(",");
		print(getTime() + " ");
		for(int i=0; i<data.length; ++i){
			print(data[i] + ",");
		}
		println("");
	}
	catch(Exception e){
		println(e.toString());
	}
}

