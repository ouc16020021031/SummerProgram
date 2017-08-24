#include<cstring>
#include<vector>
#include<iostream>
/***********value**define*******/
#define morale_Hurrah 0.8
#define morale_Defeate 0.2
#define morale_Undefeate 0.2
#define life_Reward 8

using namespace std;

enum timeline_value {MakeKnight, RunAway, SetOff, MakeLife, GetLife, Hurt, Use, Fight, ReportLife, ReportWeapon};
enum knight_value {dragon, ninjia, iceman, lion, wolf};
enum weapon_value {sword, bomb, arrow};
enum color_value {white, red, blue};
int timeline[10] = {0, 5, 10, 20, 30, 35, 38, 40, 50, 55};
int order[3][5] = {{0}, {iceman, lion, wolf, ninjia, dragon}, { lion, dragon, ninjia, iceman, wolf }};
string knight_name[5] = {"dragon", "ninjia", "iceman", "lion", "wolf"};
string weapon_name[3] = {"sword", "bomb", "arrow"};
string color_name[3] = {"white", "red", "blue"};

int attack_knight[5];
int life_make[5];
int hour, minute, total_minute;
int total_city, total_life;
int arrow_attack;
int loyal_reduce;

class Knight;//����
class City;
class Command;
class Weapon;

void print_time();
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
		number = 1;
		life = life_;
		name_value = color_;
		name = color_name[name_value];
	}
	void min_0();
	void min_10();
	void min_50() {
		cout << life << " elements in " << name << " headquarter" << endl;
	}
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
	bool active_flag;
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
		win_flag = false;
		kill_flag = false;
		active_flag = false;
		counterattack_flag = true;
		weapon[0] = NULL;
		weapon[1] = NULL;
		weapon[2] = NULL;
		city_belong = NULL;
		command_belong = command_belong_;
		color = color_;
		number = number_;
		name_value = order[color][number % 5 - 1];
		life = life_make[name_value];
		attack = attack_knight[name_value];
		name = knight_name[name_value];
		command[color]->life -= life;
		switch(name_value) {
		case dragon:
			weapon[number % 3] = new Weapon(number % 3, attack_knight[name_value]);
			morale = command[color]->life / life_make[name_value];
			break;
		case ninjia:
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
		cout << color_name[color] << ' ' << name << ' ' << number << " born\n";
		if (name_value == dragon) {
			cout << "Its morale is ";
			cout.precision(2);
			cout << fixed << morale << endl;
		}
		if (name_value == lion) {
			cout << "Its loyalty is " << loyal << endl;
		}
	}
	~Knight() {
		for (int i = 0; i < 3; ++i)
			if (weapon[i]) delete weapon[i];
	}
	bool lion_run() {
		if(loyal <= 0)return true;
		else return false;
	}
	bool killed(City* city);
	bool active_attack(Knight* enemy, City* city) ;
	bool counterattack(Knight* enemy, City* city) ;
	bool yell(int city_number) ;
	int min_55();
};

class City {
  public:
	int flag;
	int win[2];
	int life;
	int number;
	Knight* knight_temp[3];
	Knight* knight_in_city[3];
	City(int number_) {
		life = 0;
		flag = white;
		win[0] = white;
		win[1] = white;
		number = number_;
		knight_temp[white] = NULL;
		knight_temp[red] = NULL;
		knight_temp[blue] = NULL;
		knight_in_city[white] = NULL;
		knight_in_city[red] = NULL;
		knight_in_city[blue] = NULL;
	}
	void min_5();
	void min_20() {
		life += 10;
	}
	int min_30();
	void min_35();
	void min_38();
	void min_40();
};

bool Knight::killed(City* city) {
	if(life <= 0) {
		print_time();
		cout << color_name[color] << ' ' << name << ' ' << number << " was killed in city " << city->number << endl;
		return true;
	} else return false;
}

