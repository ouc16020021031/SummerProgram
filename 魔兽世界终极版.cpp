#include<cstring>
#include<vector>
#include<iostream>
/***********value**define*******/
#define morale_Hurrah 0.8
#define morale_Defeate 0.2
#define morale_Undefeate 0.2
#define life_Reward 8
#define life_CityMake 10
/***********time*define*********/
#define time_command_MakeKnight 0
#define time_lion_RunAway 5
#define time_knight_SetOff 10
#define time_city_MakeLife 20
#define time_command_GetLife 30
#define time_arrow_Hurt 35
#define time_bomb_Use 38
#define time_knight_Fight 40
#define time_command_ReportLife 50
#define time_knight_ReportWeapon 55
using namespace std;

enum timeline_value {MakeKnight, RunAway, SetOff, MakeLife, GetLife, Hurt, Use, Fight, ReportLife, ReportWeapon};
enum knight_value {dragon, ninja, iceman, lion, wolf};
enum weapon_value {sword, bomb, arrow};
enum color_value {white, red, blue};
int timeline[10] = {0, 5, 10, 20, 30, 35, 38, 40, 50, 55};
int order[3][5] = {{0}, {iceman, lion, wolf, ninja, dragon}, { lion, dragon, ninja, iceman, wolf }};
string knight_name[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
string weapon_name[3] = {"sword", "bomb", "arrow"};
string color_name[3] = {"white", "red", "blue"};

int attack_knight[5];
int life_make[5];
int hour, minute, total_minute;
int total_city, total_life;
int arrow_attack;
int loyal_reduce;

class Knight;//声明
class City;
class Command;
class Weapon;

vector<City> city;

class Command {
  public:
	int life;
	int number;
	int name_value;
	bool weather_enemy;
	Knight* knight;
	Knight* number_enemy[2];
	string name;
	Command(int color_, int life_) {
		number_enemy[0] = NULL;
		number_enemy[1] = NULL;
		weather_enemy = false;
		knight = NULL;
		number = 0;
		life = life_;
		name_value = color_;
		name = color_name[name_value];
	}
	void min_0();
	void min_10();
} *command[3];

class Weapon {
  public:
	int attack;
	int attack_times;
	string name;
	int name_value;
	Weapon(int number, int knight_attack) {
		name_value = number;
		name = weapon_name[name_value];
		switch(name_value) {
		case sword:
			attack = knight_attack / 5;
			break;
		case bomb:
			break;
		case arrow:
			attack_times = 3;
			break;
		}
	}
};

class Knight {
  public:
	int loyal;
	int life;
	int attack;
	int number;
	int color;
	int twice_flag;
	int attack_increase;
	int life_reduce;
	bool kill_flag;
	bool win_flag;
	bool counterattack_flag;
	double morale;
	string name;
	City* city_belong;
	Command* command_belong;
	Weapon* weapon[3];
	int name_value;
	Knight(int color_, int number_, Command* command_belong_) {
		win_flag=false;
		kill_flag=false;
		counterattack_flag=true;
		weapon[0] = NULL;
		weapon[1] = NULL;
		weapon[2] = NULL;
		city_belong = NULL;
		command_belong = command_belong_;
		color = color_;
		number = number_;
		name_value = order[color][number % 5];
		life = life_make[name_value];
		name = knight_name[name_value];
		switch(name_value) {
		case dragon:
			weapon[number % 3] = new Weapon(number % 3, attack_knight[name_value]);
			morale = command[color]->life / life_make[name_value];
			break;
		case ninja:
			counterattack_flag = false;
			weapon[number % 3] = new Weapon(number % 3, attack_knight[name_value]);
			weapon[number % 3 + 1] = new Weapon(number % 3 + 1, attack_knight[name_value]);
			break;
		case iceman:
			twice_flag = -1;
			life_reduce = 9;
			attack_increase = 20;
			weapon[number % 3] = new Weapon(number % 3, attack_knight[name_value]);
			break;
		case lion:
			loyal = command[color]->life;
			break;
		case wolf:
			break;
		}
		if (weapon[sword]) if (!weapon[sword]->attack) weapon[sword] = NULL;
		cout << knight_name[name_value] << ' ' << number << " born\n";
		if (name_value == dragon){
			cout << "Its morale is ";
			cout.precision(2);
			cout << fixed << morale << endl;
		}
		if (name_value == lion){cout << "Its loyalty is " << loyal << endl;}
	}
	~Knight(){
		for (int i = 0; i < 3; ++i)
			if (weapon[i]) delete weapon[i];
	}
	bool lion_run() {
		if(loyal <= 0)return true;
		else return false;
	}
};

class City {
  public:
	int flag[2];
	int life;
	int number;
	Knight* knight_temp[2];
	Knight* knight_in_city[2];
	City(int number_) {
		number = number_;
		life = 0;
		flag[0] = white;
		flag[1] = white;
		knight_temp[0] = NULL;
		knight_temp[1] = NULL;
		knight_in_city[0] = NULL;
		knight_in_city[1] = NULL;
	}
	void min_5();
};

void print_time() { //输出前面时间
	cout.width(3);
	cout.fill('0');
	cout << hour << ':';
	cout.width(2);
	cout << minute << ' ';
}

void Command::min_0() {//make knight
	print_time();
	cout << color_name[name_value] <<" ";
	knight = new Knight(name_value, number, this);
	number++;

}

void City::min_5() {//lion run away
	int i = 2;
	while(i--) {
		if(knight_in_city[i]->lion_run()) {
			delete knight_in_city[i];
			knight_in_city[i] = NULL;
		}
	}
}

void min_10() {
	//city
	vector<City>::iterator it = city.begin();
	while(it != city.end()) {
		int i = 2;
		while(i--) {
			if(it->knight_in_city[i]->color == red) {
				if(it->number != total_city)
					(it + 1)->knight_temp[i] = it->knight_in_city[i];
				else {
					if(command[red]->number_enemy[0] == NULL)command[red]->number_enemy[0] = it->knight_in_city[i];
					else command[red]->number_enemy[1] = it->knight_in_city[i];
					it->knight_in_city[i] = NULL;
				}
			}
			if(it->knight_in_city[i]->color == blue) {
				if(it->number != 0)
					(it - 1)->knight_temp[i] = it->knight_in_city[i];
				else {
					if(command[blue]->number_enemy[0] == NULL)command[blue]->number_enemy[0] = it->knight_in_city[i];
					else command[blue]->number_enemy[1] = it->knight_in_city[i];
					it->knight_in_city[i] = NULL;
				}
			}
		}
		it++;
	}
	it = city.begin();
	while(it != city.end()) {
		int i = 2;
		while(i--) {
			it->knight_in_city[i] = it->knight_temp[i];
			it->knight_temp[i] = NULL;
		}
		it++;
	}
	//command
	int i = 2;
	while(i--) {
		if(city.begin()->knight_in_city[i] == NULL) {
			city.begin()->knight_in_city[i] = command[red]->knight;
			command[red]->knight = NULL;
			break;
		}
		if((city.end() - 1)->knight_in_city[i] == NULL) {
			(city.end() - 1)->knight_in_city[i] = command[blue]->knight;
			command[blue]->knight = NULL;
			break;
		}
	}
}

void enter() {//输入数据,初始化
	cin >> total_life >> total_city >> arrow_attack >> loyal_reduce >> total_minute;
	command[red] = new Command(red, total_life);
	command[blue] = new Command(blue, total_life);
	for(int i = 0; i < 5; i++) {
		cin >> life_make[i];
	}
	for(int i = 0; i < 5; i++) {
		cin >> attack_knight[i];
	}
	for (int i = 0; i < total_city; ++i) {
		City temp(i + 1);
		city.push_back(temp);
	}
}

void time() { //时间线,发生事件
	if(60 * hour + 0 < total_minute) {
		hour++;
		command[red]->min_0();
		command[blue]->min_0();
	}
	if(60 * hour + 5 < total_minute) {
		minute = 5;
	}
	if(60 * hour + 10 < total_minute) {
		minute = 10;
	}
	if(60 * hour + 20 < total_minute) {
		minute = 20;
	}
	if(60 * hour + 30 < total_minute) {
		minute = 30;
	}
	if(60 * hour + 35 < total_minute) {
		minute = 35;
	}
	if(60 * hour + 38 < total_minute) {
		minute = 38;
	}
	if(60 * hour + 40 < total_minute) {
		minute = 40;
	}
	if(60 * hour + 50 < total_minute) {
		minute = 50;
	}
	if(60 * hour + 55 < total_minute) {
		minute = 55;
	}
}

int main() {
	int n, i = 0;
	cin >> n;
	while(n--) {
		enter();
		time();
		cout << "Case " << ++i << ":\n";
	}
	return 0;
}

