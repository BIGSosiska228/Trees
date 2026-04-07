#include <iostream>
#include <list>
#include <windows.h>

using namespace std;

class MilitaryComponent
{
protected:
    MilitaryComponent* parent;

public:
    virtual ~MilitaryComponent() {}

    void SetParent(MilitaryComponent* parent)
    {
        this->parent = parent;
    }

    virtual void Add(MilitaryComponent* component) {}
    virtual void Remove(MilitaryComponent* component) {}

    virtual bool IsComposite()
    {
        return false;
    }

    virtual int CountCommand() = 0;
};

class Soldier : public MilitaryComponent
{
private:
    string name;

public:
    Soldier(string name)
    {
        this->name = name;
    }

    int CountCommand() override
    {
        return 1;
    }
};

class Unit : public MilitaryComponent
{
private:
    list<MilitaryComponent*> components;
    string unitName;

public:
    Unit(string name)
    {
        unitName = name;
    }

    ~Unit()
    {
        for (auto component : components)
        {
            delete component;
        }
    }

    void Add(MilitaryComponent* component) override
    {
        components.push_back(component);
        component->SetParent(this);
    }

    bool IsComposite() override
    {
        return true;
    }

    int CountCommand() override
    {
        int total = 0;

        for (auto component : components)
        {
            total += component->CountCommand();
        }

        return total;
    }

    string GetName()
    {
        return unitName;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    Unit* army = new Unit("Армия");


    Unit* squad1 = new Unit("Отделение 1");
    Unit* squad2 = new Unit("Отделение 2");


    squad1->Add(new Soldier("Иванов"));
    squad1->Add(new Soldier("Петров"));

    squad2->Add(new Soldier("Сидоров"));
    squad2->Add(new Soldier("Смирнов"));


    cout << squad1->GetName() << ": " << squad1->CountCommand() << " бойца" << endl;
    cout << squad2->GetName() << ": " << squad2->CountCommand() << " бойца" << endl;


    army->Add(squad1);
    army->Add(squad2);

    cout << "Вся армия: " << army->CountCommand() << " бойца" << endl;

    delete army;

    return 0;
}