bool Knight::active_attack(Knight* enemy, City* city) {
	int temp = attack;
	if(weapon[sword]) {
		temp += weapon[sword]->attack;
		weapon[sword]->attack *= 0.8;
	}
	enemy->life -= temp;
	print_time();
	cout << color_name[color] << ' ' << name << ' ' << number << " attacked " << color_name[enemy->color] << ' ' << enemy->name << ' ' << enemy->number << " in city " << city->number << " with " << life << " elements and force " << attack << endl;
	if(enemy->killed(city)) {
		if(name_value == wolf) {
			if(enemy->weapon[arrow] && weapon[arrow] == NULL) {
				weapon[arrow] = enemy->weapon[arrow];
				enemy->weapon[arrow] = NULL;
			}
			if(enemy->weapon[bomb] && weapon[bomb] == NULL) {
				weapon[bomb] = enemy->weapon[bomb];
				enemy->weapon[bomb] = NULL;
			}
			if(enemy->weapon[sword] && weapon[sword] == NULL) {
				weapon[sword] = enemy->weapon[sword];
				enemy->weapon[sword] = NULL;
			}
		}
		delete enemy;
		city->knight_in_city[enemy->color] = NULL;
		return true;
	} else return false;
}

bool Knight::counterattack(Knight* enemy, City* city) {
	if(counterattack_flag) {
		int temp = attack / 2;
		if(weapon[sword]) {
			temp += weapon[sword]->attack;
			weapon[sword]->attack *= 0.8;
		}
		enemy->life -= temp;
		print_time();
		cout << color_name[color] << ' ' << name << ' ' << number << " fought back against " << color_name[enemy->color] << ' ' << enemy->name << ' ' << enemy->number << " in city " << city->number << endl;
		if(enemy->killed(city)) {
			if(name_value == wolf) {
				if(enemy->weapon[arrow] && weapon[arrow] == NULL) {
					weapon[arrow] = enemy->weapon[arrow];
					enemy->weapon[arrow] = NULL;
				}
				if(enemy->weapon[bomb] && weapon[bomb] == NULL) {
					weapon[bomb] = enemy->weapon[bomb];
					enemy->weapon[bomb] = NULL;
				}
				if(enemy->weapon[sword] && weapon[sword] == NULL) {
					weapon[sword] = enemy->weapon[sword];
					enemy->weapon[sword] = NULL;
				}
			}
			delete enemy;
			city->knight_in_city[enemy->color] = NULL;
			return true;
		} else return false;
	} else return false;
}

bool Knight::yell(int city_number) {
	if(morale > 0.8) {
		print_time();
		cout << color_name[color] << ' ' << name << ' ' << number << " yelled in city " << city_number << endl;
		return true;
	} else return false;
}

void print_time() { //���ǰ��ʱ��
	cout.width(3);
	cout.fill('0');
	cout << hour << ':';
	cout.width(2);
	cout << minute << ' ';
}

void Command::min_0() {//make knight
	if(life >= life_make[order[name_value][number % 5 - 1]]) {
		print_time();
		knight = new Knight(name_value, number, this);
		number++;
	}
}

void City::min_5() {//lion run away
	int i = white;
	while(i++ < 2) {
		if(knight_in_city[i] && knight_in_city[i]->name_value == lion && knight_in_city[i]->lion_run()) {
			print_time();
			cout << color_name[knight_in_city[i]->color] << ' ' << knight_in_city[i]->name << ' ' << knight_in_city[i]->number << " ran away" << endl;
			delete knight_in_city[i];
			knight_in_city[i] = NULL;
		}
	}
}

