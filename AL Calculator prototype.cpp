#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;


struct ship{

public:
string name;
int AA;
int reload;

float efficency;
string hull_class;
string ship_class;
string nation;
string skill1;
string skill2;
string skill3;
string skill4;
short int guncount;

float AA_mod;
float reload_mod;
float reload_time;
float AA_damage;
string AA_gun_name;
};

struct gun{
public:
string name;
float reload;
int dmg;
int AA;
int range;
int maxcount;
};

struct dps_comb{

public:
string gun[6];
float dps;
};

bool dps_compare(dps_comb comb1, dps_comb comb2){
    return (comb1.dps < comb2.dps);
};

void nextgun(int *current_gun, int shipcount, int amount_of_guns, int number){

    if(number >= shipcount) return;//you somehow tried to change the gun of a ship that doesn't exist, this should probably be an exception but i can't code
    if(current_gun[number] < (amount_of_guns-1)) current_gun[number]++;
    else {
            current_gun[number] = 0;
            nextgun(current_gun,shipcount,amount_of_guns, number+1);
    }

}

bool check_max_gun(gun *guns, int *current_gun, int guncount, ship *ships, int shipcount){//checks if player has enough guns
int amount_of_guns[guncount];//makes an array for all guns in the guns.txt file

for(int i = 0; i < guncount;i++){
    amount_of_guns[i] = 0;
}

for(int i = 0; i < shipcount;i++){//for every ship adds up amount of guns it has to equip to respective slot in the amount_of_guns array
    if(ships[i].hull_class!="AR"&&ships[i].name!="Isuzu"){
    amount_of_guns[current_gun[i]] += ships[i].guncount;//for most ships
    }
    else amount_of_guns[current_gun[i]] += ships[i].guncount/2;//for ships with aa gun+1

}
for(int i = 0; i < guncount; i++){
    if(amount_of_guns[i] > guns[i].maxcount) { //return false player doesn't have enough guns
    return false;
    }
}
return true;

}


void calculate_dps(int shipcount, int amount_of_guns, int guncomp_count, int guncount, gun *guns, ship *ships, vector <dps_comb> *dps_combi){


int current_gun[shipcount];
for(int i = 0; i < shipcount; i++){
    current_gun[i] = 0;
};



for(long int i = 0; i < guncomp_count; i++){

            dps_comb temp;
            float total_reload = 0;
            float total_damage = 0;

            for(int a = 0; a < shipcount; a++){
                        float to_root = 100+ships[a].reload;
                        to_root = (200/to_root);
                        ships[a].reload_time = guns[current_gun[a]].reload * sqrt(to_root);
                        ships[a].AA_damage = guns[current_gun[a]].dmg * ships[a].efficency * (100 + ships[a].AA + guns[current_gun[a]].AA) / 100;
                        ships[a].AA_gun_name = guns[current_gun[a]].name;
            };


            if(check_max_gun(guns,current_gun,amount_of_guns,ships, shipcount)){
            for(int j = 0; j<shipcount; j++){
                total_damage += (ships[j].AA_damage * ships[j].guncount);
            }


            for(int j = 0; j<shipcount; j++){
                total_reload += (ships[j].reload_time * ships[j].guncount);

            }
            total_reload = (total_reload/guncount) +0.5;

            for(int j = 0; j<shipcount; j++){
                if(ships[j].guncount != 0){
                    temp.gun[j] = ships[j].name + ": " + ships[j].AA_gun_name;}
                else temp.gun[j] = ships[j].name + " has no AA gun slots";
            }

            temp.dps = total_damage/total_reload;
            }
            else temp.dps = 0;

            dps_combi->push_back(temp);
            nextgun(current_gun,shipcount,amount_of_guns, 0);
    }
    cout << endl << "Sorting results, this might take a while...";
    sort(dps_combi->begin(),dps_combi->end(),dps_compare);
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
        AAgun[i].maxcount = atof(fileinput.c_str());

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

        string temp;

        getline(file,ships[i].name,'	');

        getline(file,temp,'	');
        ships[i].AA = atoi(temp.c_str());

        getline(file,temp,'	');
        ships[i].reload = atoi(temp.c_str());


        if(ships[i].name[0] == '$'){//Special case for ships not on the list

                getline(file,temp,'	');
                ships[i].efficency = atof(temp.c_str());


                getline(file,temp,'	');
                ships[i].guncount = atoi(temp.c_str());


                getline(file,ships[i].hull_class,'	');

                getline(file,ships[i].ship_class,'	');

                getline(file,ships[i].nation,'	');

                getline(file,ships[i].skill1,'	');

                getline(file,ships[i].skill2,'	');

                getline(file,ships[i].skill3,'	');

                getline(file,ships[i].skill4);



        }
        else getline(file,temp);
    }

}

