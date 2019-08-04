#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

enum weapon
{
    sowrd,
    bomb,
    arrow
};

enum color
{
    red,
    blue
};

string Weapon(int &weapon)
{
    if (weapon == 0)
        return (string) "sword";
    else if (weapon == 1)
        return (string) "bomb";
    else if (weapon == 2)
        return (string) "arrow";
    return nullptr;
}

string Color(int color)
{
    if (color == 0)
        return (string) "red";
    else if (color == 1)
        return (string) "blue";
    return nullptr;
}

class HeadQuarter
{
public:
    HeadQuarter(int color, int lifeElem) : _color(color), _lifeElem(lifeElem) {}

    int getColor() { return _color; }
    int getLifeElem() { return _lifeElem; }
    void bornWarrior(int hp) { _lifeElem -= hp; }

    int getWarriorNum() { return _WarriorNum; }
    void increaseWarriorNum() { ++_WarriorNum; }

    int getIcemanNum() { return _icemanNum; }
    int getLionNum() { return _lionNum; }
    int getDragonNum() { return _lionNum; }
    int getWolfNum() { return _wolfNum; }
    int getNinjaNum() { return _ninjaNum; }

    void increaseIceman() { ++_icemanNum; }
    void increaseLion() { ++_lionNum; }
    void increaseDragon() { ++_dragonNum; }
    void increaseWolf() { ++_wolfNum; }
    void increaseNinja() { ++_ninjaNum; }

private:
    int _color;
    int _lifeElem;       //生命元
    int _WarriorNum = 1; //武士编号
    int _icemanNum = 0, _lionNum = 0, _dragonNum = 0, _wolfNum = 0, _ninjaNum = 0;
};

class Warrior
{
public:
    Warrior(int num, int hp)
        : _num(num), _hp(hp)
    {
        // cout << "Warrior(int, int)" << endl;
    }

    int getNum() { return _num; }
    int getHp() { return _hp; }

private:
    int _num; //编号，从1开始
    int _hp;  //生命值
};

class Dragon
    : public Warrior
{
public:
    Dragon(int hp, HeadQuarter &head)
        : Warrior(head.getWarriorNum(), hp)
    {
        // cout << "Dragon(int, HeadQuarter &)" << endl;
        _weapon = head.getWarriorNum() % 3;
        head.bornWarrior(hp);                              //主基地生命元减少
        _morale = (double)head.getLifeElem() / (double)hp; //获得士气
        head.increaseDragon();
    }

    void display(HeadQuarter &head)
    {
#ifdef DEBUG
        cout << "dragon's num = " << getNum() << endl
             << "dragon's hp = " << getHp() << endl
             << "dragon's weapon = " << Weapon(_weapon) << endl;
        printf("dragon's morale = %.2lf\n", _morale);
#endif
#if 1
        cout << "dragon " << getNum() << " born with strength "
             << getHp() << "," << head.getDragonNum() << " dragon in "
             << Color(head.getColor()) << " headquarter" << endl
             << "It has a " << Weapon(_weapon) << "and it's morale is ";
        printf("%.2lf\n", _morale);
#endif
    }

private:
    int _weapon;    //dragon has one weapon
    double _morale; //士气
};

class Ninja
    : public Warrior
{
public:
    Ninja(int hp, HeadQuarter &head)
        : Warrior(head.getWarriorNum(), hp)
    {
        // cout << "Ninja(int, HeadQuarter &)" << endl;
        _weapon1 = head.getWarriorNum() % 3;
        _weapon2 = (head.getWarriorNum() + 1) % 3;
        head.bornWarrior(hp);
        head.increaseNinja();
    }

    void display(HeadQuarter &head)
    {
#ifdef DEBUG
        cout << "ninja's num = " << getNum() << endl
             << "ninja's hp = " << getHp() << endl
             << "ninja's weapon1 = " << Weapon(_weapon1) << endl
             << "ninja's weapon2 = " << Weapon(_weapon2) << endl;
#endif
#if 1
        cout << "ninja " << getNum() << " born with strength "
             << getHp() << "," << head.getNinjaNum() << " ninja in "
             << Color(head.getColor()) << " headquarter" << endl
             << "It has a " << Weapon(_weapon1) << "and a " << Weapon(_weapon2) << endl;
#endif
    }

private:
    int _weapon1; //ninja have two weapons
    int _weapon2;
};

class Iceman
    : public Warrior
{
public:
    Iceman(int hp, HeadQuarter &head)
        : Warrior(head.getWarriorNum(), hp)
    {
        // cout << "Iceman(int, HeadQuarter &)" << endl;
        _weapon = head.getWarriorNum() % 3;
        head.bornWarrior(hp);
        head.increaseIceman();
    }

    void display(HeadQuarter &head)
    {
#ifdef DEBUG
        cout << "iceman's num = " << getNum() << endl
             << "iceman's hp = " << getHp() << endl
             << "iceman's weapon = " << Weapon(_weapon) << endl;
#endif
#if 1
        cout << "iceman " << getNum() << " born with strength "
             << getHp() << "," << head.getIcemanNum() << " iceman in "
             << Color(head.getColor()) << " headquarter" << endl
             << "It has a " << Weapon(_weapon) << endl;
#endif
    }

private:
    int _weapon;
};

class Lion
    : public Warrior
{
public:
    Lion(int hp, HeadQuarter &head)
        : Warrior(head.getWarriorNum(), hp)
    {
        // cout << "Lion(int, HeadQuarter &)" << endl;
        head.bornWarrior(hp);
        _loyalValue = head.getLifeElem();
        head.increaseLion();
    }

    void display(HeadQuarter &head)
    {
#ifdef DEBUG
        cout << "lion's num = " << getNum() << endl
             << "lion's hp = " << getHp() << endl
             << "lion's loyalValue = " << _loyalValue << endl;
#endif
#if 1
        cout << "lion " << getNum() << " born with strength "
             << getHp() << "," << head.getLionNum() << " lion in "
             << Color(head.getColor()) << " headquarter" << endl
             << "It's loyalty is " << _loyalValue << endl;
#endif
    }

private:
    int _loyalValue;
};