void min_10() {//knight set off
	//red
	city.begin()->knight_temp[red] = command[red]->knight;
	command[red]->knight = NULL;
	//city
	vector<City>::iterator it = city.begin();
	while(it != city.end()) {
		int i = white;
		while(i++ < 2) {
			if(it->knight_in_city[i]) {
				if(it->number != total_city){cout<<"!!!!!"<<endl;
				(it + 1)->knight_temp[i] = it->knight_in_city[i];}
				else {cout<<"====="<<endl;
					if(command[blue]->weather_enemy) {
						command[blue]->number_enemy[1] = it->knight_in_city[i];
						print_time();
						cout << color_name[it->knight_in_city[i]->color] << ' ' << it->knight_in_city[i]->name << ' ' << it->knight_in_city[i]->number << " reached blue headquarter with " << it->knight_in_city[i]->life << " elements and force " << it->knight_in_city[i]->attack << endl;
						print_time();
						cout << "blue headquarter was taken" << endl;
					} else command[blue]->number_enemy[0] = it->knight_in_city[i];
					it->knight_in_city[i] = NULL;
				}
				if(it->number != 1)
					(it - 1)->knight_temp[i] = it->knight_in_city[i];
				else {
					if(command[red]->weather_enemy) {
						command[red]->number_enemy[1] = it->knight_in_city[i];
						print_time();
						cout << color_name[it->knight_in_city[i]->color] << ' ' << it->knight_in_city[i]->name << ' ' << it->knight_in_city[i]->number << " reached red headquarter with " << it->knight_in_city[i]->life << " elements and force " << it->knight_in_city[i]->attack << endl;
						print_time();
						cout << "red headquarter was taken" << endl;
					} else command[red]->number_enemy[0] = it->knight_in_city[i];
					it->knight_in_city[i] = NULL;
				}
			}
		}
		it++;
	}
	it = city.begin();
	while(it != city.end()) {
		int i = white;
		while(i++ < 2) {
			it->knight_in_city[i] = it->knight_temp[i];
			it->knight_temp[i] = NULL;
			if(it->knight_in_city[i]) {
				print_time();
				cout << color_name[i] << ' ' << it->knight_in_city[i]->name << ' ' << it->knight_in_city[i]->number << " marched to city " << it->number << " with " << it->knight_in_city[i]->life << " elements and force " << it->knight_in_city[i]->attack << endl;
			}
		}
		it++;
	}
	//blue
	(city.end() - 1)->knight_in_city[blue] = command[blue]->knight;
	command[blue]->knight = NULL;
	if((city.end() - 1)->knight_in_city[blue]) {
		print_time();
		cout << "blue " << (city.end() - 1)->knight_in_city[blue]->name << ' ' << (city.end() - 1)->knight_in_city[blue]->number << " marched to city " << total_city << " with " << (city.end() - 1)->knight_in_city[blue]->life << " elements and force " << (city.end() - 1)->knight_in_city[blue]->attack << endl;
	}
}

int City::min_30() {
	if(knight_in_city[red] && knight_in_city[blue] == NULL) {
		command[red]->life += life;
		print_time();
		cout << "red " << knight_in_city[red]->name << ' ' << knight_in_city[red]->number << " earned " << life << " elements for his headquarter" << endl;
		life = 0;
		return 0;
	}
	if(knight_in_city[blue] && knight_in_city[red] == NULL) {
		command[blue]->life += life;
		print_time();
		cout << "blue " << knight_in_city[blue]->name << ' ' << knight_in_city[blue]->number << " earned " << life << " elements for his headquarter" << endl;
		life = 0;
		return 0;
	}
}

void arrow_hurt(int number, Knight* who_arrow) {
	int i = white;
	vector<City>::iterator it = city.begin() + number;
	while(i++ < 2) {
		if(it->knight_in_city[i] && it->knight_in_city[i]->color != who_arrow->color) {
			if((it->knight_in_city[i]->life -= arrow_attack) <= 0) {
				print_time();
				cout << color_name[who_arrow->color] << who_arrow->name << ' ' << who_arrow->number << " shot and killed " << color_name[it->knight_in_city[i]->color] << ' ' << it->knight_in_city[i]->name << ' ' << it->knight_in_city[i]->number << endl;
				delete it->knight_in_city[i];
				it->knight_in_city[i] = NULL;
				if(i == red && it->knight_in_city[blue])it->knight_in_city[blue]->win_flag = true;
				if(i == blue && it->knight_in_city[red])it->knight_in_city[red]->win_flag = true;
			} else {
				print_time();
				cout << color_name[who_arrow->color] << who_arrow->name << ' ' << who_arrow->number << " shot" << endl;
			}
			if(--(who_arrow->weapon[arrow]->attack_times) == 0) {
				delete who_arrow->weapon[arrow];
				who_arrow->weapon[arrow] = NULL;
			}
		}
	}
}

void City::min_35() {
	int i = white;
	while(i++ < 2) {
		if(knight_in_city[i] && knight_in_city[i]->weapon[arrow]) {
			int temp;
			if(i == red)temp = knight_in_city[i]->number + 1;
			if(i == blue)temp = knight_in_city[i]->number - 1;
			arrow_hurt(temp - 1, knight_in_city[i]);
			break;
		}
	}
}

void bomb_use(Knight* who_bomb, Knight* enemy) {
	print_time();
	cout << color_name[who_bomb->color] << ' ' << who_bomb->name << ' ' << who_bomb->number << " used a bomb and killed " << color_name[enemy->color] << ' ' << enemy->name << ' ' << enemy->number << endl;
	delete who_bomb;
	delete enemy;
}

