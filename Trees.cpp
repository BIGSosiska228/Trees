#include <iostream>
#include <list>
#include <windows.h>
#include <string>

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

    virtual string GetName() = 0;
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

    string GetName() override
    {
        return "Солдат: " + name;
    }
};

class Unit : public MilitaryComponent
{
protected:
    list<MilitaryComponent*> soldiers;
    string unitName;

public:
    Unit(string name)
    {
        unitName = name;
    }

    void Add(MilitaryComponent* component) override
    {
        soldiers.push_back(component);
        component->SetParent(this);
    }

    void Remove(MilitaryComponent* component) override
    {
        soldiers.remove(component);
        component->SetParent(nullptr);
    }

    bool IsComposite() override
    {
        return true;
    }

    string GetName() override
    {
        string result = unitName + ": ";

        for (auto component : soldiers)
        {
            result += component->GetName() + " | ";
        }

        return result;
    }
};

void ConnectedElements(MilitaryComponent* unit, MilitaryComponent* soldier)
{
    if (unit->IsComposite())
    {
        unit->Add(soldier);
    }

    cout << "Структура: " << unit->GetName() << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MilitaryComponent* soldier1 = new Soldier("Иванов");
    MilitaryComponent* soldier2 = new Soldier("Петров");

    MilitaryComponent* squad = new Unit("Отделение");

    ConnectedElements(squad, soldier1);
    ConnectedElements(squad, soldier2);

    delete soldier1;
    delete soldier2;
    delete squad;

    return 0;
}
