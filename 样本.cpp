#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
using namespace std;
enum Knight_name{dragon, ninja, iceman, lion, wolf};//��ʿ����
enum Weapon_name{sword, bomb, arrow};//��������
string Knight[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};//��ʿ���ƣ����ʹ��
Knight_name Order[2][5] = {{iceman, lion, wolf, ninja, dragon},//����˳��
				   	   	   {lion, dragon, ninja, iceman, wolf}};
string Color[2] = {"red", "blue"};//˾���ɫ�����ʹ��
string Weapons_[3] = {"sword", "bomb", "arrow"};//�������ƣ����ʹ��
int Attack_[5];//����ʿ��ʼ������
int Loyal_reduce;//lionδɱ������������ʿ��
int Hour, Minute;//��ʱ��
int Total_Minutes;//��ֹʱ��
int Life_Make[5];//���������ʿ��������Ԫ
int arrow_attack;//arrow������
void Print_time(){//���ǰ��ʱ��
	cout.width(3); cout.fill('0');
	cout << Hour << ':';cout.width(2);
	cout << Minute << ' ';
}
class City;
class Command;
class Weapon{//����
private:
	int name, sword_attack, arrow_usetime;//�������ƣ�sword��������arrowʣ��ʹ�ô���
public:
	Weapon(int i, int satt):name(i), sword_attack(satt),arrow_usetime(3){}//����״̬��ʼ��
	bool sword_dull(){//sword���
		sword_attack = int (sword_attack * 0.8);
		return sword_attack;
	}
	int &usetime(){return arrow_usetime;}
	int sw_atk(){return sword_attack;}
};
class Warrior{//ʿ��
private:
	int Num, Life, Attack, Loyal, Step, l_life;//��ţ������������������ҳ϶ȣ�����
	Knight_name name;//��ʿ����
	double Morale;//ʿ��
	City* City_Belong_to;//��������
	Command* Command_Belong_to;//����˾�
	bool If_win,If_kill;//ս���Ƿ��ʤ���Ƿ�ɱ������
	Weapon* weapon[3];//װ��
public:
	Warrior(int n, Knight_name &name_, int &life, int &t_life,Command *COMD){//��ʼ��ʿ������
		Num = n; name = name_; Life = life; Attack = Attack_[name]; Step = 0; l_life = 0;
		weapon[0] = NULL; weapon[1] = NULL; weapon[2] = NULL;
		switch(name){
			case dragon:case iceman: weapon[Num % 3] = new Weapon(Num % 3, int(Attack_[name] * 0.2)); break;
			case ninja: weapon[Num % 3] = new Weapon(Num % 3, int(Attack_[name] * 0.2));
						weapon[(Num + 1) % 3] = new Weapon((Num + 1) % 3, int(Attack_[name] * 0.2)); break;
			default: break;
		};
		if (weapon[sword]) if (!weapon[sword]->sw_atk()) weapon[sword] = NULL;//����ʼ��������Ϊ0����delete
		Morale = double(t_life) / double(Life);
		Loyal = t_life; If_win = false; If_kill = false;
		City_Belong_to = NULL; Command_Belong_to = COMD;
		cout << Knight[name] << ' ' << Num << " born\n";
		if (name == dragon){
			cout << "Its morale is ";
			cout.precision(2);
			cout << fixed << Morale << endl;
		}
		if (name == lion){cout << "Its loyalty is " << Loyal << endl;}
	}
	bool &IF_win(){return If_win;}
	int life(){return Life;}
	bool Minute_5();//lion�Ƿ����� ���
	void Minute_10(bool );//��ʿǰ�����
	void Minute_30(int );//��ȡ��������Ԫ�����
	void arrow_shot();//ʹ�ù������
	void Be_shoted();//�����д������
	void Change_City(City * Cp){City_Belong_to = Cp;}
	void Morale_Change(){If_win ? Morale += 0.2: Morale -=0.2;}
	bool weapon_(Weapon_name name){return weapon[name];}
	void Use_bomb(Warrior *);//ʹ��bomb���
	int fight(Warrior* Wp){//����ս�����ж��Ƿ���ʤ
		if (Life > 0 and Wp->Life > 0){
			int swatk = 0;
			if (weapon[sword]) swatk = weapon[sword]->sw_atk();
			if (Wp->Life - Attack- swatk > 0){
				if (Wp->name == ninja) return 0;
				else{
					int E_swatk = 0;
					if (Wp->weapon[sword]) E_swatk = (Wp->weapon[sword])->sw_atk();
					if (Life - (Wp->Attack / 2) - E_swatk > 0) return 0;
					else return -1;
				}
			}else return 1;
		}
		return 0;
	}
	bool bomb(Warrior *, int);//�ж��Ƿ�ʹ��bomb
	void Fight(Warrior *);//��ʿս���������
	void Dead();//��ʿ�������
	void account(Warrior * Wp){//����ս����
		If_win = true;
		if(If_kill) {Wp->Dead();If_kill = false;}
		if (Wp->name == lion) Life += Wp->l_life;
		if (name == wolf)
			for (int i = 0; i < 3; ++i)
				if (Wp->weapon[i] and !weapon[i]){
					weapon[i] = Wp->weapon[i];
					Wp->weapon[i] = NULL;
				}
		Morale_Change();
	}
	void Reward();//սʤ���ȡ����
	void ADD(int);//����˾���������Ԫ
	void Loyal_Reduce(){Loyal -= Loyal_reduce;}
	void Report_weapon();//��������ʹ�����
	~Warrior(){
		for (int i = 0; i < 3; ++i)
			if (weapon[i]) delete weapon[i];
	}
};
class City{
private:
	int Number, Life, Flag, Flag_G[2];//���б�ţ�����Ԫ�����ģ�����ʿ������ʤ������
	Warrior *Warrior_In_City[2];
public:
	int Num(){return Number;}
	int Life_(){return Life;}
	City(int N){
		Number = N; Life = 0; Flag = -1;//-1 ��ʾ�������
		Warrior_In_City[0] = NULL; Flag_G[0] = 0;
		Warrior_In_City[1] = NULL; Flag_G[1] = 0;
	}
	void Minute_5(){//��������lion
		for(int i = 0; i < 2; ++i)
			if(Warrior_In_City[i]) if (Warrior_In_City[i]->Minute_5()){
				delete Warrior_In_City[i]; Warrior_In_City[i] = NULL;
			}
	}
	void Move(City* Cp, int i){//warriorǰ��
		Warrior_In_City[i] = Cp->Warrior_In_City[i];
		if(Warrior_In_City[i]) Warrior_In_City[i]->Change_City(this);
	}
	void Move(Command *, int);//warrior����з�˾�
	void Move(Warrior *Wp, int i){//warrior��command����city
		Warrior_In_City[i] = Wp;
		if (Warrior_In_City[i]) Warrior_In_City[i]->Change_City(this);
	}
	bool If_exist(int i){return Warrior_In_City[i];}
	void Minute_10(){//warriorǰ�����
		if (Warrior_In_City[0]) Warrior_In_City[0]->Minute_10(false);
		if (Warrior_In_City[1]) Warrior_In_City[1]->Minute_10(false);
	}
	void Add_Life(){Life += 10;}
	void Minute_30(){//���ڵ���warrior��ȡ����Ԫ
		for (int i = 0; i < 2; ++i)
		if ((Warrior_In_City[i]) and (!Warrior_In_City[1-i])){
			Warrior_In_City[i]->Minute_30(Life);
			Life = 0; break;
		}
	}
	void Minute_35(City* Cp[]){//����arrow�¼�
		for (int j = 0; j < 2; ++j)
			if (Warrior_In_City[j]) if (Warrior_In_City[j]->weapon_(arrow))
				if (Cp[1-j]) if ((Cp[1-j]->Warrior_In_City[1-j])){
					Warrior_In_City[j]->arrow_shot();
					Cp[1-j]->Warrior_In_City[1-j]->Be_shoted();
				}
	}
	void Minute_38(){//����bomb�¼���˳������35����ʱ��������ֻwarrior���������������
		if (Warrior_In_City[0] and Warrior_In_City[1]){
			bool p =false;
			for (int i = 0; i < 2; ++i)
				if (Warrior_In_City[i]->weapon_(bomb)){
					if (Flag == -1) p = Warrior_In_City[i]->bomb(Warrior_In_City[1-i], Number);
					else p = Warrior_In_City[i]->bomb(Warrior_In_City[1-i], Flag+1);
					if (p){
						delete Warrior_In_City[0]; Warrior_In_City[0] = NULL;
						delete Warrior_In_City[1]; Warrior_In_City[1] = NULL;
						break;
					}
				}
			if (!p and Warrior_In_City[0]->life() <= 0 and Warrior_In_City[1]->life() <= 0){
				delete Warrior_In_City[0]; Warrior_In_City[0] = NULL;
				delete Warrior_In_City[1]; Warrior_In_City[1] = NULL;
			}
		}
	}
	void Battle(){//ս�������������������Ԫ��������ȡ����
		if (Warrior_In_City[0] and Warrior_In_City[1]){
			if (Flag == -1){
				if (Number % 2) Warrior_In_City[0]->Fight(Warrior_In_City[1]);
				else Warrior_In_City[1]->Fight(Warrior_In_City[0]);
			}else
				Warrior_In_City[Flag]->Fight(Warrior_In_City[1-Flag]);
		}
	}
	void Flag_Set(int i){//ս������������
		if (i == -1){Flag_G[0] = 0; Flag_G[1] = 0;}
		else{
			++Flag_G[i]; Flag_G[1-i] = 0;
			if (Flag_G[i] == 2 and Flag != i){
				Flag = i;
				Print_time();
				cout << Color[i] << " flag raised in city " << Number << endl;}
		}
	}
	void Reward(int i){if(Warrior_In_City[i]) Warrior_In_City[i]->Reward();}
	void Warrior_report(int i){if(Warrior_In_City[i]) Warrior_In_City[i]->Report_weapon();}
	void Win_get(){//������ʤʿ������Ԫ
		for (int i = 0; i < 2; ++i)
			if (Warrior_In_City[i]){
				if (Warrior_In_City[i]->IF_win()){
					Warrior_In_City[i]->ADD(Life);
					Life = 0; Warrior_In_City[i]->IF_win() = false;
				}else if (Warrior_In_City[i]->life() <=0){
					delete Warrior_In_City[i];
					Warrior_In_City[i] = NULL;
				}
			}
	}
};