void City::min_38() {
	if(knight_in_city[red] && knight_in_city[blue] && (knight_in_city[blue]->weapon[bomb] || knight_in_city[red]->weapon[bomb])) {
		if(knight_in_city[red]->weapon[bomb]) {
			if((knight_in_city[red]->active_flag && knight_in_city[blue]->name_value != ninjia && knight_in_city[blue]->weapon[sword]->attack + knight_in_city[blue]->attack / 2 > knight_in_city[blue]->life) || (knight_in_city[red]->active_flag == false && knight_in_city[blue]->weapon[sword]->attack + knight_in_city[blue]->attack > knight_in_city[blue]->life)) {
				bomb_use(knight_in_city[red], knight_in_city[blue]);
				knight_in_city[red] = NULL;
				knight_in_city[blue] = NULL;
			}
		}
		if(knight_in_city[blue]->weapon[bomb]) {
			if((knight_in_city[blue]->active_flag && knight_in_city[red]->name_value != ninjia && knight_in_city[red]->weapon[sword]->attack + knight_in_city[red]->attack / 2 > knight_in_city[red]->life) || (knight_in_city[blue]->active_flag == false && knight_in_city[red]->weapon[sword]->attack + knight_in_city[red]->attack > knight_in_city[red]->life)) {
				bomb_use(knight_in_city[blue], knight_in_city[red]);
				knight_in_city[blue] = NULL;
				knight_in_city[red] = NULL;
			}
		}
	}
}

void City::min_40() {
	int temp, ftemp;
	if(flag == red || number % 2) {
		temp = red;
		ftemp = blue;
	} else {
		temp = blue;
		ftemp = red;
	}
	if(knight_in_city[temp] && knight_in_city[ftemp]) {
		if(knight_in_city[temp]->active_attack(knight_in_city[ftemp], this)) {
			knight_in_city[temp]->win_flag = true;
			win[0] = win[1];
			win[1] = temp;
		} else if(knight_in_city[ftemp]->counterattack(knight_in_city[temp], this)) {
			knight_in_city[ftemp]->win_flag = true;
			win[0] = win[1];
			win[1] = ftemp;
		}
	}
	if(knight_in_city[temp] == NULL && knight_in_city[ftemp]) {
		if(knight_in_city[ftemp]->win_flag) {
			win[0] = win[1];
			win[1] = ftemp;
		}
	}
	if(knight_in_city[ftemp] == NULL && knight_in_city[temp]) {
		if(knight_in_city[temp]->win_flag) {
			win[0] = win[1];
			win[1] = ftemp;
		}
	}
	if(knight_in_city[temp]) {
		if(knight_in_city[temp]->win_flag) {
			command[temp]->life += life;
			print_time();
			cout << color_name[temp] << " " << knight_in_city[temp]->name << ' ' << knight_in_city[temp]->number << " earned " << life << " elements for his headquarter" << endl;
			life = 0;
		}
		if(knight_in_city[temp]->name_value == dragon) {
			if(knight_in_city[temp]->win_flag)knight_in_city[temp]->morale += 0.2;
			else knight_in_city[temp]->morale -= 0.2;
			knight_in_city[temp]->yell(number);
		}
		knight_in_city[temp]->win_flag = false;
	}
	if(knight_in_city[ftemp]) {
		if(knight_in_city[ftemp]->win_flag) {
			command[ftemp]->life += life;
			print_time();
			cout << color_name[ftemp] << " " << knight_in_city[ftemp]->name << ' ' << knight_in_city[ftemp]->number << " earned " << life << " elements for his headquarter" << endl;
			life = 0;
		}
		if(knight_in_city[ftemp]->name_value == dragon) {
			if(knight_in_city[ftemp]->win_flag)knight_in_city[ftemp]->morale += 0.2;
			else knight_in_city[ftemp]->morale -= 0.2;
			knight_in_city[ftemp]->yell(number);
		}
		knight_in_city[ftemp]->win_flag = false;
	}
	if(win[0] == win[1])flag = win[0];
}

