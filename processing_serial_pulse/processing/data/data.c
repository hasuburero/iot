#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

struct DATA{
	char time[64];
	float emotion;
	float temp;
	float humidity;
	float dis;
	int flag;
};

struct AVE{
	char time[64];
	float emotion;
	float temp;
	float humidity;
	float dis;
	int count;
};

void cp(char *a, char *b){
	for(int i=0; a[i]; ++i){
		b[i] = a[i];
	}
}

int main(int argc, char **argv){
	FILE *fp;
	struct DATA data[20000];
	struct DATA sort[20000];
	struct AVE ave;
	char line[256];
	char buf[100];
	int i = 0;
	int num;
	int count = 0;

	num = atoi(argv[1]);

	ave.emotion = 0;
	ave.temp = 0;
	ave.humidity = 0;
	ave.count = 0;
	ave.dis = 0;

	if((fp = fopen(argv[2], "r")) == NULL){
		printf("file open err (%s)\n", strerror(errno));
		return 0;
	}
	fscanf(fp, "%s", buf);
	while(fgets(line, 256, fp) != NULL){
		sscanf(line, "%[^,],%f,%f,%f,%f", buf, &data[i].emotion, &data[i].temp, &data[i].humidity, &data[i].dis);
		if(data[i].emotion <= 0){
			data[i].flag = 0;
		}
		else{
			data[i].flag = 1;
			cp(buf, ave.time);
			ave.emotion += data[i].emotion;
			ave.temp += data[i].temp;
			ave.humidity += data[i].humidity;
			ave.dis += data[i].dis;
			++ave.count;
			if(ave.count == num){
				//printf("%.2f, %.2f, %.2f, %.2f\n", 
				//	ave.emotion = ave.emotion/ave.count, 
				//	ave.temp = ave.temp/ave.count, 
				//	ave.humidity = ave.humidity/ave.count, 
				//	ave.dis = ave.dis/ave.count);
				cp(ave.time, sort[count].time);
				sort[count].emotion = ave.emotion/ave.count;
				sort[count].temp = ave.temp/ave.count;
				sort[count].humidity = ave.humidity/ave.count;
				sort[count++].dis = ave.dis/ave.count;
				ave.emotion = 0;
				ave.temp = 0;
				ave.humidity = 0;
				ave.dis = 0;
				ave.count = 0;
			}
		}
		++i;
	}
	//printf("%.2f, %.2f, %.2f, %.2f\n", 
	//	ave.emotion/ave.count, 
	//	ave.temp/ave.count, 
	//	ave.humidity/ave.count, 
	//	ave.dis/ave.count);
	sort[count].emotion = ave.emotion/ave.count; 
	sort[count].temp = ave.temp/ave.count; 
	sort[count].humidity = ave.humidity/ave.count; 
	sort[count++].dis = ave.dis/ave.count;

	for(i=0; i<count-1; ++i){
		for(int j=0; j<count-1-i; ++j){
			if(sort[j].emotion < sort[j+1].emotion){
				struct DATA buffer = sort[j];
				sort[j] = sort[j+1];
				sort[j+1] = buffer;
			}
		}
	}

	for(i=0; i<count; ++i){
		printf("%s, %.2f, %.2f, %.2f, %.2f\n",
			sort[i].time,
			sort[i].emotion,
			sort[i].temp,
			sort[i].humidity,
			sort[i].dis);
	}

	fclose(fp);
	return 0;
}



