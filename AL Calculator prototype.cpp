#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;


struct ship{
public:
string ID;
int AA;
int reload;
float efficency;
int skill1;
int skill2;
int skill3;
int skill4;
short int guncount;
string name;
};

struct gun{
public:
string name;
double reload;
int dmg;
int AA;
int range;
};

struct dps_comb{

public:
string *gun;
long double dps;
int lower_dps;
int higher_dps;

void set_guncount(int x){
gun = new string [x];
};
};

struct shiplist{
    const int length = 500; //at least the highest id of given class, possibly later read from shiplist

    struct skills{
    int s1;
    int s2;
    int s3;
    int s4;
    };

public:
vector<string> name;
vector<double> efficiency;
vector<short int> guncount;
vector<skills> skill;

void set_ships(string filename,int *errorcode = NULL){
*errorcode = 0;
string fileinput;

    fstream file (filename.c_str());
    if(!file.is_open()){
        *errorcode = 1;
        return;
    }

    name.resize(length+1);
    efficiency.resize(length+1);
    guncount.resize(length+1);
    skill.resize(length+1);

    for(int i = 1; i<=length; i++){

            if(file.eof()){
            *errorcode = 2;
            return;
        } //throw error if reaches eof unexpectedly ie ship count doesn't match the data

        int j = 0;
        string temp = "";
        getline(file,fileinput);

        for(;fileinput[j] != 19; j++) temp += fileinput[j];

            int ID = atoi(temp.c_str());

            if(ID == i){
                temp = "";

                for(;fileinput[j] != 19; j++) temp += fileinput[j];

                name[i] = temp;
                temp = "";

                for(;fileinput[j] != 19; j++) temp += fileinput[j];

                efficiency[i] = atof(temp.c_str());
                temp = "";

                for(;fileinput[j] != 19; j++) temp += fileinput[j];

                guncount[i] = atoi(temp.c_str());
                temp = "";

                for(;fileinput[j] != 13 && fileinput[j] != 19 &&  j < fileinput.length(); j++)

                skill[i].s1 = atoi(temp.c_str());
                temp = "";

                for(;fileinput[j] != 13 && fileinput[j] != 19 &&  j < fileinput.length(); j++)

                skill[i].s2 = atoi(temp.c_str());
                temp = "";

                for(;fileinput[j] != 13 && fileinput[j] != 19 &&  j < fileinput.length(); j++)

                skill[i].s3 = atoi(temp.c_str());
                temp = "";

                for(;fileinput[j] != 13 && fileinput[j] != 19 &&  j < fileinput.length(); j++)

                skill[i].s4 = atoi(temp.c_str());
                temp = "";

            }

        }
    }

};


void read_guns(gun *AAgun){
    ifstream file ("guns.txt");
    string fileinput;

    getline(file,fileinput);
    int how_many = atoi(fileinput.c_str());
    cout << how_many;

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

        getline(file,fileinput);
}
return;
};



void read_ships(ship *ships, int shipcount, bool *failed = NULL){
    ifstream file ("ships.txt");
    string fileinput;


    getline(file,fileinput);


    for(int i = 0; i < shipcount && i<6; i++){

        if(file.eof()){
            *failed = true;
            return;
        } //throw error if reaches eof unexpectedly ie ship count doesn't match the data

        int j = 0;
        string temp = "";
        getline(file,fileinput);

        for(;fileinput[j] != 19; j++){
            temp += fileinput[j];
        }
        ships[i].ID = temp;
        temp = "";
        j++;

        for(;fileinput[j] != 19; j++){
            temp += fileinput[j];
        }
        ships[i].AA = atoi(temp.c_str());

        temp = "";
        j++;

        for(;fileinput[j] != 19; j++){
            temp += fileinput[j];
        }
        ships[i].reload = atoi(temp.c_str());


        if(ships[i].ID == "-1"){//Special case for ships not on the list

                temp = "";
                j++;

                for(;fileinput[j] != 19; j++){
                temp += fileinput[j];
                }
                ships[i].name = temp;

                temp = "";
                j++;

                for(;fileinput[j] != 19; j++){
                temp += fileinput[j];
                }
                ships[i].efficency = atof(temp.c_str());

                temp = "";
                j++;

                for(;fileinput[j] != 13 && fileinput[j] != 19 &&  j < fileinput.length(); j++){
                temp += fileinput[j];
                }
                ships[i].guncount = atoi(temp.c_str());

        }
    }
}




int main(){
string fileinput;


    //read ships
    ifstream shipfile ("ships.txt");
    if(!shipfile.is_open()){
        cout << "Failed to find ships.txt";
        getch();
        return 1;
    }

    getline(shipfile,fileinput);

    ship ships[atoi(fileinput.c_str())];


    bool failed = false;
    read_ships(&ships[0], atoi(fileinput.c_str()), &failed);
    if(failed){
        cout << "Please check ships.txt";
        getch();
        return 1;
    }
    cout << ships[1].ID << endl;


    //read guns
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

    read_guns(&AAgun[0]);



}
