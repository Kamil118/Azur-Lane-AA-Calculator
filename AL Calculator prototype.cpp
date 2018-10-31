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
char type;
int ID;
int AA;
int reload;
float efficency;
int skill1;
int skill2;
int skill3;
int skill4;
short int guncount;
string name;

float reload_time;
int AA_damage;
string AA_gun_name;
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
string gun[6];
long double dps;


};

void dps_quickSort(dps_comb *arr, int left, int right){
// modified from http://www.algolist.net/Algorithms/Sorting/Quicksort if you want me to remove this please say
      int i = left, j = right;

      dps_comb tmp;

      long double pivot = arr[(left + right) / 2].dps;


      /* partition */

      while (i <= j) {

            while (arr[i].dps < pivot)

                  i++;

            while (arr[j].dps > pivot)

                  j--;

            if (i <= j) {

                  tmp = arr[i];

                  arr[i] = arr[j];

                  arr[j] = tmp;

                  i++;

                  j--;

            }

      };


      /* recursion */

      if (left < j)

            dps_quickSort(arr, left, j);

      if (i < right)

            dps_quickSort(arr, i, right);

};

void nextgun(int *current_gun, int shipcount, int amount_of_guns, int number){

    if(number == shipcount) return;
    if(current_gun[number] < (amount_of_guns-1)) current_gun[number]++;
    else {
            current_gun[number] = 0;
            nextgun(current_gun,shipcount,amount_of_guns, number+1);
    }

}

void calculate_dps(int shipcount, int amount_of_guns, int guncomp_count, int guncount, gun *guns, ship *ships, dps_comb *dps_combi){


for(int i = 0; i < shipcount; i ++){
    float temp = (100+ships[i].reload);
    float to_root = (200/temp);
    ships[i].reload_time = guns[0].reload * sqrt(to_root);
    ships[i].AA_damage = guns[0].dmg * ships[i].efficency * (100 + ships[i].AA) / 100;
}



int current_gun[shipcount];
for(int i = 0; i < shipcount; i++){
    current_gun[i] = 0;
};
bool skip_first = true;
float total_reload = 0;
float total_damage = 0;

for(long int i = 1; i < guncomp_count; i++){




            if(skip_first == false) nextgun(current_gun,shipcount,amount_of_guns, 0);





            for(int a = 0; a < shipcount; a++){
                        float temp = (100+ships[a].reload);
                        float to_root = (200/temp);
                        ships[a].reload_time = guns[current_gun[a]].reload * sqrt(to_root);
                        ships[a].AA_damage = guns[current_gun[a]].dmg * ships[a].efficency * (100 + ships[a].AA) / 100;
                        ships[a].AA_gun_name = guns[current_gun[a]].name;

            }


            skip_first = false;
            total_reload = 0;
            total_damage = 0;

            for(int j = 0; j<shipcount; j++){
                total_damage =+ ships[j].AA_damage * ships[j].guncount;
            }
            for(int j = 0; j<shipcount; j++){
                total_reload =+ ships[j].reload_time * ships[j].guncount;
            }
            total_reload = (total_reload/guncount) + 0.5;

            for(int j = 0; j<shipcount; j++){
                dps_combi[i].gun[j] = ships[j].name + ":" + ships[j].AA_gun_name;
            }

            dps_combi[i].dps = total_damage/total_reload;
    }
    cout << endl << "Sorting results, this might take a while...";
    dps_quickSort(&dps_combi[0],0, guncomp_count-1);
};


struct shiplist{


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
int length = 500; //set to at least highest ID ship in the game, possibly load from file later
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
    getline(file,fileinput);

    for(int i = 1; i<=length; i++){

            if(file.eof()){
            *errorcode = 2;
            return;
        } //throw error if reaches eof unexpectedly ie ship count doesn't match the data

        int j = 0;
        string temp = "";

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

                getline(file,fileinput);

            }

        }
    }

};


void read_guns(gun *AAgun){
    ifstream file ("guns.txt");
    string fileinput;

    getline(file,fileinput);
    int how_many = atoi(fileinput.c_str());

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

        for(;fileinput[j] != 9; j++){
            temp += fileinput[j];
        }

        ships[i].type = temp[0];

        temp.erase(0,1);

        ships[i].ID = atoi(temp.c_str());

        temp = "";
        j++;

        for(;fileinput[j] != 9; j++){
            temp += fileinput[j];
        }
        ships[i].AA = atoi(temp.c_str());

        temp = "";
        j++;

        for(;fileinput[j] != 9; j++){
            temp += fileinput[j];
        }
        ships[i].reload = atoi(temp.c_str());

        if(ships[i].type == 'a'){//Special case for ships not on the list

                temp = "";
                j++;

                for(;fileinput[j] != 9; j++){
                temp += fileinput[j];
                }
                ships[i].name = temp;
                temp = "";
                j++;

                for(;fileinput[j] != 9; j++){
                temp += fileinput[j];
                }
                ships[i].efficency = atof(temp.c_str());

                temp = "";
                j++;

                for(;fileinput[j] != 13 && fileinput[j] != 9 &&  j < fileinput.length(); j++){
                temp += fileinput[j];
                }
                ships[i].guncount = atoi(temp.c_str());


        }
    }

}




int main(){
string fileinput;

    cout << "loading fleet composition...";
    //read ships
    int ship_count;
    ifstream shipfile ("ships.txt");
    if(!shipfile.is_open()){
        cout << "Failed to find ships.txt";
        getch();
        return 1;
    }

    getline(shipfile,fileinput);

    ship_count = atoi(fileinput.c_str());

    ship ships[ship_count];


    bool failed = false;
    read_ships(&ships[0], atoi(fileinput.c_str()), &failed);
    if(failed){
        cout << "Please check ships.txt";
        getch();
        return 1;
    }

    cout << "loaded" << endl << "loading gun stats...";

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

    cout<< "loaded" << endl;


    /* Will set properties of ships later here, but need to have the files ready first, and that means manually getting stats to spreadsheet
    shiplist normal_ships;
    shiplist pr_ships;
    shiplist colab_ships;

    normal_ships.set_ships("normalships.txt");
    pr_ships.set_ships("prships.txt");
    colab_ships.set_ships("colabships.txt");

    */
    int guncount = 0;

    for(int i = 0;  i < ship_count; i++){
        guncount =+ ships[i].guncount;
    }

    long int guncomp_count = pow(amount_of_guns,ship_count);
    dps_comb guncomp[guncomp_count];

    cout << "calculating dps, this might take a while...";

    calculate_dps       (ship_count,    amount_of_guns,     guncomp_count,      guncount,       AAgun,     ships,       guncomp           );

     cout << endl <<
     "---------------------------------------------" << endl <<
     "|            Best gun combination" << endl <<
     "|--------------------------------------------" << endl;
     for(int i = 0; i < ship_count;i++)
     cout << "|   " << guncomp[1].gun[i] << endl;
cout << "|--------------------------------------------" << endl;




system("pause");
return 0;
};