class Wolf
    : public Warrior
{
public:
    Wolf(int hp, HeadQuarter &head)
        : Warrior(head.getWarriorNum(), hp)
    {
        // cout << "Wolf(int, HeadQuarter &)" << endl;
        head.bornWarrior(hp);
        head.increaseWolf();
    }

    void display(HeadQuarter &head)
    {
#ifdef DEBUG
        cout << "wolf's num = " << getNum() << endl
             << "wolf's hp = " << getHp() << endl;
#endif
#if 1
        cout << "wolf " << getNum() << " born with strength "
             << getHp() << "," << head.getWolfNum() << " wolf in "
             << Color(head.getColor()) << " headquarter" << endl;
    }
#endif
};

int minHp(int hp1, int hp2, int hp3, int hp4, int hp5)
{
    return min(min(min(min(hp1, hp2), hp3), hp4), hp5);
}

int redTraining(int time, HeadQuarter &redHead, int dragonHp,
                int ninjaHp, int icemanHp, int lionHp, int wolfHp)
{
    static int redWarrior = 0; //每次只能造一个武士
    while (redHead.getLifeElem() >= (minHp(lionHp, wolfHp, ninjaHp, icemanHp, wolfHp)))
    {
        printf("%03d red ", time);
        //training sequence
        //iceman --> lion --> wolf --> ninja --> dragon
        if (redWarrior == 0 && redHead.getLifeElem() >= icemanHp)
        {
            Iceman iceman(icemanHp, redHead);
            iceman.display(redHead);
            ++redWarrior;
            return 1;
        }
        else if (redWarrior == 1 && redHead.getLifeElem() >= lionHp)
        {
            Lion lion(lionHp, redHead);
            // lion.display();
            lion.display(redHead);
            ++redWarrior;
            return 1;
        }
        else if (redWarrior == 2 && redHead.getLifeElem() >= wolfHp)
        {
            Wolf wolf(wolfHp, redHead);
            wolf.display(redHead);
            ++redWarrior;
            return 1;
        }
        else if (redWarrior == 3 && redHead.getLifeElem() >= ninjaHp)
        {
            Ninja ninja(ninjaHp, redHead);
            ninja.display(redHead);
            ++redWarrior;
            return 1;
        }
        else if (redWarrior == 4 && redHead.getLifeElem() >= wolfHp)
        {
            Dragon dragon(dragonHp, redHead);
            dragon.display(redHead);
            ++redWarrior;
            return 1;
        }
        if (redWarrior > 4)
        {
            redWarrior = 0;
        }
    }
    printf("%03d red headquarter stops making warriors\n", time);

    return 0;
}

int blueTraining(int time, HeadQuarter &blueHead, int dragonHp,
                 int ninjaHp, int icemanHp, int lionHp, int wolfHp)
{
    static int blueWarrior = 0;
    while (blueHead.getLifeElem() >= (minHp(lionHp, wolfHp, ninjaHp, icemanHp, wolfHp)))
    {
        //training sequence
        //lion --> dragon --> ninja --> iceman --> wolf
        printf("%03d blue ", time);
        if (blueWarrior == 0 && blueHead.getLifeElem() >= lionHp)
        {
            Lion lion(lionHp, blueHead);
            // lion.display();
            lion.display(blueHead);
            ++blueWarrior;
            return 1;
        }
        else if (blueWarrior == 1 && blueHead.getLifeElem() >= dragonHp)
        {
            Dragon dragon(dragonHp, blueHead);
            dragon.display(blueHead);
            ++blueWarrior;
            return 1;
        }
        else if (blueWarrior == 2 && blueHead.getLifeElem() >= ninjaHp)
        {
            Ninja ninja(ninjaHp, blueHead);
            ninja.display(blueHead);
            ++blueWarrior;
            return 1;
        }
        else if (blueWarrior == 3 && blueHead.getLifeElem() >= icemanHp)
        {
            Iceman iceman(icemanHp, blueHead);
            iceman.display(blueHead);
            ++blueWarrior;
            return 1;
        }
        else if (blueWarrior == 4 && blueHead.getLifeElem() >= wolfHp)
        {
            Wolf wolf(wolfHp, blueHead);
            wolf.display(blueHead);
            ++blueWarrior;
            return 1;
        }
        if (blueWarrior > 4)
        {
            blueWarrior = 0;
        }
    }
    printf("%03d blue headquarter stops making warriors\n", time);

    return 0;
}

int main()
{
    int lifeElem;
    int dragonHp, ninjaHp, icemanHp, lionHp, wolfHp;
    cin >> lifeElem;
    cin >> dragonHp >> ninjaHp >> icemanHp >> lionHp >> wolfHp;
    int ret1 = 1, ret2 = 1;
    int time = 0;
    HeadQuarter redHead(red, lifeElem);   //初始化主基地
    HeadQuarter blueHead(blue, lifeElem); //初始化主基地
    while (1)
    {
        if (ret1 == 1)
        {
            ret1 = redTraining(time, redHead, dragonHp, ninjaHp, icemanHp, lionHp, wolfHp);
        }
        if (ret2 == 1)
        {
            ret2 = blueTraining(time, blueHead, dragonHp, ninjaHp, icemanHp, lionHp, wolfHp);
        }
        if (!ret1 && !ret2)
        {
            break;
        }
        else
        {
            ++time;
        }
    }
    return 0;
}