class Command{
private:
	int Total_Life, Knights_Num, Colour, Enemy_Enter;//����Ԫ����ʿ��������command��ɫ���ж��ٵ��˽���
	bool Weather_Enter;//�Ƿ��е��˽���
	Warrior* Enemys[2];//����ĵ���
	Warrior* Knight;//warrior
public:
	int colour(){return Colour;}
	string colour(bool p){return p? Color[Colour]: Color[1-Colour];}
	Command(int TLife, int col){
		Total_Life = TLife;Colour = col;
		Knights_Num = 0;
		Knight = NULL; Enemy_Enter = 0;
		Weather_Enter = false;
		Enemys[0] = NULL; Enemys[1] = NULL;
	}
	void Minute_0(){//����warrior�����
		if (Total_Life >= Life_Make[Order[Colour][Knights_Num % 5]]){
			Total_Life -= Life_Make[Order[Colour][Knights_Num % 5]];
			Print_time();
			cout << Color[Colour] << ' ';
			Knight = new Warrior(Knights_Num+1, Order[Colour][Knights_Num % 5], Life_Make[Order[Colour][Knights_Num% 5]], Total_Life, this);
			Knights_Num++;
		}
	}
	void Minute_5(){//��������lion
		if (Knight) if (Knight->Minute_5()){delete Knight; Knight = NULL;}
	}
	void Move(City* Cp, int i){Cp->Move(Knight, i); Knight = NULL;}//warrior�߳�command
	void Enemy_Move_In(Warrior* enemy){//�з�warrior����
		Enemys[Enemy_Enter] = enemy;
		Weather_Enter = true;
		++Enemy_Enter;
	}
	void Minute_10(){//�з�warrior�������
		if (Weather_Enter){
			Enemys[Enemy_Enter-1]->Minute_10(true);
			Weather_Enter = false;
		}
	}
	bool If_occupied(){//command�Ƿ�ռ��
		if (Enemy_Enter == 2){
			Print_time();
			cout << Color[Colour] << " headquarter was taken\n";
			return true;
		}
		return false;
	}
	void Minute_30(int Add_life){Total_Life += Add_life;}
	int &Life(){return Total_Life;}
	void Report_life(){//command��������Ԫ
		Print_time();
		cout << Total_Life << " elements in " << Color[Colour] << " headquarter\n";
	}
	void Report(){if (Enemy_Enter) Enemys[Enemy_Enter-1]->Report_weapon();}//�ѽ���command��warrior��Ҫreport
	~Command(){
		if (Knight) delete Knight;
		if (Enemys[0]) delete Enemys[0];
		if (Enemys[1]) delete Enemys[1];
	}
};

