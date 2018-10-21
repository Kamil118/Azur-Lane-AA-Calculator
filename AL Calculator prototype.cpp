#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;


struct ship{
int AA;
int reload;
float efficency;
int skill1;
int skill2;
int skill3;
int skill4;
short int guncount;
};

struct gun{
string name;
double reload;
int dmg;
int AA;
int range;
};

void read_guns(gun *AAgun, int how_many){
    ifstream file ("guns.txt");
    string fileinput;

    getline(file,fileinput);
    getline(file,fileinput);


for (int i=0; i<how_many; i++){
        getline(file,fileinput);
        AAgun[i].name = fileinput;

        getline(file,fileinput);
        AAgun[i].reload = atof(fileinput.c_str());

        getline(file,fileinput);
        AAgun[i].dmg = atoi(fileinput.c_str());

        getline(file,fileinput);
        AAgun[i].AA = atoi(fileinput.c_str());

        getline(file,fileinput);
        AAgun[i].range = atoi(fileinput.c_str());
}
return;
};


int main(){
string fileinput;
const bool isshippickingdone = false;
if(isshippickingdone == true){
 ifstream ships ("ships.txt");


}

 ifstream guns ("guns.txt");
 if(!guns.is_open()){
    cout << "Failed to find guns.txt";
    getch();
    return 1;
 }


    getline(guns,fileinput);
    int amount_of_guns;
    amount_of_guns = atoi(fileinput.c_str());
    getline(guns,fileinput);

    gun AAgun[amount_of_guns];

    read_guns(&AAgun[0], amount_of_guns);


}
