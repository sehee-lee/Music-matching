#include <iostream>
#include <string.h>
#include <string>
#include <time.h>

using namespace std;

int total;
int number;
string music_name;



char * Binary (int Value) {
    
    unsigned int Mask;
    int Bit;
    char * Text;
    Text = new char[33];
    Bit = 0;
    Mask = 0X80000000;
    while (Mask != 0) {
        Text [Bit] = (Mask & Value) ? '1' : '0';
        Mask >>= 1;
        ++Bit;
    }
    Text [32] = 0;
   
    for(int i=0; i<33; i++)
        if(Text[i] == '0')
            total ++;
    
    return Text;
};

int *get_finger_print( FILE *f){
    
    int i = 0;
    char *sep = ",\n=", *sep2 = ",";
	char *token;
	char data[1000000];
    int *fp;
    int temp;
    char *name;
	for(int t=0; t<3; t++){
        
		fgets(data,1000000,f);
		
        if(t == 0){
            
            token = strtok(data,sep);
            token = strtok(NULL, sep);
            name = token;
            music_name = string(name);
            std::cout << name << std::endl;
        }
        
		else if(t == 1){
			
            
			token = strtok(data,sep);
			token = strtok(NULL,sep);
			temp = atoi(token);
            number = temp;
            
        }
		else if(t == 2){
			
			fp = (int*)malloc(sizeof(int)*temp);
            
			for(int j=0; j<temp; j++){
				
				if(j == 0){
					token = strtok(data,sep);
					token = strtok(NULL,sep);
				}
                
				else
					token = strtok(NULL, sep2);
                
				fp[j] = atoi(token);
			}
            
		}
        
	}
    
    return fp;
    
};

int match_music(int n1, int n2, int *fp1, int *fp2 ){
   
    int c=0;
    int re;
    
   
    for(int j = 0; j< n1; j++){
        for(int k = 0; k< n2; k++){
                
            re = 0;
                
            re = fp1[j] ^ fp2[k];
            c ++;
            Binary(re);
            //std::cout << c << " : " << Binary(re) << std::endl;
                
        }
    }
   
    
    return c;
    
};

int main(void){

    
    clock_t start_time, end_time;
    
    total = 0;

	int *fp[11], n1, n2, n3, n4, n5, n6,n7, n8, n9, n10, n11;
	int re;
	FILE *m1, *m2, *m3, *m4, *m5, *m6,*m7, *m8, *m9, *m10, *m11;
	char *sep = ",\n=", *sep2 = ",";
	char *token;
	char data[1000000];
    double max_per=0;
    string result_file_name;
    string mu[11];
    char *name;
    //DB
	m1 = fopen("music1","r");
	m2 = fopen("music2","r");
	m3 = fopen("music3","r");
	m4 = fopen("music4","r");
    m5 = fopen("music5","r");
    m6 = fopen("music6","r");
	m7 = fopen("music7","r");
	m8 = fopen("music8","r");
	m9 = fopen("music9","r");
    m10 = fopen("music10","r");
	//sample
    m11 = fopen("music11","r");
    
    
	int i;
    
    
    
    fp[0] = get_finger_print(m1);
    n1 = number;
    mu[0] = music_name;
    std::cout << n1 << std::endl;
    
    fp[1] = get_finger_print(m2);
    n2 = number;
    mu[1] = music_name;
    std::cout << n2 << std::endl;
    
    fp[2] = get_finger_print(m3);
    n3 = number;
    mu[2] = music_name;
    std::cout << n3 << std::endl;
    
    fp[3] = get_finger_print(m4);
    n4 = number;
    mu[3] = music_name;
    std::cout << n4 << std::endl;
    
    fp[4] = get_finger_print(m5);
    n5 = number;
    mu[4] = music_name;
    std::cout << n5 << std::endl;
    
    fp[5] = get_finger_print(m6);
    n6 = number;
    mu[5] = music_name;
    std::cout << n6 << std::endl;
    
    fp[6] = get_finger_print(m7);
    n7 = number;
    mu[6] = music_name;
    std::cout << n7 << std::endl;
    
    fp[7] = get_finger_print(m8);
    n8 = number;
    mu[7] = music_name;
    std::cout << n8 << std::endl;
    
    fp[8] = get_finger_print(m9);
    n9 = number;
    mu[8] = music_name;
    std::cout << n9 << std::endl;
    
    fp[9] = get_finger_print(m10);
    n10 = number;
    mu[9] = music_name;
    std::cout << n10 << std::endl;
    
    fp[10] = get_finger_print(m11);
    n11 = number;
    mu[10] = music_name;
    std::cout << n11 << std::endl;
    
	int c[10];
    
    
    
    double per[11];
    double matched;
    
    start_time = clock();
    
    for(int j=0; j<10; j++){
        
        total = 0;
        
        c[j] = match_music(n1, n11, fp[j], fp[10]);
        
        matched = (double)total;
        
        per[j] = matched / (c[j] * 32) * 100;
        
        cout << per[j] << endl;
        
        if(max_per < per[j]){
            max_per = per[j];
            result_file_name = mu[j];
        }
        
    }
    end_time = clock();
    std::cout << "Matched File name : " << result_file_name << "\nPercentage : " << max_per << "%" << std::endl;
    
    printf("Time : %f sec\n", ((double)(end_time-start_time)) / CLOCKS_PER_SEC);  

	return 0;

}
