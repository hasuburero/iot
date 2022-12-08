
Table input;
String filename = "data4.csv";
String[] time;
float[] emotion, temp, humidity, dis;
int data_row, data_column;

void setup(){
	input = loadTable(filename);
	data_row = input.getRowCount();
	data_column = input.getColumnCount();
	time = new String[data_row];
	emotion = new float[data_row];
	temp = new float[data_row];
	humidity = new float[data_row];
	dis = new float[data_row];

	for(int i=1; i<data_row; ++i){
		time[i] = input.getString(i, 0);
		emotion[i] = input.getFloat(i, 1);
		temp[i] = input.getFloat(i, 2);
		humidity[i] = input.getFloat(i, 3);
		dis[i] = input.getFloat(i, 4);
	}
	
	for(int i=1; i<time.length; ++i){
		println(time[i], emotion[i], temp[i], humidity[i], dis[i]);
		delay(100);
	}
}

void draw(){
}