void Game_Start(){
	int times = 0;
	cin >> times;
	for (int t = 0; t < times; ++t){
		int M, N;//��ʼcommand����Ԫ����������
		cin >> M >> N >> arrow_attack >> Loyal_reduce >> Total_Minutes;
		Command COM[2] = {Command(M,0),Command(M,1)};
		vector<City> Citys;
		for (int i = 0; i < N; ++i){
			City temp(i + 1);
			Citys.push_back(temp);
		}
		for (int i = 0; i < 5; ++i)
			cin >> Life_Make[i];
		for (int i = 0; i < 5; ++i)
			cin >> Attack_[i];
		cout << "Case " << t + 1 << ":\n";
		Hour = 0; Minute = 0;//��ʱ��ʼ
		while(Hour * 60 <= Total_Minutes){
			COM[0].Minute_0(); COM[1].Minute_0(); Minute = 5;//��0����
			if (Hour * 60 + Minute > Total_Minutes) break;//��5����
			else {
				COM[0].Minute_5();
				for (vector<City>::iterator i = Citys.begin(); i != Citys.end(); ++i)
					(*i).Minute_5();
				COM[1].Minute_5();
				Minute = 10;
			}
			if (Hour * 60 + Minute > Total_Minutes) break;//��10����
			else {
				if (Citys[0].If_exist(1)) Citys[0].Move(&COM[0], 1);//warriorǰ��
				for (int i = 0; i < N - 1; ++i)
					Citys[i].Move(&Citys[i+1], 1);
				COM[1].Move(&Citys[N - 1], 1);
				if (Citys[N-1].If_exist(0)) Citys[N-1].Move(&COM[1], 0);
				for (int i = N - 1; i > 0; --i)
					Citys[i].Move(&Citys[i-1], 0);
				COM[0].Move(&Citys[0], 0);
				COM[0].Minute_10();//warrior�ƶ����
				bool p = COM[0].If_occupied();
				for (int i = 0; i < N; ++i) Citys[i].Minute_10();
				COM[1].Minute_10();
				if (p + COM[1].If_occupied()) break;
			}
			Minute = 20;
			if (Hour * 60 + Minute > Total_Minutes) break;//��20����
			else
				for (int i = 0; i < N; ++i) Citys[i].Add_Life();
			Minute = 30;

			if (Hour * 60 + Minute > Total_Minutes) break;//��30����
			else
				for (int i = 0; i < N; ++i) Citys[i].Minute_30();
			Minute = 35;
			if (Hour * 60 + Minute > Total_Minutes) break;//��35����
			else
				if (N > 1){//city������1ʱ�Żᷢ��arrow�¼�
					City* Cp[2] = {};
					Cp[0] = NULL; Cp[1] = &Citys[1];
					Citys[0].Minute_35(Cp);
					for (int i = 1; i < N-1; ++i){
						Cp[0] = &Citys[i-1]; Cp[1] = &Citys[i+1];
						Citys[i].Minute_35(Cp);
					}
					Cp[0] = &Citys[N-2]; Cp[1] = NULL;
					Citys[N-1].Minute_35(Cp);
				}
			Minute = 38;
			if (Hour * 60 + Minute > Total_Minutes) break;//��38����
			else
				for (vector<City>::iterator i = Citys.begin(); i != Citys.end(); ++i)
					(*i).Minute_38();
			Minute = 40;
			if (Hour * 60 + Minute > Total_Minutes) break;//��40����
			else{
				for (vector<City>::iterator i = Citys.begin(); i != Citys.end(); ++i)//ս�������
					(*i).Battle();
				for (vector<City>::iterator i = Citys.begin(); i != Citys.end(); ++i)//��������Ԫ
					(*i).Reward(0);
				for (vector<City>::reverse_iterator i = Citys.rbegin(); i != Citys.rend(); ++i)
					(*i).Reward(1);
				for (vector<City>::iterator i = Citys.begin(); i != Citys.end(); ++i)//��ȡcity����Ԫ
					(*i).Win_get();
			}
			Minute = 50;
			if (Hour * 60 + Minute > Total_Minutes) break;//��50����
			else
				COM[0].Report_life();COM[1].Report_life();
			Minute = 55;
			if (Hour * 60 + Minute > Total_Minutes) break;//��55����
			else{
				for (vector<City>::iterator i = Citys.begin(); i != Citys.end(); ++i)
					(*i).Warrior_report(0);
				COM[1].Report();COM[0].Report();
				for (vector<City>::iterator i = Citys.begin(); i != Citys.end(); ++i)
					(*i).Warrior_report(1);
			}
			Minute = 0;
			Hour++;
		}
	}
}

