#include <iostream>
#include <list>
#include<windows.h>
#include <string>

using namespace std;

class TreesComponent
{
protected:
    TreesComponent* parent;

public:
    virtual ~TreesComponent() {}

    void SetParent(TreesComponent* parent)
    {
        this->parent = parent;
    }

    TreesComponent* GetParent()
    {
        return this->parent;
    }

    virtual void Add(TreesComponent* component) {}
    virtual void Remove(TreesComponent* component) {}

    virtual bool IsComposite()
    {
        return false;
    }

    virtual string GetName() = 0;
};

class Leaf : public TreesComponent
{
public:
    string GetName() override
    {
        return "Leaf";
    }
};

class Branch : public TreesComponent
{
protected:
    list<TreesComponent*> childrens;

public:
    void Add(TreesComponent* component) override
    {
        childrens.push_back(component);
        component->SetParent(this);
    }

    void Remove(TreesComponent* component) override
    {
        childrens.remove(component);
        component->SetParent(nullptr);
    }

    bool IsComposite() override
    {
        return true;
    }

    string GetName() override
    {
        string result;

        for (auto component : childrens)
        {
            result += component->GetName() + " ";
        }

        return "Branch: " + result;
    }
};

void ConnectedElements(TreesComponent* component1, TreesComponent* component2)
{
    if (component1->IsComposite())
    {
        component1->Add(component2);
    }

    cout << "Результат: " << component1->GetName() << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TreesComponent* leaf = new Leaf();
    TreesComponent* branch = new Branch();

    ConnectedElements(branch, leaf);

    delete leaf;
    delete branch;

    return 0;
}
    return 0;
}