int Knight::min_55() {
	if(weapon[arrow] && weapon[bomb] && weapon[sword]) {
		cout << color_name[color] << ' ' << name << ' ' << number << " has arrow(" << weapon[arrow]->attack_times << "), bomb, sword(" << weapon[sword]->attack << ')' << endl;
		return 0;
	}
	if(weapon[arrow] && weapon[bomb]) {
		cout << color_name[color] << ' ' << name << ' ' << number << " has arrow(" << weapon[arrow]->attack_times << "), bomb" << endl;
		return 0;
	}
	if(weapon[arrow] && weapon[sword]) {
		cout << color_name[color] << ' ' << name << ' ' << number << " has arrow(" << weapon[arrow]->attack_times << "), sword(" << weapon[sword]->attack << ')' << endl;
		return 0;
	}
	if(weapon[bomb] && weapon[sword]) {
		cout << color_name[color] << ' ' << name << ' ' << number << " has bomb, sword(" << weapon[sword]->attack << ')' << endl;
		return 0;
	}
	if(weapon[arrow]) {
		cout << color_name[color] << ' ' << name << ' ' << number << " has arrow(" << weapon[arrow]->attack_times << ')' << endl;
		return 0;
	}
	if(weapon[bomb]) {
		cout << color_name[color] << ' ' << name << ' ' << number << " has bomb" << endl;
		return 0;
	}
	if(weapon[sword]) {
		cout << color_name[color] << ' ' << name << ' ' << number << " has sword(" << weapon[sword]->attack << ')' << endl;
		return 0;
	}
	cout << color_name[color] << ' ' << name << ' ' << number << " has no weapon" << endl;
}

void enter() {//��������,��ʼ��
	hour = -1;
	minute = 0;
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

int time() { //ʱ����,�����¼�
	minute = 0;
	hour++;
	if(60 * hour + 0 <= total_minute) {//make knight
		command[red]->min_0();
		command[blue]->min_0();
	}
	minute = 5;
	if(60 * hour + 5 <= total_minute) {//lion run away
		vector<City>::iterator it = city.begin();
		while(it != city.end()) {
			it->min_5();
			it++;
		}
		int _clolor_ = blue;
		while(_clolor_) {
			if(command[_clolor_]->knight && command[_clolor_]->knight->name_value == lion && command[_clolor_]->knight->lion_run()) {
				print_time();
				cout << color_name[_clolor_] << ' ' << command[_clolor_]->knight->name << ' ' << command[_clolor_]->knight->number << " ran away" << endl;
				delete command[_clolor_]->knight;
				command[_clolor_]->knight = NULL;
			}
			_clolor_--;
		}
	}
	minute = 10;
	if(60 * hour + 10 <= total_minute) {//knight set off
		min_10();
		if(command[red]->number_enemy[1] || command[blue]->number_enemy[1])return 0;
	}
	minute = 20;
	if(60 * hour + 20 <= total_minute) {//city make life
		vector<City>::iterator it = city.begin();
		while(it != city.end()) {
			it->min_20();
			it++;
		}
	}
	if(60 * hour + 30 <= total_minute) {//command get life
		minute = 30;
		vector<City>::iterator it = city.begin();
		while(it != city.end()) {
			it->min_30();
			it++;
		}
	}
	minute = 35;
	if(60 * hour + 35 <= total_minute) {//use arrow          debug
		vector<City>::iterator it = city.begin();
		while(it != city.end()) {
			it->min_35();
			it++;
		}
	}
	minute = 38;
	if(60 * hour + 38 <= total_minute) {//use bomb           coding...
		vector<City>::iterator it = city.begin();
		while(it != city.end()) {
			it->min_38();
			it++;
		}
	}
	minute = 40;
	if(60 * hour + 40 <= total_minute) {//fight
		vector<City>::iterator it = city.begin();
		while(it != city.end()) {
			it->min_40();
			it++;
		}
	}
	minute = 50;
	if(60 * hour + 50 <= total_minute) {//report life
		print_time();
		command[red]->min_50();
		print_time();
		command[blue]->min_50();
	}
	minute = 55;
	if(60 * hour + 55 <= total_minute) {//report weapon
		vector<City>::iterator it = city.begin();
		while(it != city.end()) {
			if(it->knight_in_city[red]) {
				print_time();
				it->knight_in_city[red]->min_55();
			}
			if(it->knight_in_city[blue]) {
				print_time();
				it->knight_in_city[blue]->min_55();
			}
			it++;
		}
	}
}

int main() {
	int n, i = 0;
	cin >> n;
	while(n--) {
		enter();
		cout << "Case " << ++i << ":\n";
		while(hour * 60 + minute <= total_minute) {
			time();
		}
	}
	return 0;
}

