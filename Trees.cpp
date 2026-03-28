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

    MilitaryComponent* GetParent()
    {
        return this->parent;
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

    void Add(MilitaryComponent* component) override
    {
        components.push_back(component);
        component->SetParent(this);
    }

    void Remove(MilitaryComponent* component) override
    {
        components.remove(component);
        component->SetParent(nullptr);
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
};

void ConnectedElements(MilitaryComponent* unit, MilitaryComponent* soldier)
{
    if (unit->IsComposite())
    {
        unit->Add(soldier);
    }

    cout << "Командный состав армии: " << unit->CountCommand() << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MilitaryComponent* soldier1 = new Soldier("Иванов");
    MilitaryComponent* soldier2 = new Soldier("Петров");
    MilitaryComponent* soldier3 = new Soldier("Сидоров");

    MilitaryComponent* squad = new Unit("Отделение");

    ConnectedElements(squad, soldier1);
    ConnectedElements(squad, soldier2);
    ConnectedElements(squad, soldier3);

    delete soldier1;
    delete soldier2;
    delete soldier3;
    delete squad;

    return 0;
}