int main(){
//	freopen("d:\\anser.txt", "w", stdout);
	Game_Start();
//	fclose(stdout);
	return 0;
}
bool Warrior::Minute_5(){
	if (name == lion) if (Loyal <= 0){
		Print_time();
		cout << Command_Belong_to->colour(true) << " lion " << Num << " ran away\n";
		return true;
	}
	return false;
}
void Warrior::Minute_10(bool If_arrive){
	++Step;
	if (name == iceman and !(Step % 2)){
		if (Life < 10) Life = 1;
		else Life -= 9;
		Attack += 20;
	}
	Print_time();
	cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num;
	if (If_arrive)
		cout << " reached " << Command_Belong_to->colour(false) << " headquarter";
	else cout << " marched to city " << City_Belong_to->Num();
	cout << " with " << Life << " elements and force " << Attack << endl;
}
void Warrior::Minute_30(int Add_life){
	Print_time();
	cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " earned " << Add_life << " elements for his headquarter\n";
	Command_Belong_to->Minute_30(Add_life);
}
void Warrior::arrow_shot(){
	Print_time();
	cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " shot";
	weapon[arrow]->usetime()--;
	if(!weapon[arrow]->usetime()){delete weapon[arrow]; weapon[arrow] = NULL;}
}
void Warrior::Be_shoted(){
	Life -= arrow_attack;
	if (Life <= 0){cout << " and killed " << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num;}
	cout << endl;
}
void City::Move(Command *Cp, int i){
	Cp->Enemy_Move_In(Warrior_In_City[i]);
	Warrior_In_City[i] = NULL;
}
void Warrior::Use_bomb(Warrior *Wp){
	Print_time();
	cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " used a bomb and killed " << (Wp->Command_Belong_to)->colour(true) << ' ' << Knight[Wp->name] << ' ' << Wp->Num << endl;
}
bool Warrior::bomb(Warrior *Wp, int p){
	if ((p + Command_Belong_to->colour()) % 2){
		if (fight(Wp) == -1) {Use_bomb(Wp); return true;}
	}else
		if (Wp->fight(this) == 1) {Use_bomb(Wp); return true;}
	return false;
}
void Warrior::Dead(){
	Print_time();
	cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " was killed in city " << City_Belong_to->Num() << endl;
}
void Warrior::Fight(Warrior *Wp){
	Warrior *Wp_win = NULL; Warrior *Wp_lose = NULL;
	l_life = Life; Wp->l_life = Wp->Life;
	if (Life > 0 and (Wp->Life) > 0){
		int swatk = 0;
		if (weapon[sword]) swatk = weapon[sword]->sw_atk();
		Print_time();
		cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " attacked " << (Wp->Command_Belong_to)->colour(true) << ' ' << Knight[Wp->name] << ' ' << Wp->Num << " in city " << City_Belong_to->Num() << " with " << Life << " elements and force " << Attack << endl;
		Wp->Life = Wp->Life - Attack - swatk;
		if (swatk) if (!weapon[sword]->sword_dull()){delete weapon[sword]; weapon[sword] = NULL;}
		if (Wp->Life > 0){
			if (Wp->name == ninja) {City_Belong_to->Flag_Set(-1);Morale_Change();Loyal_Reduce();}
			else{
				int E_swatk = 0;
				if (Wp->weapon[sword]) E_swatk = (Wp->weapon[sword])->sw_atk();
				Print_time();
				cout << (Wp->Command_Belong_to)->colour(true) << ' ' << Knight[Wp->name] << ' ' << Wp->Num << " fought back against " << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " in city " << City_Belong_to->Num() <<endl;
				Life = Life - (Wp->Attack / 2) - E_swatk;
				if (E_swatk) if(!(Wp->weapon[sword])->sword_dull()){delete Wp->weapon[sword]; Wp->weapon[sword] = NULL;}
				if (Life > 0) {City_Belong_to->Flag_Set(-1);Morale_Change();Wp->Morale_Change();Loyal_Reduce();Wp->Loyal_Reduce();}
				else{Wp->If_kill = true;Wp_lose = this;Wp_win = Wp;}
			}
		}else{If_kill = true;Wp_win = this;Wp_lose = Wp;}
	}else{
		if (Life > 0){Wp->l_life = 0;Wp_win = this;Wp_lose = Wp;}
		else {l_life = 0;Wp_lose = this;Wp_win = Wp;}
	}
	if (Wp_win){Wp_win->account(Wp_lose);}
	if (name == dragon and Life > 0 and Morale > 0.8){
		Print_time();
		cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " yelled in city " << City_Belong_to->Num() << endl;
	}
	if (Wp_win){
		Print_time();
		cout << (Wp_win->Command_Belong_to)->colour(true) << ' ' << Knight[Wp_win->name] << ' ' << Wp_win->Num << " earned " << City_Belong_to->Life_() << " elements for his headquarter\n";
		(Wp_win->City_Belong_to)->Flag_Set((Wp_win->Command_Belong_to)->colour());
	}
}
void Warrior::Reward(){
	if (If_win)
		if (Command_Belong_to->Life() > 7){
			Command_Belong_to->Life() -= 8;
			Life += 8;
		}
}
void Warrior::ADD(int life){Command_Belong_to->Life() += life;}
void Warrior::Report_weapon(){
	bool p = false;
	Print_time();
	cout << Command_Belong_to->colour(true) << ' ' << Knight[name] << ' ' << Num << " has ";
	for (int i = 2; i >= 0; --i)
		if (weapon[i]){
			if (p) cout << ',';else p = true;
			cout << Weapons_[i];
			if (i == 2) cout << '(' << weapon[arrow]->usetime() << ')';
			if (i == 0) cout << '(' << weapon[sword]->sw_atk() << ')';
		}
	if(!p) cout << "no weapon";
	cout << endl;
}