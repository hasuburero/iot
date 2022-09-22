int width = 1000;
int height = 700;

boolean clear_flag = false;

void setup()
{
	size(1000, 700);		//変数を入れない
	frameRate(120);			//フレームレート．デフォルトは60フレーム
	background(0, 255, 0);	//背景色
	fill(255, 0, 0);		//図形の色
	strokeWeight(5);		//線の幅
}

void draw()
{
	stroke(255, 0, 255);	//線の色
	if(mousePressed){		//押されていればtrue
		line(pmouseX, pmouseY, mouseX, mouseY);	
	}
	if(clear_flag){
		background(0, 255, 0);
		clear_flag = false;
	}

	noStroke();	//フチなし
	rect(width-150, height-120, width-50, height-50);
}

void mousePressed()
{
	//四角形の位置でクリックすると初期化
	if(width-150 <= mouseX && mouseX <= width-50){
		if(height-120 <= mouseY && mouseY <= height-50){
			clear_flag = true;
		}
	}
}