void assign_ship(ship *assigned_ship, int *fail){
fstream file ("list_of_ships.txt");
string temp;
getline(file,temp);
if(!file.is_open()){
    *fail = 1;
    return;
}

if((*assigned_ship).name[0] == '$') return; //don't overwrite custom ships

int i = 0;
while(true){//searches for the correct ship on the list
        string name;
        getline(file,name, '	');
        if((*assigned_ship).name == name) break;
        getline(file,temp);
        i++;
        if(file.eof()){
            *fail = 2;
            return;
        }
}
getline(file,temp, '	');
(*assigned_ship).efficency = atof(temp.c_str());
getline(file,temp, '	');
(*assigned_ship).guncount = atoi(temp.c_str());
getline(file,(*assigned_ship).hull_class, '	');
getline(file,(*assigned_ship).ship_class, '	');
getline(file,(*assigned_ship).nation,'	');

getline(file,(*assigned_ship).skill1, '	');
getline(file,(*assigned_ship).skill2, '	');
getline(file,(*assigned_ship).skill3, '	');
getline(file,(*assigned_ship).skill4);
}




int main(){
string fileinput;

    cout << "loading fleet composition...";
    //read ships
    int ship_count;
    ifstream shipfile ("ships.txt");
    if(!shipfile.is_open()){
        cout << "Failed to find ships.txt" << endl;
        system("pause");
        return 1;
    }

    getline(shipfile,fileinput);

    ship_count = atoi(fileinput.c_str());

    ship ships[ship_count];


    bool failed = false;
    read_ships(&ships[0], atoi(fileinput.c_str()), &failed);
    if(failed){
        cout << "Please check ships.txt" << endl;
        system("pause");
        return 1;
    }

    cout << "loaded" << endl << "loading gun stats...";

    //read guns
    ifstream guns ("guns.txt");
    if(!guns.is_open()){
        cout << "Failed to find guns.txt" << endl;
        system("pause");
        return 1;
    }





    getline(guns,fileinput);
    int amount_of_guns;
    amount_of_guns = atoi(fileinput.c_str());
    getline(guns,fileinput);

    gun AAgun[amount_of_guns];

    read_guns(&AAgun[0]);

    cout<< "loaded" << endl;


    cout << "Assigning ship stats..." << endl;

    int failure = 0;
    for(int i = 0; i < ship_count; i++){
        assign_ship((ships+i), &failure);
        if(failure == 1){
            cout << "list_of_ships.txt not found" << endl;
            system("pause");
            return 1;
        }
        if(failure == 2){
            cout << "Ship called " << ships[i].name << " not found on the list" << endl;
            return 1;
        }
    }


    int guncount = 0;

    for(int i = 0;  i < ship_count; i++){
        guncount += ships[i].guncount;
    }

    long int guncomp_count = pow(amount_of_guns,ship_count);

    vector <dps_comb> guncomp;

    cout << "calculating dps, this might take a while...";

    calculate_dps       (ship_count,    amount_of_guns,     guncomp_count,      guncount,       AAgun,     ships,       &guncomp           );

     cout << endl <<
     "---------------------------------------------" << endl <<
     "|            Best gun combination" << endl <<
     "|--------------------------------------------" << endl;
     for(int i = 0; i < ship_count;i++)
     cout << "|   " << guncomp[guncomp_count-1].gun[i] << endl;
     cout << "|   DPS: " << guncomp[guncomp_count-1].dps << endl;
cout << "|--------------------------------------------" << endl;


system("pause");
return 0;
};
